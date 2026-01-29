 /* /d/Cirath/athas/a_tyr/jail/room/b32.c
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





  add_exit(TZ_JAIL+"room/b36.c","north",0,1);
  add_exit(TZ_JAIL+"room/b33.c","west",0,1);
  add_exit(TZ_JAIL+"room/b26.c","south",0,1);
  add_exit(TZ_JAIL+"room/b31.c","east",0,1);
}

