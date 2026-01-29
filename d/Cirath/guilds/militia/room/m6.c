inherit "/std/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"
#include "/d/Cirath/common/defs.h"


void
create_room()
 {
  set_short("Courtyard");
  set_long("Here you see more men and women sparring, but unlike "
  	+"some of the other areas of the courtyard the people are "
  	+"training the unarmed combat forms.  There is striking, "
  	+"grappling and throwing going on, as well as the art of "
  	+"dodging blows.\n");
  add_item(({"men","women"}),"They are all recruits of the militia, "
  	+"trying to keep in shape if they are ever needed.\n");
  	
  add_exit(MILITIA_ROOM + "m7","northwest");
  add_exit(MILITIA_ROOM + "m5","east");

}

