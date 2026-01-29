inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include "/d/Roke/Cirath/defs.h"
#include <macros.h>

void create_room()
{
  set_short("In a desert close to a hill");
  set_long(break_string(
    "You're in a desert, southwest of a large, but not "+
    "so very high, hill with boulders scattered all "+
    "over it.\n",60));

  OUTSIDE;

  add_exit(DESERT+"d37","west");
  add_exit(HILL+"h16","north");
}
