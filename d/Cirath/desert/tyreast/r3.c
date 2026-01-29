inherit "/std/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"
#include "/d/Cirath/common/defs.h"
#include "/d/Cirath/common/mobber.h"


void
create_room()
 {
  set_short("On a road, east of Tyr");
  set_long("The road bends southeast here, while stretching west "
  	+"to the gates of Tyr.  To the north, you can see the "
  	+"Ringing Mountains looming over the desert below.  Many "
  	+"a traveller has wandered into those mountains, only to "
  	+"never be heard from again.  The road is usually safe "
  	+"from marauders, though, fear of Kalak's rage ensures "
  	+"that.\n");
    add_item(({"gate","east gate","champion's gate"}),
    	"Carved through the thick stone walls which surround Tyr, "
    	+"the Champion's Gate is composed of a massive tunnel and "
    	+"the portcullises on either side.  It has kept invaders "
    	+"from breaching Tyr's defences for millenia.\n");
    add_item("road","It is made of earth packed virtually rock "
    	+"hard from use over the ages.\n");
    add_exit(DESERT + "d16","north");
    add_exit(DESERT + "d17","northeast");
    add_exit(DESERT + "d15","northwest");
   add_exit(DESERT + "d13","east");
    add_exit(DESERT + "r2","west");
    add_exit(DESERT + "d9","southwest");
    add_exit(DESERT + "d10","south");
    add_exit(DESERT + "r4","southeast");
}

