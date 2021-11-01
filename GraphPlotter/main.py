import sys
import math

import matplotlib.pyplot as plt
import csv


def decomment(csv_file):
	for row in csv_file:
		raw = row.split('#')[0].strip()
		if raw:
			yield raw


def show_plot():
	millis = []
	micros = []
	time = []
	accel_x = []
	accel_y = []
	accel_z = []
	accel_max = -math.inf
	accel_min = math.inf
	accel_x_delta = []
	accel_y_delta = []
	accel_z_delta = []
	rot_x = []
	rot_y = []
	rot_z = []
	rot_max = -math.inf
	rot_min = math.inf
	rot_x_delta = []
	rot_y_delta = []
	rot_z_delta = []
	absolute_accel_sum = []
	absolute_accel_delta_sum = []
	absolute_rot_delta_sum = []

	with open('3DPrinter1-BallBearing-stealthchop.csv', 'r') as csv_file:
		reader = csv.reader(decomment(csv_file), delimiter=' ')
		for row in reader:
			row_millis = int(row[0])
			millis.append(row_millis)
			row_micros = int(row[1])
			micros.append(row_micros)
			row_time = int(row_millis * 1000 + row_micros % 1000)
			time.append(row_time)
			row_accel_x = int(row[2])
			accel_x.append(row_accel_x)
			row_accel_y = int(row[3])
			accel_y.append(row_accel_y)
			row_accel_z = int(row[4])
			accel_z.append(row_accel_z)
			row_rot_x = int(row[5])
			rot_x.append(row_rot_x)
			row_rot_y = int(row[6])
			rot_y.append(row_rot_y)
			row_rot_z = int(row[7])
			rot_z.append(row_rot_z)

			accel_max = max([row_accel_x, row_accel_y, row_accel_z, accel_max])
			accel_min = min([row_accel_x, row_accel_y, row_accel_z, accel_min])
			rot_max = max([row_rot_x, row_rot_y, row_rot_z, rot_max])
			rot_min = min([row_rot_x, row_rot_y, row_rot_z, rot_min])

	print("accel_min: ", accel_min)
	print("accel_max: ", accel_max)
	print("rot_min: ", rot_min)
	print("rot_max: ", rot_max)
	accel_range = 2*max(abs(accel_min), abs(accel_max))
	rot_range = 2*max(abs(rot_min), abs(rot_max))

	if len(millis) > 0:
		accel_x_delta.append(0)
		rot_x_delta.append(0)
		accel_y_delta.append(0)
		rot_y_delta.append(0)
		accel_z_delta.append(0)
		rot_z_delta.append(0)
		absolute_accel_delta_sum.append(0)
		absolute_accel_sum.append(0)
		absolute_rot_delta_sum.append(0)
	for i in range(1, len(millis)):
		accel_x_delta.append(accel_x[i] - accel_x[i-1])
		accel_y_delta.append(accel_y[i] - accel_y[i - 1])
		accel_z_delta.append(accel_z[i] - accel_z[i - 1])
		rot_x_delta.append(rot_x[i] - rot_x[i - 1])
		rot_y_delta.append(rot_y[i] - rot_y[i - 1])
		rot_z_delta.append(rot_z[i] - rot_z[i - 1])
		absolute_accel_delta_sum.append((abs(accel_x_delta[i]) + abs(accel_y_delta[i]) + abs(accel_z_delta[i])) / 3)
		absolute_accel_sum.append((abs(accel_x[i]) + abs(accel_y[i]) + abs(accel_z[i])) / 3)
		absolute_rot_delta_sum.append((abs(rot_x_delta[i]) + abs(rot_y_delta[i]) + abs(rot_z_delta[i])) / 3)

	plt.plot(time, absolute_accel_sum)
	plt.xlabel('Time')
	plt.ylabel('Value')
	plt.title("A simple line graph")
	plt.show()


# Press the green button in the gutter to run the script.
if __name__ == '__main__':
	show_plot()

# See PyCharm help at https://www.jetbrains.com/help/pycharm/
