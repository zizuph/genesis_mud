 /* /d/Cirath/athas/a_tyr/jail/room/d33.c
  * Jail cell.
  * Decius, March 1996
  */


inherit "/std/room";
#include "defs.h"
#include "descs.h"

void create_room()
{
  ::create_room();
  SHORT_CELL;




  add_exit(TZ_JAIL+"room/d39.c","north",0,1);
}

