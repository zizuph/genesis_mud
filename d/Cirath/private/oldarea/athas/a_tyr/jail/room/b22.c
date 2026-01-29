 /* /d/Cirath/athas/a_tyr/jail/room/b22.c
  * Top of a staircase;
  * Decius, March 1996
  */


inherit "/std/room";
#include "defs.h"
#include "descs.h"

void create_room()
{
  ::create_room();
  set_short(
    "Top of a staircase");




  add_exit(TZ_JAIL+"room/c22.c","down",0,1);
  add_exit(TZ_JAIL+"room/b21.c","east",0,1);
}


