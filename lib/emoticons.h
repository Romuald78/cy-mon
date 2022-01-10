#ifndef EMOTICONS_H
    #define EMOTICONS_H

    //----------------------------------------------
    // UTF-8 and UNICODE values for EMOTICONS
    //----------------------------------------------
    #define EMOT_BLANK       "  "
    // Digits
    #define EMOT_NUM1        "\xE2\x91\xA0"
    #define EMOT_NUM2        "\xE2\x91\xA1"
    #define EMOT_NUM3        "\xE2\x91\xA2"
    #define EMOT_NUM4        "\xE2\x91\xA3"
    #define EMOT_NUM5        "\xE2\x91\xA4"
    #define EMOT_NUM6        "\xE2\x91\xA5"
    #define EMOT_NUM7        "\xE2\x91\xA6"
    #define EMOT_NUM8        "\xE2\x91\xA7"
    #define EMOT_NUM9        "\xE2\x91\xA8"    
    // Trees and grass
    #define EMOT_PINE        "\xF0\x9F\x8C\xB2"
    #define EMOT_TREE        "\xF0\x9F\x8C\xB3"
    #define EMOT_CACTUS      "\xF0\x9F\x8C\xB5"
    #define EMOT_PALMTREE    "\xF0\x9F\x8C\xB4"
    #define EMOT_CLOVER      "\xF0\x9F\x8D\x80"
    #define EMOT_HERB        "\xF0\x9F\x8C\xBF"
    // Flowers
    #define EMOT_TULIP       "\xF0\x9F\x8C\xB7"
    #define EMOT_FLOWER      "\xF0\x9F\x8C\xB8"
    #define EMOT_ROSE        "\xF0\x9F\x8C\xB9"
    #define EMOT_HIBISCUS    "\xF0\x9F\x8C\xBA"
    #define EMOT_SUNFLOWER   "\xF0\x9F\x8C\xBB"
    // Shapes
    #define EMOT_CIRCLE_BLUE "\xF0\x9F\x94\xB5"
    #define EMOT_CIRCLE_RED  "\xF0\x9F\x94\xB4"
    #define EMOT_TICK        "\xE2\x9C\x85"
    // Food
    #define EMOT_APPLE_RED   "\xF0\x9F\x8D\x8E"
    #define EMOT_APPLE_GREEN "\xF0\x9F\x8D\x8F"
    // Natural elements
    #define EMOT_ROCK        "\xF0\x9F\xAA\xA8"
    #define EMOT_FLAME       "\xF0\x9F\x94\xA5"
    #define EMOT_BOLT        "\xE2\x9A\xA1"
    // Buildings
    #define EMOT_HOUSE1      "\xF0\x9F\x8F\xA0"
    #define EMOT_HOUSE2      "\xF0\x9F\x8F\xA1"
    #define EMOT_BUILDING    "\xF0\x9F\x8F\xA2"
    #define EMOT_HUT         "\xF0\x9F\x9B\x96"
    // Animals    
    #define EMOT_MOUSE       "\xF0\x9F\x90\x81"   
    #define EMOT_RABBIT      "\xF0\x9F\x90\x87"   
    #define EMOT_SPIDER      "\xF0\x9F\x95\xB7" 
    #define EMOT_SNAIL       "\xF0\x9F\x90\x8C"
    #define EMOT_SNAKE       "\xF0\x9F\x90\x8D"
    #define EMOT_HORSE       "\xF0\x9F\x90\x8E"
    #define EMOT_GOAT        "\xF0\x9F\x90\x90"  
    #define EMOT_SHEEP       "\xF0\x9F\x90\x91"
    #define EMOT_MONKEY      "\xF0\x9F\x90\x92"
    #define EMOT_CHICKEN1    "\xF0\x9F\x90\x93"
    #define EMOT_CHICKEN2    "\xF0\x9F\x90\x94"
    #define EMOT_BEE         "\xF0\x9F\x90\x9D"
    #define EMOT_LADYBUG     "\xF0\x9F\x90\x9D"
    #define EMOT_FISH1       "\xF0\x9F\x90\x9F"
    #define EMOT_FISH2       "\xF0\x9F\x90\xA0"
    #define EMOT_TURTLE      "\xF0\x9F\x90\xA2"
    #define EMOT_BABYCHICK_S "\xF0\x9F\x90\xA4"
    #define EMOT_BABYCHICK_F "\xF0\x9F\x90\xA5"
    #define EMOT_BIRD        "\xF0\x9F\x90\xA6"
    #define EMOT_PENGUIN     "\xF0\x9F\x90\xA7"
    // Special characters
    #define EMOT_FAIRY       "\xF0\x9F\xA7\x9A"   
    #define EMOT_GHOST       "\xF0\x9F\x91\xBB"
    #define EMOT_DEVIL       "\xF0\x9F\x91\xBF"
    #define EMOT_ALIEN       "\xF0\x9F\x91\xBD"
    // Valuable Items
    #define EMOT_GEM         "\xF0\x9F\x92\x8E"
    #define EMOT_MONEYBAG    "\xF0\x9F\x92\xB0"
    #define EMOT_BANKNOTE    "\xF0\x9F\x92\xB6"
    #define EMOT_CROWN       "\xF0\x9F\x91\x91"
    #define EMOT_RING        "\xF0\x9F\x92\x8D"
    #define EMOT_CREDITCARD  "\xF0\x9F\x92\xB3" 
    // Tools
    #define EMOT_WRENCH      "\xF0\x9F\x94\xA7"
    #define EMOT_HAMMER      "\xF0\x9F\x94\xA8"
    #define EMOT_AXE         "\U0001FA93"
    #define EMOT_TOOLBOX     "\U0001F9F0"
    #define EMOT_MAGNET      "\U0001F9F2"
    // Furnitures
    #define EMOT_COMPUTER    "\xF0\x9F\x92\xBB"
    // Miscellaneous items
    #define EMOT_POSTBOX1    "\xF0\x9F\x93\xAA"
    #define EMOT_POSTBOX2    "\xF0\x9F\x93\xAB"
    #define EMOT_POSTBOX3    "\xF0\x9F\x93\xAC"
    #define EMOT_POSTBOX4    "\xF0\x9F\x93\xAD"
    #define EMOT_KEY         "\xF0\x9F\x94\x91"
    #define EMOT_LOCK_CLOSED "\xF0\x9F\x94\x92"
    #define EMOT_LOCK_OPEN   "\xF0\x9F\x94\x93"
    #define EMOT_HEART       "\xE2\x9D\xA4"
    #define EMOT_TROPHY      "\xF0\x9F\x8F\x86"
    #define EMOT_DISC1       "\xF0\x9F\x92\xBF"         
    #define EMOT_DISC2       "\xF0\x9F\x93\x80"
    #define EMOT_MOBILEPHONE "\xF0\x9F\x93\xB1"         
    // Flags
    #define EMOT_RACEFLAG    "\xF0\x9F\x8F\x81"    
    // Clock
    #define EMOT_CLK_00      "\xF0\x9F\x95\x90"
    #define EMOT_CLK_01      "\xF0\x9F\x95\x9C"
    #define EMOT_CLK_02      "\xF0\x9F\x95\x91"
    #define EMOT_CLK_03      "\xF0\x9F\x95\x9D"
    #define EMOT_CLK_04      "\xF0\x9F\x95\x92"
    #define EMOT_CLK_05      "\xF0\x9F\x95\x9E"
    #define EMOT_CLK_06      "\xF0\x9F\x95\x93"
    #define EMOT_CLK_07      "\xF0\x9F\x95\x9F"
    #define EMOT_CLK_08      "\xF0\x9F\x95\x94"
    #define EMOT_CLK_09      "\xF0\x9F\x95\xA0"
    #define EMOT_CLK_10      "\xF0\x9F\x95\x95"
    #define EMOT_CLK_11      "\xF0\x9F\x95\xA1"
    #define EMOT_CLK_12      "\xF0\x9F\x95\x96"
    #define EMOT_CLK_13      "\xF0\x9F\x95\xA2"
    #define EMOT_CLK_14      "\xF0\x9F\x95\x97"
    #define EMOT_CLK_15      "\xF0\x9F\x95\xA3"
    #define EMOT_CLK_16      "\xF0\x9F\x95\x98"
    #define EMOT_CLK_17      "\xF0\x9F\x95\xA4"
    #define EMOT_CLK_18      "\xF0\x9F\x95\x99"
    #define EMOT_CLK_19      "\xF0\x9F\x95\xA5"
    #define EMOT_CLK_20      "\xF0\x9F\x95\x9A"
    #define EMOT_CLK_21      "\xF0\x9F\x95\xA6"
    #define EMOT_CLK_22      "\xF0\x9F\x95\x9B"
    #define EMOT_CLK_23      "\xF0\x9F\x95\xA7"
    // Borders
    #define EMOT_HORIZONTAL  "\u2501"
    #define EMOT_VERTICAL    "\u2503"
    #define EMOT_CORNER_TL   "\u250F"
    #define EMOT_CORNER_TR   "\u2513"
    #define EMOT_CORNER_BL   "\u2517"
    #define EMOT_CORNER_BR   "\u251B"
    #define EMOT_TEE_TOP     "\u2533"
    #define EMOT_TEE_BOTTOM  "\u253B"
    #define EMOT_TEE_LEFT    "\u2523"
    #define EMOT_TEE_RIGHT   "\u252B"
    #define EMOT_CROSS       "\u254B"
    
    
#endif

