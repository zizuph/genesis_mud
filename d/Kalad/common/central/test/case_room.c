inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

/* modified by Antharanos */


#define SHOWCASE CENTRAL(test/showcase)


void
create_room()
{
   object basket;
   
   ::create_room();
   hear_bell = 3; /*loud: central district outdoors */
   
   set_short("five-way Intersection");
   set_long(
      "You are standing in a five-way intersection. " +
      "Market Street, High Street, and Caravan Street " +
      "lead off to the northwest, north, and northeast " +
      "respectively. To the south,a short wall " +
      "runs along massive cliffs and Precipice " +
      "Run follows it to the east and west. It is just " +
      "high enough to prevent accidents without blocking " +
      "the stunning view of the Bay of Kabal. " +
      "Huge wooden cranes lower straw baskets and iron " +
      "platforms to transport goods and passangers down the " +
      "side of the cliff to the city's port below. " +
      "Three of these winches are in operation, and several more " +
      "hang useless nearby.\n"+
      "A large sign has been planted here.\n");
   add_item("sign","@@sign");
   add_cmd_item("sign","read","@@sign");
   add_item(({"short wall","wall"}),"A stone wall that prevents people "+
      "and trade goods from falling off the cliff.\n");
   add_item(({"bay of kabal","bay"}),"A magnificent blue bay, whose "+
      "expansive waters sparkle in the Kaladian sun.\n");
   add_item(({"huge wooden cranes","huge cranes","wooden cranes","cranes","crane"}),
      "Large contraptions used in lowering people and goods to the Port "+
      "District below.\n");
   add_item(({"winches","winch"}),"The machines used to lower items "+
      "to the port at the bottom of the cliff.\n");
   add_exit(CENTRAL(market/s0),"northwest");
   add_exit(CENTRAL(high/s5),"north");
   add_exit(CENTRAL(caravan/s9),"northeast");
   add_exit(TRADE(cliffside/cliffside8),"east");

/*   
   basket=clone_object("/d/Kalad/common/port/basket");
   basket->move(this_object());
*/

   reset_room();
}


reset_room()
{
   SHOWCASE->load_me();
   if (!present(find_object(SHOWCASE)))
      SHOWCASE->move(TO);
}


come_and_go(which)
{
   object liftbasket,realbasket;
   liftbasket=present("basket",this_object());
   if(which==0&&!liftbasket) {   /* 0 = arriving, 1 = leaving  */
      realbasket=clone_object("/d/Kalad/common/port/basket");
      realbasket->move(this_object());
      tell_room(this_object(),
         "The basket arrives from below. Now you may board it, for it will soon\n"+
         "leave.\n");
      return 1;
   }
   if(which==1&&liftbasket) {
      realbasket=present("basket",this_object());
      "secure/master"->do_debug("destroy",realbasket);
      tell_room(TO,
         "The basket leaves for the port below.\n");
      return 1;
   }
}


sign()
{
   return "Access to the Market District is presently unavailable to "+
   "foreigners. Access may be granted barring the decision of the "+
   "City Council. You are duly encouraged to return back to the Port "+
   "District below, or to the Central District in the north, or Trade "+
   "District in the east.\n";
}
