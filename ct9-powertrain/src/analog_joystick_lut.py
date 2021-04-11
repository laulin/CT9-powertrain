DEAD_ZONE = 15
FULL_RANGE = 1024
HALF_RANGE_VALUE = int(FULL_RANGE/2)
offset = HALF_RANGE_VALUE
alpha = (HALF_RANGE_VALUE+1)/(HALF_RANGE_VALUE - DEAD_ZONE)

first = [int(x*alpha) for x in range(HALF_RANGE_VALUE-DEAD_ZONE)]
middle = [HALF_RANGE_VALUE for x in range(2*DEAD_ZONE)]
last = [int(x*alpha + HALF_RANGE_VALUE) for x in range(HALF_RANGE_VALUE-DEAD_ZONE)]
values = list(map(str, first + middle + last))
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
print(len(values))
