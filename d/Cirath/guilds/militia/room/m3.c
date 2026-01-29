inherit "/std/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"
#include "/d/Cirath/common/defs.h"


void
create_room()
 {
  set_short("Courtyard");
  set_long("You are at the back side of the courtyard surrounding "
  	+"the militia's headquarters.  It is quiet and out of the "
  	+"way, the perfect place for a warrior to gain a moment's "
  	+"respite from the activity of the guildhall in general.\n");
  add_item(({"men","women"}),"They are all recruits of the militia, "
  	+"trying to keep in shape if they are ever needed.\n");
  add_item("plants","They are small leafless vines that are growing in "
  	+"a tangle near the wall.\n");
  add_item("footprints","They look to be deliberately left footprints "
  	+"used for people to hone their tracking skill.\n");
  	
  add_exit(MILITIA_ROOM + "m4","south");
  add_exit(MILITIA_ROOM + "m2","northwest");

}

