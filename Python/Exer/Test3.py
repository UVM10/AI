#test1 = "(){}[]" -> True
#test2 = "(({} " -> False
#test3 = "()" -> True
#test4 = "((((}}}}" -> False
#test5 = "(({}{})){}}" -> False
#Cho một chuỗi S đại diện cho một biểu thức chứa các loại dấu ngoặc khác nhau: {}, () và [],
#nhiệm vụ là xác định xem các dấu ngoặc trong biểu thức có được cân bằng hay không.
#Một biểu thức cân bằng là một trong đó mọi khung mở đều có một khung đóng tương ứng theo đúng thứ tự.