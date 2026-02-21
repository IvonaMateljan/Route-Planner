import osmnx as ox
import pandas as pd
import folium

G = ox.graph_from_place("Florence, Italy", network_type="walk")

route_df = pd.read_csv("data/route.csv")
route_nodes = route_df["osmId"].tolist()
route_nodes = [n for n in route_nodes if n in G.nodes]
route_coords = [(G.nodes[n]["y"], G.nodes[n]["x"]) for n in route_nodes]

sights_df = pd.read_csv("data/selected_sights.csv")

m = folium.Map(location=route_coords[0], zoom_start=15)

folium.PolyLine(route_coords, color="red", weight=5, opacity=0.8).add_to(m)

for _, row in sights_df.iterrows():
    lat, lon = row["lat"], row["lon"]
    name = row.get("display_name", row.get("name", "Unknown"))
    folium.Marker(
        [lat, lon],
        popup=name,
        icon=folium.Icon(color="blue", icon="info-sign")
    ).add_to(m)

m.save("route_with_sights.html")
print("Saved interactive map with sights to route_with_sights.html")