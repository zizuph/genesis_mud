#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/std/door";

void
create_door()
{
    set_door_name(({"iron portcullis","portcullis"}));
    set_door_desc("This is a huge, iron portcullis. Thick iron bars " +
        "combined with thick oak beams make the portcullis a formidable " +
        "obstruction.\n");
    set_pass_command(({"e","east"}));
    set_door_id("neraka_black_outer");
    set_other_room(NOUTER+"black/b5");
    set_open(1);
    /* The gate is not supposed to be opened by hand by any player. A giant
       could open it though. */
    set_str(300);
    set_open_command(({"open","raise"}));
    set_close_command(({"close","lower"}));

    add_prop(OBJ_I_WEIGHT, 1200000);
    add_prop(OBJ_I_VOLUME, 500000);
}

string
standard_open_mess2()
{
    return "With a low rumble, the " + query_door_name()[0] + " rises.\n";
}

string
standard_close_mess2()
{
    return "With a resounding crash, the " + query_door_name()[0] +
        " is lowered, sealing off the exit.\n";
}
