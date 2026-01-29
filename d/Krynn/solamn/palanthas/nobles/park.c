/* Mortis 11.2005 */

#include "../local.h"
#include CLOCKH
#include <cmdparse.h>
#include <macros.h>

inherit NOBLE_BASE;

#define FOUND_HEDGE_CRAWLSPACE  "_found_hedge_crawlspace"

#include "fountain_drink.h"

string
query_to_jail()
{
	return "east";
}

// Prototypes
int stupid_search();

object fountain;
object bench;
object city_board;

nomask public string
get_time_desc()
{
    string desc = "";
	string road = "Fields of low, firm grass spread out across the nobles "
	+ "park of Palanthas stretching to the north and south surrounding "
	+ "small oases of artfully arranged, exotic flowers, bushes, and "
	+ "short trees.  A hedge of tall bushes forms a wall to the west "
	+ "running the length of the park.  Around the water-sprouting "
	+ "fountain at the park's center wraps a series of marble benches "
	+ "and a white gravel path which exits the park to the east.  ";
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	desc += road + "A cool, misty breeze blows south from the bay as rays of "
	+ "pale purple light from the sun rising above the hedge in the east "
	+ "catch the top of the fountain's streams in sparkling bands of purple "
	+ "and silver before they arc back down with tinkling bloops into the "
	+ "stone pool below.\n";
	break;
	
    case TOD_DAY:
	desc += road + "A cool breeze blows south from the bay as the fountain's "
	+ "streams sparkle in the midday sun before arcing back down with tinkling "
	+ "bloops into the stone pool below.\n";
	break;

    case TOD_TWILIGHT:
	desc += road + "A cool, misty breeze blows south from the bay as the "
	+ "last rays of the sun setting behind the western hedge catch the top "
	+ "of the fountain's streams before they arc back down with tinkling "
	+ "bloops into the stone pool below.\n";
    break;

    case TOD_NIGHT:
	desc += road + "The moon and stars shed pale light across the low grass "
	+ "of the nobles park as a cool, night breeze blows south from the bay.  "
	+ "Moonlight catches silver streams from the fountain as they arc back "
	+ "down with tinkling bloops into the stone pool below.\n";
    break;

    default:
	break;
    }
    return desc;
}

void
reset_palan_room()
{
	if (!city_board)
	{
		city_board = clone_object(NOBLE + "obj/palanthas_board");
		city_board->move(TO);
	}

    if (!fountain)
    {
		fountain = clone_object(NOBLE + "obj/fountain");
		fountain->move(TO);
    }

    if(!bench)
	{
		bench = clone_object(NOBLE + "obj/parkbench");
		bench->move(TO);
	}
}

