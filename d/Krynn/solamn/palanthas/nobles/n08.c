/* Mortis 11.2005
 * Possible alley access to western estates
 */

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
	string road = "  Through the buildings to the west are a pair of large "
	+ "noble estates.  Palanthas Circle curves through the noble district "
	+ "north towards Scholar's Walk and south where it intersects with "
	+ "Nobles' Way.  To the east is the Court d'Plaisiri, the heart of the "
	+ "Plaisir district.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The pristine marble of Palanthas Circle and its buildings "
	+ "glows in pale purple hues as the sun peeks above the mountains.  "
	+ "A cool, misty breeze blows south from the bay." + road;
	break;

    case TOD_DAY:
	desc += "The pristine marble of Palanthas Circle and its buildings "
	+ "gleams in the midday sun as nobles, their servants, and retinues "
	+ "walk to and from the court." + road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Palanthas Circle catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as well-dressed citizens make their way about the court." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Palanthas Circle amplifying the yellow glow of the street lamps.  "
	+ "Many people still make their way about at this hour." + road;
    break;

    default:
	break;
    }
    return desc;
}

void
create_palan_room()
{
    SHORT("On Palanthas Circle west of the Plaisir district");
    LONG("@@get_time_desc@@");

	ITEM(({"estate", "estates", "noble estate", "noble estates"}), "You see "
	+ "a pair of estates off through the buildings to your west, one to the "
	+ "north and south.  Their architecture is typical of the old buildings "
	+ "of marble rising several stories here in the noble district.\n");

	add_smell("vampire", "Misty air blowing south off the bay mingles here "
	+ "the scents of fragrant flowers, greenery, and perfumes though they "
	+ "pale to the smell of noble family blood coming from the estates to "
	+ "the west.  There is an enticingly ripe scent of blood from the "
	+ "east as well.");
    add_smell("morgul", "Misty air blowing south off the bay mingles here "
	+ "with the smell of fragrant, green courtyards to the west and odd "
	+ "perfumes east.");
	add_smell("human", "Misty air blowing south off the bay mingles here with "
	+ "the smell of fragrant greenery in the noble estate courtyards with a "
	+ "hint of perfume from the west and exotic, alluring fragrances from the "
	+ "eastern court.");
	add_smell("elf", "Misty air blowing south off the bay mingles here with "
	+ "the smells of non-native flowers, cultivated bushes, and trees bred "
	+ "for diminutive stature as well as overpowering human perfumes from "
	+ "the western estates.  The fragrances from the court to the east are "
	+ "oddly alluring.");
	add_smell("goblin", "Flowery plants and things and fruity smells from "
	+ "the west mix here with misty air blowing south off the bay and the "
	+ "sick smells of humanfumes to the east.");
	add_smell("dwarf", "Misty air blowing south off the bay mingles here "
	+ "with the smells of human dwellings and gardens.  The weird fragrances "
	+ "from the court to the east make you want to sneeze.");
	add_smell("hobbit", "Misty air blowing south off the bay mingles here "
	+ "with the fragrances of flowery perfumes and flowery gardens, but the "
	+ "occasional roasted scent leads you to believe the estates in the "
	+ "west are likely to have well stocked kitchens.  An array of new "
	+ "perfumey smells call alluringly from the court to the east.");
	add_smell("gnome", "There's moisture in the air blowing south off the "
	+ "bay.  Adding to its salty flavor are the smells of flowers, bushes, "
	+ "and human scent flavourings from the western estates and human "
	+ "perfumes designed for attracting mates from the eastern court.");
	add_smell("minotaur", "Misty air blowing south off the bay mingles here "
	+ "with the smells of gardeny courtyards and man perfumes from the "
	+ "western estates and pretty man fragrances from the court to the "
	+ "east.");
	add_smell("halfhuman", "Misty air blowing south off the bay mingles here "
	+ "with the smell of fragrant greenery in the noble estate courtyards "
	+ "with a hint of perfume from the west and exotic, alluring fragrances "
	+ "from eastern court.");
	add_smell("halfelf", "Misty air blowing south off the bay mingles here "
	+ "with the not unfamiliar smells of human perfumes from the nearby "
	+ "estates and alluringly exotic fragrances from the eastern court.");
	add_smell("orc", "Misty air blowing south off the bay mingles here with "
	+ "the smell of greenery from the courtyards of the estates to the west "
	+ "and bizarre, pretty manfumes from the eastern court.");
	add_smell("hobgoblin", "Misty air blowing south off the bay mingles here "
	+ "with the smells of extensively tended green courtyards of flower "
	+ "things and the perfumed halls of noble human estates to the west and "
	+ "flowery manfumes from the court to the east.");
	add_smell("kender", "Misty air blowing south off the bay mingles here "
	+ "with the delightful blend of fragrances from flowery perfumes and "
	+ "flowery gardens, but the occasional roasted scent leads you to "
	+ "believe the estates in the west are likely to have well stocked "
	+ "kitchens as well as unimaginably exciting objects of interest from "
	+ "foreign lands, maybe.  An array of new perfumey smells call "
	+ "enticingly from the court to the east.");
	add_smell("noldor", "Misty air blowing south off the bay mingles here with "
	+ "the smells of non-native flowers, cultivated bushes, and trees bred "
	+ "for diminutive stature as well as overpowering human perfumes from "
	+ "the western estates so typically used by men without taste.  The "
	+ "perfumes from the east, however, are somewhat alluring.");
	add_smell("unknown", "You smell flowers and perfumes and such, but "
	+ "your race is unknown to the immortals!  Please mail Krynn with your "
	+ "race.");

	EXIT(NOBLE + "n04", "north", 0, 0);
	EXIT(NOBLE + "nplaza", "east", 0, 0);
	EXIT(NOBLE + "er3", "south", 0, 0);

}
