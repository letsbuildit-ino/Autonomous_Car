import pygame
import requests
URL = "http://192.168.1.7"

def init():
    pygame.init()
    win = pygame.display.set_mode((150, 150))

def getKey(keyName):
    ans = False
    for eve in pygame.event.get(): pass
    keyInput = pygame.key.get_pressed()
    myKey = getattr(pygame, 'K_{}'.format(keyName))
    if keyInput[myKey]:
        ans = True
    pygame.display.update()
    return ans

def main():
    if getKey("w"):
        requests.get(URL + "/F")
        
    elif getKey("s"):
        requests.get(URL + "/B")
        
    elif getKey("a"):
        requests.get(URL + "/L")

    elif getKey("d"):
        requests.get(URL + "/R")

    elif getKey("q"):
        requests.get(URL + "/EL")

    elif getKey("e"):
        requests.get(URL + "/ER")

    elif getKey("x"):
        requests.get(URL + "/X")
        
    else:
        requests.get(URL + "/S")

if __name__ == '__main__':
    init()
    while True:
        main()
