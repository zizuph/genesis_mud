inherit "/d/Gondor/common/room";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"
#include "/d/Gondor/minas/houses/horses.h"

void
create_room()
{
    set_short("Royal Stables");
  set_long(BSN("These are the Royal Stables of Minas Tirith. Long rows "+
    "of stalls can be seen within, and the sounds and the smells indicate "+
    "that a good number of horses rest inside. "+
    "A stableboy is brooming the floor, but seems ready to attend "+
    "to any request from you. "+
    "A sign hangs on the east wall. "+
    "South is the street of the Sixth Circle. "));
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
  add_prop(ROOM_I_IS_STABLE,1);
  add_exit(MINAS_DIR+"n2crc6","south",0);
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
