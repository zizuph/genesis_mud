inherit "/std/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"
#include "/d/Cirath/common/defs.h"


void
create_room()
 {
  set_short("Courtyard");
  set_long("The sound of staffs and spears slapping against shields "
  	+"is quite loud here.  There are a number of militia members "
  	+"mock fighting with practice weapons, trying to learn the "
  	+"intricacies of the spear and shield style.\n");
  add_item(({"men","women"}),"They are all recruits of the militia, "
  	+"trying to keep in shape if they are ever needed.\n");
  	
  add_exit(MILITIA_ROOM + "joinroom","north");
  add_exit(MILITIA_ROOM + "m6","southeast");

}

