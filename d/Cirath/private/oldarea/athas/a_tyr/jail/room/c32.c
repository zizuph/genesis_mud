 /* /d/Cirath/athas/a_tyr/jail/room/c32.c
  * An intersection south of the entrance.
  * Decius, March 1996
  */

inherit "/std/room";
#include "defs.h"
#include "descs.h"

void create_room()
{
  ::create_room();
  set_short(
    "An intersection south of the entrance");






  add_exit(TZ_JAIL+"room/c36.c","north",0,1);
  add_exit(TZ_JAIL+"room/c33.c","west",0,1);
  add_exit(TZ_JAIL+"room/c26.c","south",0,1);
  add_exit(TZ_JAIL+"room/c31.c","east",0,1);
}

