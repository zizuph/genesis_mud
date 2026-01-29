
/************************************************************
 * Area: Dargaard Keep.
 * By  : Ruben
 * Date: June 2001
 * Desc: room6 
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
    set_short("Supply room");
    set_long("This is a grim place. In a huge room"+
	           " are layer upon layer of corpses. Some"+
             " are in the process of decaying others"+
	           " are already skeletons."+
	           " The stench is nearly overwhelming."+
             " The walls are lined with torches"+
             " their light revealing sickly brown and"+
             " green spots on the walls. These corpses"+
             " are likely to be animated in a case of"+
             " an emergency by Lord Soth or by one of"+
             " the liches.\n"); 

    add_item(({"corpses", "corpse"}), 
     "The corpses seem to lie here already for some time."+ 
     " They are in various states of decay. Worms and "+ 
     " maggots as well as other vermin already feast on them.\n"); 

    add_item(({"dust"}), 
     "This thick layer of white covers everything. Here and"+ 
     " there the dust was disturbed but you cannot make"+ 
     " out anything.\n"); 

    add_item(({"dark-brown mud", "mud"}), 
     "This is a patch of earth holding quite some"+ 
     " moisture and seems to be made of fertile"+ 
     " earth. In some time there might be a plant"+     
     " growing there.\n"); 

    add_item(({"mist"}), 
     "It is a fine, silky mist. It seems to touch you with cold, wet fingers.\n"); 

    add_item(({"skeletons"}), 
     "These skeletons seem to be very old, their bones are not"+ 
     " white but grey. You heard stories of animated corpses"+ 
     " but you doubt that these bones hold any life.\n"); 

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

    add_exit(DROOM + "room18","east",0);
    
}
