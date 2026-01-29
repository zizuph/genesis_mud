 /* /d/Cirath/athas/a_tyr/jail/room/b29.c
  * (Sergeant's Quarters ?!)
  * Decius, March 1996
  */

inherit "/std/room";
#include "defs.h"
#include "descs.h"

void create_room()
{
  ::create_room();
  set_short(
    "(Sergeant's Quarters ?!)");





  add_exit(TZ_JAIL+"room/b28.c","east",0,1);
}

