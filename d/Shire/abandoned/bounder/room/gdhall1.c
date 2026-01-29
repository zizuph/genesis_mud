/* 
 * This is gdhall1.c, mainroom of the Green Dragon Inn.
 * Jaypeg Brandybuck of the Shire , Oct 1997
 */

inherit  "/std/room";
#include "/d/Shire/defs.h"
#include "/d/Shire/bounders/guild.h"


void create_room()
{

    add_prop(ROOM_I_INSIDE,1);
    set_short("The dim, musty, interior of the Green Dragon Inn");
    set_long("Wrapped in smokey aged cedar, the atmosphere of the "+
      "Green Dragon Inn greets you as you soak in your surrounds. "+
      "The ceiling is high even for a human establishment, held steady "+
      "by hardwood beams too thick to wrap your arms around. A faint, "+
      "sour odor of old ale and spilt brandy lingers amongst the pipe-"+
      "smoke and tang of tavern food. Burly tables and creaky old "+
      "chairs surround you, and a long polished bar seperates you "+
      "from the east wall, where a few stalwart local hobbit folk "+
      "keep the spirits and gossip flowing. The west side of the Inn "+
      "is split into two, the southwest being the entry parlour and "+
      "access to the street, and the northwest being a sheltered and "+
      "more private corner, most often customised by dwarven and "+
      "human travellers prefering their privacy. In the northeast "+
      "corner of the Inn a staircase dissapears up onto the next "+
      "floor.\n");

    add_item(({"cedar","beams","hardwood"}),
      "These walls, that have stood for generations of hobbits, "+
      "are held up by some very sturdy hardwood beams, judging by "+
      "the heady smell probably cedar.\n");
    add_item(({"smoke","smell","odor"}),
      "The musky smell that envelopes you is born of old hardwood, "+
      "tavern food, ale and spirits carried by the tangy smelling "+
      "smoke of pipe-weed.\n");
    add_item(({"bar","barmen","long bar","long polished bar"}),
      "Running almost the entire length of the east wall is a long, "+
      "polished bar of some dark hardwood. There are stools of two "+
      "distinct heights, mostly the higher stools for the locals to "+
      "sit apon. Behind the bar stand a few of the local barmen on "+
      "a raised floor, gossiping with the customers and making sure "+
      "no-one goes thirsty.\n");
    add_item(({"tables","burly tables","chairs","old chairs"}),
      "All about you are the heavy-set hardwood tables and chairs "+
      "that service the custom of the Inn. Most of the chairs are "+
      "the high-chairs the local hobbitfolk and the rarely seen gnomes "+
      "use, though there are a few lower chairs for the occasional "+
      "bigger folk passing through, most often dwarves or humans.\n");
    add_item(({"entryway","foyer","parlour","entry parlour"}),
      "Taking up the southwest corner of the Inn is an entry "+
      "parlour, where customers make their way in and out of the "+
      "Green Dragon Inn. You can see the wide door and rows of "+
      "pegs for visitors to place their hats and coats.\n");
    add_item(({"corner","northwest corner"}),
      "The northwest corner of the Inn is a darker and more private "+
      "area than where you stand, when it is busy its most likely "+
      "preferred by the travellers prefering their privacy, rather "+
      "than the local hobbits who like to mingle and gossip.\n");


    add_exit( BOUND_ROOM_DIR + "gdentry", "entryway", 0 );
    add_exit( BOUND_ROOM_DIR + "gdhall2", "corner", 0 );
    add_exit( BOUND_ROOM_DIR + "gdup1", "up", 0 );

}
