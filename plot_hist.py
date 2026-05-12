import matplotlib.pyplot as plt
import pandas as pd

df = pd.read_csv("data/histogram.csv")
centers = (df["left"] + df["right"]) / 2
widths = df["right"] - df["left"]

plt.bar(centers, df["count"], width=widths, align="center", edgecolor="black")
plt.xlabel("X[0]")
plt.ylabel("Count")
plt.tight_layout()
plt.show()