void create_palan_room()
{
    SHORT("In the nobles park of Palanthas");
    LONG("@@get_time_desc@@");

	ITEM(({"hedge", "hedges", "bush", "bushes"}), "A tall hedge of well "
	+ "tended and cultured bushes trimmed and squared off on all sides "
	+ "rises over ten feet to your west running north and south.  It is "
	+ "too dense to peer all the way through.  The base of the bushes "
	+ "reveals their roots are thick as small trees.\n");
	ITEM(({"base", "roots"}), "Thick roots as wide as small trees rise from "
	+ "the ground up to the heights of the hedge.  These bushes must be old "
	+ "and very well tended." + "@@aware_hedge@@" + "\n");
	ITEM("fountain", "The fountain is a small scale replica of the Tower of "
	+ "Arms in the Merchants district.  Rising from a white, marble pool, "
	+ "it stands nearly eight feet.  Streams of water arc high into the "
	+ "air from the tops of its four corners before falling with tinkling "
	+ "bloops into the stone pool below.\n");
	ITEM(({"flower", "flowers", "oasis", "oases", "tree", "trees"}),
	  "Small oases of artfully arranged, exotic flowers, bushes, and "
	+ "short trees dot the park amidst its lush green fields of grass.  "
	+ "The flowers especially must have been planted by a skilled gardener "
	+ "as their naturally growing beauty and arrangement is quite striking."
	+ "\n");
	ITEM(({"field", "fields", "grass"}), "Fields of low, firm grass cover "
	+ "the park.  The grass itself is over half a foot high and so lush and "
	+ "thick that you hardly sink into it while on it.  It's like walking "
	+ "on carpet.\n");
	ITEM("pool", "A stone pool nearly twenty feet across is set in the "
	+ "middle of the park.  Streams of water from out the top of the tower "
	+ "fountain in its center arc into the pool which is several feet "
	+ "deep.\n");

	CMD(({ "water", "from fountain", "water from fountain" }), "drink",
		drink_water);
	CMD(({"fountain", "tall fountain", "marble fountain", "tower "
	+ "fountain", "tall marble tower fountain", "tall marble fountain",
	  "tall tower fountain", "marble tall tower", "bench", "benches"}),
		"search", stupid_search);


	add_prop(OBJ_I_CONTAIN_WATER, 1);

	set_tell_time(140);
	add_tell("There is a rustling from the hedge to the west.  A blue "
	+ "bird flaps vigorously as it flies out from the top.\n");
	add_tell("There is a slight rustling from an oasis of flowers and "
	+ "bushes in the northwest.\n");
	add_tell("The hedges in the west rustle briefly as the breeze picks "
	+ "up momentarily.\n");
	add_tell("As the wind picks up, leaves are blown from the hedges and "
	+ "trees.\n");
	add_tell("A pigeon alights in a small tree to the southeast.\n");
	add_tell("A white rabbit pops up in the oasis of flowers to the "
	+ "southwest, munches on a stalk, and then is gone back down.\n");
	add_tell("A nearby bird trills sweetly, but you did not see from "
	+ "where it sang.\n");
	add_tell("Puffy clouds float lazily by overhead.\n");
	add_tell("A page hurries by looking for someone.\n");
	add_tell("A lamp atop a tall lamppost by the gravel path exiting the "
	+ "park flickers briefly.\n");
	add_tell("Water streams out of the four corners atop the fountain "
	+ "before arcing into the stone pool below with tinkling bloops.\n");
	add_tell("Water streams out of the four corners atop the fountain "
	+ "before arcing into the stone pool below with tinkling bloops.\n");
	add_tell("Water streams out of the four corners atop the fountain "
	+ "before arcing into the stone pool below with tinkling bloops.\n");

	add_smell("vampire", "Cool air blowing south off the bay mingles here "
	+ "with the smells of lush, wet greenery.  The scent of blood is weak "
	+ "here.");
    add_smell("morgul", "Misty air blowing south off the bay mingles here "
	+ "with the smell of greenery.");
	add_smell("human", "Misty air blowing south off the bay mingles here with "
	+ "the smell of lush greenery and fresh air.");
	add_smell("elf", "Misty air blowing south off the bay mingles here with "
	+ "the scent of lush greenery, flowers, and water from the park.");
	add_smell("goblin", "The fresh smells of dirt and green things mix here "
	+ "with cool air blowing south off the bay.");
	add_smell("dwarf", "Misty air blowing south off the bay mingles here "
	+ "with the smells of greenery.");
	add_smell("hobbit", "Misty air blowing south off the bay mingles here "
	+ "with the fresh smells of a lush green park with fragrant flowers and "
	+ "hopefully a piece of fruit or two on some of the trees.");
	add_smell("gnome", "There's moisture in the air blowing south off the "
	+ "bay.  Adding to its salty flavor are the smells of plant life and "
	+ "flowing water.");
	add_smell("minotaur", "Misty air blowing south off the bay mingles here "
	+ "with the lush, wet scents of green growing things.");
	add_smell("halfhuman", "Misty air blowing south off the bay mingles here "
	+ "with the smell of lush greenery.");
	add_smell("halfelf", "Misty air blowing south off the bay mingles here "
	+ "with the smells of lush, wet greenery with a hint of flowers.");
	add_smell("orc", "Misty air blowing south off the bay mingles here with "
	+ "the smells of water, dirt, and plants.");
	add_smell("hobgoblin", "Misty air blowing south off the bay mingles here "
	+ "with the smells of a lush park.");
	add_smell("kender", "Misty air blowing south off the bay mingles here "
	+ "with the bright smells of plants and bushes and trees and no doubt "
	+ "pretty flowers all over.  Are there fruits or berries around?  You "
	+ "don't know yet!");
	add_smell("noldor", "Misty air blowing south off the bay mingles here "
	+ "with the smells of a human cultured park with halfway decently "
	+ "tended flowers.");
	add_smell("drow", "Moist air blowing south off the saltwater bay mingles "
	+ "here with the bizarre and foreign smells of a human cultured flowers, "
	+ "plants, and grasses.\n");
	add_smell("unknown", "You smell the park, but your race is unknown to "
	+ "the immortals!  Please mail Krynn with your race.");

	EXIT(NOBLE + "parkn", "north", 0, 0);
	EXIT(NOBLE + "parks", "south", 0, 0);
	EXIT(NOBLE + "n10", "east", 0, 0);

	reset_palan_room();

}

