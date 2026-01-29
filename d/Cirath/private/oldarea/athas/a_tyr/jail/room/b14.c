 /* /d/Cirath/athas/a_tyr/jail/room/b14.c
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





  add_exit(TZ_JAIL+"room/b21.c","north",0,1);
  add_exit(TZ_JAIL+"room/b15.c","west",0,1);
  add_exit(TZ_JAIL+"room/b07.c","southeast",0,1);
}

