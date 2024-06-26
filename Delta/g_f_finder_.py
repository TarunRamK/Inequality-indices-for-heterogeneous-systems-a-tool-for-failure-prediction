import csv
import os

def gini_index(trimmed_array):
    trimmed_array.sort()
    cu_array = [sum(trimmed_array[0:i+1]) for i in range(0, len(trimmed_array))]
    max_val = max(cu_array)
    lor_array = [i/max_val for i in cu_array]
    area = 0
    dt = 1/(len(lor_array)+1)
    for i in lor_array:
        area = area + (i*dt)
    tot_area = 0.5
    g_ind = (tot_area - area)/ tot_area
    return g_ind

dir_name = '0.4/Files/Time Rate Data/'
li = os.listdir(dir_name)
print(li)
output_file = open("g_results/s.5c1t.4.txt","a")

out_li = []
f_no=1
for f_name in li:
    array1 = []
    file_name = dir_name + f_name
    with open(file_name) as file:
        reader = csv.reader(file, delimiter=' ')
        for row in reader:
            array1.append(int(row[1]))

    g_list=[]
    t_list=[]
    g_val = gini_index(array1)
    g_list.append(g_val)
    time = len(array1)
    t_list.append(time)
    print(f_no)
    f_no = f_no + 1
    print(g_list[-1])
    output_file.write(str(t_list[-1]) +" "+ str(g_list[-1]) + "\n")
    out_li.append(g_list[-1])
print(out_li)

output_file.close()
