// file name:    slid.c
// creator(s)    Lilith, Aug 2021
// last update:  Lilith   July 2021   Added some exits in case the
//                                    player doesn't get moved out.
// purpose: This is the place where a player is when he is sliding
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/common/dead/barrow_base";
#include "../dead.h"

void
create_barrow_room()
{
    set_short("inside chute");
    set_long("A small ledge inside a chute.\n");
    add_prop(ROOM_S_DARK_MSG, "The darkness around you is much too "
      +"thick to");
    add_prop(ROOM_S_DARK_LONG, "Darkness presses upon you "
      +"from all directions. The air smells of moisture "
	  +"and death.\n");
	
    // Swallowed by earth, the darkness is deep.
    add_prop(ROOM_I_LIGHT, -10);

    // In the event mortal doesn't get moved out of here
    // Lets give them some exits
    add_exit(BARROW+"barrow15","up", 0, 10, 1);	
    add_exit(CRYPT+"crypt66","down", 0, 0, 1);
    add_exit(BARROW+"sliding","out");

}
