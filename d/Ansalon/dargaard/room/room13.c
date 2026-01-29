
/************************************************************
 * Area: Dargaard Keep.
 * By  : Ruben
 * Date: June 2001
 * Desc: room7 
 *
 *
 *
 ************************************************************/

#include "../local.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
inherit DARGAARD_IN;

object skeleton;
object skeleton2;
object skeleton3;

void
reset_dargaard_room()
{
   if(!objectp(skeleton))
   {
      skeleton = clone_object(DNPC + "skeleton");
      skeleton->move(TO);
   }
   if(!objectp(skeleton2))
   {
      skeleton2 = clone_object(DNPC + "skeleton");
      skeleton2->move(TO);
   }
   if(!objectp(skeleton3))
   {
      skeleton3 = clone_object(DNPC + "skeleton");
      skeleton3->move(TO);
   }
}

void
create_dargaard_room()
{
    reset_dargaard_room();
    set_short("A hallway of Dargaard Keep");
    set_long("You find yourself in a gloomy passage "+
             "in Dargaard Keep. Water is dripping down "+
             "the ceiling. The echo reminds you of a "+
             "heart's rhytmic beating. Ankle-high mist "+
             "covers the floor weaving intricate patterns "+
             "and glowing in a sickly green light due to "+
             "the light radiated by some strange fungi you "+
             "haven't seen before. To the north you see a "+
             "well-lit staircase however the other passages "+
             "are lost in the darkness, but you do manage "+
             "to hear a steady splashing of water to the south.\n"); 

    add_exit(DROOM + "room5","south",0);
    add_exit(DROOM + "room16","north",0);

    add_item(({"ground"}), 
     "The ground is even and in a good condition except some"+ 
     " puddles and debris lying around.\n"); 

    add_item(({"mist"}), 
     "It is a fine, silky mist. It seems to touch you with cold, wet fingers.\n"); 

    add_item(({"dark-brown mud", "mud"}), 
     "This is a patch of earth holding quite some"+ 
     " moisture and seems to be made of fertile"+ 
     " earth. In some time there might be a plant"+     
     " growing there.\n"); 

    add_item(({"torches"}), 
     "These are standard torches which you can find everywhere"+ 
     " on Krynn.\n"); 

    add_item(({"fungi"}), 
     "The fungi is covered with slime that smells terribly"+ 
     " Maybe it is a kind of algae or maybe something"+ 
     " entirely different.\n"); 

    add_item(({"stone floor", "floor"}), 
     "This floor is made of ordinary stone. It seems that because of"+ 
     " practicality normal stone was used in this corridor. Probably"+ 
     " the precious but more delicate stones would have been damaged"+ 
     " in no time.\n"); 

    add_item(({"stones","walls", "wall"}),
      "The walls are covered with moss and charred black by "+
      "an intense fire many years ago.\n");

  
}