int
stupid_search()
{
	write("Why would you want to search that?  Are you mad?\n");
	say(QCTNAME(TP) + " contemplates a maddening search but regains "
	+ HIS(TP) + " serenity slowly.\n");
	return 1;
}

string
aware_hedge()
{
	string seehedge;

	if (TP->query_skill(110) > 50 + random(6))
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
		TP->move_living("crawling into the hedge of bushes to the west",
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

object
return_in_park(string what_be_here)
{
    object *thing_list;
    if(!sizeof(thing_list=(FIND_STR_IN_OBJECT(what_be_here, TO))))
        return 0;
    return thing_list[0];
}

mixed
return_obj_in_park()
{
    return (all_inventory(TO));
}

void
init()
{
  ::init();
  add_action(hedge_crawl, "crawl");
  add_action("action_sit", "sit");
  add_action("action_stand", "stand");
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}

int 
action_sit(string str)
{
        if(TP->query_prop(TSIT))
        {
                write("But you are already sitting on a bench! How do you "
				+ "expect to sit in two places at once?\n");
                return 1;
        }
          
        if(str == "around bench" | str == "around a bench" | 
		   str == "at bench" | str == "at a bench" | str == "by bench" |
		   str == "by a bench" | str == "bench" |
		   str == "on a bench" | str == "on the bench" |
		   str == "on one of the benches" | str == "chair at bench" |
		   str == "in chair at bench" | str == "in a chair at a bench" |
		   str == "chair by bench" | str == "in chair by bench" |
	       str == "on bench") 
        {
                TP->catch_msg("You sit down on one of the marble benches.\n");
                say(QCTNAME(TP) + " sits down in one of the marble "
				+ "benches.\n");
                TP->add_prop(TSIT, 1);
                TP->add_prop(LIVE_S_EXTRA_SHORT," is sitting on one of the "
				+ "curved marble benches");
                return 1;
        }
	
        else
        {
                TP->catch_msg("Where would you like to sit?  On a bench?\n");
                return 1;
        }
        
        return 1;
}

int 
action_stand(string str)
{
        if(str == "up" || str != "up")
        {
                if(TP->query_prop(TSIT))
                {
                        
                        TP->catch_msg("You stand up and leave the bench.\n");
                        say(QCTNAME(TP)+" stands up from the bench.\n");
                        TP->remove_prop(TSIT);
                        TP->remove_prop(LIVE_S_EXTRA_SHORT);
                        return 1;
                }

        }
        
        else
        {
                TP->catch_msg("Stand?  Stand up?\n");
                return 1;
        }
        
        return 1;
}

void leave_inv(object ob, object to)
{
        ::leave_inv(ob, to);    
        
        if(!objectp(to) || !objectp(ob))
                return;
                
        if(TP->query_prop(TSIT))
        {
                TP->catch_msg("You stand up from the bench before leaving.\n");
                say(QCTNAME(TP) + " stands up from the bench as "+ HE(TP) +" leaves.\n");
                TP->remove_prop(LIVE_S_EXTRA_SHORT);
                TP->remove_prop(TSIT);
        }

}

int
park_closed()
{
	write("Though the park stretches in that direction, there isn't "
	+ "anything else to see now.\n");
	return 1;
}
