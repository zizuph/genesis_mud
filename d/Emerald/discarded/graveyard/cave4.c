inherit "/std/room";

#include "/d/Emerald/defs.h"

void
create_room()
{
   set_short("Large cold cave");
   set_long( "You are standing in a large cave before a pool of "+
      "crystal clear water. On the other side of the pool you can see a "+
      "passage leading north, but the only exit from here is back south.\n"
   );
   
   add_item(({"pool","water"}), "It's a large pool of very clear water. " +
      "However, the water is also icy cold, and you don't think it would be"+
      " a good idea to enter it.\n" );
   
   add_prop(ROOM_I_LIGHT,0);
   add_prop(ROOM_I_INSIDE,1);
   add_prop(ROOM_I_TYPE,ROOM_BEACH);
   
   add_exit(GRAVEYARD_DIR + "cave3","south",0,1);
}


void
init()
{
   ::init();
   add_action("do_enter","enter");
   add_action("do_drink","drink");
}



int
do_enter(string str)
{
   if (str != "pool" && str != "water")
      {
      write("Enter what?\n");
      return 1;
   }
   
   write("You try to enter the pool, but it is just too cold.\n");
   return 1;
}


int
do_drink(string str)
{
   int a;
   int drink_amount=TP->query_stat(SS_CON)*5;
   
   notify_fail("Drink what?\n");
   if (str != "water" && str != "from pool")
      return 0;
   
   if (!(TP->drink_soft(drink_amount,1)))
      {
      write("You try to drink the cool water, but alas! " +
         "Your stomach is full.\n");
      return 1;
   }
   TP->drink_soft(drink_amount);
   write ( "You drink some cool water from the pool. "+
      "You feel very refreshed.\n" );
   
   say( QCTNAME(this_player()) + " drinks from the pool.\n" );
   
   return 1;
}
