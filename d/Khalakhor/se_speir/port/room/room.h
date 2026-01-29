#include "../village.h"

#define WAREBASE      ROOM + "ware_base"
#define ROADBASE      ROOM + "road_base"
#define TUNNEL_BASE   ROOM + "tunnel_base"
#define ROAD_MESSAGES ROOM + "road_messages"
#define KIRK_ROOM     "/d/Khalakhor/guilds/sean-rhian/macdunnkirk/room/"
#define ZOUTDOOR      "/d/Khalakhor/guilds/sean-rhian/lib/zoutdoor"

#define INSIDE       add_prop(ROOM_I_INSIDE, 1)
#define DARK         add_prop(OBJ_I_LIGHT, -1)
#define LIGHT        add_prop(OBJ_I_LIGHT, 1)
