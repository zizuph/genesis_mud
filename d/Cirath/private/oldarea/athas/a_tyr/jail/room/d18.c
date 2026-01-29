 /* /d/Cirath/athas/a_tyr/jail/room/d18.c
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



  add_exit(TZ_JAIL+"room/d24.c","north",0,1);
  add_exit(TZ_JAIL+"room/d19.c","west",0,1);
}

