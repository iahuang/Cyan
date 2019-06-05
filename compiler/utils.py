"""
Utility module for Cyan

"""

def removeall(lst, val):
    """ Remove all instances of an item from a list """
    new = []
    for i in lst:
        if i != val:
            new.append(i)

    return new
