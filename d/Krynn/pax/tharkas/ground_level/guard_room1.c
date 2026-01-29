/*
   Pax Tharkas, Ground level, Guard room in west tower.

   guard_room1.c
   -------------

   Coded ........: 95/03/02
   By ...........: Jeremiah

   Latest update : 95/05/07
   By ...........: Jeremiah

*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"
#include <filter_funs.h>                 /* filter functions */
#include <composite.h>

inherit PAXINROOM;

#define WROOM \
   ({   \
      GROUND_LEVEL + "guard_room2", \
   })

object guard1, guard2, guard3;
object patrol_leader1, patrol1a, patrol1b, patrol1c;
object patrol_leader2, patrol2a, patrol2b, patrol2c; 

void
reset_patrol1()
{
   if(objectp(patrol_leader1))
      return;

   patrol_leader1 = clone_object(PMONSTER + "sivak_leader1");
   patrol1a = clone_object(PMONSTER + "bozak");
   patrol1b = clone_object(PMONSTER + "bozak");
   patrol1c = clone_object(PMONSTER + "bozak");

   patrol1a->set_leader(patrol_leader1);
   patrol1b->set_leader(patrol_leader1);
   patrol1c->set_leader(patrol_leader1);

   patrol_leader1->team_join(patrol1a);
   patrol_leader1->team_join(patrol1b);
   patrol_leader1->team_join(patrol1c);

   patrol_leader1->set_aggressive(1);
   patrol1a->set_aggressive(1);
   patrol1b->set_aggressive(1);
   patrol1c->set_aggressive(1);

   patrol_leader1->move_living("arrives", TO);
   patrol1a->move_living("arrives", TO);
   patrol1b->move_living("arrives", TO);
   patrol1c->move_living("arrives", TO);
}


void
reset_patrol2()
{
   if(objectp(patrol_leader2))
      return;

   patrol_leader2 = clone_object(PMONSTER + "sivak_leader2");
   patrol2a = clone_object(PMONSTER + "bozak");
   patrol2b = clone_object(PMONSTER + "kapak");
   patrol2c = clone_object(PMONSTER + "bozak");

   patrol2a->set_leader(patrol_leader2);
   patrol2b->set_leader(patrol_leader2);
   patrol2c->set_leader(patrol_leader2);

   patrol_leader2->team_join(patrol2a);
   patrol_leader2->team_join(patrol2b);
   patrol_leader2->team_join(patrol2c);

   patrol_leader2->set_aggressive(1);
   patrol2a->set_aggressive(1);
   patrol2b->set_aggressive(1);
   patrol2c->set_aggressive(1);

   patrol_leader2->move_living("arrives", TO);
   patrol2a->move_living("arrives", TO);
   patrol2b->move_living("arrives", TO);
   patrol2c->move_living("arrives", TO);
}


void
reset_pax_room()
{
   set_alarm(3.0, 0.0, "reset_patrol1");
   set_alarm(6.0, 0.0, "reset_patrol2");

   if(objectp(guard1) || objectp(guard2) || objectp(guard3))
      return;
     
   guard1 = clone_object(PMONSTER + "sivak");
   guard2 = clone_object(PMONSTER + "sivak");
   guard3 = clone_object(PMONSTER + "bozak");

   guard2->set_leader(guard1);
   guard3->set_leader(guard1);
   
   guard1->team_join(guard2);
   guard1->team_join(guard3);

   guard1->add_descr("sitting in a chair");
   guard2->add_descr("sharpening his sword");

   guard1->move_living("arrives", TO, 0);
   guard2->move_living("arrives", TO, 0);
   guard3->move_living("arrives", TO, 0);
}


void
create_pax_room()
{
   reset_pax_room();

   set_short("East end of guard room");
   set_long("@@room_descr");
	
   INSIDE;

   add_item("wall", "Grey walls of stone. There's a strange drawing on " +
            "one of the walls.\n");

   add_item("drawing", "It is a drawing of a mountain with two dark " +
            "caverns near the top, and a large stalagmite and stalactite " +
            "filled cave entrance. You realize that it looks somewhat like " +
            "a huge humanoid skull. This drawing does look newer than the " +
            "rest of the things in here.\n");

   add_item(({"table", "large table"}), "This is a heavy oak wood table. " +
            "The table is twice as long as it is wide, and quite a large " +
            "number of people could sit here. It looks very used. The " +
            "table is filled with dirty tin plates and more or less " +
            "filled mugs.\n");

   add_item(({"plates", "tin plates"}), "Old tin plates, filthy with " +
            "leftovers from more than one meal.\n");

   add_item(({"mug", "mugs"}), "These are clay mugs all of them more or " +
            "less filled with some kind of liquid. Wine maybe.\n");
 
   add_exit(GROUND_LEVEL + "hallway2", "east", 0);
   add_exit(GROUND_LEVEL + "guard_room2", "west", 0);
   add_exit(GROUND_LEVEL + "large_w_prison", "south", 0);
}


string
wroom_descr()
{
   string *roomfiles;
   object *inv, *live, room;
   int i;

   roomfiles = WROOM;
   inv = ({});

   for (i = 0; i < sizeof(roomfiles); i++)
   {
      if ((room = find_object(roomfiles[i])) != 0)
         inv += all_inventory(room);
   }

   if (inv && sizeof(inv) > 0)
   {
     live = FILTER_LIVE(inv);
     if (sizeof(live) > 0)
        return ("In the other end of the guard room you see " +
                 COMPOSITE_LIVE(live) + ". ");
   }
   return ("The other end of the guard room is empty. ");
}


string
room_descr()
{
   return "You enter a very large room, a guard room by the look of it. " +
          "You are standing in the east end of the room. A large table " +
          "with lots of chairs, stands near this end. " + wroom_descr() +
          "Someone has made a drawing of a strange looking mountain on " +
          "the wall.\n"; 
} 
