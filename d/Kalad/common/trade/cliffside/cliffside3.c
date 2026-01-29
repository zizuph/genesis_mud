#include "/sys/stdproperties.h"
#include "/sys/macros.h"

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

void
create_room()
{
     ::create_room();
set_short("Cliffside Road");
       set_long("You are on the Cliffside road. The road continues to "
                      +"the east and west. Directly to your south is a "
              +"large cliff that separates the rest of Kabal from "
              +"the port district. A large junction in the roads "
              +"is to the east.\n");
  add_item(({"road","roads","intersection"}),"This is a plain road, "
	+"not at all interesting in the least. It is made of worn "
	+"stone, and is dirty.\n");
  add_item(({"homes","houses","house","home"}),"They are small old "
	+"houses belonging to the lower classed tradesman of Kabal.\n");
  add_item(({"shops","shop"}),"They are small businesses run by the "
	+"lower-classed people.\n");
add_exit(TRADE(cliffside/cliffside4),"west");
add_exit(TRADE(cliffside/cliffside_junc),"east");
add_item(({"cliff"}),"The cliff to your south is a sheer ridge of "
                        +"granite which extends down into the port district.\n");
     
     hear_bell = 2;
}

              
