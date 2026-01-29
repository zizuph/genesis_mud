
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

    add_exit(DROOM + "room5","west",0);
    add_exit(DROOM + "room7","east",0);


    add_item(({"torches"}), 
     "The torches are made of wood with a oily top.\n"); 

    add_item(({"stones","walls", "wall"}),
      "The walls are covered with moss and charred black by "+
      "an intense fire many years ago.\n");

    add_item(({"dark-brown mud", "mud"}), 
     "This is a patch of earth holding quite some"+ 
     " moisture and seems to be made of fertile"+ 
     " earth. In some time there might be a plant"+     
     " growing there.\n"); 

    add_item(({"moss"}), 
     "The moss has a black-green color and covers all the walls here.\n"); 

    add_item(({"dirt"}), 
     "Wind and especially storms seems to have found"+ 
     " their way into the Keep over the centuries and have"+ 
     " blown some things like earth and plants into the keep.\n"); 

    add_item(({"mist"}), 
     "It is a fine, silky mist. It seems to touch you with cold, wet fingers.\n"); 




    reset_dargaard_room();
}

