inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include "/d/Roke/Cirath/defs.h"
#include <macros.h>

void create_room()
{
  set_short("On a mountain in the desert");
  set_long(break_string(
    "Northeast part of desert on north base of "+
    "a mountain.\n",60));

  OUTSIDE;

  add_exit(DESERT+"d05","west");
  add_exit(DESERT+"d12","southeast");
}
