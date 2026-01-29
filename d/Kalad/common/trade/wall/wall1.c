inherit "/d/Kalad/room_std";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Kalad/defs.h"

void
create_room()
{
set_short("Wall Street");
set_long("You are near the corner of Wall Street and Cliffside Road. "
        +"To your east, stands the huge wall that protects Kabal from "
        +"invaders, and other unwanted guests.\n");
add_item(({"wall"}),"This is the great wall of Kabal which "
                   +"seperates the city from the outsiders "
                             +"and demihumans who try to get in.\n");
  add_item(({"road","street","streets","roads","intersection"}),
	"This is a plain road, "
        +"not at all interesting in the least. It is made of worn "
        +"stone, and is dirty.\n");
  add_item(({"shops","shop"}),"They are small businesses run by the "
        +"lower-classed people.\n");
add_exit(TRADE(wall/wall2),"north");
add_exit(TRADE(cliffside/cliff_turn),"south");
hear_bell = 1;
}
