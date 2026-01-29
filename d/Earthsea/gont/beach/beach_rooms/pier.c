/*
* Pier to karg island , created by Ged 6/10/2001
*/

#include "default.h"

inherit SANDY;

object ship;

void restart_ship()
{
 if(!ship)
  {
   ship=clone_object("/d/Earthsea/ships/karg_line/ship");
   ship->move(TO);
   ship->start_ship(0);
  }
 }

void create_beach()
{
 set_short("Small pier");
 set_long("You are standing on the small pier , running straight into "+
   "the open sea. It looks damaged , you wonder what kind of ship "+
   "would land here.\n");

 add_exit(BEACH_DIR+"beach12","north");

 set_alarm(1.0,0.0,&restart_ship());
}

