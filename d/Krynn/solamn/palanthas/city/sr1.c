/* Mortis 07.2005 */

#include "../local.h"
#include CLOCKH

inherit CITY_BASE;

string
query_to_jail()
{
  return "north";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  To the north is the palatial plaza, its great white "
	+ "tower still visible above the buildings from this distance.  To the "
	+ "south the road continues on to the aesthetics district.  A side "
	+ "street to the southeast leads to the great three-story library, "
	+ "and Inner Circle street curves east and west from here.\n";
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
	+ "filling the street with the noisy murmurings of their daily business."
	+ road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Aesthetics Row catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as well-dressed citizens make their way about the street." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Aesthetics Row amplifying the yellow glow of the street lamps.  "
	+ "A few people still make their way about at this hour." + road;
    break;

    default:
	break;
    }
    return desc;
}

void create_palan_room()
{
    SHORT("On Aesthetics Row south of the palatial plaza");
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

	EXIT(ROOM + "plaza", "north", 0, 0);
	EXIT(MONKS + "sr2", "south", 0, 0);
	EXIT(ROOM + "ic5", "east", 0, 0);
	EXIT(ROOM + "ic6", "west", 0, 0);
	EXIT(TDIR + "library/public", "southeast", 0, 0);

}