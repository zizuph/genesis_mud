/* Mortis 12.2005
 * Smells of businesses.
 */

#include "../local.h"
#include CLOCKH

inherit MERCH_BASE;

string
query_to_jail()
{
  return "south";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  Emptoris Row continues south out of the arms district, "
	+ "and ends here in a cul-de-sac of shops.  From the low building to "
	+ "the north pours black smoke from a wide chimney, and the distinctive "
	+ "metal on metal hammering noises give it away as the smithy.  Above "
	+ "the door of the two-story shop to the east hangs a taut, leather "
	+ "banner.  A thin, palewood sign is hung on the door of the small "
	+ "shop to the west.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The worn marble of Emptoris Row and its buildings "
	+ "glows in " + one_of_list(({"pale purple ", "soft pink ",
	  "pale orange ", "grey and pink "})) + "hues as the sun peeks above the "
	+ "mountains in the east.  The air is rich with the smells of morning "
	+ "cooking and coffee borne on a cool, misty breeze." + road;
	break;

    case TOD_DAY:
	desc += "The worn marble of Emptoris Row and its buildings lights up "
	+ "in the midday sun as travellers, merchants, and shoppers travel "
	+ "throughout the Merchant quarter filling the street with the noisy "
	+ "murmurings of their daily business." + road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Emptoris Row catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as travellers and merchants make their way about the "
	+ "street." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Emptoris Row amplifying the yellow glow of the street lamps.  "
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
    SHORT("At Emptoris Row's end in a cul-de-sac");
    LONG("@@get_time_desc@@");

	ITEM(({"sign", "thin sign", "palewood sign", "thin palewood sign"}),
	  "A thin and flimsy piece of yellowing palewood, the words "
	+ "\"Sachmun Tanner\" are written in black.  It hangs on the door "
	+ "of the west shop.\n");
	ITEM(({"banner", "taut banner", "leather banner", "taut leather banner"}),
	  "Stretched taut, this sturdy leather banner is hung by cords at each "
	+ "of its corners tied to bolts above the door of the shop to the east.  "
	+ "Seared into the leather in perfect ancient style print are the "
	+ "words \"Leather Arms\".\n");
	ITEM(({"smith", "smithy", "forge", "north shop", "north building"}),
	  "Built of translucent marble blocks, the smithy is a solid building "
	+ "with a wide, brick chimney from which pours puffy, black smoke.  "
	+ "Chiseled above its doorsill in simple letters is \"Smith\".\n");
	ITEM(({"small shop", "west shop"}), "A small, one-story shop is to "
	+ "your west.  Its windows are darkened and filmy, but its outside "
	+ "marble is clean.\n");
	ITEM(({"east shop", "two-story shop"}), "The two-story, marble shop "
	+ "to your east has a taut, leather banner strung above its doorway.\n");

	CMD(({"sign", "thin sign", "palewood sign"}), "read", "@@read_sign");
	CMD(({"banner", "leather banner", "taut banner"}), "read", "@@read_ban");

	add_smell("vampire", "Misty air blowing south off the bay mingles here "
	+ "with the harsh smells of tanning fluids to the west, coal smoke from "
	+ "the north, and rich leather to the east.  The smell of blood is all "
	+ "around you in this busy cul-de-sac.");
	add_smell("morgul", "Misty air blowing south off the bay mingles here "
	+ "with the harsh smells of tanning fluids to the west, coal smoke from "
	+ "the north, and rich leather to the east.");
	add_smell("human", "Misty air blowing south off the bay mingles here "
	+ "with the harsh smells of tanning fluids to the west, coal smoke from "
	+ "the north, and rich leather to the east.");
	add_smell("elf", "Misty air blowing south off the bay mingles here "
	+ "with the pungent and harsh smells of tanning fluids used by humans "
	+ "in the west, thick, polluting, coal smoke from the north, and rich "
	+ "leather tones to the east.");
	add_smell("goblin", "Misty air blowing south off the bay mingles here "
	+ "with the appealing smells of skin tanning fluids in the west, "
	+ "thick coal smoke from the north, and rich leather in the east.");
	add_smell("dwarf", "Warm, moist air blowing south off the bay mingles "
	+ "here with the pungent smells of tanning fluids used by humans in the "
	+ "west, coal smoke from the north, and rich leather tones, likely from "
	+ "armour, in the east.  If only this were underground, you'd be right "
	+ "at home.");
	add_smell("hobbit", "Misty air blowing south off the bay mingles here "
	+ "with the nose turning smells of pungent tanning fluids in the west, "
	+ "nasty coal smoke from the north, and rich, warm leather tones in "
	+ "the east.  Nothing pleasant to eat or drink reaches your nose here.");
	add_smell("gnome", "Misty air blowing south off the bay mingles here "
	+ "with the strong, pungent smells of pungent tanning fluids commonly "
	+ "used by human tanners in the west, thin black smoke from a human "
	+ "smithy in the north, and rich leather tones from leather armours to "
	+ "the east.  Quite an industrial, little human cul-de-sac this "
	+ "Emporium Row.");
	add_smell("minotaur", "Misty air blowing south off the bay mingles here "
	+ "with the appealing smells of skin tanning fluids in the west, "
	+ "thick coal smoke from the north, and rich leather to the east "
	+ "although the strongest smell is the pervasive scent of men all "
	+ "around you in this busy cul-de-sac.");
	add_smell("halfhuman", "Misty air blowing south off the bay mingles here "
	+ "with the harsh smells of tanning fluids to the west, coal smoke from "
	+ "the north, and rich leather to the east.");
	add_smell("halfelf", "Misty air blowing south off the bay mingles here "
	+ "with the harsh smells of tanning fluids in the west, coal smoke from "
	+ "the north, and rich leather to the east.");
	add_smell("orc", "Misty air blowing south off the bay mingles here "
	+ "with the appealing smells of skin tanning fluids in the west, "
	+ "thick coal smoke from the north, and rich leather to the east "
	+ "although the strongest smell is the pervasive scent of manflesh "
	+ "all around you in this busy cul-de-sac.");
	add_smell("hobgoblin", "Misty air blowing south off the bay mingles here "
	+ "with the appealing smells of skin tanning fluids used by human "
	+ "tanners in the west, thick coal smoke from the north, and rich "
	+ "leather to the east, likely from armour.");
	add_smell("kender", "Misty air blowing south off the bay mingles here "
	+ "with the nose tickling smells of pungent tanning fluids in the west, "
	+ "puffy coal smoke from the north, and rich, warm leather tones in "
	+ "the east.  Such an industrial cul-de-sac to explore even without "
	+ "any hints of tasty food or drink.");
	add_smell("drow", "Misty air blowing south off the bay mingles here "
	+ "with the appealing smells of skin tanning fluids used by human "
	+ "tanners in the west, thick coal smoke from the north, and rich "
	+ "leather to the east, likely from armour.");
	add_smell("noldor", "Misty air blowing south off the bay mingles here "
	+ "with the pungent and harsh smells of tanning fluids used by humans "
	+ "in the west, thick, polluting, coal smoke from the north, and rich "
	+ "leather tones to the east.");
	add_smell("uruk", "Misty air blowing south off the bay mingles here "
	+ "with the appealing smells of skin tanning fluids in the west, "
	+ "thick coal smoke from the north, and rich leather to the east "
	+ "although the strongest smell is the pervasive scent of manflesh "
	+ "all around you in this busy cul-de-sac.");
	add_smell("presence", "This isn't the best form to appreciate the "
	+ "mingling of the harsh smells from the west, coal smoke from the "
	+ "north, and leather from the east mingling with the misty air "
	+ "blowing south off the bay.");
	add_smell("unknown", "You smell the misty air mingling with harsh "
	+ "tanning fluids, coal smoke, and leather, but what the heck race "
	+ "are you?  Why not mail Krynn for fun?");

	EXIT(MERCH + "smith", "north", 0, 0);
	EXIT(MERCH + "leather", "east", 0, 0);
	EXIT(MERCH + "m12", "south", 0, 0);
	EXIT(MERCH + "tanner", "west", "@@place_closed", 0);

}

read_sign()
{
	write("Written with iron bars in a simple form of the ancient style, "
	+ "it reads, \"Kaysee's Tanner\".\n");
	return 1;
}

read_ban()
{
	write("The taut, leather banner reads, \"Leather Arms\".\n");
	return 1;
}

int
place_closed()
{
	write("Certain chemicals employed by the tanner are under review by "
	+ "the Bureaumancers for their safety in the public habitat.\n");
	return 1;
}
