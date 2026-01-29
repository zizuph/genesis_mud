#pragma strict_types

#include "defs.h"
inherit TEMPLE_OBJ_DIR + "stone_door";

void
create_door()
{
    ::create_door();
    set_door_id("khiraa_western_door");
    set_pass_command(({"s","south"}));
    set_other_room(TEMPLE_DIR + "temple02");
}
