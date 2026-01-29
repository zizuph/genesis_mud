 /* /d/Cirath/athas/a_tyr/jail/room/c20.c
  * The common barracks.
  * Decius, March 1996
  */

inherit "/std/room";
#include "defs.h"
#include "descs.h"

void create_room()
{
  ::create_room();
  set_short(
    "The common barracks");






  add_exit(TZ_JAIL+"room/c27.c","north",0,1);
  add_exit(TZ_JAIL+"room/c21.c","west",0,1);
  add_exit(TZ_JAIL+"room/c13.c","south",0,1);
  add_exit(TZ_JAIL+"room/c19.c","east",0,1);
}

