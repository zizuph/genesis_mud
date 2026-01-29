
/************************************************************
 * Area: Dargaard Keep.
 * By  : Ruben
 * Date: June 2001
 * Desc: room9 
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
    set_short("Crossroad in Dargaard Keep");
    set_long("You are at a kind of crossroad within"+
             " the basement. Torches flicker because of"+
             " the bad air and mist covers, like everywhere,"+
             " the floor. The gloom is pressive and you see "+
             "the dark hallway continue to the north, east, west "+
             "and south.\n"); 

    add_item(({"ground"}), 
     "The ground is even and in a good condition except some"+ 
     " puddles and debris lying around.\n"); 

    add_item(({"mist"}), 
     "It is a fine, silky mist. It seems to touch you with cold, wet fingers.\n"); 

    add_item(({"mud"}), 
     "You cannot make out anything extraordinary"+ 
     " in the mud. Seems to be quite normal mud.\n"); 

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

    add_exit(DROOM + "room18","north",0);
    add_exit(DROOM + "room12","east",0);
    add_exit(DROOM + "nowhere","west","@@nowhere",0);
    add_exit(DROOM + "room10","south",0);
}

int
nowhere()
{
    write("That corridor is blocked with debris and rubble, you "+
          "are unable to find a way through it.\n");
    return 1;
}
