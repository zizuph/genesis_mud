 /* /d/Cirath/athas/a_tyr/jail/room/c29.c
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





  add_exit(TZ_JAIL+"room/c28.c","east",0,1);
  add_exit(TZ_JAIL+"room/c34.c","northeast",0,1);
}


