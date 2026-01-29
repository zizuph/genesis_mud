 /* /d/Cirath/athas/a_tyr/jail/room/c33.c
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






  add_exit(TZ_JAIL+"room/c34.c","west",0,1);
  add_exit(TZ_JAIL+"room/c28.c","southwest",0,1);
  add_exit(TZ_JAIL+"room/c32.c","east",0,1);
}

