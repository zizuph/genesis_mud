 /* /d/Cirath/athas/a_tyr/jail/room/c02.c
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






  add_exit(TZ_JAIL+"room/c06.c","north",0,1);
  add_exit(TZ_JAIL+"room/c03.c","west",0,1);
  add_exit(TZ_JAIL+"room/m34.c","south",0,1);
  add_exit(TZ_JAIL+"room/c01.c","east",0,1);
}



