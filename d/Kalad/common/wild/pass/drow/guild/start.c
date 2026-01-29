inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/*
 * Guild is closed and not returning.
 * New racial was opened in Faerun.
 * 	- Lucius, June 2017
 */
void
create_room()
{ 
    ::create_room();
    INSIDE;
    set_short("");
    set_long("");
}

void 
enter_inv(object ob, object from)
{
    string start = ob->query_def_start();

    ::enter_inv(ob, from);

    if (ob->query_default_start_location() ==
	"/d/Kalad/common/wild/pass/drow/start")
    {
	ob->set_default_start_location(start);
    }

    ob->move_living("X", start);
}
