/*
   Pax Tharkas, Ground level, Corridor end.

   corridor7.c
   -----------

   Coded ........: 95/01/23
   By ...........: Jeremiah

   Latest update : 95/05/17
   By ...........: Jeremiah

*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"
#include <filter_funs.h>                 /* filter functions */
#include <composite.h>

inherit "/d/Krynn/pax/tharkas/misc/Blamp_base";
inherit PAXINROOM;

#define NCORR \
   ({   \
      GROUND_LEVEL + "corridor5", \
      GROUND_LEVEL + "corridor4", \
   })


object guard1, guard2, guard3, guard4;

reset_pax_room()
{
   if (!present("kapak",TO))
   {
      guard1 = clone_object(PMONSTER + "kapak");
      guard2 = clone_object(PMONSTER + "kapak");
      guard3 = clone_object(PMONSTER + "kapak");
      guard4 = clone_object(PMONSTER + "kapak");

      guard2->set_leader(guard1);
      guard3->set_leader(guard1);
      guard4->set_leader(guard1);

      guard1->team_join(guard2);
      guard1->team_join(guard3);
      guard1->team_join(guard4);

      guard1->move(TO);
      guard2->move(TO);
      guard3->move(TO);
      guard4->move(TO);
   }
}

void
create_pax_room()
{
   reset_pax_room();

   add_the_lamp();

   set_short("End of corridor");
   set_long("@@room_descr");
	
   INSIDE;

   add_exit(GROUND_LEVEL + "corridor5", "north", 0);
   add_exit(GROUND_LEVEL + "playroom", "south", "@@check_guards");
}


string
ncorr_descr()
{
   string *roomfiles;
   object *inv, *live, room;
   int i;

   roomfiles = NCORR;
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
        return ("Looking north, along the corridor, you can see " +
                 COMPOSITE_LIVE(live) + ". ");
   }
   return ("The corridor to the north is empty. ");
}


string
room_descr()
{
   return "You are at the end of a bright corridor. The walls look " +
          "as if they were made of one large piece of solid rock. " +
          "The light from a brass oil lamp fills the room with ample " +
          "light. The corridor goes back north from here. " + 
          ncorr_descr() +
          "An open door in the south end of the corridor leads into " +
          "another room.\n";
}


int
check_guards()
{
   string who;

   if (!present("kapak",TO))
      return 0;

   if (L(TP->query_name()) == "rat" ||
       L(TP->query_name()) == "gully dwarf" ||
	TP->query_dragonarmy_occ_member())
      return 0;

   who = L(TP->query_name());
   write("The draconian guard stops you!\n");
   say(QCTNAME(TP) + " is stopped by the draconian guard.\n");

   if(objectp(guard1))
      guard1->command("kill " + who);

   if(objectp(guard2))
      guard2->command("kill " + who);

   if(objectp(guard3))
      guard3->command("kill " + who);

   if(objectp(guard4))
      guard4->command("kill " + who);

   return 1;
}

