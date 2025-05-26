def kiem_tra_day_so(num, lenght):
    for i in range(-1, -lenght -1, -1):
        count = [k for k, c in enumerate(num) if c == num[i]]
        if len(count) >= 2:
            return False
    else:
        return True
list1 = [1, 5, 7, 9]
list2 = [2, 4, 5, 5, 7, 9]
print(kiem_tra_day_so(list1,len(list1)))
print(kiem_tra_day_so(list2,len(list2)))