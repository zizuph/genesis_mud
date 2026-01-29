/* Mortis 11.2005 */

#include "../local.h"
#include CLOCKH

inherit NOBLE_BASE;

object inndoor;

string
query_to_jail()
{
  return "northeast";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "The pristine marble of Havecius Court changes gradually "
	+ "here to polished granite becoming a wide, grey path to the doorstep "
	+ "of the Greystone Inn, a great, three-story, granite building "
	+ "fashioned after a manor house of the ancient style.  ";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += road + "A cool, misty breeze blows south from the bay as the "
	+ "sun peeks above the mountains lighting the sky and stones in pale "
	+ one_of_list(({"purple", "orange", "pink", "grey and purple"}))
	+ " hues.\n";
	break;

    case TOD_DAY:
	desc += road + "The midday sun shines down upon the stonework as a "
	+ "breeze occasionally blows south from the bay.\n";
	break;

    case TOD_TWILIGHT:
	desc += road + "Flecks in the grey granite stonework sparkle as they "
	+ "catch the last rays of the setting sun while a cool breeze blows "
	+ "south from the bay, and well-dressed citizens make their way about "
	+ "the court to the northeast.\n";
    break;

    case TOD_NIGHT:
	desc += road + "The moon and stars shed pale light across the "
	+ "translucent marble and polished granite amplifying the yellow "
	+ "glow of the street lamps.  A few people still make their way about "
	+ "at this hour to the northeast.\n";
    break;

    default:
	break;
    }
    return desc;
}

void create_palan_room()
{
    SHORT("In the courtyard of the Greystone Inn");
    LONG("@@get_time_desc@@");

	ITEM(({"inn", "greystone", "greystone inn"}), "One of the older "
	+ "dwellings in the quarter, the Greystone Inn is a great, three-story "
	+ "building facing Havecius Court to its northeast.  Fashioned in the "
	+ "ancient style, its roof bears many worn gargoyles and a pair of "
	+ "parapets, and the outer face of its granite blocks is intentionally "
	+ "left rough hewn and unpolished.\n");
	/* Parapets artfully conceal the great chimneys. */
	ITEM(({"granite", "stonework", "polished granite", "granite blocks"}),
	  "The granite blocks of the wide path leading to Havecius Court are "
	+ "a half foot across and polished to a reflective gleam.  The stonework "
	+ "of the inn is intentionally left rough hewn to give it the look of "
	+ "the ancient style.  The granite was imported generations ago and "
	+ "contains tiny silver flecks that sparkle when the sun hits them just "
	+ "right.\n");
	ITEM("path", "As Havecius Court approaches the Greystone from the "
	+ "northeast, its pristine marble blocks are gradually replaced with "
	+ "polished granite blocks creating a symmetric pattern making it "
	+ "appear as if granite shadows of the inn's parapets were spreading "
	+ "into the white marble like the rays of a grey sun.\n");
	ITEM(({"parapet", "parapets"}), "Two sizeable, crenallated parapets of "
	+ "granite rise from the roof of the Greystone Inn.\n");

	add_smell("vampire", "Misty air blowing south off the bay mingles here "
	+ "with the smells of lush, wet greenery to the northeast and human food "
	+ "from the inn where the smell of blood is also strong.");
    add_smell("morgul", "Misty air blowing south off the bay mingles here "
	+ "with the smell of greenery to your northeast and cooking from the "
	+ "inn.");
	add_smell("human", "Misty air blowing south off the bay mingles here with "
	+ "the smell of lush greenery to the northeast and fresh cooking in the "
	+ "inn.");
	add_smell("elf", "Misty air blowing south off the bay mingles here with "
	+ "the scent of lush greenery, flowers, and water from the park off "
	+ "to the northeast and the smells of human food cooking in the "
	+ "inn.");
	add_smell("goblin", "The fresh smells of dirt and green things from the "
	+ "northeast mix here with human food from the inn and misty air "
	+ "blowing south off the bay.");
	add_smell("dwarf", "Misty air blowing south off the bay mingles here "
	+ "with the smells of greenery to your northeast and warm human food "
	+ "cooking at the inn.");
	add_smell("hobbit", "Misty air blowing south off the bay mingles here "
	+ "with the fresh smells of a lush green park through the hedges to "
	+ "your northeast and a human inn to the southwest which, judging by the "
	+ "smells of cooking, most assuredly has a well stocked kitchen.");
	add_smell("gnome", "There's moisture in the air blowing south off the "
	+ "bay.  Adding to its salty flavor are the smells of plant life and "
	+ "flowing water to the northeast and human cooking odours from the "
	+ "inn.");
	add_smell("minotaur", "Misty air blowing south off the bay mingles here "
	+ "with the lush, wet scents of green growing things to the northeast "
	+ "and human food from the inn.");
	add_smell("halfhuman", "Misty air blowing south off the bay mingles here "
	+ "with the smell of lush greenery to the northeast and fresh cooking at "
	+ "the inn.");
	add_smell("halfelf", "Misty air blowing south off the bay mingles here "
	+ "with the not unfamiliar smells of human cooking from the inn "
	+ "and lush, wet greenery with a hint of flowers to your northeast.");
	add_smell("orc", "Misty air blowing south off the bay mingles here with "
	+ "the smells of human food at the inn and water, dirt, and "
	+ "plants to your northeast.");
	add_smell("hobgoblin", "Misty air blowing south off the bay mingles here "
	+ "with the smells of a well run inn to the southwest and a lush park "
	+ "over the hedges to the northeast.");
	add_smell("kender", "Misty air blowing south off the bay mingles here "
	+ "with the bright smells of plants and bushes and trees and no doubt "
	+ "pretty flowers over the imposing hedge to the northeast and warm "
	+ "cooking along with who knows how many interesting objects from the "
	+ "inn to the southwest perhaps.");
	add_smell("noldor", "Misty air blowing south off the bay mingles here "
	+ "with the smells of a human cultured park on the other side of the "
	+ "hedges to the northeast.  From the southwest comes the typical "
	+ "smell of an active noble human inn.");
	add_smell("unknown", "You smell the park to your northeast and inn to "
	+ "the southwest, but your race is unknown to the immortals!  Please "
	+ "mail Krynn with your race.");

	add_alley("nw", "northwest", NOBLE + "alley006");
	add_alley("se", "southeast", NOBLE + "alley010");

	EXIT(NOBLE + "n09", "northeast", 0, 0);

	inndoor = clone_object(NOBLE_DOOR + "greystone2.c");
	inndoor->move(TO);

}
