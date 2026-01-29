 /* /d/Cirath/athas/a_tyr/jail/room/d10.c
  * Laundry room.
  * Decius, March 1996
  */


inherit "/std/room";
#include "defs.h"
#include "descs.h"

void create_room()
{
  ::create_room();
  set_short(
    "Laundry room");




  add_exit(TZ_JAIL+"room/d11.c","west",0,1);
}

