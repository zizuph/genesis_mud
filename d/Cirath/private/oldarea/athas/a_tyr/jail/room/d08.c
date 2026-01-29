 /* /d/Cirath/athas/a_tyr/jail/room/d08.c
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



  add_exit(TZ_JAIL+"room/d09.c","west",0,1);
  add_exit(TZ_JAIL+"room/d07.c","east",0,1);
}

