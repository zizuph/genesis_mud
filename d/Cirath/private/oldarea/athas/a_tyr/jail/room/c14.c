 /* /d/Cirath/athas/a_tyr/jail/room/c14.c
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






  add_exit(TZ_JAIL+"room/c21.c","north",0,1);
  add_exit(TZ_JAIL+"room/c15.c","west",0,1);
  add_exit(TZ_JAIL+"room/c07.c","southeast",0,1);
}


