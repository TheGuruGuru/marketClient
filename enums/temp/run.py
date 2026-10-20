import json
from ctypes import cast
from unittest import case


def get_tier(unique_name):
    # e.g. "T4_BAG@1" -> "4.1", "T4_BAG" -> "4.0"
    if len(unique_name) > 1 and unique_name[1].isdigit():
        enchant = unique_name.rsplit("@", 1)[1] if "@" in unique_name else "0"
        return f"{unique_name[1]}.{enchant}"
    return ""

def make():
    with open("./items.json", "r", encoding="utf-8") as f:
        items = json.load(f)

    new_items = []
    for item in items:
        unique_name = item.get("UniqueName") or ""
        tier = get_tier(unique_name)
        print(item.get("name") + tier)

        new_items.append({
            "UniqueName": unique_name,
            "Name": item.get("name") or "",
            "Tier": tier,
            "Category": item.get("category") or input("category: "),
            "SubCategory": item.get("subcategory") or input("subcategory: "),
            "nutritionNeeded": 0,
            "nutrition": 0,
            "Recipe": [
                {"UniqueName": "", "Amount": 0}
            ],
        })

    with open("./newitems.json", "w", encoding="utf-8") as f:
        json.dump(new_items, f, indent=2, ensure_ascii=False)

def sort():
    return

if __name__ == "__main__":
    getsubcats()