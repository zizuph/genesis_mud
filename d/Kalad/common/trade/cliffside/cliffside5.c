inherit "/d/Kalad/room_std";
#include "/sys/stdproperties.h"
#include "/d/Kalad/defs.h"
#include "/sys/macros.h"

void
create_room()
{
set_name("Cliffside Road");
set_long("The road here is a bit different, yet still seems the same...strange you "
       +"don't hear the same sounds as you have gotten used to hearing, "
         +"no children, no bargaining traders. "
        +"There is an open door leading to a house south, but that is "
        +"all that seems to stand out to you.\n");
add_exit(TRADE(cliffside/cliffside4),"east");
add_exit(TRADE(cliffside/cliffside6),"west");
add_exit(TRADE(house_entrance),"south");
add_item(({"house"}),"The house is old and delapidated. You really "
                    +"don't think you should go inside it, yet "
                    +"something is drawing you towards it.\n");
add_item(({"door"}),"The door is brown and quite open.\n");
  add_item(({"road","roads","intersection"}),"This is a plain road, "
	+"not at all interesting in the least. It is made of worn "
	+"stone, and is dirty.\n");
  add_item(({"homes","home"}),"They are small old "
	+"houses belonging to the lower classed tradesman of Kabal.\n");
  add_item(({"shops","shop"}),"They are small businesses run by the "
	+"lower-classed people.\n");
hear_bell = 2;
}
