/* Mortis 11.2005
 * Alleys?  Paper smells?
 */

#include "../local.h"
#include CLOCKH

inherit MONKS_BASE;

string
query_to_jail()
{
  return "west";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  The circle curves west into its intersection with "
	+ "Aesthetics Row and east towards more shops and homes.  A side street "
	+ "winds east to the doorway of a two-story marble shop above which "
	+ "hangs a sign with the picture of an unfurled scroll upon it.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The translucent marble of Palanthas Circle and its buildings "
	+ "glows in " + one_of_list(({"pale purple ", "soft pink ",
	  "pale orange ", "grey and pink "})) + "hues as the sun peeks above the "
	+ "mountains in the east.  The air is rich with the smells of morning "
	+ "cooking and " + one_of_list(({"tea", "coffee"})) + " borne on a cool, "
	+ "misty breeze from the bay." + road;
	break;

    case TOD_DAY:
	desc += "The translucent marble of Palanthas Circle and its buildings "
	+ "appears mostly white in the midday sun as people travel along the way "
	+ "filling the street with the murmurings of their daily business."
	+ road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Palanthas Circle catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as citizens and maroon robed aesthetics make their way about the "
	+ "street." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Palanthas Circle amplifying the yellow glow of the street lamps.  "
	+ "A few people and maroon robed aesthetics still make their way about at "
	+ "this hour." + road;
    break;

    default:
	break;
    }
    return desc;
}

void
create_palan_room()
{
    SHORT("On Palanthas Circle east of Aesthetics Row");
    LONG("@@get_time_desc@@");

	ITEM(({"shop", "two-story shop"}), "Built of translucent white marble "
	+ "and topped with beige bricks and a sloping roof of new gargoyles, "
	+ "this shop sits off Palanthas Circle to the south.  Its doorway is "
	+ "open.  Above it is hung a wooden sign upon which has been "
	+ "accurately drawn the picture of an unfurled, vellum scroll.\n");
	ITEM(({"sign", "wooden sign", "picture", "vellum scroll",
		   "unfurled scroll", "unfurled vellum scroll"}), "Painted as if "
	+ "viewed from a slight side angle, the detail of the quality vellum "
	+ "texturing is noticeable.  The top and bottom of the scroll curve "
	+ "back several times into a roll.  Near the bottom roll in small "
	+ "cursive is written, \"Scroll Trade Guilde\".\n");

	EXIT(MONKS + "a05", "east", 0, 0);
	EXIT(MONKS + "scrolls", "south", "@@place_closed", 0);
	EXIT(MONKS + "sr3", "west", 0, 0);

}

int
place_closed()
{
	write("This will open in the future.\n");
	return 1;
}