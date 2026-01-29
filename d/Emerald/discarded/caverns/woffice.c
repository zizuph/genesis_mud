/*
 * OFFICE.c
 * This is a beer office.
 * - Alaron Janauary 1997
 */

#include <stdproperties.h>
#include "defs.h"

inherit BASECAVE;

void
create_cave()
{
   set_short("Beer Office");
   set_long("   You are standing in a sparsely furnished office. Despite "+
	    "the fact that it is an office, the cave walls remain intact, "+
	    "still dripping water endlessly from the ceiling to the floor, "+
	    "creating little streams of water flowing in different "+
	    "directions. There is a broken desk covered with scattered "+
	    "papers and scrolls in the back of the room. Several large "+
	    "lamps keep the room warm and feeling relatively dry compared "+
	    "to the rest of the caverns. There is a large sign posted "+
	    "above the desk.\n\n");

   add_prop(ROOM_I_INSIDE, 1);

   add_item(({"lamp", "lamps", "large lamps"}),
	    "The lamps are large and oil-burning, creating a nice "+
	    "warm, sweet-smelling feel to the entire room. It is "+
	    "not, however, quite warm enough to keep the cave walls "+
	    "dry.\n");

   add_item(({"desk","broken desk"}),
	    "The desk is made of the finest rosewood in Emerald by the best "+
	    "of Goblin woodworkers in all of Genesis. At one point "+
	    "it must have been a priceless possession, and could even "+
	    "have been worthy of placing in a museum. The carving "+
	    "of one solid piece of wood into a desk is no small task "+
	    "for any woodworker. Now, the desk before you is cracked, "+
	    "stained and ruined due to water damage and neglect.\n");

   add_item(({"papers","scattered papers","paper"}),
	    "Papers are scattered all over the room. They seem to "+
	    "be receipts for alcohol, ripped pages from a ledger, and "+
	    "orders for more drinks.\n");
   
   add_item(({"receipt","receipts"}),
	    "They are receipts from alcohol.\n");

   add_item(({"ripped pages","pages"}),
	    "They are ripped pages with columns of tabulated "+
	    "numbers.\n");
   
   add_item(({"columns","column","tabulated numbers","number",
		"numbers"}),
	    "There are lots of tabulated numbers on the pages. You "+
	    "wish you had some idea of what they all mean.\n");
   
   add_item(({"order","orders"}),
	    "Someone was planning on ordering more drinks. It "+
	    "appears that there is no authorizing signature "+
	    "on the orders.\n");
   
   add_item("sign",
	    "You can make out some writing on it.\n");
   
   add_exit(THIS_DIR + "wturn4", "east");
}

void
init()
{
   ::init();
   add_action("read","read");
   add_action("sign","sign");
}

int
read(string arg)
{
   notify_fail("Read what?\n");
   if(!arg || arg != "sign")
     return 0;
   write("This office will no longer accept alcohol deliveries until "+
         "further notice.\n Berhaun - Quartermaster\n");
   return 1;
}  

int
sign(string arg)
{
  write("You can not authorize the orders with your "+
	"signature; you will have to find someone else to do "+
        "it.\n");
  return 1;
}
