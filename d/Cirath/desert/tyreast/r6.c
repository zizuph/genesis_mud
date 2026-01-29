inherit "/std/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"
#include "/d/Cirath/common/mobber.h"


void
create_room()
 {
  set_short("On a road, southeast of Tyr");
  set_long("Far to your northwest you can still barely see the "
  	+"high defensive walls of Tyr, and to the north, the vague "
  	+"outline of the massive mountains known as the Ringing "
  	+"Mountains.  You are however much more concerned with your "
  	+"current position, which is on a narrow road somewhere "
  	+"in an enormous wasteland.  Storms rage off to the sides of "
  	+"the road, obscuring much of your surroundings.\n");
    add_item(({"gate","east gate","champion's gate"}),
    	"Carved through the thick stone walls which surround Tyr, "
    	+"the Champion's Gate is composed of a massive tunnel and "
    	+"the portcullises on either side.  It has kept invaders "
    	+"from breaching Tyr's defences for millenia.\n");
    add_item("road","It is made of earth packed virtually rock "
    	+"hard from use over the ages.\n");

   add_exit(DESERT + "r5","northwest");
    add_exit(DESERT + "d4","west");
    add_exit(DESERT + "d3","southwest");
   add_exit(DESERT + "r7","southeast","@@block");
}

int
block()
{

      write("The swirling sands creep over the road like "
      	+"a plague, preventing you from going further along it.  "
      	+"For now....\n");
      return 1;
  return 0;
}

