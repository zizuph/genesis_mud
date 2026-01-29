/* Mortis 11.2005
 */

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
	string road = "  Kosten Way curves through this portion of the nobles "
	+ "quarter from the northeast, where it begins on Old Circle, to the "
	+ "southeast where it also ends on Old Circle.  A side street leads "
	+ "southwest to Palanthas Circle, and there is a gravel path to a tall "
	+ "noble estate south.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The pristine marble of Kosten Way and its buildings "
	+ "glows in pale purple hues as the sun peeks above the mountains.  "
	+ "A cool, misty breeze blows south from the bay." + road;
	break;

    case TOD_DAY:
	desc += "The pristine marble of Kosten Way and its buildings "
	+ "gleams in the midday sun as people walk about the intersection "
	+ "filling the streets with the gentle murmurings of their daily "
	+ "business." + road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Kosten Way catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as well-dressed citizens make their way about the street." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Kosten Way amplifying the yellow glow of the street lamps.  "
	+ "A few people still make their way about at this hour." + road;
    break;

    default:
	break;
    }
    return desc;
}

void
create_palan_room()
{
    SHORT("On Kosten Way in the nobles quarter");
    LONG("@@get_time_desc@@");

	ITEM(({"umbertos", "umberto's", "umbertos cloth", "umberto's cloth"}),
	  "A large, two-story marble building with a great, purple banner "
	+ "hanging vertically from an upper level window can be seen through "
	+ "the buildings to your southwest.\n");
	ITEM(({"estate", "noble estate"}), "There is a large, noble estate "
	+ "to the south.  Built of pristine, translucent marble, its "
	+ "architecture is typical of the old buildings here in the noble "
	+ "quarter.  It rises four stories, larger than its neighbors.  A "
	+ "gravel path leads south to it.\n");
	ITEM(({"path", "gravel path"}), "A path of translucent white, marble "
	+ "gravel leads south to a four-story marble noble estate.  On either "
	+ "side it is lined with a row of cultivated hedges trimmed to be "
	+ "vertically flat on their sides with a perfectly trimmed wave "
	+ "pattern on top.\n");
	ITEM(({"hedge", "hedges"}), "Rows of hedges line both sides of the "
	+ "gravel path leading to the southern noble estate.  They are trimmed "
	+ "to be vertically flat on their sides with a perfectly trimmed wave "
	+ "pattern on top.\n");

	EXIT(NOBLE + "n05", "west", 0, 0);
	EXIT(NOBLE + "n06", "northwest", 0, 0);
	EXIT(NOBLE + "nbx", "south", "@@noble_closed", 0);
	EXIT(NOBLE + "w05", "southeast", 0, 0);

}

int
noble_closed()
{
	write("Nobles aren't open.\n");
	return 1;
}
