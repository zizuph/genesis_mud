 /* /d/Cirath/athas/a_tyr/jail/room/c24.c
  * A corridor within Pandora's Tower.
  * Decius, March 1996
  */

inherit "/std/room";
#include "defs.h"
#include "descs.h"

void create_room()
{
  ::create_room();
  SHORT_CORRIDOR;





  add_exit(TZ_JAIL+"room/c31.c","northwest",0,1);
  add_exit(TZ_JAIL+"room/c17.c","south",0,1);
  add_exit(TZ_JAIL+"room/c23.c","east",0,1);
}

