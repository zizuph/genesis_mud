 /* /d/Cirath/athas/a_tyr/jail/room/c10.c
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






  add_exit(TZ_JAIL+"room/c17.c","north",0,1);
  add_exit(TZ_JAIL+"room/c05.c","southwest",0,1);
  add_exit(TZ_JAIL+"room/c09.c","east",0,1);
}

