 /* /d/Cirath/athas/a_tyr/jail/room/c30.c
  * In a common lounge.
  * Decius, March 1996
  */

inherit "/std/room";
#include "defs.h"
#include "descs.h"

void create_room()
{
  ::create_room();
  set_short(
    "In a common lounge");
  




  add_exit(TZ_JAIL+"room/c31.c","west",0,1);
  add_exit(TZ_JAIL+"room/c23.c","southeast",0,1);
}

