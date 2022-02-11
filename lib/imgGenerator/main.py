#!/usr/bin/python3
import math
import shutil

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

def getOthers():
    myList = [
        ("bar_H"    , 0x02501),
        ("bar_V"    , 0x02503),
        ("corner_TL", 0x0250F),
        ("corner_TR", 0x02513),
        ("corner_BL", 0x02517),
        ("corner_BR", 0x0251B),
        ("tee_L"    , 0x02523),
        ("tee_R"    , 0x0252B),
        ("tee_T"    , 0x02533),
        ("tee_B"    , 0x0253B),
    ]
    return myList

def getEmoji():
    myList = [
        ("blank", 0),

        # Trees
        ("tree1"    , 0x1F332),
        ("tree2"    , 0x1F333),
        ("tree3"    , 0x1F384),
        ("palmtree" , 0x1F334),
        ("cactus"   , 0x1F335),

        # Nature
        ("rock"     , 0x1FAA8),
        ("clover"   , 0x1F340),
        ("mushroom" , 0x1F344),

        # Big Objects
        ("barrier"  , 0x1F6A7),
        ("grave"    , 0x1FAA6),
        ("post"     , 0x1FAA7),

        # Flowers
        ("flower1"  , 0x1F337),
        ("flower2"  , 0x1F338),
        ("flower3"  , 0x1F339),
        ("flower4"  , 0x1F33A),
        ("flower5"  , 0x1F33B),
        ("flower6"  , 0x1F33C),
        ("flower7"  , 0x1F4AE),
        ("flower8"  , 0x1FAB4),

        # Food
        ("burger"   , 0x1F354),
        ("fries"    , 0x1F35F),
        ("bread1"   , 0x1F35E),
        ("bread2"   , 0x1F956),
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
        ("potato"   , 0x1F954),
        ("carrot"   , 0x1F955),
        ("egg"      , 0x1F95A),
        ("peanut"   , 0x1F95C),
        ("kiwi"     , 0x1F95D),
        ("coconut"  , 0x1F965),
        ("broccoli" , 0x1F966),
        ("pie"      , 0x1F967),
        ("pretzel"  , 0x1F968),
        ("meat"     , 0x1F969),
        ("sandwich" , 0x1F96A),
        ("can"      , 0x1F96B),
        ("leafy"    , 0x1F96C),
        ("mango"    , 0x1F96D),
        ("cake"     , 0x1F96E),
        ("bagel"    , 0x1F96F),
        ("cheese"   , 0x1F9C0),
        ("apple1"   , 0x1F34E),
        ("apple2"   , 0x1F34F),

        # Drinks
        ("drink1"   , 0x1F376),
        ("drink2"   , 0x1F377),
        ("drink3"   , 0x1F378),
        ("drink4"   , 0x1F379),
        ("drink5"   , 0x1F37A),
        ("drink6"   , 0x1F37B),
        ("drink7"   , 0x1F964),
        ("drink8"   , 0x1F9C9),
        ("drink9"   , 0x1F9CB),

        # Valuables
        ("crown"    , 0x1F451),
        ("ring"     , 0x1F48D),
        ("gem"      , 0x1F48E),
        ("moneybag" , 0x1F4B0),
        ("card"     , 0x1F4B3),
        ("money"    , 0x1F4B5),
        ("trophy"   , 0x1F3C6),
        ("coin"     , 0x1FA99),

        # Misc. Items
        ("glasses1" , 0x1F453),
        ("glasses2" , 0x1F576),
        ("bouquet"  , 0x1F490),
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
        ("scroll"   , 0x1F4DC),
        ("package"  , 0x1F4E6),
        ("magnify"  , 0x1F50D),
        ("bell"     , 0x1F514),
        ("crystal"  , 0x1F52E),
        ("warning"  , 0x026A0),
        ("heart1"   , 0x02764),
        ("heart2"   , 0x1F9E1),
        ("heart3"   , 0x1F49B),
        ("heart4"   , 0x1F49A),
        ("heart5"   , 0x1F499),
        ("heart6"   , 0x1F49C),
        ("heart7"   , 0x1F90E),
        ("heart8"   , 0x1F5A4),
        ("bone"     , 0x1F9B4),
        ("shield"   , 0x1F6E1),
        ("barrel"   , 0x1F6E2),
        ("wand"     , 0x1FA84),
        ("wood"     , 0x1FAB5),

        # Electronics
        ("pager"    , 0x1F4DF),
        ("antenna"  , 0x1F4E1),
        ("mobile"   , 0x1F4F1),
        ("phone"    , 0x0260E),
        ("camera1"  , 0x1F4F7),
        ("camera2"  , 0x1F4F8),
        ("tv"       , 0x1F4FA),
        ("radio"    , 0x1F4FB),
        ("computer" , 0x1F4BB),
        ("light1"   , 0x1F4A1),
        ("light2"   , 0x1F526),
        ("battery"  , 0x1F50B),

        # Tools
        ("key"      , 0x1F511),
        ("lock1"    , 0x1F512),
        ("lock2"    , 0x1F513),
        ("wrench"   , 0x1F527),
        ("hammer"   , 0x1F528),
        ("nutbolt"  , 0x1F529),
        ("ruler1"   , 0x1F4CF),
        ("ruler2"   , 0x1F4D0),
        ("axe"      , 0x1FA93),
        ("toolbox"  , 0x1F9F0),
        ("magnet"   , 0x1F9F2),

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
        ("speech1"  , 0x1F4AC),
        ("speech2"  , 0x1F5E8),
        ("fire"     , 0x1F525),
        ("bolt"     , 0x026A1),

        # Music Instruments
        ("saxophone", 0x1F3B7),
        ("guitar"   , 0x1F3B8),
        ("keyboard" , 0x1F3B9),
        ("trumpet"  , 0x1F3BA),
        ("violin"   , 0x1F3BB),
        ("banjo"    , 0x1FA95),

        # Flags
        ("checkflag", 0x1F3C1),

        # Earth Animals
        ("rat"      , 0x1F400),
        ("mouse"    , 0x1F401),
        ("ox"       , 0x1F402),
        ("buffalo"  , 0x1F403),
        ("cow"      , 0x1F404),
        ("rabbit"   , 0x1F407),
        ("dragon"   , 0x1F409),
        ("cat"      , 0x1F408),
        ("crocodile", 0x1F40A),
        ("scapegoat", 0x1F40C),
        ("snake"    , 0x1F40D),
        ("ram"      , 0x1F40F),
        ("sheep"    , 0x1F411),
        ("monkey"   , 0x1F412),
        ("rooster"  , 0x1F413),
        ("dog1"     , 0x1F415),
        ("pig"      , 0x1F416),
        ("elephant" , 0x1F418),
        ("turtle"   , 0x1F422),
        ("dog2"     , 0x1F429),
        ("camel1"   , 0x1F42A),
        ("camel2"   , 0x1F42B),
        ("chipmunk" , 0x1F43F),
        ("turkey"   , 0x1F983),
        ("kangaroo" , 0x1F998),
        ("llama"    , 0x1F999),
        ("hippo"    , 0x1F99B),

        # Air animals
        ("chick1"   , 0x1F423),
        ("chick2"   , 0x1F424),
        ("chick3"   , 0x1F425),
        ("bird"     , 0x1F426),
        ("penguin"  , 0x1F427),
        ("duck"     , 0x1F986),
        ("bat"      , 0x1F987),
        ("peacock"  , 0x1F99A),
        ("parrot"   , 0x1F99C),

        # Water Animals
        ("octopus"  , 0x1F419),
        ("fish1"    , 0x1F41F),
        ("fish2"    , 0x1F420),
        ("fish3"    , 0x1F421),
        ("dolphin"  , 0x1F42C),
        ("whale"    , 0x1F433),
        ("crab"     , 0x1F980),
        ("squid"    , 0x1F991),
        ("cricket"  , 0x1F997),

        # Insects
        ("ant"      , 0x1F41C),
        ("bee"      , 0x1F41D),
        ("ladybug"  , 0x1F41E),
        ("spider"   , 0x1F577),
        ("scorpion" , 0x1F982),
        ("butterfly", 0x1F98B),
        ("mosquito" , 0x1F99F),

        # Characters
        ("ogre"     , 0x1F479),
        ("ghost"    , 0x1F47B),
        ("alien"    , 0x1F47D),
        ("imp"      , 0x1F47F),
        ("fairy"    , 0x1F9DA),
        ("genie"    , 0x1F9DE),
        ("clown"    , 0x1F921),

    ]
    # Add clock emojis
    for i in range(24):
        n = "0"+str(i) if i<10 else str(i)
        myList.append( (f"clock{n}", 0x1F550+i) )
    # Add buildings (except ATM)
    j = 1
    k = 0
    for i in range(0x1F3E0,0x1F3ED+1):
        n = "0" + str(j) if j < 10 else str(j)
        if i != 0x1F3E7:
            myList.append((f"building{j}", i))
            j += 1
    myList.append((f"building{j}", 0x1F6D6))
    # add moon
    j = 1
    for i in range(0x1F311, 0x1F318+1):
        n = "0" + str(j) if j < 10 else str(j)
        myList.append((f"moon{j}", i))
        j += 1
    # return full list
    return myList

