 /* /d/Cirath/athas/a_tyr/jail/room/d42.c
  * Bottom of the staircase.
  * Decius, March 1996
  */

inherit "/std/room";
#include "defs.h"
#include "descs.h"

void create_room()
{
  ::create_room();
  set_short(
    "Bottom of the staircase");





  add_exit(TZ_JAIL+"room/d09.c","up",0,1);
  add_exit(TZ_JAIL+"room/d41.c","east",0,1);
}

