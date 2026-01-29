inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include "/d/Roke/Cirath/defs.h"
#include <macros.h>

void create_room()
{
  set_short("In the eastern part of a desert");
  set_long(break_string(
    "You're in the eastern part of a sand desert. You "+
    "wonder if anybody could live here. West of you "+
    "are some massive mountains and northeast, you can "+
    "see a hill of some kind.\n",60));

  OUTSIDE;

  add_exit(DESERT+"d36","west");
  add_exit(DESERT+"d39","east");
  add_exit(DESERT+"d38","south");
}
