/* Mortis 07.2005 */

#include "../local.h"
#include CLOCKH

inherit NOBLE_BASE;

string
query_to_jail()
{
  return "west";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  To the west is the inner city, its "
	+ "great white tower still visible above the buildings from this "
	+ "distance.  Through the buildings, you spot to your northwest some "
	+ "noble estates and to the northeast, the Plaisir district.  The "
	+ "tall green hedge of a park can be seen southwest.  The road "
	+ "leads east to the eastern gates.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The pristine marble of Nobles' Way and Palanthas Circle "
	+ "glows in pale purple hues as the sun peeks above the mountains.  "
	+ "A cool, misty breeze blows south from the bay." + road;
	break;

    case TOD_DAY:
	desc += "The pristine marble of Nobles' Way and Palanthas Circle "
	+ "gleams in the midday sun as people walk about the intersection "
	+ "filling the streets with the gentle murmurings of their daily "
	+ "business." + road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Nobles' Way and Palanthas Circle "
	+ "catches the last rays of the sun appearing to glow of its own accord "
	+ "as well-dressed citizens make their way about the street." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Nobles' Way and Palanthas Circle amplifying the yellow glow of the "
	+ "street lamps.  A few people still make their way about at this hour."
	+ road;
    break;

    default:
	break;
    }
    return desc;
}

void create_palan_room()
{
    SHORT("On Nobles' Way and Palanthas Circle in the "
	+ "heart of the nobles district");
    LONG("@@get_time_desc@@");

	ITEM(({"estates", "estate", "noble estate", "noble estates"}),
	  "Through the buildings to the northwest can be seen some of the "
	+ "larger, great noble estates among the other marble buildings.\n");
	ITEM("plaisir district", "The Plaisir district "
	+ "is highly regarded in Palanthas by the nobility, bureaucracy, and "
	+ "well-to-do for its variety of services.  You catch a glimpse of it "
	+ "through the buildings to the northeast.\n");

	ITEM(({"hedge", "hedges", "bush", "bushes"}), "You see a tall hedge of "
	+ "well tended and cultured bushes trimmed and squared off on all sides "
	+ "and rising over ten feet to your southwest.  It is too dense to peer "
	+ "through.\n");

	EXIT(NOBLE + "er2", "west", 0, 0);
	EXIT(NOBLE + "n08", "north", 0, 0);
	EXIT(NOBLE + "er4", "east", 0, 0);
	EXIT(NOBLE + "n10", "south", 0, 0);

}