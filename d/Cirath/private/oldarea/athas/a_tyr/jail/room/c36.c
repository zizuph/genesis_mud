 /* /d/Cirath/athas/a_tyr/jail/room/c36.c
  * The entrance to Pandora's Tower.
  * Decius, February 1996
  */

inherit "/std/room";
#include "defs.h"
#include "descs.h"

void create_room()
{
  ::create_room();
  
  set_short(
    "A guardpost at the tower entrance");

 
  

  
  add_exit(TZ_JAIL+"room/c38.c","north",0,1);
  add_exit(TZ_JAIL+"room/c37.c","west",0,1);
  add_exit(TZ_JAIL+"room/c35.c","east",0,1);
  add_exit(TZ_JAIL+"room/c32.c","south",0,1);
}

