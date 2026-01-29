inherit "/d/Kalad/room_std";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Kalad/defs.h"

void
create_room()
{
 set_short("Cliffside Road");
 set_long("To the west the road enters the central district. Left behind "
	+"is the boredom of the commoners area, and hopefully the "
	+"city will hold some intrigue for any adventurer.\n");
add_exit(TRADE(cliffside/cliffside7),"east");
add_exit("/d/Kalad/common/central/lift_room","west");
add_item(({"north house"}),"This house is dirty and shabby, yet is "
                          +"one of the few 2 story houses around. "
                          +"On the front door is scrawled a couple of "
                          +"words.\n");
add_item(({"south house"}),"This is an ordinary house. Less than ordinary even.\n");
add_item(({"words"}),"These words are in a language you don't understand.\n");
  add_item(({"road","roads","intersection"}),"This is a plain road, "
	+"not at all interesting in the least. It is made of worn "
	+"stone, and is dirty.\n");
  add_item(({"homes","home"}),"They are small old "
	+"houses belonging to the lower classed tradesman of Kabal.\n");
  add_item(({"shops","shop"}),"They are small businesses run by the "
	+"lower-classed people.\n");
hear_bell = 1;
}
