 /* /d/Cirath/athas/a_tyr/jail/room/b12.c
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



  add_exit(TZ_JAIL+"room/b13.c","west",0,1);
  add_exit(TZ_JAIL+"room/b06.c","south",0,1);
  add_exit(TZ_JAIL+"room/b11.c","east",0,1);
}

