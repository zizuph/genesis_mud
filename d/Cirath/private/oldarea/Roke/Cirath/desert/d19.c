inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include "/d/Roke/Cirath/defs.h"
#include <macros.h>

void create_room()
{
  set_short("In a desert close to a river");
  set_long(break_string(
    "In a desert. North of a river and southeast "+
    "of a large mountain.\n",60));

  OUTSIDE;

  add_exit(DESERT+"d15","northwest");
  add_exit(DESERT+"d25","southeast");
}
