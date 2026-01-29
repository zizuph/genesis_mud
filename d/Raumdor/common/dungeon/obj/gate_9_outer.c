#include "defs.h"
inherit DUNGEON_OBJ_DIR + "gate";

void
create_door()
{
    ::create_door();
    set_door_id("dungeon_gate_9");
    set_pass_command(({"w", "west"}));
    set_door_name(DUNGEON_DOOR_NAMES + ({"west gate"}));

    set_other_room(DUNGEON_DIR + "dungeon05");
}
