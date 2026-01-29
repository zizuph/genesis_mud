 /* /d/Cirath/athas/a_tyr/jail/room/d09.c
  * Top of the staircase.
  * Decius, March 1996
  */


inherit "/std/room";
#include "defs.h"
#include "descs.h"

void create_room()
{
  ::create_room();
  set_short(
    "Top of the staircase");




  add_exit(TZ_JAIL+"room/d42.c","down",0,1);
  add_exit(TZ_JAIL+"room/d08.c","east",0,1);
}

