inherit "/std/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"
#include "/d/Cirath/common/defs.h"


void
create_room()
 {
  set_short("Courtyard");
  set_long("This is a courtyard that surrounds the headquarters of the "
  	+"Tyrian Militia.  There are men and women here training with "
  	+"polearms and shields, trying to keep prepared in case of an "
  	+"attack on the city.\n");
  add_item(({"men","women"}),"They are all recruits of the militia, "
  	+"trying to keep in shape if they are ever needed.\n");
  	
  add_exit(MILITIA_ROOM + "joinroom","southwest");
  add_exit(MILITIA_ROOM + "m2","east");

}

