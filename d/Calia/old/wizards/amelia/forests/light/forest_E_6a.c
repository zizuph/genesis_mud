/*
*	by Amelia for use in the Light Forest
*/
inherit "/std/room";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "defs.h"

void
create_room()
{
	object door;
	set_short("The light forest");

       set_long("As you follow the path through the trees, you can see a "+
               "clearing just ahead.  You come upon a small cottage, made of "+
                "pink and grey stones, with a thatch roof.  It has "+
                "windows with open shutters to let in the sun, and a "+
                "dutch door in front, with the top part open.  In the yard "+
                "you see flowers growing.  There is a door leading into the "+
                "cottage.\n");

       add_exit((FPATH+"forest_E_5a"), "west", 0, 0);
	door = clone_object(FPATH+"granny_door_o");
       door->move(this_object());

       add_prop(ROOM_I_LIGHT, 1);
       add_prop(ROOM_I_IS, 1);
       add_prop(ROOM_I_INSIDE, 0);



}
