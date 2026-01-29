
/************************************************************
 * Area: Dargaard Keep.
 * By  : Ruben
 * Date: June 2001
 * Desc: room4
 *
 *
 *
 ************************************************************/

#include "../local.h"
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/guild/dknights/local.h"
#include <stdproperties.h>
inherit DARGAARD_IN;

void
reset_dargaard_room()
{

}

void
create_dargaard_room()
{
    reset_dargaard_room();
    set_short("Passage in the basement of Dargaard Keep");
    set_long("You find yourself in a gloomy passage in"+
	     " Dargaard Keep."+
	     " Water is dripping down the ceiling. The echo"+
	     " reminds you of a heart's rhytmic beating."+
             " Ankle-high mist covers the floor weaving"+
	     " intricate patterns and glowing in a sickly"+
             " green light due to the light radiated by"+
	     " some strange fungi you haven't seen before."+
	     " To the north you see a well-lit staircase"+
	     " leading up. The other passages are lost"+
	     " in the darkness, however, you hear a steady"+
	     " splashing of water to the north.\n"); 


    add_item(({"walls", "wall"}), 
     "The walls are pitch-black, absorbing any light touching them."+ 
     " You wonder if only the soot on the walls is the reason for that"+ 
     " or if a more sinister force is at work.\n"); 

    add_item(({"torches"}), 
     "The torches are made of wood with a oily top.\n"); 

    add_item(({"water"}), 
     "It looks like ordinary water but with a kind of faint red hue.\n"); 

    add_item(({"mist"}), 
     "It is a fine, silky mist. It seems to touch you with cold, wet fingers.\n"); 

    add_item(({"light"}), 
     "The light seems to be weak and somehow it looks"+ 
     " sickly to you. It adds an eerie aura to the general"+ 
     " gloom.\n"); 

    add_item(({"mud"}), 
     "You cannot make out anything extraordinary"+ 
     " in the mud. Seems to be quite normal mud.\n"); 

    add_item(({"fungi"}), 
     "The fungi seems to be sticky and smells terribly"+ 
     " Maybe it is a kind of algae, maybe something"+ 
     " entirely different.\n"); 

    add_item(({"stone floor", "floor"}), 
     "This floor is made of ordinary stone. It seems that because of"+ 
     " practicality normal stone was used in this corridor. Probably"+ 
     " the precious but more delicate stones would have been damaged"+ 
     " in no time.\n"); 

    add_exit(DROOM + "room5","north",0);
    add_exit(GUILD_ROOM + "room1","south",0);

}
