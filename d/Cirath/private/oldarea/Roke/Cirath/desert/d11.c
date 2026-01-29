inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include "/d/Roke/Cirath/defs.h"
#include <macros.h>

void create_room()
{
  set_short("By a river in the desert");
  set_long(break_string(
    "Southeast part of desert close to a mountain and "+
    "north of a river.\n",60));

  OUTSIDE;

  add_exit(DESERT+"d10","north");
  add_exit(DESERT+"d07","west");
}
