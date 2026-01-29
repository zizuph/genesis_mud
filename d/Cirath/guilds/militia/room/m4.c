inherit "/std/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"
#include "/d/Cirath/common/defs.h"


void
create_room()
 {
  set_short("Courtyard");
  set_long("Some wiry scrub plants are growing back here in wild "
  	+"disarray.  You see footprints on the ground that lead in "
  	+"and out of the brush.  This must be the area where people "
  	+"can come to practice the tracking skills they have learned "
  	+"in the training room in the guild.\n");
  add_item(({"men","women"}),"They are all recruits of the militia, "
  	+"trying to keep in shape if they are ever needed.\n");
  add_item("plants","They are small leafless vines that are growing in "
  	+"a tangle near the wall.\n");
  add_item("footprints","They look to be deliberately left footprints "
  	+"used for people to hone their tracking skill.\n");
  	
  add_exit(MILITIA_ROOM + "m5","southwest");
  add_exit(MILITIA_ROOM + "m3","north");

}

