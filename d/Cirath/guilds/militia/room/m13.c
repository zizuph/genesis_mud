inherit "/std/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"
#include "/d/Cirath/common/defs.h"


void
create_room()
 {
  set_short("Tower Top");
  set_long("You are at the very peak of the tower which acts as the "
  	+"guildhall for Tyr's militia.  Before you, the city of Tyr "
  	+"spreads out like some vast teeming colony of ants, while "
  	+"outside its protective walls, the harsh reality of the "
  	+"desert sits waiting for the chance to kill any intrepid "
  	+"adventurer foolish enough to journey through its wastes.\n");
  add_item("ladder","It is made of sturdy agafari wood and leads down "
  	+"into the guild itself.\n");
  add_item("battlements","These low notched parapets circle the top "
  	+"of the tower, offering some protection to those standing up "
  	+"here.\n");
  add_exit(MILITIA_ROOM + "m12","northeast");
}

