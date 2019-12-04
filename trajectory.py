#! /usr/bin/python3.6

import matplotlib.pyplot as plt 
import numpy as np
import os
import sys

if 'momo' in plt.style.available:
    plt.style.use('momo')

data = np.loadtxt('cmake-build-debug/m2_{}.dat'.format(int(sys.argv[1])))

time = data[:, 0]
x1 = data[:, 1]
x2 = data[:, 2]

# create a new figure
fig, ax = plt.subplots(figsize=(3.375, 2.86))

ax.plot(
    time,
    x1,
    label=r'$m_1 = 1$'
)

ax.plot(
    time,
    x2,
    label=r'$m_2 = {}$'.format(int(sys.argv[1]))
)

ax.legend()

ax.set_ylabel(r'Position')
ax.set_xlabel(r'Time')

# ax.set_xlim(min(date)-10, max(date)+10)
# ax.set_ylim(.385, .505)

fig.savefig('m2_{}.pdf'.format(int(sys.argv[1])))


