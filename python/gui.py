import tkinter as tk
from tkinter import ttk
import pandas as pd

# Load and clean data
sights_df = pd.read_csv("data/tourist_sights.csv")

sights_df['display_name'] = sights_df['display_name'].fillna("").astype(str)
sights_df['tourism'] = sights_df['tourism'].fillna("").astype(str)

sights_df = sights_df[sights_df['tourism'] != ""]

# Build category dictionary
categories = sorted(sights_df['tourism'].unique().tolist())

sights_by_category = {
    cat: sights_df[sights_df['tourism'] == cat][['display_name', 'osmid']].values.tolist()
    for cat in categories
}

selected_global = set()

current_category = categories[0]

# Tkinter setup
root = tk.Tk()
root.title("Select Tourist Sights")

selected_category = tk.StringVar(value=current_category)
search_var = tk.StringVar()

# Listbox
listbox = tk.Listbox(root, selectmode=tk.MULTIPLE, width=60, height=20)
listbox.pack(pady=5)

def update_listbox(*args):
    global current_category

    current_category = selected_category.get()
    items = sights_by_category[current_category]

    term = search_var.get().lower()

    filtered = [
        item for item in items
        if term in item[0].lower()
    ]

    listbox.delete(0, tk.END)

    for display_name, osmid in filtered:
        listbox.insert(tk.END, display_name)

    # Reselect already selected items
    for i, (display_name, osmid) in enumerate(filtered):
        if (display_name, osmid) in selected_global:
            listbox.selection_set(i)


def on_listbox_select(event):
    global selected_global

    items = sights_by_category[current_category]
    term = search_var.get().lower()

    filtered = [
        item for item in items
        if term in item[0].lower()
    ]

    selected_indices = listbox.curselection()

    currently_selected = {
        tuple(filtered[i]) for i in selected_indices
    }

    # Remove all items from this category
    selected_global -= {tuple(item) for item in items}

    # Add currently selected ones
    selected_global |= currently_selected


def submit():
    print("\nSelected sights:\n")

    for display_name, osmid in selected_global:
        print(f"{display_name} (OSM ID: {osmid})")

    # Export selected rows
    selected_osm_ids = [osmid for _, osmid in selected_global]

    export_df = sights_df[sights_df['osmid'].isin(selected_osm_ids)]
    export_df.to_csv("data/selected_sights.csv", index=False)

    print("\nExported selected_sights.csv")

    root.destroy()



category_menu = ttk.Combobox(
    root,
    textvariable=selected_category,
    values=categories,
    state="readonly"
)
category_menu.pack(pady=5)
category_menu.bind("<<ComboboxSelected>>", update_listbox)

search_entry = tk.Entry(root, textvariable=search_var, width=60)
search_entry.pack(pady=5)
search_var.trace_add("write", update_listbox)

listbox.bind("<<ListboxSelect>>", on_listbox_select)

submit_btn = tk.Button(root, text="OK", command=submit)
submit_btn.pack(pady=10)

# Initial populate
update_listbox()

root.mainloop()