#include "../local.h"
inherit THIS_DIR+"ex-p";

void
create_map_room()
{
  ::create_map_room();
  remove_exit("north"); // we do not want two exits to north
  // (if properly designed there was no north exit to be removed)
  add_exit(THIS_DIR+"entry", "north", 0, 1); // new exit north
}
