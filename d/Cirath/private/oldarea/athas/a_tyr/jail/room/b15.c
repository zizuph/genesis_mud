 /* /d/Cirath/athas/a_tyr/jail/room/b15.c
  * Storage room.
  * Decius, March 1996
  */


inherit "/std/room";
#include "defs.h"
#include "descs.h"

void create_room()
{
  ::create_room();
  set_short(
    "Storage room");




  add_exit(TZ_JAIL+"room/b14.c","east",0,1);
}

