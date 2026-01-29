/* Mortis 12.2005 
 * Exits to west/east.
 * Smells should be good here.
 */

#include "../local.h"
#include CLOCKH

inherit MONKS_BASE;

string
query_to_jail()
{
  return "north";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  Aesthetics Row leads north towards Palanthas Circle "
	+ "in the heart of the quarter and south to the southern city gates.  "
	+ "A brick walkway leads to an estate to the west and the open door of "
	+ "a marble shop is to your east.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The pristine marble of Aesthetics Row and its buildings "
	+ "glows in pale orange hues as the sun peeks above the mountains.  "
	+ "The air is rich with the smells of morning cooking and coffee borne "
	+ "on a cool, misty breeze from the bay." + road;
	break;

    case TOD_DAY:
	desc += "The pristine marble of Aesthetics Row and its buildings "
	+ "gleams in the midday sun as people travel about the Aesthetics "
	+ "quarter filling the street with the murmurings of their daily business."
	+ road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Aesthetics Row catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as various citizens and maroon-robed monks make their way about the "
	+ "street." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Aesthetics Row amplifying the yellow glow of the street lamps.  "
	+ "A few people and maroon-robed monks still make their way about at this "
	+ "hour." + road;
    break;

    default:
	break;
    }
    return desc;
}

void create_palan_room()
{
    SHORT("On Aesthetics Row north of the southern city gates");
    LONG("@@get_time_desc@@");

	ITEM("housing district", "Virtually the only wooden buildings you have "
	+ "seen in Palanthas can be seen in the Jem housing district to the "
	+ "west.  A few are brick and occasionally exceed one floor.  The "
	+ "appearance of working street lamps is more sporadic in the Jem.\n");
	ITEM(({"gate", "gates", "s gate", "s gates", "southern gate",
		   "southern gates"}), "A large metal gate.\n");
	ITEM("estate", "A two-story estate of brick sits to your west.  Its "
	+ "construction is more modern than most marble buildings in the city "
	+ "but its bricks are collecting dirt, soot, and grout.  A small, brick "
	+ "courtyard is its front yard.\n");
	ITEM(({"walkway", "brick walkway"}), "Tightly laid bricks lead west from "
	+ "the road to the courtyard of a modest, brick estate.\n");
	ITEM(({"courtyard", "brick courtyard"}), "A small, circular area of "
	+ "tightly laid bricks serves as a simple front yard for the two-story "
	+ "estate to the west.\n");
	ITEM(({"shop", "marble shop"}), "An old, two-story, marble building that "
	+ "has collected dirt and soot over its long lifetime sits off the road "
	+ "to the east, its open doorway boasts a long, chiseled block above "
	+ "which reads, \"Book Bindery of Palanthas\" in the ancient style.\n");

	EXIT(MONKS + "sr3", "north", 0, 0);
	EXIT(MONKS + "binders", "east", "@@place_closed", 0);
	EXIT(MONKS + "sr5", "south", 0, 0);
	EXIT(MONKS + "hausx", "west", "@@place_closed", 0);

}

int
place_closed()
{
	write("Opening in the future.\n");
	return 1;
}
