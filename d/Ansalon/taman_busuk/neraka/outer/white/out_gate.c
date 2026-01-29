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
    set_pass_command(({"se","southeast"}));
    set_door_id("neraka_white_outer");
    set_other_room(NOUTER + "white/tunnel");
    set_open(1);
    /* The gate is not supposed to be opened by hand by any player. A giant
       could open it though. */
    set_str(300);
    set_open_command(({"open","raise"}));
    set_close_command(({"close","lower"}));

    add_prop(OBJ_I_WEIGHT, 1200000);
    add_prop(OBJ_I_VOLUME, 500000);
}

int
pass_door(string arg)
{
    object d;

    d = present("draconian",E(TO));

    /* Only try to go through if the door is open */
    if (query_open() && !(NERAKA_ADMIN)->query_may_enter_city(TP,d))
    {
        TP->catch_msg(QCTNAME(d) + " stops you from entering the city.\n");
        return 1;
    }
    else
        return ::pass_door(arg);
}


void
remote_open()
{
    if (!other_door)
	load_other_door();
	
    do_open_door(check_call(open_mess[1]));
    other_door->do_open_door(check_call(open_mess[1]));
}

void
remote_close()
{
    if (!other_door)
	load_other_door();
	
    do_close_door(check_call(close_mess[1]));
    other_door->do_close_door(check_call(close_mess[1]));
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
        " is lowered, sealing off the entrance.\n";
}
