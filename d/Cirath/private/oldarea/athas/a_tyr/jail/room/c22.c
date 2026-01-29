 /* /d/cirath/athas/a_tyr/jail/room/c22.c
  * Bottom of a staircase.
  * Decius, March 1996
  */

inherit "/std/room";
#include "defs.h"
#include "descs.h"

void create_room()
{
  ::create_room();
  set_short(
    "Bottom of a staircase");






  add_exit(TZ_JAIL+"room/b22.c","up",0,2);
  add_exit(TZ_JAIL+"room/c21.c","east",0,1);
}

