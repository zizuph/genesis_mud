inherit "/std/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"
#include "/d/Cirath/common/defs.h"


void
create_room()
 {
  set_short("Courtyard");
  set_long("The wall bends to the southeast here and heads back to the "
  	+"west as well.  This area has a few members of the militia "
  	+"doing physical training.  There are men and women doing "
  	+"calisthenics, some running, doing push-ups, all sorts of "
  	+"work-out routines.  The air is hot and dry here, as always, "
  	+"but these hardy soldiers seem not to mind.\n");
  add_item(({"men","women"}),"They are all recruits of the militia, "
  	+"trying to keep in shape if they are ever needed.\n");
  add_item("plants","They are small leafless vines that are growing in "
  	+"a tangle near the wall.\n");
  add_item("footprints","They look to be deliberately left footprints "
  	+"used for people to hone their tracking skill.\n");
  	
  add_exit(MILITIA_ROOM + "m3","southeast");
  add_exit(MILITIA_ROOM + "m1","west");

}

