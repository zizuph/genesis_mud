inherit "/std/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"
#include "/d/Cirath/common/defs.h"


void
create_room()
 {
  set_short("Tower Top");
  set_long("You stand at the top of the short tower which houses the "
  	+"members of the Tyrian Militia.  A narrow ladder leads down "
  	+"into the tower itself.  Short battlements ring the tower top, "
  	+"giving you some amount of protection, as well as some barrier "
  	+"between you and the open sky.  The wind blows strongly across "
  	+"the roofs of the city, whipping at your clothes and causing "
  	+"you to squint your eyes from the dust particles as well as the "
  	+"blindingly bright light from the twin suns of Athas.\n");
  add_item("ladder","It is made of sturdy agafari wood and leads down "
  	+"into the guild itself.\n");
  add_item("battlements","These low notched parapets circle the top "
  	+"of the tower, offering some protection to those standing up "
  	+"here.\n");
  add_exit(MILITIA_ROOM + "m10","down");
  add_exit(MILITIA_ROOM + "m13","southwest");
}

