inherit "/std/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"
#include "/d/Cirath/common/defs.h"

void
create_room()
 {
  set_short("Rocky Outcropping");
  set_long("Rocks seem to be piled here, almost forming a corridor "
  	+"leading southward.  You can still move in all directions, "
  	+"but something obviously was herding you southward.\n");
  add_item(({"large rocks","rocks","outcroppings","rocky outcroppings"}),
  	"Large rough edged rocks thrust upward from the ground, some "
  	+"still part of some massive formation, some broken shards "
  	+"of it.\n");
  add_item("shade","A rare thing on Athas, and a thing even rarer to "
  	+"find unoccupied.  Things lurk in the shade, beware.\n");
  add_exit(SOUTH + "d16","west");
  add_exit(SOUTH + "d14","east");
  add_exit(SOUTH + "d17","northwest");
  add_exit(SOUTH + "d18","north");
  add_exit(SOUTH + "d19","northeast");
  add_exit(SOUTH + "d6", "southwest");
  add_exit(SOUTH + "d7", "south");
  add_exit(SOUTH + "d8", "southeast");
}

