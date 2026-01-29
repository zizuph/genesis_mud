/*
   Pax Tharkas, Wall level, Eastern tower.

   east_tower.c
   ------------

   Coded ........: 95/02/16
   By ...........: Jeremiah

   Latest update : 95/03/11
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
      guard1->team_join(guard3);

      guard1->set_aggressive(1);
      guard2->set_aggressive(1);

      guard1->move(TO);
      guard2->move(TO);
   }
   
   if(!objectp(guard3))
   {
     guard3 = clone_object(PMONSTER+"aurak2");
     guard3->move(TO, 1);
     guard3->set_agressive(1);
   }
}


void
create_pax_room()
{
   reset_pax_room();

   set_short("Eastern tower");
   set_long("You are standing behind the mighty stone battlements of the " +
            "east tower of Pax Tharkas. A large dark pit leads down " +
            "into the heart of the tower. The kharolis mountain range " +
            "blocks the view to the south, east and west. North the " +
            "valley, with its plains and forests, leading up the " +
            "fortress, and its curtain walls, spreads out in front of " +
            "you. South is the huge courtyard and the open iron ore " +
            "mines attached to Pax Tharkas.\n"); 
   OUTSIDE;

   add_item(({"pit", "dark pit"}), "The pit is a huge opening in the " + 
            "tower roof, it looks like it has been made in recent " +
            "times. The opening into the tower hasn't been made with the " +
            "same care as the rest of the tower. The pit leads down into " +
            "the heart of the tower, into darkness. Looking down into " +
            "the darkness below, a strange feeling of fear creeps over " + 
            "you.\n");



   set_alarm(30.0,120.0, "do_breeze");

   add_exit(WALL_LEVEL + "stair_to_etow3", "down", 0);
} 


do_breeze()
{
   tell_room(TO, "A chilly mountain breeze blows gently through " +
             "your hair.\n");
}
