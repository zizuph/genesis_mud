#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit FLOTSAM_IN;
object guard1;
object guard2;
object guard3;


void
reset_flotsam_room()
{
   if(!objectp(guard1))
      {
      guard1 = clone_object(FNPC + "guard");
      guard1->arm_me();
      guard1->move(TO);
   }
   if(!objectp(guard2))
      {
      guard2 = clone_object(FNPC + "guard");
      guard2->arm_me();
      guard2->move(TO);
   }
   if(!objectp(guard3))
      {
      guard3 = clone_object(FNPC + "guard");
      guard3->arm_me();
      guard3->move(TO);
   }
}

create_flotsam_room()
{
   set_short("Guardroom");
   set_long("@@long_descr");
   
   add_item(({"bed","beds","un-made beds"}),
      "Very simple, single beds. They " +
      "seem to have been used recently. \n");
   add_item(({"card","cards"}),"On the table is a pack of " +
      "36 cards, each card bearing the symbol of one of the old gods.\n");
   add_item(({"gate","gates"}),"To the west is one of " +
      "the gates that lead out of Flotsam.\n");
   add_item(({"card table","table"}),"A circular card table " +
      "sits in the middle of the room. It looks like the guards " +
      "were playing 'Black Banshee', a game that involves a deck of cards " +
      "that represents the pantheon of the old gods, where the " +
      "highest card is Takhisis, Queen of Darkness. \n");
   
   add_exit(FROOM + "street37","west","@@guard_exit",0);
   
   reset_flotsam_room();
}

string
long_descr()
{
   return "This is a spartan guardroom. At one stage these rooms " +
   "were rarely used and people freely came in and out of these " +
   "gates as they pleased, but after the occupation of the town " +
   "by the Dragonarmies, the gates have been guarded around the " +
   "clock, and these guardrooms are constantly occupied. " +
   "A few un-made beds sit at " +
   "the back of the room, and a card table surrounded " +
   "by chairs stands in its middle. \n";
}

int
guard_exit()
{
   write("You leave the guardroom... \n");
   return 0;
}
