import osmnx as ox
import pandas as pd

place = "Florence, Italy"

G = ox.graph_from_place(place, network_type="walk")

tags = {"tourism": True}
all_pois = ox.features_from_place(place, tags)

exclude = ["hotel", "hostel", "guest_house", "apartment"]
tourist_sights = all_pois[~all_pois["tourism"].isin(exclude)]

# reset index so we get 'id' column
tourist_sights = tourist_sights.reset_index()
tourist_sights["osmid"] = tourist_sights["id"]

# convert polygons to points
tourist_sights = tourist_sights.to_crs(epsg=3857)  # Web Mercator, meters
tourist_sights["geometry"] = tourist_sights.geometry.centroid

# Reproject back to lat/lon
tourist_sights = tourist_sights.to_crs(epsg=4326)

# filter out collumns
columns_to_keep = ["osmid", "geometry", "tourism"]
if "name" in tourist_sights.columns:
    columns_to_keep.append("name")
tourist_sights = tourist_sights[columns_to_keep]

#snap sights to nearest node
tourist_sights["nearest_node"] = tourist_sights.apply(
    lambda row: ox.distance.nearest_nodes(G, row.geometry.x, row.geometry.y),
    axis=1
)

sights_df = tourist_sights
sights_df['name'] = sights_df['name'].fillna("").astype(str)
sights_df['tourism'] = sights_df['tourism'].fillna("unknown").astype(str)

sights_df["lon"] = sights_df.geometry.x
sights_df["lat"] = sights_df.geometry.y

def make_display_name(row):
    if row['name'].strip():
        return row['name'].replace(",", "")
    else:
        return f"{row['tourism'].capitalize()} near ({row['lat']:.4f} {row['lon']:.4f})"

sights_df["display_name"] = sights_df.apply(make_display_name, axis=1)

sights_df[
    ["osmid", "display_name", "tourism", "lat", "lon", "nearest_node"]
    ].to_csv("data/tourist_sights.csv", index=False)

#save edges between nodes
edges = []

for u, v, data in G.edges(data=True):
    length = data.get("length", 1)  # fallback to 1 meter if missing
    edges.append([u, v, length])

edges_df = pd.DataFrame(edges, columns=["from", "to", "distance"])
edges_df.to_csv("data/graph_edges.csv", index=False)