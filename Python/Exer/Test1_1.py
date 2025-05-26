food_list = [
    ["Bơ", "Pizza", "Sữa"],
    ["Xúc xích", "Táo", "Kem"],
    ["Cà rốt", "Bánh dâu", "Cupcake"]
]

search_item = ["Cà rốt", "Táo", "Sữa"]

for i in range(3):
    for k in range(3):
        if search_item[k] in food_list[i]:
             print(f"Vị trí của {search_item[k]} là: hàng {i+1}, cột {food_list[i].index(search_item[k])+1}\n")