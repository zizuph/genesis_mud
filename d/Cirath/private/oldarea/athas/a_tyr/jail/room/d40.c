 /* /d/Cirath/athas/a_tyr/jail/room/d40.c
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




  add_exit(TZ_JAIL+"room/d46.c","north",0,1);
  add_exit(TZ_JAIL+"room/d41.c","west",0,1);
  add_exit(TZ_JAIL+"room/d34.c","south",0,1);
  add_exit(TZ_JAIL+"room/d39.c","east",0,1);
}

