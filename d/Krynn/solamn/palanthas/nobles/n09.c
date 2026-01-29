/* Mortis 11.2005 */

#include "../local.h"
#include CLOCKH

inherit NOBLE_BASE;

#define FOUND_HEDGE_CRAWLSPACE  "_found_hedge_crawlspace"

string
query_to_jail()
{
  return "north";
}

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "  To the southwest is the Greystone Inn, and to the east "
	+ "is a tall hedge of bushes.  The street continues north ending in an "
	+ "intersection with Nobles' Way.\n";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += "The pristine marble of Havecius Court and its buildings "
	+ "glows in pale purple hues as the sun peeks above the mountains.  "
	+ "A cool, misty breeze blows south from the bay." + road;
	break;

    case TOD_DAY:
	desc += "The pristine marble of Havecius Court and its buildings "
	+ "gleams in the midday sun as people walk about filling the court "
	+ "with the gentle murmurings of their daily business." + road;
	break;

    case TOD_TWILIGHT:
	desc += "The translucent marble of Havecius Court catches the "
	+ "last rays of the sun appearing to glow of its own accord "
	+ "as well-dressed citizens make their way about the court." + road;
    break;

    case TOD_NIGHT:
	desc += "The moon and stars shed pale light across the translucent marble "
	+ "of Havecius Court amplifying the yellow glow of the street lamps.  "
	+ "A few people still make their way about at this hour." + road;
    break;

    default:
	break;
    }
    return desc;
}

void create_palan_room()
{
    SHORT("On Havecius Court south of Nobles' Way in the nobles district");
    LONG("@@get_time_desc@@");

	ITEM(({"hedge", "hedges", "bush", "bushes"}), "A tall hedge of well "
	+ "tended and cultured bushes trimmed and squared off on all sides "
	+ "rises over ten feet to your east running north and south.  It is "
	+ "too dense to peer all the way through.  The base of the bushes "
	+ "reveals their roots are thick as small trees.\n");
	ITEM(({"base", "roots"}), "Thick roots as wide as small trees rise from "
	+ "the ground up to the heights of the hedge.  These bushes must be old "
	+ "and very well tended." + "@@aware_hedge@@" + "\n");

	add_smell("vampire", "Misty air blowing south off the bay mingles here "
	+ "with the smells of lush, wet greenery to the east and human food "
	+ "to the southwest where the smell of blood is also strong.");
    add_smell("morgul", "Misty air blowing south off the bay mingles here "
	+ "with the smell of greenery to your east and cooking to the southwest.");
	add_smell("human", "Misty air blowing south off the bay mingles here with "
	+ "the smell of lush greenery to the east and fresh cooking to the "
	+ "southwest.");
	add_smell("elf", "Misty air blowing south off the bay mingles here with "
	+ "the scent of lush greenery, flowers, and water from the park over "
	+ "the hedge to the east and the smells of human food cooking to the "
	+ "southwest.");
	add_smell("goblin", "The fresh smells of dirt and green things from the "
	+ "east mix here with human food to the southwest and misty air blowing "
	+ "south off the bay.");
	add_smell("dwarf", "Misty air blowing south off the bay mingles here "
	+ "with the smells of greenery to your east and warm human food cooking "
	+ "to the southwest.");
	add_smell("hobbit", "Misty air blowing south off the bay mingles here "
	+ "with the fresh smells of a lush green park through the hedges to "
	+ "your east and a human inn to the southwest which, judging by the "
	+ "smells of cooking, most assuredly has a well stocked kitchen.");
	add_smell("gnome", "There's moisture in the air blowing south off the "
	+ "bay.  Adding to its salty flavor are the smells of plant life and "
	+ "flowing water to the east and human cooking odours to the "
	+ "southwest.");
	add_smell("minotaur", "Misty air blowing south off the bay mingles here "
	+ "with the lush, wet scents of green growing things to the east and "
	+ "human food to the southwest.");
	add_smell("halfhuman", "Misty air blowing south off the bay mingles here "
	+ "with the smell of lush greenery to the east and fresh cooking to the "
	+ "southwest.");
	add_smell("halfelf", "Misty air blowing south off the bay mingles here "
	+ "with the not unfamiliar smells of human cooking to your southwest "
	+ "and lush, wet greenery with a hint of flowers to your east.");
	add_smell("orc", "Misty air blowing south off the bay mingles here with "
	+ "the smells of human food to the southwest and water, dirt, and "
	+ "plants to your east.");
	add_smell("hobgoblin", "Misty air blowing south off the bay mingles here "
	+ "with the smells of a well run inn to the southwest and a lush park "
	+ "over the hedges to your east.");
	add_smell("kender", "Misty air blowing south off the bay mingles here "
	+ "with the bright smells of plants and bushes and trees and no doubt "
	+ "pretty flowers over the imposing hedge to your east and warm cooking "
	+ "along with who knows how many interesting objects from the inn to "
	+ "the southwest perhaps.");
	add_smell("noldor", "Misty air blowing south off the bay mingles here "
	+ "with the smells of a human cultured park on the other side of the "
	+ "hedges to your east.  From the southwest comes the typical smell of "
	+ "an active noble human inn.");
	add_smell("unknown", "You smell the park to your east and inn to the "
	+ "southwest, but your race is unknown to the immortals!  Please mail "
	+ "Krynn with your race.");

	CMD(({"into bushes", "into hedge"}), ({"crawl"}), "@@hedge_crawl");

	EXIT(NOBLE + "grey_ent", "southwest", "@@grey_closed", 0);
	EXIT(NOBLE + "er2", "north", 0, 0);

}

string
aware_hedge()
{
	string seehedge;

	if (TP->query_skill(110) > 40 + random(6))
	{	
		TP->add_prop(FOUND_HEDGE_CRAWLSPACE, 1);
		seehedge = "  You notice a space between two of the larger root "
		+ "bases you may crawl into.";
	}
	else
	{   seehedge = ""; }
	return seehedge;
}

int
hedge_crawl(string arg)
{
	if (TP->query_prop(FOUND_HEDGE_CRAWLSPACE) == 1 )
	{

	   if (strlen(arg) == 0)
		{ write("Crawl into what?\n");
	      return 1; }

       if (parse_command(arg, ({}),
	   "'between' / 'in' / 'into' [the] 'bushes' / 'hedge' / 'crawlspace' / 'space' / 'roots'"))
		{
		write("You crawl between a pair of large roots into the hedge.\n"); 
		TP->move_living("crawling into the hedge of bushes to the east",
		NOBLE + "hedge", 1, 0);
		tell_room(NOBLE + "park", one_of_list(({
			"The hedge of bushes to the west rustles briefly.",
			"A small, blue bird flutters out of the hedges to the west.",
			"A furry marmot scampers out of the bushes in the west and "
		  + "darts away to the north.",
			"The wind rustles through the bushes shaking a few leaves "
		  + "to the ground.",
			"A twig snaps in the bushes to the west."}))
		  + "\n");
		 return 1;
		}
		write("Crawl into what?\n");
		return 1;
     }
	notify_fail("What?\n");
}

void
init()
{
  ::init();
  add_action(hedge_crawl, "crawl");
}

int
grey_closed()
{
	write("The Greystone Inn is closed for repairs.\n");
	return 1;
}
