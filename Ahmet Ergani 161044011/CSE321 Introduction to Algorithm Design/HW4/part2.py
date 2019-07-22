def fix_corrupt(text,dictionary):
    A = 0           #beginning of the word
    B = len(text)   #end of th word
    while 1:
        if B - A == 1:
            return False
        if dictionary.__contains__(text[A:B]):
            if dictionary[text[A:B]]:
                print(text[A:B])
                if B == len(text):
                    return True
                A = B
                B = len(text)
                continue
        B = B - 1

text = "itwasthebestoftimes"
dictionary = { 
        "it": True,
        "was": True,
        "the": True,
        "best": True,
        "of": True,
        "times": True,
        "heb": False
    }
fix_corrupt(text,dictionary)
