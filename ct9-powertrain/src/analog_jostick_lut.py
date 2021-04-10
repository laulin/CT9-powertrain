DEAD_ZONE = 25
HALF_RANGE_VALUE = int(1024/2)
offset = HALF_RANGE_VALUE
alpha = (-HALF_RANGE_VALUE-DEAD_ZONE)/HALF_RANGE_VALUE

first = [max(0, int(x*alpha + offset)) for x in range(HALF_RANGE_VALUE)]
values = list(map(str, first + first[::-1]))
tmp = list()
for i,v in enumerate(values):
    tmp.append(v)
    if i%16 == 0 and i != 0:
        tmp.append(",\n")
    else:
        if i != len(values)-1:
            tmp.append(", ")
str_values = "".join(tmp)
print(f"const PROGMEM uint16_t JOYSTICK_LUT[1024] = {{ {str_values} }};")
