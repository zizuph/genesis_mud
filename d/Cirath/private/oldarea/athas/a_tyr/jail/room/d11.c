 /* /d/Cirath/athas/a_tyr/jail/room/d11.c
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




  add_exit(TZ_JAIL+"room/d12.c","west",0,1);
  add_exit(TZ_JAIL+"room/d06.c","south",0,1);
  add_exit(TZ_JAIL+"room/d10.c","east",0,1);
}

