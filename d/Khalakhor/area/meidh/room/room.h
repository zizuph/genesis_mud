#include "../area.h"

#define ROADBASE      ROOM + "road_base"
#define ROAD_MESSAGES ROOM + "road_messages"

#define INSIDE       add_prop(ROOM_I_INSIDE, 1)
#define DARK         add_prop(OBJ_I_LIGHT, -1)
#define LIGHT        add_prop(OBJ_I_LIGHT, 1)
