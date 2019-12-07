#! /usr/bin/python3.6

if __name__ == '__main__':
    import pandas as pd 
    import matplotlib.pyplot as plt 
    import numpy as np
    import os
    import sys

    if 'momo' in plt.style.available:
        plt.style.use('momo')

    file_list = [i for i in os.listdir('./data/') if i.startswith('m2_')]

    for file in file_list:

        df = pd.read_csv('data/' + file, index_col=0)
        mass_ratio = int(file[3:-4])

        # create a new figure
        fig, ax = plt.subplots(figsize=(3.375, 2.086))

        ax.plot(
            df.index,
            df.x_1,
            label=r'$m_1 = 1$'
        )

        ax.plot(
            df.index,
            df.x_2,
            label=r'$m_2 = {}$'.format(mass_ratio)
        )

        ax.legend()

        ax.set_ylabel(r'Position')
        ax.set_xlabel(r'Time')

        # ax.set_xlim(min(date)-10, max(date)+10)
        # ax.set_ylim(.385, .505)

        fig.tight_layout(pad=.1)
        fig.savefig('graphics/m2_{}.png'.format(mass_ratio))
