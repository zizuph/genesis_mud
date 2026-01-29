/* The lab of the evil mage. This room can only be accessed with magic!
 * One of the means to get here is with the Kitiara's ring.
 * No other means are known to the world (yet??)
 *
 * Aridor 09/95
 *
 * This room contains a part of the ring quest. A lot of items and
 * parts for the quest (actually all of them except the ring :) can
 * be found in this room.
 */

#include "local.h"


inherit INSIDE_BASE;

object mage, drawer;

void add_stuff();

void
create_splains_room()
{
    set_short("In a laboratory");
    set_long("This is a typical laboratory with things strewn around " +
	     "everywhere. Predominant in the room is a large heptagon " +
	     "drawn on the floor in the middle of the room. Leading " +
	     "east the room continues for a bit and then opens up. " +
	     "Lining the three walls are shelves with books, jars and " +
	     "bottles. Below one of the shelves is a desk.\n");

    INSIDE;
    add_prop(ROOM_I_NO_TELEPORT,1);
    add_exit(VOLCANO,"east");

    add_item(({"lab","laboratory"}),
	     "");
    add_search(({"lab","laboratory","here"}),10,"find_something_here",1);
    add_item("shelves","Stacked upon the shelves are books, jars and " +
	     "bottles.\n");
    add_item("books","");
    add_search("books",6,RECIPE,-1);
    add_item("desk","This is an ordinary looking desk with a large drawer " +
	     "underneath. Stacked on the desk are papers, flasks and other " +
	     "unidentifiable things.\n");
    add_search("desk",7,FEATHER,-1);
    add_item("heptagon","The border of the heptagon has been drawn with " +
	     "some kind of sparkling color. The heptagon itself is about " +
	     "10 feet in diameter!\n");
    add_item("bottles","There are many different bottles, but you can't " +
	     "see any writing on them indicating what might be inside.\n");
    add_search("bottles",5,RANDOM_ACID,-4);

    add_stuff();
}

void
reset_room()
{
    if (mage)
      return;
    mage = clone_object(MAGICIAN);
    mage->move(TO);
    drawer->reset_it();
}

void
add_stuff()
{
    drawer = clone_object(DRAWER);
    drawer->move(TO);

    reset_room();
}
