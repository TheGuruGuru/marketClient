import json

def main():
    with open("./items.json", "r", encoding="utf-8") as f:
        items = json.load(f)

    new_items = {}
    for item in items:
        unique_name = item.get("UniqueName") or ""
        if not unique_name:
            continue

        new_items.update({unique_name: 0})


    with open("../../data/prices/bridgewatch.json", "w", encoding="utf-8") as f:
        json.dump(new_items, f, indent=2, ensure_ascii=False)
    with open("../../data/prices/fortsterling.json", "w", encoding="utf-8") as f:
        json.dump(new_items, f, indent=2, ensure_ascii=False)
    with open("../../data/prices/martlock.json", "w", encoding="utf-8") as f:
        json.dump(new_items, f, indent=2, ensure_ascii=False)
    with open("../../data/prices/lymhurst.json", "w", encoding="utf-8") as f:
        json.dump(new_items, f, indent=2, ensure_ascii=False)
    with open("../../data/prices/thetfort.json", "w", encoding="utf-8") as f:
        json.dump(new_items, f, indent=2, ensure_ascii=False)
    with open("../../data/prices/caerleon.json", "w", encoding="utf-8") as f:
        json.dump(new_items, f, indent=2, ensure_ascii=False)
    with open("../../data/prices/blackMarket.json", "w", encoding="utf-8") as f:
        json.dump(new_items, f, indent=2, ensure_ascii=False)

if __name__ == "__main__":
    main()