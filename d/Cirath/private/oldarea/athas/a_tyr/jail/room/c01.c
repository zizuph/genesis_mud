 /* /d/Cirath/athas/a_tyr/jail/room/c01.c
  * A storage room.
  * Decius, March 1996
  */

inherit "/std/room";
#include "defs.h"
#include "descs.h"

void create_room()
{
  ::create_room();
  set_short(
    "A storage room");






  add_exit(TZ_JAIL+"room/c02.c","west",0,1);
}

