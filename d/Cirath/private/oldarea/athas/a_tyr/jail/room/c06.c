 /* /d/Cirath/athas/a_tyr/jail/room/c06.c
  * A hallway within Pandora's Tower.
  * Decius, March 1996
  */

inherit "/std/room";
#include "defs.h"
#include "descs.h"
void create_room()
{
  ::create_room();
  SHORT_HALLWAY;











  add_exit(TZ_JAIL+"room/c12.c","north",0,1);
  add_exit(TZ_JAIL+"room/c07.c","west",0,1);
  add_exit(TZ_JAIL+"room/c02.c","south",0,1);
  add_exit(TZ_JAIL+"room/c05.c","east",0,1);
}

