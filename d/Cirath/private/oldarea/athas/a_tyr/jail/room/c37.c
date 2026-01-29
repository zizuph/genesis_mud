 /* /d/Cirath/athas/a_tyr/jail/room/c37.c
  * A guard lounge.
  * Decius, March 1996
  */

inherit "/std/room";
#include "defs.h"
#include "descs.h"

void create_room()
{
  ::create_room();

  set_short(
    "A guard lounge");






  add_exit(TZ_JAIL+"room/c36.c","east",0,1);
}


