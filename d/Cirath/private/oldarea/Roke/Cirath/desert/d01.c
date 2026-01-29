inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include "/d/Roke/Cirath/defs.h"
#include <macros.h>

void create_room()
{
  set_short("At a steep in the desert");
  set_long(break_string(
    "West end of desert. Steep cliff and bridge over Durni "+
    "to Dohrath.\n",60));

  OUTSIDE;

  add_exit(DESERT+"d03","east");
}
