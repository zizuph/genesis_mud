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
	string road = "  To the west is the inner city and palatial plaza, its "
	+ "great white tower still visible above the buildings from this "
	+ "distance.  To the north is Livery Street, the south Havecius Court, "
	+ "the hedge of a park can be seen to the southeast, and the road leads "
	+ "east to the heart of the nobles district.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The pristine marble of Nobles' Way and its buildings "
	+ "glows in pale purple hues as the sun peeks above the mountains.  "
	+ "A cool, misty breeze blows south from the bay." + road;
	break;

    case TOD_DAY:
	desc += "The pristine marble of Nobles' Way and its buildings "
	+ "gleams in the midday sun as people walk about the intersection "
	+ "filling the streets with the gentle murmurings of their daily "
	+ "business." + road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Nobles' Way catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as well-dressed citizens make their way about the street." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Nobles' Way amplifying the yellow glow of the street lamps.  "
	+ "A few people still make their way about at this hour." + road;
    break;

    default:
	break;
    }
    return desc;
}

void create_palan_room()
{
    SHORT("On Nobles' Way east of the palatial plaza and west of the "
	+ "heart of the nobles district");
    LONG("@@get_time_desc@@");

	ITEM(({"hedge", "hedges", "bush", "bushes"}), "You see a tall hedge of "
	+ "well tended and cultured bushes trimmed and squared off on all sides "
	+ "and rising over ten feet to your southeast.  It is too dense to peer "
	+ "through.\n");
	ITEM(({"estates", "estate", "noble estate", "noble estates"}),
	  "Through the buildings to the northeast can be seen some of the "
	+ "larger, great noble estates among the other marble buildings.\n");

	EXIT(ROOM + "er1", "west", 0, 0);
	EXIT(NOBLE + "n01", "north", 0, 0);
	EXIT(NOBLE + "er3", "east", 0, 0);
	EXIT(NOBLE + "n09", "south", 0, 0);

}