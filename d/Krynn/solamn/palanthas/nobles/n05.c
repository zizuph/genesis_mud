/* Mortis 11.2005
 */

#include "../local.h"
#include CLOCKH

inherit NOBLE_BASE;

string
query_to_jail()
{
  return "northwest";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  To the southeast is a large, two-story, marble "
	+ "shop with a great, purple cloth banner hanging from a large window "
	+ "on the upper floor.  Side streets lead both northeast and east to "
	+ "the curved Kosten Way.  Palanthas Circle curves northwest towards "
	+ "Scholar's Walk and south into the heart of the nobles quarter.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The pristine marble of Palanthas Circle and its buildings "
	+ "glows in pale purple hues as the sun peeks above the mountains.  "
	+ "A cool, misty breeze blows south from the bay." + road;
	break;

    case TOD_DAY:
	desc += "The pristine marble of Palanthas Circle and its buildings "
	+ "gleams in the midday sun as people walk about the intersection "
	+ "filling the streets with the gentle murmurings of their daily "
	+ "business." + road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Palanthas Circle catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as well-dressed citizens make their way about the street." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Palanthas Circle amplifying the yellow glow of the street lamps.  "
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
    SHORT("On Palanthas Circle northwest of Umberto's Cloth");
    LONG("@@get_time_desc@@");

	ITEM(({"umbertos", "umberto's", "umbertos cloth", "umberto's cloth"}),
	  "A large, two-story marble building with a great, purple banner "
	+ "hanging vertically from an upper level window.\n");
	ITEM(({"harnoncourt", "jeweler", "jewelers", "harnoncourt jewelers"}),
	  "The Harnoncourt Jewelers is a three-story marble building "
	+ "to your southwest.  Its marble is pristine and clean.\n");
	ITEM(({"banner", "purple banner"}), "This great, deep purple banner "
	+ "is hung from a window in the upper floor, hangs down over a dozen "
	+ "feet, and is secured at its base by a bolted rod above a ground "
	+ "floor window.  Large, flowing writing is embroidered in silver "
	+ "thread vertically down its length.  You may <read banner>.\n");

	CMD("banner", "read", "@@read_banner");

	EXIT(NOBLE + "ner5", "northwest", 0, 0);
	EXIT(NOBLE + "n06", "northeast", 0, 0);
	EXIT(NOBLE + "n07", "east", 0, 0);
	EXIT(NOBLE + "finecloth", "southeast", "@@umb_closed", 0);
	EXIT(NOBLE + "n04", "south", 0, 0);

}

read_banner()
{
	write("        F\n"
		+ "     U  i\n"
		+ "     M  n\n"
		+ "     B  e\n"
		+ "     E   \n"
		+ "     R  C\n"
		+ "     T  l\n"
		+ "     O  o\n"
		+ "     '  t\n"
		+ "     S  h\n"
		+ "        *\n\n");
		return 1;
}

int
umb_closed()
{
	write("The store is closed for now.\n");
	return 1;
}