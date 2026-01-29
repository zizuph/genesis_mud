#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/std/door";

void
create_door()
{
    set_door_name(({"iron gate","gate"}));
    set_door_desc("This is a huge, iron gate. Thick iron bars " +
        "combined with thick oak beams make the portcullis a formidable " +
        "obstruction.\n");
    set_pass_command(({"n","north"}));
    set_door_id("neraka_main_outer");
    set_other_room(NOUTER+"main/r1");
    set_open(1);
    set_str(60);
    set_open_command(({"open"}));
    set_close_command(({"close"}));

    add_prop(OBJ_I_WEIGHT, 1200000);
    add_prop(OBJ_I_VOLUME, 500000);
}

