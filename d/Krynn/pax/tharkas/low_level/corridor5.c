/*
   Pax Tharkas, Low level, corridor, stairs to ground level. 

   corridor5.c
   ----------

   Coded ........: 95/01/07
   By ...........: Jeremiah

   Latest update : 95/04/27
   By ...........: Jeremiah

*/


inherit "/d/Krynn/pax/tharkas/misc/Ilamp_base";
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"
#include <filter_funs.h>                 /* filter functions */
#include <composite.h>

inherit PAXINROOM;

#define NCORR \
   ({   \
      LOW_LEVEL + "corridor3", \
   })


object guard1, guard2;

reset_pax_room()
{
   if(!P("kapak",TO))
   {
      guard1 = clone_object(PMONSTER + "kapak");
      guard2 = clone_object(PMONSTER + "kapak");

      guard2->set_leader(guard1);
      guard1->team_join(guard2);

      /* these guards are a bit drunk -> higher dis(5) and lower dex(1) */

      guard1->set_stat_extra(1,-20);
      guard1->set_stat_extra(5,20);
      guard1->add_descr("leaning against the wall");

      guard2->set_stat_extra(1,-20);
      guard2->set_stat_extra(5,20);

      guard1->move(TO);
      guard2->move(TO);
   }
}


create_pax_room()
{
   reset_pax_room();

   add_the_lamp();

   set_short("Corridor in cellar");
   set_long("@@room_descr");

   INSIDE;

   add_item(({"stairs", "staircase"}), "The stairs are look very " +
            "solid. They are made of large greyish stones.\n");

   set_alarm(30.0,360.0,"do_flicker");

   add_exit(LOW_LEVEL + "corridor3", "north", 0);
   add_exit(LOW_LEVEL + "stair_to_gl", "up","@@check_guards", 1);
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
        return ("Looking north, up the corridor, you can see " +
                 COMPOSITE_LIVE(live) + ".\n");
   }
   return ("The corridor back north is empty.\n");
}


string
room_descr()
{
   return "You are standing at the foot of a stone staircase. The " +
          "corridor ends here and the only light source is a small " +
          "iron lamp hanging on the wall. " +
          "There's a vague draft coming from the staircase. " +
          "The corridor leads back north. " + ncorr_descr();
}


void
do_flicker()
{
   tell_room(TO,"The light from the oil lamps flickers.\n");
}


int
check_guards()
{
   string who;

   if (!P("kapak",TO))
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

   return 1;
}

