 /* /d/Cirath/athas/a_tyr/jail/room/d02.c
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




  add_exit(TZ_JAIL+"room/d06.c","north",0,1);
  add_exit(TZ_JAIL+"room/d03.c","west",0,1);
  add_exit(TZ_JAIL+"room/d01.c","east",0,1);
}

