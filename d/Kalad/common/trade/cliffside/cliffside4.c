inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

void
create_room()
{
   set_short("Cliffside Road");
   set_long("The road continues to both the east and west here. "
           +"Pitiful houses line the street, and some children scamper from "
           +"beneath your feet and run back to their homes. This is "
           +"a poor community who lives off trade and labor, and it is "
           +"obvious.\n");
add_exit(TRADE(cliffside/cliffside3),"east");
add_exit(TRADE(cliffside/cliffside5),"west");
add_item(({"houses"}),"The houses are run down and shabby, not to mention a bit plain.\n");
add_item(({"children"}),"The children are dirty and lack good care. "
                       +"You feel somewhat sorry for them.\n");
  add_item(({"road","roads","intersection"}),"This is a plain road, "
	+"not at all interesting in the least. It is made of worn "
	+"stone, and is dirty.\n");
  add_item(({"homes","home"}),"They are small old "
	+"houses belonging to the lower classed tradesman of Kabal.\n");
  add_item(({"shops","shop"}),"They are small businesses run by the "
	+"lower-classed people.\n");
hear_bell = 2;
}
