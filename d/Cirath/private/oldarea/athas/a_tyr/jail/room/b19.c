 /* /d/Cirath/athas/a_tyr/jail/room/b19.c
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





  add_exit(TZ_JAIL+"room/a26.c","up",0,1);
  add_exit(TZ_JAIL+"room/b20.c","west",0,1);
  add_exit(TZ_JAIL+"room/b18.c","east",0,1);
}

