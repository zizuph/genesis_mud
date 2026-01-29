inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* More of this great casino, by Sarr */
void
create_room()
{
    ::create_room();
    set_short("Inside Guido's Gaming Palace.\n");
    set_long("This room is where people come to bet on the famouse rat"+
    "races of Kabal.\n");
    add_exit(MRKT_PATH(casino02), "south");
    add_prop(MRKT_IN_NO_HEAR,1);
    INSIDE;
}

