/*
   Pax Tharkas, Low level, guard room.

   rubbles2.c
   ----------

   Coded ........: 95/01/09
   By ...........: Jeremiah

   Latest update : 95/05/08
   By ...........: Jeremiah

*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"

inherit PAXINROOM;

#define I_FOUND_KEY "_i_found_pax_key"

int    key_found = 0;  /* 0 = key NOT found.       */
                       /* 1 = key found, no reset. */
                       /* 2 = key found, reset     */

object guard1, guard2, guard3;

reset_pax_room()
{
   if(key_found)
   {
      if(key_found > 1)
         key_found = 0;
      else
         key_found++;
   }

   if(!present("bozak",TO) && !present("sivak",TO))
   {
      guard1 = clone_object(PMONSTER + "sivak");
      guard2 = clone_object(PMONSTER + "bozak");
      guard3 = clone_object(PMONSTER + "bozak");


      guard2->set_leader(guard1);
      guard3->set_leader(guard1);
      guard1->team_join(guard2);
      guard1->team_join(guard3);

      /* these guards are drunk -> more dis(5) and lower dex(1) */

      guard1->set_stat_extra(1,-20);
      guard1->set_stat_extra(5,20);
      guard1->add_descr("throwing dice");
      
      guard2->set_stat_extra(1,-20);
      guard2->set_stat_extra(5,20);
      guard2->add_descr("throwing dice");

      guard3->set_stat_extra(1,-20);
      guard3->set_stat_extra(5,20);
      guard3->add_descr("slumbering in a chair");

      guard1->move_living("arrives",TO);
      guard2->move_living("arrives",TO);
      guard3->move_living("arrives",TO);
   }
}
 

void
create_pax_room()
{
   reset_pax_room();

   set_short("Guard room");
   set_long("You are in a sparse furnitured room. It looks like this " +
            "room is being used as some sort of guard room. It has " +
            "been equipped to accommodate about 6 persons. " +
            "A few beds are standing along the northern wall and a table " +
            "with some chairs are standing in the middle of room. " +
            "Different kinds of weapon racks, and a small cupboard, are " +
            "hanging on the southern " +
            "wall. A few smashed bottles lie on the floor. An old wooden " +
            "door leads east, and a doorless opening leads west.\n");

   INSIDE;
   add_prop(ROOM_I_LIGHT,1);
   
   add_item(({"bed", "beds"}), "Simple beds build with a wooden frame, " + 
            "and a straw mattress.\n");

   add_item("table", "The table is filled with empty bottles and " +
            "empty wineskins.\n");

   add_item(({"chair", "chairs"}), "These are plain wooden chairs.\n");

   add_item(({"rack", "racks", "weapon rack", "weapon racks"}), "One of " +
            "the racks is used to hold spears, and another to hold " +
            "swords. They are both empty at the moment.\n");

   add_item("cupboard", "@@cupboard_descr");

   add_item(({"bottle", "bottles"}), "There are some on the table, and " +
            "some smashed on the floor. By the smell in here, these are " +
            "definately liquor bottles.\n");

   add_exit(LOW_LEVEL + "corridor4", "west", 0);
   add_exit(LOW_LEVEL + "rubbles2", "east", 0);
}


string
cupboard_descr()
{
   string ret_str = "This is a small wooden cupboard. In the back of " +
                    "it there are a few hooks, on which you can hang " +
                    "things. ";

   if((P("sivak", TO)) || (P("bozak", TO)))
   {
      TP->catch_msg("The draconian guard stops you from getting to " +
                    "the cupboard.\n");

      if(objectp(guard1))
         guard1->command("kill " + L(TP->query_name()));

      if(objectp(guard2))
         guard2->command("kill " + L(TP->query_name()));

      if(objectp(guard3))
         guard3->command("kill " + L(TP->query_name()));

      return "";
   }

   if(key_found)
   {
      ret_str += "Keys maybe?, right now the cupboard is empty.\n";
     
      return ret_str;
   } 

   ret_str += "You find an iron key in the cupboard, and take it.\n";
   tell_room(TO, QCTNAME(TP) + " finds something in the " +
             "small cupboard.\n", TP);
   clone_object(POBJ + "prison_key")->move(TP);
   TP->add_prop(I_FOUND_KEY, 1);
   key_found = 1;

   return ret_str;
}

