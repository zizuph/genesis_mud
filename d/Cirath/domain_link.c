 /* /d/Cirath/domain_link.c
  * The preload file for Cirath.
  * Decius, December 1996
  */

inherit "/std/domain_link";
#include "/d/Cirath/common/defs.h"

void
preload_link()
{
   preload(CLOCK);
   preload("/d/Cirath/std/room");
   preload("/d/Cirath/ships/kalad/tyr_port");
   preload("/d/Cirath/ships/roke/tyr_port");

   // Gladiator's chest room
   preload("/d/Cirath/athas/gladiator/room/gldchest");
}

void
delete_player(string str)
{

}

