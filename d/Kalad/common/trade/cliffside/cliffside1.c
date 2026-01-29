#include "/sys/stdproperties.h"
#include "/sys/macros.h"

inherit "/d/Kalad/room_std";
# include "/d/Kalad/defs.h"

void
create_room()
{
     ::create_room();
          set_short("Cliffside road");
      set_long("You are on Cliffside road. The road continues to "
               +"the east and west. To your south lies the cliff "
               +"which seperates the Port and Tradesman districts. "
               +"Surrounding you are houses of the underclass people "
             +"of Kabal. To your west you spot a sign flapping in "
               +"the breeze.\n");
  add_item(({"road","roads","intersection"}),"This is a plain road, "
	+"not at all interesting in the least. It is made of worn "
	+"stone, and is dirty.\n");
  add_item(({"sign"}),"It is to your west.\n");
add_exit(TRADE(cliffside/cliff_turn),"east");
add_exit(TRADE(cliffside/cliffside2),"west");
          
          hear_bell = 2;
}
                                                        
