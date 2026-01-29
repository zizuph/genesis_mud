 /* /d/Cirath/athas/a_tyr/jail/room/b28.c
  * A hallway within Pandora's Tower.
  * Decius, March 1996.
  */

inherit "/std/room";
#include "defs.h"
#include "descs.h"

void create_room()
{
  ::create_room();
  SHORT_HALLWAY;





  add_exit(TZ_JAIL+"room/b29.c","west",0,1);
  add_exit(TZ_JAIL+"room/b21.c","south",0,1);
  add_exit(TZ_JAIL+"room/b33.c","northeast",0,1);
}

