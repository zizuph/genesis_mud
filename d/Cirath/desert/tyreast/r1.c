inherit "/std/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"
#include "/d/Cirath/tyr/tyr.h"
#include "/d/Cirath/common/defs.h"
#include "/d/Cirath/common/mobber.h"

void
create_room()
 {
  set_short("On a road, east of Tyr");
  set_long("The desert of Athas is a harsh place, even so close to "
  	+"the city of Tyr.  Towering west of you is the east gate, "
  	+"also known as the Champion's Gate.  The hard packed "
  	+"earth road continues to the east before winding off "
  	+"into the swirling dust and sand that blankets the "
  	+"land here.\n");
    add_item(({"gate","east gate","champion's gate"}),
    	"Carved through the thick stone walls which surround Tyr, "
    	+"the Champion's Gate is composed of a massive tunnel and "
    	+"the portcullises on either side.  It has kept invaders "
    	+"from breaching Tyr's defences for millenia.\n");
    add_item("road","It is made of earth packed virtually rock "
    	+"hard from use over the ages.\n");
    add_item(({"portcullis","portcullises"}),"They are made of "
    	+"huge pieces of granite bound in iron.  Large iron "
    	+"spiked protrude from the front and bottom of them.\n");
    add_exit(DESERT + "d14","north");
    add_exit(DESERT + "d15","northeast");
    add_exit(DESERT + "r2","east");
    add_exit(DESERT + "d8","south");
    add_exit(DESERT + "d9","southeast");
   add_exit(TYR_GATES + "champgate","west");
}

