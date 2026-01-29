/*
   Pax Tharkas, Wall level, Western tower.

   west_tower.c
   ------------

   Coded ........: 95/03/03
   By ...........: Jeremiah

   Latest update : 95/03/23
   By ...........: Jeremiah

*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"

inherit PAXINROOM;

object guard1, guard2, guard3;

reset_pax_room()
{
   if(!P("sivak",TO))
   {
      guard1 = clone_object(PMONSTER + "sivak");
      guard2 = clone_object(PMONSTER + "sivak");

      guard2->set_leader(guard1);
      guard1->team_join(guard2);

      guard1->set_aggressive(1);
      guard1->add_descr("sitting on the parapet");
      guard2->set_aggressive(1);

      guard1->move(TO);
      guard2->move(TO);
   }

   if(!objectp(guard3))
   {
     guard3 = clone_object(PMONSTER + "aurak2");
     guard3->move(TO, 1);
     guard3->set_aggressive(1);
   }
}


void
create_pax_room()
{
   reset_pax_room();

   set_short("Eastern tower");
   set_long("You are standing behind the mighty stone battlements of the " +
            "west tower of Pax Tharkas. The kharolis mountain range " +
            "blocks the view to the south, east and west. North the " +
            "valley, with its plains and forests, leading up the " +
            "fortress, and its curtain walls, spreads out in front of " +
            "you. South you see the huge courtyard and the open iron " +
            "ore mines attached to Pax Tharkas.\n"); 
   OUTSIDE;

   set_alarm(30.0,120.0, "do_breeze");

   add_exit(WALL_LEVEL + "stair_to_wtow3", "down", 0);
} 


do_breeze()
{
   tell_room(TO, "A chilly mountain breeze gently sweeps across the " +
             "tower.\n"); 
}
