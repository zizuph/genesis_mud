/* Mortis 12.2005 */

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
	string road = "  To the north is the inner city and palatial plaza, its "
	+ "great white tower still visible above the buildings from this "
	+ "distance.  The great three-story library of Palanthas can be seen "
	+ "above the buildings to your northeast, and west is a grand, old, "
	+ "marble monastic building.  To the south the road continues further "
	+ "into the aesthetics quarter while a side street leads east toward a "
	+ "housing district.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The pristine marble of Aesthetics Row and its buildings "
	+ "glows in pale purple hues as the sun peeks above the mountains.  "
	+ "The air is rich with the smells of morning cooking and coffee borne "
	+ "on a cool, misty breeze from the bay." + road;
	break;

    case TOD_DAY:
	desc += "The pristine marble of Aesthetics Row and its buildings "
	+ "gleams in the midday sun as people travel to and from the plaza "
	+ "and Aesthetics quarter filling the street with the murmurings of "
	+ "their daily business."
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
    SHORT("On Aesthetics Row south of the palatial plaza in the Aesthetics "
	+ "quarter");
    LONG("@@get_time_desc@@");

	ITEM(({"library", "great library", "great library of palanthas"}),
	  "The library is a magnificent, three-story building of translucent "
	+ "marble edged all over in smoothly chiseled elegant patternry and "
	+ "roofed in copper tiles and copper-plated spires which have turned "
	+ "green with exposure to the elements.  Its larger, central spire is "
	+ "topped with an arrow weather vane currently pointing south"
	+ one_of_list(({"west", "", "east"})) + ".  "
	+ "Aesthetics and citizens of all classes come and go at all hours "
	+ "hours at the Great Library of Palanthas.\n");
	ITEM(({"monastery", "monastic building", "old building"}), "Done ages "
	+ "in the ancient style, its sloping, curved rooftops are covered in "
	+ "gargoyles.  Its walls are buttressed with great arcs of translucent "
	+ "marble all the way up its three stories.  Aesthetic monks in their "
	+ "maroon robes as well as various citizens can be seen coming and "
	+ "going freely from their open doorway.\n");
	ITEM(({"aesthetics", "monks"}), "Men and women of all ages in their "
	+ "simple, maroon robes and sandals can be seen coming and going from "
	+ "the monastery to the west at all hours.\n");
	ITEM("housing district", "For the Aesthetics quarter the section of "
	+ "houses to the east are large and somewhat well spaced.  Some are "
	+ "not only two stories but occasionally three.\n");

	EXIT(ROOM + "sr1", "north", 0, 0);
	EXIT(MONKS + "a02", "east", 0, 0);
	EXIT(MONKS + "sr3", "south", 0, 0);
	EXIT(MONKS + "aesthetics", "west", "@@place_closed", 0);

}

int
place_closed()
{
	write("This will open in the future.\n");
	return 1;
}