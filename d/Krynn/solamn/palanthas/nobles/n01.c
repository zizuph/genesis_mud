/* Mortis 07.2005 */

#include "../local.h"
#include CLOCKH

inherit NOBLE_BASE;

string
query_to_jail()
{
  return "south";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  To the west is the Solamnian Livery, and to the east "
	+ "are some of the noble estates.  The street continues north and to "
	+ "the south ends in an intersection with Nobles' Way.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The pristine marble of Livery Street and its buildings "
	+ "glows in pale purple hues as the sun peeks above the mountains.  "
	+ "A cool, misty breeze blows south from the bay." + road;
	break;

    case TOD_DAY:
	desc += "The pristine marble of Livery Street and its buildings "
	+ "gleams in the midday sun as people walk about the intersection "
	+ "filling the streets with the gentle murmurings of their daily "
	+ "business." + road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Livery Street catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as well-dressed citizens make their way about the street." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Livery Street amplifying the yellow glow of the street lamps.  "
	+ "A few people still make their way about at this hour." + road;
    break;

    default:
	break;
    }
    return desc;
}

void create_palan_room()
{
    SHORT("On Livery Street north of Nobles' Way in the nobles district");
    LONG("@@get_time_desc@@");

	ITEM(({"livery", "solamnian livery", "stable", "stables"}), "The livery "
	+ "to your west is actually a large estate with a field just before you, "
	+ "a corral to your southwest, a long stable of wood to your northwest, "
	+ "and a great, marble manor house in its midst to your west.  The house "
	+ "is an old, translucent marble building whose grounds were converted "
	+ "ages ago to accomodate the field, wood-fenced corral, and stables.  "
	+ "The stables are a great longhouse of wood with a fenced in area for "
	+ "bringing horses to and from the stalls.\n");

	ITEM(({"estate", "estates", "noble estate", "noble estates"}), "There "
	+ "are a pair of estates off a court to your east.  Their architecture "
	+ "is typical of the old buildings of marble rising several stories "
	+ "here in the noble district.\n");

	add_smell("vampire", "Misty air blowing south off the bay mingles here "
	+ "with the pungent smell of fresh cut hay, boiled leather, and well "
	+ "groomed horses.  Though strong here, these scents pale to the smell "
	+ "of noble family blood coming from the estates to the east.");
    add_smell("morgul", "Misty air blowing south off the bay mingles here "
	+ "with the smell of horses and leather to your west.");
	add_smell("human", "Misty air blowing south off the bay mingles here with "
	+ "the smell of fresh cut hay, leather, and horses.");
	add_smell("elf", "Misty air blowing south off the bay mingles here with "
	+ "the smells of fresh cut hay, tanned leather, and well cared for "
	+ "horses to your west and the hint of perfumes to your east.");
	add_smell("goblin", "The fresh smells of horses and manure from the "
	+ "west mix here with misty air blowing south off the bay.");
	add_smell("dwarf", "Misty air blowing south off the bay mingles here "
	+ "with the smells of hay, tanned and boiled leathers, and horses from "
	+ "your west.");
	add_smell("hobbit", "Misty air blowing south off the bay mingles here "
	+ "with the relaxing smell of fresh cut hay, the warm smell of leather, "
	+ "and horse scents coming from your west.  The estates to the east "
	+ "smell flowery and are likely to have well stocked kitchens.");
	add_smell("gnome", "There's moisture in the air blowing south off the "
	+ "bay.  Adding to its salty flavor are the smells of hay, horses, and "
	+ "leather from the livery to your west.");
	add_smell("minotaur", "Misty air blowing south off the bay mingles here "
	+ "with the familiar smells of well groomed horses and leather as well "
	+ "as fresh, crunchy hay to your west.");
	add_smell("halfhuman", "Misty air blowing south off the bay mingles here "
	+ "with the familiar smells of hay, horses, and leather to your west.");
	add_smell("halfelf", "Misty air blowing south off the bay mingles here "
	+ "with the not unfamiliar smells of fresh cut hay, leather, and horses "
	+ "coming from your west and the hint of flowers to your east.");
	add_smell("orc", "Misty air blowing south off the bay mingles here with "
	+ "the mouth-watering smell of horse flesh and leather to your west.");
	add_smell("hobgoblin", "Misty air blowing south off the bay mingles here "
	+ "with the smells of well groomed horse, good leather, and fresh hay to "
	+ "your west and the perfumed halls of noble human estates to your east.");
	add_smell("kender", "Misty air blowing south off the bay mingles here "
	+ "with the relaxing smell of fresh cut hay, the warm smell of leather, "
	+ "and horse scents coming from your west.  The estates to the east "
	+ "are a delightful blend of flowery perfumes and unimaginably exciting "
	+ "objects of interest from foreign lands, maybe.");
	add_smell("noldor", "Misty air blowing south off the bay mingles here "
	+ "with the smells of fresh cut hay, leather, and groomed horses from "
	+ "the livery to your west.  From the east comes the typical smell of a "
	+ "perfumed noble human dwelling.");
	add_smell("unknown", "You smell the horses and such to your west, but "
	+ "your race is unknown to the immortals!  Please mail Krynn with your "
	+ "race.");

	EXIT(NOBLE + "liv_ent", "west", 0, 0);
	EXIT(NOBLE + "n03", "north", 0, 0);
	EXIT(NOBLE + "n02", "east", 0, 0);
	EXIT(NOBLE + "er2", "south", 0, 0);

}