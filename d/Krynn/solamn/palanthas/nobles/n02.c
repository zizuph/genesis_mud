/* Mortis 11.2005
 * Add north and south doors to noble estates
 * Request audience at them?  Then alley access from
 * n03/n04 alley system?
 */

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
	string road = "  To the west is Livery Street, and to the north and "
	+ "south are large, three-story noble estates.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The pristine marble of August Court and its buildings "
	+ "glows in pale purple hues as the sun peeks above the mountains.  "
	+ "A cool, misty breeze blows south from the bay." + road;
	break;

    case TOD_DAY:
	desc += "The pristine marble of August Court and its buildings "
	+ "gleams in the midday sun as nobles, their servants, and retinues "
	+ "walk to and from the court." + road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of August Court catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as well-dressed citizens make their way about the court." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of August Court amplifying the yellow glow of the street lamps.  "
	+ "Few people still make their way about at this hour." + road;
    break;

    default:
	break;
    }
    return desc;
}

void create_palan_room()
{
    SHORT("On August Court east of Livery Street in the nobles district");
    LONG("@@get_time_desc@@");

	ITEM(({"estate", "estates", "noble estate", "noble estates"}), "There "
	+ "are a pair of estates off this court, one to the north and south.  "
	+ "Their architecture is typical of the old buildings of marble rising "
	+ "several stories here in the noble district.  Their courtyards are "
	+ "filled with perfectly landscaped bushes, flowers, small trees, and "
	+ "walkways leading to their doors.\n");
	ITEM(({"courtyard", "courtyards"}), "Courtyards before each noble "
	+ "estate are filled with perfectly landscaped bushes, flowers, small "
	+ "trees, and walkways leading to their doors.\n");
	ITEM(({"bush", "bushes", "flower", "flowers", "tree", "trees",
		   "small tree", "small trees"}), "Well-trimmed bushes, "
	+ "professionally arranged flowerbeds, and exotic small tree varieties "
	+ "are perfectly arrayed about the courtyards of the noble estates.\n");
	ITEM(({"walkway", "walkways"}), "The noble estate to the north has a "
	+ "walkway of tan bricks curving its way to the front door, while the "
	+ "southern estate boasts a more traditional walkway of translucent "
	+ "marble blocks.\n");

	add_smell("vampire", "Misty air blowing south off the bay mingles here "
	+ "the scents of fragrant flowers, greenery, and perfumes though they "
	+ "pale to the smell of noble family blood coming from the estates to "
	+ "the north and south.");
    add_smell("morgul", "Misty air blowing south off the bay mingles here "
	+ "with the smell of fragrant, green courtyards to the north and south.");
	add_smell("human", "Misty air blowing south off the bay mingles here with "
	+ "the smell of fragrant greenery in the noble estate courtyards and a "
	+ "hint of perfume.");
	add_smell("elf", "Misty air blowing south off the bay mingles here with "
	+ "the smells of non-native flowers, cultivated bushes, and trees bred "
	+ "for diminutive stature as well as overpowering human perfumes from "
	+ "the north and south estates.");
	add_smell("goblin", "Flowery plants and things and fruity smells "
	+ "mix here with misty air blowing south off the bay.");
	add_smell("dwarf", "Misty air blowing south off the bay mingles here "
	+ "with the smells of human dwellings and gardens.");
	add_smell("hobbit", "Misty air blowing south off the bay mingles here "
	+ "with the fragrances of flowery perfumes and flowery gardens, but the "
	+ "occasional roasted scent leads you to believe the estates in the "
	+ "court are likely to have well stocked kitchens.");
	add_smell("gnome", "There's moisture in the air blowing south off the "
	+ "bay.  Adding to its salty flavor are the smells of flowers, bushes, "
	+ "and human scent flavourings from the north and south estates.");
	add_smell("minotaur", "Misty air blowing south off the bay mingles here "
	+ "with the familiar smells of well groomed horses and leather as well "
	+ "as fresh, crunchy hay far to your west as well as the gardeny "
	+ "courtyards and man perfumes from the estates.");
	add_smell("halfhuman", "Misty air blowing south off the bay mingles here "
	+ "with the smell of fragrant greenery in the noble estate courtyards "
	+ "and a hint of perfume.");
	add_smell("halfelf", "Misty air blowing south off the bay mingles here "
	+ "with the not unfamiliar smells of human perfumes from the nearby "
	+ "estates and cultivated, green courtyards of flowers and bushes.");
	add_smell("orc", "Misty air blowing south off the bay mingles here with "
	+ "the mouth-watering smell of horse flesh far to your west, loud "
	+ "smelling greenery from the courtyards, and manfumes from the "
	+ "estates.");
	add_smell("hobgoblin", "Misty air blowing south off the bay mingles here "
	+ "with the smells of extensively tended green courtyards of flower things "
	+ "and the perfumed halls of noble human estates to the north and south.");
	add_smell("kender", "Misty air blowing south off the bay mingles here "
	+ "with the delightful blend of fragrances from flowery perfumes and "
	+ "flowery gardens, but the occasional roasted scent leads you to "
	+ "believe the estates in the court are likely to have well stocked "
	+ "kitchens as well as unimaginably exciting objects of interest from "
	+ "foreign lands, maybe.");
	add_smell("noldor", "Misty air blowing south off the bay mingles here with "
	+ "the smells of non-native flowers, cultivated bushes, and trees bred "
	+ "for diminutive stature as well as overpowering human perfumes from "
	+ "the north and south estates so typically used by men without taste.");
	add_smell("unknown", "You smell flowers and houses and such, but "
	+ "your race is unknown to the immortals!  Please mail Krynn with your "
	+ "race.");

	EXIT(NOBLE + "n01", "west", 0, 0);

}