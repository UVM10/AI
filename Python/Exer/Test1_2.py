lst_data = []
for i in range(1,13):
    if not(i&1): lst_data.append(i)
print(lst_data)
for i in lst_data: 
    if i%3 == 0: lst_data.remove(i)
print(lst_data)
lst_data += [1,2,3]
print(lst_data)
lst_data[3:3] = [6,7,8]
print(lst_data)
for i, k in enumerate(lst_data):
    if not(k&1) or (k%5 == 0): lst_data[i] = 0
print(lst_data)