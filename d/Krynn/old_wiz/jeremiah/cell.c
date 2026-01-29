/*
   Pax Tharkas, Ground level, prison cell.

   cell.c
   ------

   Coded ........: 95/01/25
   By ...........: Jeremiah

   Latest update : 95/05/19
   By ...........: Jeremiah

*/


#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"

inherit PAXINROOM;

#define I_AM_PRISONER "_live_i_am_pax_prisoner"

object door;
/* object other_room = GROUND_LEVEL + "corridor2"; */
object other_room = "/d/Krynn/jeremiah/corridor2";
int rat_alarm, gully_alarm1, gully_alarm2, gully_alarm3;


void
create_pax_room()
{
   set_short("Prison cell");
   set_long("You are standing in a very spartan furnitured room. " +
            "The room looks almost too much like a prison cell. The " +
            "walls are made of dark grey rock, giving the cell a " +
            "gloomy appearance. You wouldn't want to get stuck in " +
            "here. A narrow rickety folding bed and a small " +
            "table, both made of wood, is all thats in here. " +
            "The only way out of here is through the door.\n");
	
   INSIDE;

   add_item(({"bed", "folding bed"}), "It's an old rickety folding " +
            "bed, it doesn't look comfortable at all.\n");

   add_item(({"table", "small table"}), "A small wooden table. The " +
            "surface area not larger than that of a small shield.\n");
  
   add_item(({"wall", "walls"}), "Dark grey stone walls, made of " +
            "tightly fitted large pieces of rock. There is a gaping " +
            "crack between some of the rocks near the floor, in the " +
            "east wall.\n");
   
   add_item(({"rock", "rocks"}), "The walls are build of these " +
            "tightly fitted large pieces of dark rock. There is " +
            "a gaping crack between some of the rocks, near the " +
            "floor, in the east wall.\n"); 

   add_item("crack", "A crack between some of the large rocks, near " +
            "the floor, in the east wall. The crack is, at it widest " +
            "place, as wide as a hand. The crack smells terribly of " +
            "rat.\n"); 

   add_exit("/d/Krynn/jeremiah/corridor2", "south", 0);

/*
   door = clone_object(POBJ + "cell_door1b");
   door->move(TO);
*/
}


init()
{
   ::init();
   add_action("my_drop", "drop");
}


int
my_drop()
{
   return 0;
}


void
gully_bring_food()
{
   tell_room(TO, "A gully arrives, and gives you some food.\n");
   gully_alarm1 = 0;
}


void
bring_out_rat()
{
   tell_room(TO, "A grey hairy rat peeks out of the crack in the " +
             "wall and looks quickly around.\n");

   if(present("_bread_", TO))
   {
      tell_room(TO, "The rat eyes the piece of bread on the floor " +
                "and scurries over to it.\n");
      clone_object(PMONSTER + "cell_rat")->move(TO);
      return;
   }
   tell_room(TO, "The rat dissapears back into the crack again.\n");
}


void
gully_check_on_prisoner()
{
   tell_room(TO, "A gully arrives, and looks around, then leaves " +
             "again.\n");
   gully_alarm2 = 0;
}


void
gully_forget_door()
{
   tell_room(TO, "A gully arrives, looks around and leaves, " +
             "forgetting to lock the door.\n");
   gully_alarm3 = 0;
}


void
start_prisoner_sequence()
{
   rat_alarm = set_alarm(90.0, 90.0, "bring_out_rat");
   gully_alarm1 = set_alarm(30.0, 0.0, "gully_bring_food");   
   gully_alarm2 = set_alarm(240.0, 0.0, "gully_check_on_prisoner");
   gully_alarm3 = set_alarm(600.0, 0.0, "gully_forget_door");
}


void
remove_rat_alarm()
{
   remove_alarm(rat_alarm);
}


void
enter_inv(object ob, object from)
{
   if(living(ob))
   {
      if(ob->query_prop(I_AM_PRISONER))
      {
         start_prisoner_sequence();
         find_living("jeremiah")->catch_msg("RATS!\n");
      }
   }
   ::enter_inv(ob, from);
}


void
leave_inv(object ob, object to)
{
   if(living(ob))
   {
      if(ob->query_prop(I_AM_PRISONER))
      {
         ob->remove_prop(I_AM_PRISONER);
         if(gully_alarm1)
            remove_alarm(gully_alarm1);
         if(gully_alarm2)
            remove_alarm(gully_alarm2);
         if(gully_alarm3);
            remove_alarm(gully_alarm3);
         remove_rat_alarm();
      }
   }
   ::leave_inv(ob, to);
}
