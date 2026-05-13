import csv
from datetime import datetime
from pathlib import Path

import matplotlib.pyplot as plt

csv_path = Path("data/histogram.csv")

centers = []
widths = []
counts = []

with csv_path.open(newline="", encoding="utf-8") as f:
    reader = csv.DictReader(f)
    for row in reader:
        left = float(row["left"])
        right = float(row["right"])
        centers.append((left + right) / 2.0)
        widths.append(right - left)
        counts.append(int(row["count"]))

plt.bar(centers, counts, width=widths, align="center", edgecolor="black")
plt.xlabel("susceptible humans")
plt.ylabel("number of simulations")
plt.tight_layout()

timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
output_path = Path("data") / f"histogram_{timestamp}.png"
plt.savefig(output_path, dpi=150)
