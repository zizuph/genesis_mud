 /* /d/Cirath/athas/a_tyr/jail/room/b25.c
  * Barracks.
  * Decius, March 1996
  */

inherit "/std/room";
#include "defs.h"
#include "descs.h"

void create_room()
{
  ::create_room();
  SHORT_BARRACKS;






  add_exit(TZ_JAIL+"room/b26.c","west",0,1);
}

