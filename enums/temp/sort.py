import json
import re
from collections import defaultdict
from pathlib import Path

INPUT_FILE = "./newitems.json"
OUTPUT_DIR = Path("./categories")
FALLBACK = "uncategorized"  # used when Category or SubCategory is empty


def safe_filename(name):
    """Turn a category name into something safe to use as a file name."""
    cleaned = re.sub(r'[<>:"/\\|?*\s]+', "_", name).strip("._")
    return cleaned or FALLBACK


def main():
    with open(INPUT_FILE, "r", encoding="utf-8") as f:
        items = json.load(f)

    cats = ["tool","farming","gathering","refining","loot", "food", "none", "warrior", "mage", "hunter"]


    # categories[category][subcategory] -> list of items
    categories = defaultdict(lambda: defaultdict(list))
    for item in items:
        category = item.get("Category") or FALLBACK

        subcategory = item.get("SubCategory") or FALLBACK

        if category not in cats:
            print(category)
            print(subcategory)
            print(item.get("Name"))
            category = input("Category: ")
            subcategory = input("SubCategory: ")

        categories[category][subcategory].append(item)

    OUTPUT_DIR.mkdir(exist_ok=True)

    # Two categories could map to the same file name after cleaning,
    # so track used names and add a suffix if needed.
    used = set()
    for category, subcategories in sorted(categories.items()):
        filename = safe_filename(category)
        base, n = filename, 2
        while filename.lower() in used:
            filename = f"{base}_{n}"
            n += 1
        used.add(filename.lower())

        path = OUTPUT_DIR / f"{filename}.json"
        with open(path, "w", encoding="utf-8") as f:
            json.dump(subcategories, f, indent=2, ensure_ascii=False)

        count = sum(len(v) for v in subcategories.values())
        print(f"{path}: {count} items, {len(subcategories)} subcategories")


if __name__ == "__main__":
    main()