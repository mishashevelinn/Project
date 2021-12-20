import pandas as pd
import matplotlib.pyplot as plt

path = "cmake-build-debug/res2.txt"
pd.set_option('max_columns', None)


def get_data(path):
    df = pd.read_csv("data/res2.txt", sep=" ")
    return df


df = get_data(path)
fig, ax = plt.subplots(2, 5)
for i in range(2):
    k = 0
    for j in range(0, int(df.shape[0] / 2), 9):
        print(df.iloc[j: j + 9])
        ax[i][k].stem(df.iloc[j: j + 9]['g'], df.iloc[j: j + 9]['P(failure)'])
        ax[i][k].set_title(f'g = {k + 5 * i + 5}')
        ax[i][k].set_xlabel("n")
        ax[i][k].set_ylabel("P(success)")
        k += 1
# plt.style.use('dark_background')
fig.tight_layout()
plt.show()

plt.show()
