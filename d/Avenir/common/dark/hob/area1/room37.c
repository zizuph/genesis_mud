#pragma strict_types

#include "../hob.h"
inherit HOB_ROOM_SERVER;
#include "room.h"

public void
hob_room(void)
{
    add_npc(MON + "hobgoblin", 3 + random(4));
}
