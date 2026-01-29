/* Mortis 12.2005
 * Smells
 * Alleys northward
 */

#include "../local.h"
#include CLOCKH

inherit MERCH_BASE;

string
query_to_jail()
{
  return "north";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  To the west is a wide, marble shop.  A great white "
	+ "banner stretches across its second floor.  To the south is a "
	+ "three-story building of ornate marble with thick double doors of "
	+ "dark iron bearing engraved gold letters, and east is an inn of "
	+ "marble at its base and shingled wood comprising its second story.  "
	+ "A wooden sign swings from a dark iron rod above its door.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The clean marble of the shops and buildings of this court "
	+ "glows in " + one_of_list(({"pale purple ", "soft pink ",
	  "pale orange ", "grey and pink "})) + "hues as the sun peeks above the "
	+ "mountains in the east.  The air is rich with the smells of morning "
	+ "cooking and coffee borne on a cool, misty breeze." + road;
	break;

    case TOD_DAY:
	desc += "The worn marble of the shops and buildings of this court lights "
	+ "up in the midday sun as travellers, merchants, and shoppers travel "
	+ "throughout the Merchant quarter filling the street with the noisy "
	+ "murmurings of their daily business." + road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of the shops and buildings of this court "
	+ "catches the last rays of the sun appearing to glow of its own accord "
	+ "as travellers and merchants make their way about the "
	+ "street." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of the shops and buildings of this court amplifying the yellow glow of "
	+ "the street lamps.  A few people still make their way about at this "
	+ "hour." + road;
    break;

    default:
	break;
    }
    return desc;
}

void
create_palan_room()
{
    SHORT("On Green Marble road in the center of a great deal of shops");
    LONG("@@get_time_desc@@");

	ITEM(({"green marble road", "green road", "green marble"}),
	  "The marble blocks of Green Marble road are indeed imbued with a "
	+ "tinge of light, mossy green!  There is no road like it in all the "
	+ "city.  How is it these blocks alone are tinted green?  How did it "
	+ "come to be?  Who would know such a thing?\n");
	ITEM("shops", "This district is thick with a variety of shops.\n");
	ITEM(({"west shop", "marble shop", "wide shop", "wide marble shop"}),
		   "A great white banner stretches across the second story of this "
	+ "wide, marble shop.  It appears very busy at all hours, thus its door "
	+ "is left propped open.\n");
	ITEM(({"banner", "white banner"}), "A banner of white sailcloth "
	+ "stretches on white cords across the second floor of the shop to your "
	+ "west.  Its simple black lettering done in the ancient style reads "
	+ "\"Morti's General Trader\".\n");
	ITEM(({"bank", "south building", "three-story building", "double doors",
		   "double doors of dark iron", "iron doors", "dark doors",
		   "dark iron doors"}), "A pair of dark iron double doors leads "
	+ "south into the three-story building of thick marble before you.  Its "
	+ "upper windows are barred.  Upon the dark iron doors are recessed "
	+ "letters done in the ancient style and perfectly leafed in gold "
	+ "reading \"City Bank of Palanthas\".\n");
	ITEM(({"the green twitch", "green twitch", "the green twitch inn",
		  "green twitch inn", "inn"}), "From its base of marble blocks, the "
	+ "inn to your east's second story has been added onto with wood covered "
	+ "by wood shingling from which rises a beige, brick chimney giving it a "
	+ "warm appeal.  A wooden sign hanging from an iron rod above the door "
	+ "reads \"The Green Twitch Inn\".\n");
	ITEM(({"wood sign", "wooden sign", "sign"}), "It's a wooden sign hanging "
	+ "from an iron rod above the door of the inn to the east.  Carved into "
	+ "its wood are the words \"The Green Twitch Inn\".\n");
	ITEM(({"rod", "iron rod"}), "It's a simple, dark iron rod protruding from "
	+ "above the door of the inn to the east.  From it hangs a wooden "
	+ "sign.\n");

	CMD("banner", "read", "@@read_banner");
	CMD(({"doors", "letters", "engraved letters", "gold letters"}), "read",
		  "@@read_letters");
	CMD("sign", "read", "@@read_sign");

	EXIT(MERCH + "m02", "north", 0, 0);
	EXIT(MERCH + "shop", "west", 0, 0);
	EXIT(MERCH + "bank", "south", 0, 0);
	EXIT(MERCH + "green_twitch", "east", 0, 0);

}

read_banner()
{
	write("In simple black lettering done in the ancient style is written "
	+ "\"Morti's General Trader\" upon the white banner over the shop to "
	+ "your east.\n");
	return 1;
}

read_letters()
{
	write("Recessed letters covered with gold leaf set into the dark iron "
	+ "double doors in the south building read \"City Bank of Palanthas\"."
	+ "\n");
	return 1;
}

read_sign()
{
	write("Freshly carved into the wood of the sign hanging above the door "
	+ "of the inn to your east are the words \"The Green Twitch Inn\".\n");
	return 1;
}
