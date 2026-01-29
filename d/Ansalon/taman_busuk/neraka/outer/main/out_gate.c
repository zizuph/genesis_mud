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
    set_pass_command(({"s","south"}));
    set_door_id("neraka_main_outer");
    set_other_room(NOUTER + "main/tunnel");
    set_open(1);
    set_str(60);
    set_open_command(({"open"}));
    set_close_command(({"close"}));

    add_prop(OBJ_I_WEIGHT, 1200000);
    add_prop(OBJ_I_VOLUME, 500000);
}

int
pass_door(string arg)
{
    object d;

    d = present("guard",E(TO));

    /* Only try to go through if the door is open */
    if (query_open() && !(NERAKA_ADMIN)->query_may_enter_city(TP,d))
    {
        TP->catch_msg(QCTNAME(d) + " stops you from entering the city.\n");
        return 1;
    }
    else
        return ::pass_door(arg);
}

