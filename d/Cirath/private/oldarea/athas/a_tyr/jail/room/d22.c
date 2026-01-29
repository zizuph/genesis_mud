 /* /d/Cirath/athas/a_tyr/jail/room/d22.c
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




  add_exit(TZ_JAIL+"room/d28.c","north",0,1);
  add_exit(TZ_JAIL+"room/d23.c","west",0,1);
  add_exit(TZ_JAIL+"room/d16.c","south",0,1);
  add_exit(TZ_JAIL+"room/d21.c","east",0,1);
}

