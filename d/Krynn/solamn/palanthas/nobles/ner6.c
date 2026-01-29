/* Mortis 11.2005
 * Add_smells for crab shack to nw.
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>

inherit NOBLE_BASE;

string
query_to_jail()
{
  return "southwest";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  To the southwest is the inner city and palatial plaza, "
	+ "its great white tower still visible above the buildings from this "
	+ "distance.  A sidewalk leads northwest to a small, marble building.  "
	+ "From it hangs a wooden sign which reads \"Bishon's Crabbery\".  "
	+ "To the northeast the road continues towards Scholar's Gate.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The pristine marble of Scholar's Walk and its buildings "
	+ "glows in pale purple hues as the sun peeks above the mountains.  "
	+ "The air is rich with the smells of morning cooking and coffee borne "
	+ "on a cool, misty breeze from the bay." + road;
	break;

    case TOD_DAY:
	desc += "The pristine marble of Scholar's Walk and its buildings "
	+ "gleams in the midday sun as people travel to and from the plaza "
	+ "filling the street with the noisy murmurings of their daily business."
	+ road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Scholar's Walk catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as well-dressed citizens make their way about the street." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Scholar's Walk amplifying the yellow glow of the street lamps.  "
	+ "A few people still make their way about at this hour." + road;
    break;

    default:
	break;
    }
    return desc;
}

void create_palan_room()
{
    SHORT("On Scholar's Walk southwest of Scholar's Gate");
    LONG("@@get_time_desc@@");

	ITEM("sign", "The sign outside the small, marble building to your "
	+ "northwest hangs from a wooden rod and pair of shiny chains.  It "
	+ "is a square of thick wood into which its letters have been carved "
	+ "then painted white.  It reads, \"Bishon's Crabbery\".\n");
	ITEM("sidewalk", "The sidewalk is wide enough for several people to "
	+ "walk abreast.  Small, marble blocks are arranged in a pattern "
	+ "imitating sideways crab tracks leading northwest.\n");
	ITEM("rod", "A simple wooden rod bolted into the marble above the door "
	+ "of the small, marble building to your northwest.\n");
	ITEM(({"chains", "shiny chains"}), "A few simple links of polished steel "
	+ "extending from the wooden rod above the doorway in the small, marble "
	+ "building to your northwest from which is hung a wooden sign.\n");
	ITEM(({"small marble building", "small building"}), "A one-story, marble "
	+ "building from which a pair of chimneys release steady streams of thin "
	+ "smoke.  The sign hanging above its door reads, \"Bishon's Crabbery\""
	+ ".\n");
	ITEM(({"chimney", "chimneys"}), "Smoke rises from small, wood-topped "
	+ "chimneys atop the small, marble building to your northwest.\n");
	ITEM(({"gate", "northeast gate", "ne gate", "scholars gate",
		   "scholar's gate"}), "A large metal gate.\n");

	CMD("sign", "read", "@@read_sign");

	EXIT(NOBLE + "ner5", "southwest", 0, 0);
	EXIT(NOBLE + "crabshack", "northwest", "@@place_closed", 0);
	EXIT(NOBLE + "ner7", "northeast", 0, 0);

}

read_sign()
{
	write("\"Bishon's Crabbery\"\n");
	return 1;
}

int
place_closed()
{
    return 0;
/*
	write("The shack isn't open yet.\n");
	return 1;
*/
}