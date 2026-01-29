 /* /d/Cirath/athas/a_tyr/jail/room/c26.c
  * The entrance to the common barracks.
  * Decius, March 1996
  */

inherit "/std/room";
#include "defs.h"
#include "descs.h"

void create_room()
{
  ::create_room();
  set_short(
    "The entrance to the common barracks");





  add_exit(TZ_JAIL+"room/c32.c","north",0,1);
  add_exit(TZ_JAIL+"room/c27.c","west",0,1);
  add_exit(TZ_JAIL+"room/c19.c","south",0,1);
  add_exit(TZ_JAIL+"room/c25.c","east",0,1);
}

