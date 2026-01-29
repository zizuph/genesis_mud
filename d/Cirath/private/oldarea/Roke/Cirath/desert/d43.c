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
    "In a desert, north of a quite large river with "+
    "a bridge crossing it, and "+
    "south of a quite large hill with boulders "+
    "spread all over it.\n",60));

  OUTSIDE;

  add_exit(HILL+"h22","north");
  add_exit(JUNGLE+"road/r7","south");
}
