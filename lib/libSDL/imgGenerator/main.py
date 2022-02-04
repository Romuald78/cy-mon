#!/usr/bin/python3
import math

from PIL import Image

#COLS = 67 * 2
#ROWS = 18 * 2
#im1 = Image.open("Pyrogen.png")
#w,h = im1.size
#ratio = max(w/COLS, h/ROWS)
#im1 = im1.resize( (int(w/ratio),int(h/ratio)) )
#im1.save("Pyrogen_small.png")
#im1.close()


from PIL import Image, ImageDraw, ImageFont, ImageFilter

def getUnicodeList():
    myList = [
        ("blank", 0),

        # Trees
        ("tree1"    , 0x1F332),
        ("tree2"    , 0x1F333),
        ("tree3"    , 0x1F384),
        ("palmtree" , 0x1F334),
        ("cactus"   , 0x1F335),
        # Nature
        ("rock", 0x1FAA8),
        ("clover"   , 0x1F340),
        ("mushroom" , 0x1F344),
        # Flowers
        ("flower1"  , 0x1F337),
        ("flower2"  , 0x1F338),
        ("flower3"  , 0x1F339),
        ("flower4"  , 0x1F33A),
        ("flower5"  , 0x1F33B),
        ("flower6"  , 0x1F33C),
        ("flower7"  , 0x1F4AE),
        # Food
        ("burger"   , 0x1F354),
        ("fries"    , 0x1F35F),
        ("bread"    , 0x1F35E),
        ("sushi"    , 0x1F363),
        ("shrimp"   , 0x1F364),
        ("ice1"     , 0x1F366),
        ("ice2"     , 0x1F367),
        ("ice3"     , 0x1F368),
        ("doughnut" , 0x1F369),
        ("cookie"   , 0x1F36A),
        ("chocolate", 0x1F36B),
        ("candy"    , 0x1F36C),
        ("lollipop" , 0x1F36D),
        # Drinks
        ("drink1"   , 0x1F376),
        ("drink2"   , 0x1F377),
        ("drink3"   , 0x1F378),
        ("drink4"   , 0x1F379),
        ("drink5"   , 0x1F37A),
        ("drink6"   , 0x1F37B),
        # Valuables
        ("crown"    , 0x1F451),
        ("ring"     , 0x1F48D),
        ("gem"      , 0x1F48E),
        ("moneybag" , 0x1F4B0),
        ("card"     , 0x1F4B3),
        ("money"    , 0x1F4B5),
        # Misc. Items
        ("glasses"  , 0x1F453),
        ("purse"    , 0x1F45B),
        ("handbag"  , 0x1F45C),
        ("pouch"    , 0x1F45D),
        ("present"  , 0x1F381),
        ("balloon"  , 0x1F388),
        ("ticket"   , 0x1F3AB),
        ("dice"     , 0x1F3B2),
        ("pill"     , 0x1F48A),
        ("letter1"  , 0x1F48C),
        ("letter2"  , 0x1F4E8),
        ("bomb"     , 0x1F4A3),
        ("briefcase", 0x1F4BC),
        ("disc1"    , 0x1F4BF),
        ("disc2"    , 0x1F4C0),
        ("page1"    , 0x1F4C3),
        ("page2"    , 0x1F4C4),
        ("calendar1", 0x1F4C5),
        ("calendar2", 0x1F4C6),
        ("pin1"     , 0x1F4CC),
        ("pin2"     , 0x1F4CD),
        ("paperclip", 0x1F4CE),
        ("ruler1"   , 0x1F4CF),
        ("ruler2"   , 0x1F4D0),
        ("scroll"   , 0x1F4DC),
        ("pager"    , 0x1F4DF),
        ("antenna"  , 0x1F4E1),
        ("package"  , 0x1F4E6),
        ("magnify"  , 0x1F50D),
        ("bell"     , 0x1F514),
        ("crystal"  , 0x1F52E),
        ("warning"  , 0x026A0),

        # Electronics
        ("mobile"   , 0x1F4F1),
        ("phone"    , 0x0260E),
        ("camera"   , 0x1F4F7),
        ("tv"       , 0x1F4FA),
        ("radio"    , 0x1F4FB),
        ("computer" , 0x1F4BB),
        ("light1"   , 0x1F4A1),
        ("light2"   , 0x1F526),

        # Tools
        ("key"      , 0x1F511),
        ("lock1"    , 0x1F512),
        ("lock2"    , 0x1F513),
        ("wrench"   , 0x1F527),
        ("hammer"   , 0x1F528),
        ("nutbolt"  , 0x1F529),

        # Effects
        ("music1"   , 0x1F3B5),
        ("music2"   , 0x1F3B6),
        ("prints"   , 0x1F43E),
        ("sleep"    , 0x1F4A4),
        ("explode"  , 0x1F4A5),
        ("splash"   , 0x1F4A6),
        ("dash"     , 0x1F4A8),
        ("dizzy"    , 0x1F4AB),
        ("anger"    , 0x1F4A2),
        ("speech"   , 0x1F4AC),
        ("fire"     , 0x1F525),
        ("bolt"     , 0x026A1),

        # Music Instruments
        ("saxophone", 0x1F3B7),
        ("guitar"   , 0x1F3B8),
        ("keyboard" , 0x1F3B9),
        ("trumpet"  , 0x1F3BA),
        ("violin"   , 0x1F3BB),

        # Flags
        ("checkflag", 0x1F3C1),

        # Earth Animals
        ("scapegoat", 0x1F40C),
        ("snake"    , 0x1F40D),
        ("sheep"    , 0x1F411),
        ("elephant" , 0x1F418),
        ("turtle"   , 0x1F422),
        # Air animals
        ("chick1"   , 0x1F423),
        ("chick2"   , 0x1F424),
        ("chick3"   , 0x1F425),
        ("bird"     , 0x1F426),
        ("penguin"  , 0x1F427),
        # Water Animals
        ("octopus"  , 0x1F419),
        ("fish1"    , 0x1F41F),
        ("fish2"    , 0x1F420),
        ("fish3"    , 0x1F421),
        ("dolphin"  , 0x1F42C),
        ("whale"    , 0x1F433),
        # Insects
        ("ant"      , 0x1F41C),
        ("bee"      , 0x1F41D),
        ("ladybug"  , 0x1F41E),
        # Monsters
        ("ghost"    , 0x1F47B),
        ("alien"    , 0x1F47D),
        ("imp"      , 0x1F47F),
    ]
    # Add clock emojis
    for i in range(24):
        n = "0"+str(i) if i<10 else str(i)
        myList.append( (f"clock{n}", 0x1F550+i) )
    # return full list
    return myList


