inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include "/d/Roke/Cirath/defs.h"
#include <macros.h>

void create_room()
{
  set_short("Near an oasis camp");
  set_long(break_string(
    "In a desert, south of a camp in an oasis.\n",60));

  OUTSIDE;

  add_exit(DESERT+"oasis","north");
  add_exit(DESERT+"d21","east");
}
