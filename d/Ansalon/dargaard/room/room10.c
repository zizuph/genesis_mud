
/************************************************************
 * Area: Dargaard Keep.
 * By  : Ruben
 * Date: June 2001
 * Desc: room_2 
 *
 *
 *
 ************************************************************/

#include "../local.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
inherit DARGAARD_IN;

object wraith;

void
reset_dargaard_room()
{
   if(!objectp(wraith))
   {
      wraith = clone_object(DNPC + "wraith");
      wraith->move(TO);
   }
}

void
create_dargaard_room()
{
    reset_dargaard_room();
    set_short("Passage in the lower level of Dargaard Keep");
    set_long(" You are in a passage in the basement of Dargaard"+
	     " Keep. The walls are cracked and the floor is covered with"+
	     " strange, whirling mist. Torches line the walls creating"+
      	     " a meager light.\n");
	
    add_exit(DROOM + "room11","north",0);
    add_exit(DROOM + "room2","southeast",0);    

    add_item(({"mist"}), 
     "It is a fine, silky mist. It seems to touch you with cold, wet fingers.\n"); 

    add_item(({"dirt"}), 
     "Wind and especially storms seems to have found"+ 
     " their way into the Keep over the centuries and have"+ 
     " blown some things like earth and plants into the keep.\n"); 

    add_item(({"walls", "wall"}), 
     "The walls are pitch-black, absorbing any light touching them."+ 
     " You wonder if only the soot on the walls is the reason for that"+ 
     " or if a more sinister force is at work.\n"); 

    add_item(({"torches"}), 
     "The torches are made of wood with a oily top.\n"); 

    add_item(({"stone floor", "floor"}), 
     "This floor is made of ordinary stone. It seems that because of"+ 
     " practicality normal stone was used in this corridor. Probably"+ 
     " the precious but more delicate stones would have been damaged"+ 
     " in no time.\n"); 
}
