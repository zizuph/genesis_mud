 /* /d/Cirath/athas/a_tyr/jail/room/c04.c
  * The mess hall.
  * Decius, March 1996
  */

inherit "/std/room";
#include "defs.h"
#include "descs.h"

void create_room()
{
  ::create_room();
  set_short(
    "The mess hall");






  add_exit(TZ_JAIL+"room/c05.c","west",0,1);
  add_exit(TZ_JAIL+"room/c09.c","northeast",0,1);
}

