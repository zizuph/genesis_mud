/* Mortis 11.2005
 * Door to noble house.  Guards.
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>

inherit NOBLE_BASE;

string
query_to_jail()
{
  return "north";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  Nobil Row runs north where it intersects with Nobles' "
	+ "Way and south towards several large, noble estates, and a side street "
	+ "that heads east towards the old, city wall.  Over the buildings "
	+ "east can be seen the top of a short marble tower.  A private road "
	+ "leads to the door of a great, four-story manor house estate to the "
	+ "west.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The pristine marble of Nobil Row and its buildings "
	+ "glows in " + one_of_list(({"pale purple ", "soft pink ",
	  "pale orange ", "grey and pink "})) + "hues as the sun peeks above "
	+ "the mountains.  The air is rich with the salty smells from the bay "
	+ "borne on a cool, misty breeze." + road;
	break;

    case TOD_DAY:
	desc += "The pristine marble of Nobil Row and its buildings "
	+ "gleams in the midday sun as people travel to and from the estates "
	+ "of the noble quarter filling the street with the noisy murmurings "
	+ "of their daily business." + road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Nobil Row catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as travellers, merchants, and seamen make their way about the street."
	+ road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Nobil Row amplifying the yellow glow of the street lamps.  "
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
    SHORT("On Nobil Row in the heart of the nobles quarter");
    LONG("@@get_time_desc@@");

	ITEM(({"estates", "estate", "noble estate", "noble estates"}),
	  "To the north along Nobil Row can be seen some of the "
	+ "larger, great noble estates among the other marble buildings.  "
	+ "A great manor house estate is to your west.\n");
	ITEM(({"manor", "manor house", "manor house estate", "manor estate"}),
	  "The manor house style estate is constructed of large, marble blocks "
	+ "up to the curling, slanted roof atop the fourth level whereon sit "
	+ "many crouching gargoyles.  Its door faces you to the west.\n");
	ITEM("private road", "A short, private road of perfectly cut squares of "
	+ "translucent white marble leads to the doorstep of a grand manor house "
	+ "estate.\n");
	ITEM(({"short tower", "short marble tower", "marble tower"}), "A tower "
	+ "of translucent, white marble rises at least forty feet into the air "
	+ "above the buildings to your northeast, higher than nearly all of the "
	+ "buildings in this section of the noble quarter.\n");


	add_smell("vampire", "Misty air blowing south off the bay mingles here "
	+ "with the smells of a noble dwelling to the west where the scent of "
	+ "blood catches your attention.");
	add_smell("human", "Misty air blowing south off the bay mingles here with "
	+ "the smell of perfumes to the west.");
	add_smell("elf", "Misty air blowing south off the bay mingles here with "
	+ "the smells of a noble human dwelling to the west.");
	add_smell("hobbit", "Misty air blowing south off the bay mingles here "
	+ "with the smells of a human estate to the west which, judging by the "
	+ "perfumes, must be a lovely place.");
	add_smell("gnome", "There's moisture in the air blowing south off the "
	+ "bay.  Adding to its salty flavor is the smell of a human dwelling "
	+ "to the west.");
	add_smell("minotaur", "Misty air blowing south off the bay mingles here "
	+ "with the smells of man house to the west.");
	add_smell("orc", "Misty air blowing south off the bay mingles here with "
	+ "the smells of a human estate to the west.");
	add_smell("hobgoblin", "Misty air blowing south off the bay mingles here "
	+ "with the smells of a well to do estate to the west.");
	add_smell("kender", "Misty air blowing south off the bay mingles here "
	+ "with the smells of a human estate to the west which, judging by the "
	+ "perfumes, must be a lovely place.");
	add_smell("noldor", "Misty air blowing south off the bay mingles here "
	+ "with the smells of a typical smelling noble human estate.");
	add_smell("unknown", "You smell the estate "
	+ "to the west, but your race is unknown to the immortals!  Please mail "
	+ "Krynn with your race.");

	EXIT(NOBLE + "er4", "north", 0, 0);
	EXIT(NOBLE + "n15", "south", 0, 0);

}
