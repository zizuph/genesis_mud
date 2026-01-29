inherit "/std/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"
#include "/d/Cirath/common/defs.h"


void
create_room()
 {
  set_short("Courtyard");
  set_long("The wind blows faintly through the corner of the militia "
  	+"headquarters, causing dust to dance erratically in the air.  "
  	+"It is very quiet here, almost serene, but it is a rare place "
  	+"indeed in Athas where absolute serenity can be found.\n");
  add_item(({"men","women"}),"They are all recruits of the militia, "
  	+"trying to keep in shape if they are ever needed.\n");
  	
  add_exit(MILITIA_ROOM + "m6","west");
  add_exit(MILITIA_ROOM + "m4","northeast");

}

