inherit "/d/Kalad/room_std";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Kalad/defs.h"

void
create_room()
{
set_name("Old House");
set_long("This is one old ugly house. It makes you queasy being so "
	+"close to the edge of a huge cliff. You have a strong urge "
       +"to get the hell out of here before you fall off the cliff. "
	+"The only thing in this room is a rug.\n");
set_noshow_obvious(1);
add_exit(TRADE(cliffside/cliffside5),"north");
add_exit(TRADE(sewers/s7),"down");
add_item(({"rug"}),"A nice looking carpet, totally dustfree, unlike "
                  +"everything else in here. A strange thin piece of "
                  +"rope is barely sticking out from the side of the "
                  +"rug, how unusual.\n");
add_item(({"rope","strange rope","thin rope","strange thin rope"}),
          "You pull on the piece of rope, and the rug moves, revealing "
         +"an exit going down.\n");
add_prop(ROOM_NO_TIME_DESC,1);
hear_bell = 1;
}
