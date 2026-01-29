/* Mortis 11.2005
 * Alleys into surroundings?  Need smells?  Thinking
 * we can use them to tip off how to climb up on the
 * south building.  Watch people moving from gate,
 * way into N?
 */

#include "../local.h"
#include CLOCKH

inherit NOBLE_BASE;

string
query_to_jail()
{
  return "southwest";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  The buildings are packed in tightly here in the "
	+ "alleyway between Knight's High road to the southwest and Old Circle "
	+ "to the southeast.\n";
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
	desc += "The translucent marble of Palanthas Circle and its buildings "
	+ "catches the last rays of the sun appearing to glow of its own accord "
	+ "as well-dressed citizens make their way about the street." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Palanthas Circle and its buildings amplifying the yellow glow of the "
	+ "street lamps.  A few people still make their way about at this hour."
	+ road;
    break;

    default:
	break;
    }
    return desc;
}

void
create_palan_room()
{
    SHORT("In an alley between Knight's High road and Old Circle");
    LONG("@@get_time_desc@@");

	ITEM(({"estates", "estate", "noble estate", "noble estates"}),
	  "Through the buildings to the north can be seen some of the "
	+ "larger noble estates among the other marble buildings.\n");
	
/*	add_smell("vampire", "Misty air blowing south off the bay mingles here "
	+ "with the smells of lush, wet greenery to the northwest and noble "
	+ "dwellings to the east where the scent of blood catches your "
	+ "attention.");
    add_smell("morgul", "Misty air blowing south off the bay mingles here "
	+ "with the smell of greenery to your northwest.");
	add_smell("human", "Misty air blowing south off the bay mingles here with "
	+ "the smell of lush greenery to the northwest and perfumes to the east.");
	add_smell("elf", "Misty air blowing south off the bay mingles here with "
	+ "the scent of lush greenery, flowers, and water from the park through "
	+ "the hedge to the northwest and the smells of a noble human dwelling "
	+ "to the east.");
	add_smell("goblin", "The fresh smells of dirt and green things from the "
	+ "northwest mix here with misty air blowing south off the bay.");
	add_smell("dwarf", "Misty air blowing south off the bay mingles here "
	+ "with the smells of greenery to your northwest.");
	add_smell("hobbit", "Misty air blowing south off the bay mingles here "
	+ "with the fresh smells of a lush green park through the hedges to "
	+ "your northwest and human estates to the east which, judging by the "
	+ "perfumes, must be lovely places.");
	add_smell("gnome", "There's moisture in the air blowing south off the "
	+ "bay.  Adding to its salty flavor are the smells of plant life and "
	+ "flowing water to the northwest and human dwelling odours to the "
	+ "east.");
	add_smell("minotaur", "Misty air blowing south off the bay mingles here "
	+ "with the lush, wet scents of green growing things to the northwest "
	+ "and man house smells to the east.");
	add_smell("halfhuman", "Misty air blowing south off the bay mingles here "
	+ "with the smell of lush greenery to the wnorthest and the hint of "
	+ "perfumes to the east.");
	add_smell("halfelf", "Misty air blowing south off the bay mingles here "
	+ "with the not unfamiliar smells of human perfumes from the estates to "
	+ "your east and lush, wet greenery with a hint of flowers to your "
	+ "northwest.");
	add_smell("orc", "Misty air blowing south off the bay mingles here with "
	+ "the smells of human estates to the east and water, dirt, and "
	+ "plants to your northwest.");
	add_smell("hobgoblin", "Misty air blowing south off the bay mingles here "
	+ "with the smells of a well to do estate to the east and a lush park "
	+ "through the hedges to your northwest.");
	add_smell("kender", "Misty air blowing south off the bay mingles here "
	+ "with the fresh smells of a lush green park through the hedges to "
	+ "your northwest and human estates to the east which, judging by the "
	+ "perfumes, must be lovely places.");
	add_smell("noldor", "Misty air blowing south off the bay mingles here "
	+ "with the smells of a human cultured park through the hedges to your "
	+ "northwest.  From the east come the typical smells of noble human "
	+ "estates.");
	add_smell("unknown", "You smell the park to the northwest and estate "
	+ "to the east, but your race is unknown to the immortals!  Please mail "
	+ "Krynn with your race.");*/

	EXIT(NOBLE + "ser6", "southwest", 0, 0);
	EXIT(NOBLE + "w10", "southeast", 0, 0);

}