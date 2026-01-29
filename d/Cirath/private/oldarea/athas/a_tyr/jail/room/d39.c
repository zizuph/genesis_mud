 /* /d/Cirath/athas/a_tyr/jail/room/d39.c
  * Dimly lit passage.
  * Decius, March 1996
  */


inherit "/std/room";
#include "defs.h"
#include "descs.h"

void create_room()
{
  ::create_room();
  SHORT_DIMLY;




  add_exit(TZ_JAIL+"room/d45.c","north",0,1);
  add_exit(TZ_JAIL+"room/d40.c","west",0,1);
  add_exit(TZ_JAIL+"room/d33.c","south",0,1);
  add_exit(TZ_JAIL+"room/d38.c","east",0,1);
}

