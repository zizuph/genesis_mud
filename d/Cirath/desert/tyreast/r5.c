inherit "/std/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"
#include "/d/Cirath/common/defs.h"
#include "/d/Cirath/common/mobber.h"


void
create_room()
 {
  set_short("On a road, southeast of Tyr");
  set_long("The hard packed road leads on.  Back to the west, it "
  	+"will take you towards the great city state of Tyr, "
  	+"while following it further east will pull you further "
  	+"and further into the vast wasteland of Athas.  Somewhat "
  	+"to the south and east also lies the remnants of a huge "
  	+"battle fought during the Cleansing War, the Black "
          +"Wastes.\n");
    add_item(({"gate","east gate","champion's gate"}),
    	"Carved through the thick stone walls which surround Tyr, "
    	+"the Champion's Gate is composed of a massive tunnel and "
    	+"the portcullises on either side.  It has kept invaders "
    	+"from breaching Tyr's defences for millenia.\n");
    add_item("road","It is made of earth packed virtually rock "
    	+"hard from use over the ages.\n");
    add_exit(DESERT + "d12","north");
    add_exit(DESERT + "d11","northeast");
    add_exit(DESERT + "d13","northwest");
    add_exit(DESERT + "r4","west");
    add_exit(DESERT + "d5","southwest");
    add_exit(DESERT + "d4","south");
    add_exit(DESERT + "r6","southeast");
}

