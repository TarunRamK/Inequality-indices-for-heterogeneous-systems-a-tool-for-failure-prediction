import csv
import os
import numpy

def k_index(trimmed_array):
    trimmed_array.sort()
    cu_array = [sum(trimmed_array[0:i+1]) for i in range(0, len(trimmed_array))]
    lor_array = [i/max(cu_array) for i in cu_array]
    delta = 1/len(lor_array)
    k=0
    index = 0
    while(k<=1):
        if (1-k) - lor_array[index] <= 0:
          #print(len(lor_array), "  ", k, "  ", index)
          return k
        k = k + delta
        index = index+1
        if k >= 1:
          print("Cound not find k index")
          break
          
dir_name = '0.4/Files/Time Rate Data/'
li = os.listdir(dir_name)
print(li)
output_file = open("k_results/s.3c1t.4.txt","a")

f_no=1  
for f_name in li:
    array1 = []
    
    file_name = dir_name + f_name
    with open(file_name) as file:
        reader = csv.reader(file, delimiter=' ')
        for row in reader:
            array1.append(int(row[1]))

    t_val = len(array1)
    k_list=[]
    k_val = k_index(array1)
    k_list.append(k_val)
    print(f_no)
    f_no = f_no + 1
    print(k_list[-1])
    output_file.write(str(t_val) +" "+ str(k_list[-1]) + "\n")
output_file.close()