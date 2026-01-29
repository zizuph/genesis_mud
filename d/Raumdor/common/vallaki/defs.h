#include "../defs.h"

#define VALLAKI_DIR               "/d/Raumdor/common/vallaki/"

#define VALLAKI_ARM_DIR           VALLAKI_DIR + "arm/"
#define VALLAKI_NPC_DIR           VALLAKI_DIR + "npc/"
#define VALLAKI_OBJ_DIR           VALLAKI_DIR + "obj/"
#define VALLAKI_SHOP_DIR          VALLAKI_DIR + "shop/"
#define VALLAKI_WEP_DIR           VALLAKI_DIR + "wep/"
#define VALLAKI_HOUSE_STD_ROOM    VALLAKI_DIR + "std/vallaki_indoor_room"
#define VALLAKI_INDOOR_DIR        VALLAKI_DIR + "indoor/"
#define VALLAKI_ROAD_STD_ROOM     VALLAKI_DIR + "std/vallaki_outdoor_room"
#define VALLAKI_OUTDOOR_DIR       VALLAKI_DIR + "outdoor/"


#define ROAD_LONG_DESC ([ 1:({"You are somewhere inside the southern wall of Vallaki. ", \
                              "blap blaph. ",}) , \
                          2:({"glitterdust.\n",   \
                              "scrutinize.\n",}), \
		                  ])
                          
#define ROAD_SHORT_DESC ([ 1:({"On a dirt road in Vallaki near the wall",    \
                               "beep",}) , \
                          2:({"glitterdust.\n",   \
                              "scrutinize.\n",}), \
		                  ])


