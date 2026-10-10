import matplotlib.pyplot as plt
import pandas as pd

df = pd.read_csv("results.csv").sort_values(by="x").reset_index(drop=True)
df.columns = ["x", "h", "f_x"]

fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(10, 8), sharex=True)

ax1.plot(df["x"], df["f_x"], color="blue", label="f(x)", zorder=1)
ax1.scatter(df["x"], df["f_x"], color="crimson", s=20, label="points", zorder=2)
ax1.set_title("Function with adaptive integration grid")
ax1.set_ylabel("f(x)")
ax1.grid(True, linestyle="--")
ax1.legend()

ax2.plot(df["x"], df["h"], "o-", color="purple", ms=4)
ax2.set_title("Step size distribution")
ax2.set_xlabel("X")
ax2.set_ylabel("Step size (h)")
ax2.grid(True, linestyle="--")

plt.tight_layout()
plt.savefig("result.png")
plt.show()