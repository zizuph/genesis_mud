
/************************************************************
 * Area: Dargaard Keep.
 * By  : Ruben
 * Date: June 2001
 * Desc: room_1 
 *
 *
 *
 ************************************************************/

#include "../local.h"
#include "/d/Ansalon/common/defs.h"
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
    set_short("Gloomy hallway in Dargaard Keep");
    set_long("This is a dark alcove. Slime and fungus covers the"+
             " walls. On some places of the walls you still can see"+
	           " the once beautiful ornaments. A few torches lit up "+
             "the hallway, which continues to the southwest and east.\n"); 
	
    add_exit(DROOM + "room16","east",0);
    add_exit(DROOM + "room18","southwest",0);

    add_item(({"slime"}), 
     "The slime seems to be sticky and smells terribly"+ 
     " Maybe it is a kind of algae, maybe something"+ 
     " entirely different.\n"); 

    add_item(({"torches"}), 
     "These are standard torches which you can find everywhere"+ 
     " on Krynn.\n");

    add_item(({"stone floor", "floor"}), 
     "This floor is made of ordinary stone. It seems that because of"+ 
     " practicality normal stone was used in this corridor. Probably"+ 
     " the precious but more delicate stones would have been damaged"+ 
     " in no time.\n"); 

    add_item(({"walls", "wall"}), 
     "The walls are pitch-black, absorbing any light touching them."+ 
     " You wonder if only the soot on the walls is the reason for that"+ 
     " or if a more sinister force is at work.\n"); 

    add_item(({"ornaments"}), 
     "These ornaments are very intricate and the artists"+ 
     " who made them must have been very skilled. Many"+ 
     " of the finer features, however, were destroyed in the"+ 
     " raging fire which seems to have raged throughout the"+ 
     " whole castle.\n"); 

    add_item(({"mist"}), 
     "It is a fine, silky mist. It seems to touch you with cold, wet fingers.\n"); 

    add_item(({"dirt"}), 
     "Wind and especially storms seems to have found"+ 
     " their way into the Keep over the centuries and have"+ 
     " blown some things like earth and plants into the keep.\n"); 

    add_item(({"dark-brown mud", "mud"}), 
     "This is a patch of earth holding quite some"+ 
     " moisture and seems to be made of fertile"+ 
     " earth. In some time there might be a plant"+     
     " growing there.\n"); 

}
