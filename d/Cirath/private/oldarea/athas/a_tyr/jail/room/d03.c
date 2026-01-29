 /* /d/Cirath/athas/a_tyr/jail/room/d03.c
  * Kitchen.
  * Decius, March 1996
  */


inherit "/std/room";
#include "defs.h"
#include "descs.h"

void create_room()
{
  ::create_room();
  set_short(  
    "Kitchen");



  add_exit(TZ_JAIL+"room/d02.c","east",0,1);
}

