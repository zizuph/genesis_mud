/* Mortis 12.2005 
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
	string road = "  Palanthas circle intersects here heading west towards "
	+ "the Jem housing district and east towards shops and businesses.  "
	+ "Aesthetics Row leads north towards a monastery, the great library, "
	+ "and the city center and takes travellers south towards the southern "
	+ "gates.\n";
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
    SHORT("At the intersection of Aesthetics Row and Palanthas Circle in "
	+ "the heart of the Aesthetics quarter");
    LONG("@@get_time_desc@@");

	ITEM(({"monastery", "monastic building", "old building"}), "Through "
	+ "the buildings to the northwest you can just make it out.  Done ages "
	+ "in the ancient style, its sloping, curved rooftops are covered in "
	+ "gargoyles.  Its walls are buttressed with great arcs of translucent "
	+ "marble all the way up its three stories.  Aesthetic monks in their "
	+ "maroon robes as well as various citizens can be seen coming and "
	+ "going freely from their open doorway.\n");
	ITEM("housing district", "Virtually the only wooden buildings you have "
	+ "seen in Palanthas can be seen in the Jem housing district to the "
	+ "southwest.  A few are brick and occasionally exceed one floor.  The "
	+ "appearance of working street lamps is more sporadic in the Jem.\n");
	ITEM(({"gate", "gates", "s gate", "s gates", "southern gate",
		   "southern gates"}), "A large metal gate.\n");

	EXIT(MONKS + "sr2", "north", 0, 0);
	EXIT(MONKS + "a06", "east", 0, 0);
	EXIT(MONKS + "sr4", "south", 0, 0);
	EXIT(MONKS + "a07", "west", 0, 0);

}