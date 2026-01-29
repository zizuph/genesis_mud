 /* /d/Cirath/athas/a_tyr/jail/room/c25.c
  * In the common barracks. 
  * Decius, March 1996
  */

inherit "/std/room";
#include "defs.h"
#include "descs.h"

void create_room()
{
  ::create_room();
  set_short(
    "In the common barracks");





  add_exit(TZ_JAIL+"room/c26.c","west",0,1);
  add_exit(TZ_JAIL+"room/c18.c","south",0,1);
}

