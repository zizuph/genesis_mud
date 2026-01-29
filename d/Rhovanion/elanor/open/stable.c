/*
 * Sample stable where you can summon your steed
 */

inherit "/std/room";

/*
 * We need some properties
 */
#include <stdproperties.h>

/*
 * Function name: create_room
 * Description:   Set up room descriptions
 */
void
create_room()
{
    set_short("Royal Stables");
    set_long(break_string("These are the royal stables of the King Elessar "+
			  "many brave and valiant horses stand awaiting "+
			  "their riders.  On the east wall is a large and " +
			  "important looking sign\n", 76));
    add_item("sign", "There is writing on it perhaps you should read it. \n");
    add_cmd_item(  ({ "sign", "writing" }),
			"read",
                         "                                 Instructions\n" +
		  "1)..To summon your horse:  call <horsename>\n" +
		  "2)..To feed your horse: feed <horsename> with <food>\n" +
		  "3)..Food is available at the stable shop and livestock stores\n" +
		  "    throughout the universe\n" +
		  "4)..To send your horse back to the nearest stable: release <horsename> \n" +
		  "    This will cost you 1 gold coin to ensure correct feeding\n" +
		  "    and your horses safety\n" +
		  "5)..Horses will respond to owners as long as they are in\n" +
		  "    the same landmass as their owner and do not have to\n" +
                  "    cross bodies of water larger than a ford in a river\n");

    add_prop(ROOM_I_INSIDE, 1);
}

/*
 * Function name: query_call_horse
 * Description:   Function called by the pedigree to see if calling for
 *                a horse is possible here.
 * Returns:       1 - calling a horse is possible
 */
int
query_call_horse()
{
    return 1;
}
