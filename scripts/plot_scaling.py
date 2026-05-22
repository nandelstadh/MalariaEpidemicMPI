#!/usr/bin/env python3

from pathlib import Path

import matplotlib

matplotlib.use("Agg")
import matplotlib.pyplot as plt


def read_scaling_csv(path: Path):
    lines = [line.strip() for line in path.read_text(encoding="utf-8").splitlines() if line.strip()]
    header = lines[0].split()
    idx_t = header.index("tmax")
    idx_n = header.index("n")
    idx_p = header.index("p")

    rows = []
    for line in lines[1:]:
        cols = line.split()
        rows.append(
            {
                "tmax": float(cols[idx_t]),
                "n": float(cols[idx_n]),
                "p": float(cols[idx_p]),
            }
        )

    rows.sort(key=lambda row: row["p"])
    return rows


def ideal_runtime(rows):
    t0 = rows[0]["tmax"]
    n0 = rows[0]["n"]
    p0 = rows[0]["p"]
    baseline_work_per_process = n0 / p0

    return [t0 * ((row["n"] / row["p"]) / baseline_work_per_process) for row in rows]


def plot_strong_speedup(rows, output_path: Path):
    p = [row["p"] for row in rows]
    t = [row["tmax"] for row in rows]
    t0 = t[0]
    p0 = p[0]
    measured_speedup = [t0 / time for time in t]
    ideal_speedup = [proc / p0 for proc in p]

    fig, ax = plt.subplots(figsize=(8, 5))
    ax.plot(p, measured_speedup, "o-", label="measured speedup")
    ax.plot(p, ideal_speedup, "--", label="ideal")
    ax.set_title("Strong scaling")
    ax.set_xlabel("number of processes (p)")
    ax.set_ylabel("speedup")
    ax.grid(True, alpha=0.3)
    ax.legend()
    fig.tight_layout()
    fig.savefig(output_path, dpi=200)
    plt.close(fig)


def plot_weak_runtime(rows, output_path: Path):
    p = [row["p"] for row in rows]
    t = [row["tmax"] for row in rows]
    t0 = t[0]
    ideal = [t0 for _ in rows]

    fig, ax = plt.subplots(figsize=(8, 5))
    ax.plot(p, t, "o-", label="measured time")
    ax.plot(p, ideal, "--", label="ideal")
    ax.set_title("Weak scaling")
    ax.set_xlabel("number of processes (p)")
    ax.set_ylabel("time (s)")
    ax.set_ylim(max(0.0, t0 - 20.0), t0 + 20.0)
    ax.grid(True, alpha=0.3)
    ax.legend()
    fig.tight_layout()
    fig.savefig(output_path, dpi=200)
    plt.close(fig)


def main():
    root = Path(__file__).resolve().parents[1]
    csv_dir = root / "final_results" / "final_csv"
    out_dir = root / "final_results" / "final_plots"
    out_dir.mkdir(parents=True, exist_ok=True)

    strong_rows = read_scaling_csv(csv_dir / "strong_scale.csv")
    weak_rows = read_scaling_csv(csv_dir / "weak_scale.csv")

    plot_strong_speedup(strong_rows, out_dir / "strong_scaling.png")
    plot_weak_runtime(weak_rows, out_dir / "weak_scaling.png")


if __name__ == "__main__":
    main()
