/* Mortis 12.2005 
 * wood smells?  alley?
 */

#include "../local.h"
#include CLOCKH

inherit MERCH_BASE;

string
query_to_jail()
{
  return "southeast";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  The great white tower of the palatial plaza is still "
	+ "visible above the buildings to the southeast.  Along the road to the "
	+ "southwest is a thick wood, and through some buildings to the east you "
	+ "can see a great estate.  The road leads northwest towards its "
	+ "intersection with Palanthas Circle and southeast to city center.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The pristine marble of Horizon road and its buildings "
	+ "glows in " + one_of_list(({"pale purple ", "soft pink ",
	  "pale orange ", "grey and pink "})) + "hues as the sun peeks above the "
	+ "mountains in the east.  The air is rich with the smells of morning "
	+ "cooking and coffee borne on a cool, misty breeze from the bay." + road;
	break;

    case TOD_DAY:
	desc += "The pristine marble of Horizon road and its buildings "
	+ "gleams in the midday sun as people travel to and from the plaza "
	+ "filling the street with the noisy murmurings of their daily business."
	+ road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Horizon road catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as merchants and travellers make their way about the street." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Horizon road amplifying the yellow glow of the street lamps.  "
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
    SHORT("On Horizon road northwest of the palatial plaza by a thick wood");
    LONG("@@get_time_desc@@");

	ITEM(({"wood", "woods", "north wood", "north woods", "thick wood",
		   "thick woods"}), "A thick wood of trees stands to your southwest.  "
	+ "They are the Gallant Field Woods and home to the constabulary of "
	+ "Palanthas, the Palanthian Guard.  Their Tower of Arms rises from "
	+ "the vast field at its center.\n");
	ITEM(({"estate", "great estate"}), "Through some buildings to the east "
	+ "you can see the top of a great, marble estate rising four stories "
	+ "with elaborate stonework, hordes of gargoyles on its roof and "
	+ "corners, and many large shuttered windows.\n");

	EXIT(ROOM + "nwr2", "southeast", 0, 0);
	EXIT(MERCH + "nwr4", "northwest", 0, 0);

}