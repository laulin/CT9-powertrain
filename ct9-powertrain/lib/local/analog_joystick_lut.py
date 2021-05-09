def create_values():
    values = list()
    for i in range(1024):
        tmp = i - 512

        if tmp <= 0:
            value = int((tmp * tmp / 512) * - 64)
            values.append(str(value))
        else:
            value = int((tmp * tmp / 511 + 1) * 64)
            values.append(str(value))
    return values

values = create_values()
tmp = list()
for i,v in enumerate(values):
    tmp.append(v)
    if i%16 == 0 and i != 0:
        tmp.append(",\n")
    else:
        if i != len(values)-1:
            tmp.append(", ")
str_values = "".join(tmp)
print(f"const PROGMEM int16_t JOYSTICK_LUT[1024] = {{ {str_values} }};")
print(len(values))
