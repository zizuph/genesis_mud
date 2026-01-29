 /* /d/Cirath/athas/a_tyr/jail/room/d06.c
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


  add_exit(TZ_JAIL+"room/d11.c","north",0,1);
  add_exit(TZ_JAIL+"room/d07.c","west",0,1);
  add_exit(TZ_JAIL+"room/d02.c","south",0,1);
  add_exit(TZ_JAIL+"room/d05.c","east",0,1);
}

