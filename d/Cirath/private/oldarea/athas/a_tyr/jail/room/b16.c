 /* /d/Cirath/athas/a_tyr/jail/room/b16.c
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




  add_exit(TZ_JAIL+"room/b23.c","north",0,1);
  add_exit(TZ_JAIL+"room/b17.c","west",0,1);
  add_exit(TZ_JAIL+"room/b09.c","south",0,1);
}