# X*Y >= nbItems
# Y/X = 16/9
# Y = 16.X/9
# 16X²/9 >= N
# X >= sqrt(9*N/16)
def createAtlas(font, out_name, strList):
    N = len(strList)
    NBY = int(math.sqrt(9*N/16))
    NBX = int((NBY*16/9))
    while N > NBX*NBY:
        NBX += 1
    print(N,NBX,NBY)
    SIZE = 80
    # sort list
    strList = sorted(strList, key=lambda x:x[1])
    # Load font
    fnt = ImageFont.truetype(font, size=109, layout_engine=ImageFont.LAYOUT_RAQM)
    # Create image according to emoji list
    im   = Image.new("RGBA", (NBX*SIZE,NBY*SIZE), (0,0,0,0))
    # For each item draw emoji
    x = 0
    y = 0
    for entry in strList:
        name = entry[0]
        ucode= entry[1]
        im1 = Image.new("RGBA", (128,128), (0,0,0,0))
        dr1 = ImageDraw.Draw(im1)
        dr1.text( (0,0), chr(ucode), fill=(0,0,0,255), embedded_color=True, font=fnt)
        im1 = im1.resize((SIZE,SIZE),resample=Image.ANTIALIAS)
        im.paste(im1,(x*SIZE,y*SIZE))
        x += 1
        if x >= NBX:
            x  = 0
            y += 1

    im.show()
    im.save(f"testemoji_{out_name}.png")




createAtlas(r"../GameRGR/fonts/NotoColorEmoji.ttf", "noto", getUnicodeList())
