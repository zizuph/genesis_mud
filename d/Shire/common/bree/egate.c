#include "defs.h"
inherit STDGATEROOM;

create_gateroom() {
  set_short("Eastern gate of Bree");
  set_long("@@my_long");
  add_exit(ERE_DIR + "erb2", "northeast");
  set_other_room(STAND_DIR + "townr2");
  set_direction("west");


    add_item(({"hills","hill","bree hill"}),
      "Bree Hill fills your view here, climbing gently to a peak some few "+
      "hundred feet above and easily a half-mile away, where you can "+
      "imagine Combe snuggled on its back, and Archet in the distance at "+
      "the edge of the Chetwood. The landscape is much more flat in all "+
      "other directions, save a gentle rolling of slopes. Farther to the "+
      "south and east you can make out the South Downs.\n");
/*  add_item(({"gate","south gate","bree gate"}),
      "The sturdy oak double gates swing on ancient tempered iron hinges, "+
      "keeping the peaceful folk of Bree protected from the wilds of the "+
      "surrounding lands. The gates are always closed at night.\n");
*/  add_item(({"hedge","dike","walls"}),
      "Circling the town of Bree is a deep dike outside of a thick hedge, "+
      "providing ample protection from the elements of the wild.\n");
    add_item(({"guard house","guards"}),
      "Peeking over the hedge wall and iron-bound gate is a small guard "+
      "house, made of sturdy oak logs and a neatly thatched roof.\n");

}

my_long() {
  string str;

  if (gatestate) str = "The gates are open";
  else str = "The gates are closed to keep villains out";
  return break_string("The rolling hills around you meet in a valley here "+
      "below what the locals call Bree Hill. Bree Hill fills your "+
      "field of vision to the north and, and to the south lightly "+
      "forested hills stretch out into the distance. The dike and "+
      "hedge that protects the town of Bree here has a gate of entry, "+
      "and a small thatched guardhouse. The Great East road heads northeast "+
      "from here, into the Chetwood and towards Staddle. "+str+".\n", 70);

}
