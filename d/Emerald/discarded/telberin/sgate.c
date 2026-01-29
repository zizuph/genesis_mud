inherit "/std/room";

#include "default.h"

void
create_room()
{
   set_short("South Gate");
   set_long("You arrive before the towering South Gate of Telberin, "+
      "and feel compelled to stare. Shining white walls manned by "+
      "paladins in white and silver hold back the great forests of "+
      "Emerald, and through the towering gate you see crowds of people "+
      "about their daily lives. \n");
   
   add_exit(THIS_DIR + "o1", "north");
   add_exit(OUT_DIR + "p4", "south");
   
   add_item(({"walls","wall"}), "The city wall is made of beautiful white "+
      "marble blocks. They are perfectly cut and glisten in the "+
      "sunlight. \n");
   add_item(({"Gate","gate","south gate"}),"They are currently wide "+
      "open, as the King prefers. The tempered steel grillwork "+
      "of the portcullis could be very effective if it were lowered.\n");
   add_item("castle", "Through the buildings to the northeast "+
      "you can see the towering white castle of the King and "+
      "Queen of Telberin. \n");
   add_item("people", "This seems to be a city of elves. \n");
   add_item(({"trees", "forest"}), "The trees have a serene beauty all "+
      "of their own. They might have even been shaped by magic.\n");
   
   /*
   set_alarm(1.0, 0.0, reset_room);
   */
   
}
