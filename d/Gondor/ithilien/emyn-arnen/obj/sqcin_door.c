inherit "/std/door";
#include "/d/Gondor/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

void
create_door()
{
    ::create_door();
    set_other_room(ITH_DIR + "emyn-arnen/palace/sqcorr");
    set_door_id("Emyn-Arnen_SQCorr_Door");
    set_pass_command(({"n","north"}));
    set_door_name(({"door", "wooden door"}));
    set_door_desc("A simple wooden door, without lock or key hole.\n");
    set_open(0);         /* 1 if open, 0 if closed */

    set_str(10);
}

void
reset_door()
{
    other_door->reset_door();
}
