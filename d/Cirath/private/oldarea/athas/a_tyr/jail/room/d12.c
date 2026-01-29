 /* /d/Cirath/athas/a_tyr/jail/room/d12.c
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




  add_exit(TZ_JAIL+"room/d11.c","east",0,1);
}

