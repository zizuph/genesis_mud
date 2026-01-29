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
  set_long("The road begins a gradual sloping southward here, "
  	+"heading towards the other civilized parts of Athas.  "
  	+"Continuing in this direction will bring you far to the "
   +"southeast of here, through the Black Wastes, and "
  	+"eventually, on to Urik.\n");
    add_item(({"gate","east gate","champion's gate"}),
    	"Carved through the thick stone walls which surround Tyr, "
    	+"the Champion's Gate is composed of a massive tunnel and "
    	+"the portcullises on either side.  It has kept invaders "
    	+"from breaching Tyr's defences for millenia.\n");
    add_item("road","It is made of earth packed virtually rock "
    	+"hard from use over the ages.\n");
    add_exit(DESERT + "d13","north");
    add_exit(DESERT + "d12","northeast");
    add_exit(DESERT + "r3","northwest");
    add_exit(DESERT + "r5","east");
    add_exit(DESERT + "d10","west");
    add_exit(DESERT + "d6","southwest");
    add_exit(DESERT + "d5","south");
    add_exit(DESERT + "d4","southeast");
}

