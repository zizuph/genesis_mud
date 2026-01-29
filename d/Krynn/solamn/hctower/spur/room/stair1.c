// stair1
// grace aug 1994

#include "../local.h"

inherit SPURRM;

create_spur_room()
{
    SHORT("Northeast stairwell in the lower level of Knights' Spur");
    LONG("You are standing at the base of the stairs which lead up "
         + "to the second level of the Knights' Spur. The stairwell "
         + "appears to be narrow and poorly lit.\n");

    INSIDE;
    LIGHT;

    add_exit(ROOM + "stair2","up",0);
AE(ROOM + "arch2", "south", 0);

} 






