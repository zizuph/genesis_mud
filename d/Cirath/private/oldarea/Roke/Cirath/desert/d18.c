inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include "/d/Roke/Cirath/defs.h"
#include <macros.h>

void create_room()
{
  set_short("On a mountain in a desert");
  set_long(break_string(
    "In a desert on the eastern base of a large mountain.\n",60));

  OUTSIDE;

  add_exit(DESERT+"d17","north");
  add_exit(DESERT+"d23","southeast");
  add_exit(DESERT+"d15","southwest");
}
