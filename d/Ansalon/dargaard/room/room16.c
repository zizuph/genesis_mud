
/************************************************************
 * Area: Dargaard Keep.
 * By  : Ruben
 * Date: June 2001
 * Desc: room13 
 *
 *
 *
 ************************************************************/

#include "../local.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>

inherit DARGAARD_IN;

object ghoul;

void
reset_dargaard_room()
{
   if(!objectp(ghoul))
   {
      ghoul = clone_object(DNPC + "ghoul");
      ghoul->move(TO);
   }
}

void
create_dargaard_room()
{
    reset_dargaard_room();
    set_short("A hallway of Dargaard Keep");
    set_long("You are standing at a spiral stairway which leads to the"+
	     " upper levels. The beginning of the stairway is flanked"+
             " by two posts, each with a dwarven skull on the top."+
	     " The eyes of the skulls glow eerily blue. Two humanoid,"+
	     " burning forms hover over the skulls, most likely the"+
             " skulls' former owners, screaming in eternal but silent"+
 	     " torment, however, providing ample illumination for the"+
             " room and the stairwell. Thick layers of dark-brown "+
             "mud cover the lower part of the walls, "+
             "and completely covers the black stone "+
             "floor. An empty brazier stands up against "+
             "the north wall. The hallway continues to "+
             "the south, east and west.\n"); 

    add_item(({"brazier"}), 
     "A flat, pan-like pot attached to a metallic rod. It is"+ 
     " filled with coals for illumination and decoration.\n"); 

    add_item(({"dark-brown mud", "mud"}), 
     "This is a patch of earth holding quite some"+ 
     " moisture and seems to be made of fertile"+ 
     " earth. In some time there might be a plant"+     
     " growing there.\n"); 

    add_item(({"dust"}), 
     "This thick layer of white covers everything. Here and"+ 
     " there the dust was disturbed but you cannot make"+ 
     " out anything.\n"); 

    add_item(({"walls", "wall"}), 
     "The walls are pitch-black, absorbing any light touching them."+ 
     " You wonder if only the soot on the walls is the reason for that"+ 
     " or if a more sinister force is at work.\n"); 

    add_item(({"light"}), 
     "The light seems to be weak and somehow it looks"+ 
     " sickly to you. It adds an eerie aura to the general"+ 
     " gloom.\n"); 

    add_item(({"skull", "skulls"}), 
     "The skulls have a faded yellow color and any skin and flesh on them "+
     "have been removed.\n"); 

    add_exit(DROOM + "room15","east",0);
    add_exit(DROOM + "room13","south",0);
    add_exit(DROOM + "nowhere","up","@@nowhere",0);
    add_exit(DROOM + "room17","west",0);
}

int
nowhere()
{
    write("That stairway is blocked with debris and rubble, you "+
          "are unable to find a way through it.\n");
    return 1;
}