def createAtlas(font1, font2, list1, list2):
    N = len(list1) + len(list2)
    NBY = int(math.sqrt(9 * N / 15))
    NBX = int((NBY * 15 / 9))
    while N > NBX * NBY:
        NBX += 1
    print(N, NBX, NBY)
    SIZE = 80

    # sort list
    #strList = sorted(strList, key=lambda x:x[1])

    # Load font
    fnt1 = ImageFont.truetype(font1, size=109, layout_engine=ImageFont.LAYOUT_RAQM)
    fnt2 = ImageFont.truetype(font2, size=109, layout_engine=ImageFont.LAYOUT_RAQM)
    # Create image according to emoji list
    im   = Image.new("RGBA", (NBX*SIZE,NBY*SIZE), (0,0,0,0))

    # Open C-header-file
    fp = open("emoji.h", "w")
    fp.write( "#ifndef EMOJI_H\n")
    fp.write( "  #define EMOJI_H\n\n")
    fp.write(f"  #define EMOJI_SIZE {SIZE}\n\n")
    # For each item draw ...
    x = 0
    y = 0
    for entry in list2:
        name  = entry[0]
        ucode = entry[1]
        # Paste emoticon into final atlas
        im1 = Image.new("RGBA", (128,128), (0,0,0,0))
        dr1 = ImageDraw.Draw(im1)
        dr1.text( (0,0), chr(ucode), fill=(0,0,0,255), embedded_color=True, font=fnt2)
        im1 = im1.resize((SIZE,SIZE),resample=Image.ANTIALIAS)
        im.paste(im1,(x*SIZE,y*SIZE))
        # Write C-header-file
        fp.write(f"  #define {name.upper()} ({hex((y*256)+x)})\n")
        # Next emoji
        x += 1
        if x >= NBX:
            x  = 0
            y += 1

    for entry in list1:
        name = entry[0]
        ucode= entry[1]
        # Paste emoticon into final atlas
        im1 = Image.new("RGBA", (128,128), (0,0,0,0))
        dr1 = ImageDraw.Draw(im1)
        dr1.text( (0,0), chr(ucode), fill=(0,0,0,255), embedded_color=True, font=fnt1)
        im1 = im1.resize((SIZE,SIZE),resample=Image.ANTIALIAS)
        im.paste(im1,(x*SIZE,y*SIZE))
        # Write C-header-file
        fp.write(f"  #define {name.upper()} ({hex((y*256)+x)})\n")
        # Next emoji
        x += 1
        if x >= NBX:
            x  = 0
            y += 1

    # Close file
    fp.write("\n#endif // EMOJI_H \n")
    fp.close()

    im.show()
    im.save(f"emoji.png")





createAtlas(r"../GameRGR/fonts/DejaVuSansMono.ttf",
            r"../GameRGR/fonts/NotoColorEmoji.ttf",
            getOthers(),
            getEmoji()
            )

# Copy Header file + png atlas
shutil.copyfile("./emoji.h"  , "../GameRGR/includes/emoji.h")
shutil.copyfile("./emoji.png", "../GameRGR/fonts/emoji.png" )

