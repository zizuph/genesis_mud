#include "defs.h"
inherit DUNGEON_OBJ_DIR + "gate";

void
create_door()
{
    ::create_door();
    set_door_id("dungeon_gate_8");
    set_pass_command(({"s", "south"}));
    set_door_name(DUNGEON_DOOR_NAMES + ({"south gate"}));

    set_other_room(DUNGEON_DIR + "dungeon01");
}
