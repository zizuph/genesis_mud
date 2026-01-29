 /* /d/Cirath/athas/a_tyr/jail/room/c08.c
  * The common armoury.
  * Decius, March 1996
  */

inherit "/std/room";
#include "defs.h"
#include "descs.h"

void create_room()
{
  ::create_room();
  set_short(
    "The common armoury");






  add_exit(TZ_JAIL+"room/c15.c","northwest",0,1);
  add_exit(TZ_JAIL+"room/c07.c","east",0,1);
}

