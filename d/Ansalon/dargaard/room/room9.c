
/************************************************************
 * Area: Dargaard Keep.
 * By  : Ruben
 * Date: June 2001
 * Desc: room_up3 
 *
 *
 *
 ************************************************************/

#include "../local.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>

inherit DARGAARD_IN;

object zombie;
object zombie2;

void
reset_dargaard_room()
{
   if(!objectp(zombie))
   {
      zombie = clone_object(DNPC + "zombie");
      zombie->move(TO);
   }
   if(!objectp(zombie2))
   {
      zombie2 = clone_object(DNPC + "zombie");
      zombie2->move(TO);
   }
}

void
create_dargaard_room()
{
    reset_dargaard_room();
    set_short("Stairway");
    set_long("You are standing at a spiral stairway which leads to the"+
	     " upper levels. The beginning of the stairway is flanked"+
             " by two  posts, each with a dwarven skull on the top."+
	     " The eyes of the skulls glow eerily blue. Two humanoid,"+
	     " burning forms hover over the skulls, most likely the"+
             " skulls' former owners, screaming in eternal but silent"+
 	     " torment, however, providing ample illumination for the"+
             " room and the stairwell. The blackened wall has partly "+
       "collapsed to the west revealing a narrow opening into the darkness."+
	     " The air down here is stale, damp and unnaturally cold."+
	     " Strange sounds can be heard in the distance."+
	     " Ankle-high mist covers the floor which seems"+
             " to have a life of its own.\n"); 
	
    add_exit(DROOM + "room8","north",0);
    add_exit(DROOM + "nowhere","up","@@nowhere",0);
    

    add_item(({"form", "forms"}),
     "The humanoid form is transparent and very shady. You can't"+
     " see its features clearly but you recognize the stout,"+
     " compact form of a dwarven body. It is obviously a damned"+
     " soul who had the bad luck to cross the path of the Death"+
     " Knights. Indeed death holds no honour.\n");

    add_item(({"mist"}),
     "The mist is not high. However, it moves and sometimes it "+
     "seems to reach out with milky white tendrils.\n");    

    add_item(({"gloom candles", "candles"}), 
     "Made of the fat of newborn babies and the blood"+ 
     " of virgins these candles emit no real light but a soft"+ 
     " otherworldy gloom. Rumours have it that powerful mages"+ 
     " who are skilled in the dark art of necromancy use those candles"+ 
     " to summon extraplanar denizens to these realms. This"+ 
     " is made possible because it is said that the candles weaken"+ 
     " the fabric of reality.\n"); 

    add_item(({"dirt"}), 
     "Wind and especially storms seems to have found"+ 
     " their way into the Keep over the centuries and have"+ 
     " blown some things like earth and plants into the keep.\n"); 

    add_item(({"walls", "wall"}), 
     "The walls are pitch-black, absorbing any light touching them."+ 
     " You wonder if only the soot on the walls is the reason for that"+ 
     " or if a more sinister force is at work. The wall to the west "+
     "has south has collapsed revealing a small opening.\n"); 

    add_item(({"torches"}), 
     "The torches are made of wood with a oily top.\n"); 

    add_item(({"stone floor", "floor"}), 
     "This floor is made of ordinary stone. It seems that because of"+ 
     " practicality normal stone was used in this corridor. Probably"+ 
     " the precious but more delicate stones would have been damaged"+ 
     " in no time.\n"); 

    add_item(({"opening", "hole"}),
      "The opening is shrouded in darkness, it is impossible to see anything "+
      "beyond it.\n");

    add_cmd_item(({"opening", "hole"}), ({"enter"}), "@@into_upperDargaard");

}

string
into_upperDargaard()
{
    write("You enter the small opening.\n");
    TP->move_living("into the small opening in the wall.",
      DROOM + "well.c", 1, 0);
    return "";
}

int
nowhere()
{
    write("That stairway is blocked with debris and rubble, you "+
          "are unable to find a way through it.\n");
    return 1;
}
