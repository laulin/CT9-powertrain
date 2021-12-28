def transform(forward:bool, reverse:bool, left:bool, right:bool):
    if left and right:
        raise Exception("Left and right conflict")

    if forward and reverse:
        raise Exception("forward and reverse conflict")

    if forward:
        if not right and not left:
            return 1, 1
        elif left:
            return 0,1
        elif right:
            return 1,0 
    elif reverse:
        if not right and not left:
            return -1, -1
        elif left:
            return 0,-1
        elif right:
            return -1,0 
    else:
        return 0,0