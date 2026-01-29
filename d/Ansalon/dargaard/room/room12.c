
/**  DARGAARD KEEP ROOM **/

#include "/d/Ansalon/dargaard/local.h"
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
    set_short("A well-lit corridor in Dargaard Keep");
    set_long("You are standing in a well-lit corridor in Dargaard "+
             "Keep. "+ 
	           "This passage is also in a state of decay, however "+
	           "some sconces on the wall provied illiumination as well "+
             "as some strange mosses which emanate a sickly green "+
             "light. The whole passage is also very damp providing "+
             "excellent life condition for those mosses.\n"); 

    add_exit(DROOM + "room11","west",0);
    add_exit(DROOM + "room5","east",0);

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

    add_item(({"moss"}), 
     "The moss is covered with slime that smells terribly"+ 
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

    reset_dargaard_room();
}

