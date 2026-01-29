/* Mortis 01.2006
 *
 * Drink sold at the Green Twitch Inn in Palanthas.
 * Can be sipped or drank whole.
 */

#include "../../local.h"
#include <language.h>
#include <macros.h>

inherit "/std/object";
inherit "/lib/keep";

int alco = 12; /* Equivalent of set_alco.  This is what's dipped
				* into with each sip. */
string cofrace;
string race_smell();
string race_smell_do();
string race_sip();
string race_sip_do();
string race_drink();
string race_drink_do();
void sippin_cof();

create_object()
{
    set_name("beer");
	add_name(({"mug", "harrmoor", "drink"}));
	add_pname(({"mugs", "harrmoors", "drinks"}));
    set_adj(({"dark"}));
    set_short("mug of Harrmoor Dark beer");
    set_pshort("mugs of Harrmoor Dark beer");
    set_long("@@my_long@@" + "\n");

	add_prop(OBJ_M_NO_SELL, 1);
}

void
init()
{
    ::init();
    ADA("smell");
	ADA("sip");
	ADA("drink");
}

string
my_long()
{
	if (alco >= 11)
	{
		return "This mug is full of Harrmoor Dark beer which is a rich "
		+ "brown in colour and topped with a tall, frothy white head.";
	}

	if (alco >=8)
	{
		return "This mug is three quarters full of Harrmoor Dark beer "
		+ "which is a rich brown in colour and topped with a frothy "
		+ "white head.";
	}

	if (alco >=5)
	{
		return "This mug is half full of Harrmoor Dark beer which is a "
		+ "rich brown in colour and topped with a frothy white head.";
	}

	if (alco >= 3)
	{
		return "This mug is a quarter full of Harrmoor Dark beer which "
		+ "is a rich brown in colour and topped with a thin layer of "
		+ "white froth.";
	}

	else
	{
		return "This mug contains only a sip or two of Harrmoor Dark beer "
		+ "which is a rich brown in colour.";
	}
}

int
smell(string str)
{
	cofrace = QRACE(TP);

    NF("Smell what?\n");

    if (!str)
	return 0;

    if (!parse_command(str, ({}), "[harrmoor] [dark] 'mug' / 'beer'"))
	return 0;

    write("You take a whiff of your " + short() + ".  " + race_smell()
	+ "\n");
    tell_room(E(TP), QCTNAME(TP)+ " takes a whiff of " + HIS(TP) + " "
	+ short() + ".  " + race_smell_do() + "\n", ({TO, TP}));

    return 1;
}

int
sip(string str)
{
	cofrace = QRACE(TP);

	NF("Sip what?\n");

    if (!str)
	return 0;

    if (!parse_command(str, ({}),
	   "[from] [harrmoor] [dark] 'mug' / 'beer'"))
	return 0;

	if (TP->drink_alco(1, 0))
	{
		TP->drink_alco(1, 0);

		write("You take a sip from your " + short() + ".  " + race_sip()
		+ "\n");
		tell_room(E(TP), QCTNAME(TP) + " takes a sip from " + HIS(TP)
		+ " " + short() + ".  " + race_sip_do() + "\n", ({TO, TP}));
		
		alco--;
		if (alco <= 0)
			{ sippin_cof(); }
	}

	else write("You are too inebriated to drink any more.\n");

    return 1;
}

public mixed
sippin_cof()
{
	TP->catch_msg("You turn up the mug and the last drop of Harrmoor Dark "
	+ "beer falls on your tongue.\n");
	tell_room(E(TP), QCTNAME(TP) + " turns up " + HIS(TP) + " " + short()
	+ " allowing the last drop of Harrmoor Dark beer to fall on " + HIS(TP)
	+ " tongue.\n", ({TO, TP}));
	remove_object();
}

int
drink(string str)
{
	cofrace = QRACE(TP);

	if (!str)
	return 0;

    if (!parse_command(str, ({}),
	   "[from] [harrmoor] [dark] 'mug' / 'beer'"))
	return 0;

	if (TP->drink_alco(alco, 0))
	{
		TP->drink_alco(alco, 0);

		if (alco > 0)
		{
			TP->catch_msg("You take a drink from your " + short()
			+ ", breathing in its dark, frothy aroma.  " + race_drink()
			+ "\n");
			tell_room(E(TP), QCTNAME(TP) + " takes a drink from " + HIS(TP)
			+ " " + short() + ", breathing in its dark, frothy aroma.  "
			+ race_drink_do() + "\n", ({TO, TP}));

			alco = alco - 12;
			if (alco <= 0)
				{ sippin_cof(); }
		}
	}

	else write("You are too inebriated to drink any more.\n");

    return 1;
}

string
race_smell()
{

	if (TP->query_guild_name_occ() == "Vampires of Emerald")
	{
		return "There is no blood in this drink, only the aroma of "
		+ "a frothy, dark brown beer.";
	}

	else if (TP->query_guild_name_occ() == "Morgul Mages")
	{
		return "The smell of a frothy dark beer fills your senses.";
	}

	else if (TP->query_guild_name_race() == "Noldor of Imladris")
	{
		return "The smell of a frothy dark beer fills your senses.  Not "
		+ "bad for humans.";
	}

	else switch(cofrace)
	{

	case "elf":
	case "noldor":
	case "half-elf":
	case "gnome":
		return "The smell of a frothy dark beer fills your senses.  Not "
		+ "bad.";
	break;

	case "goblin":
	case "orc":
	case "hobgoblin":
	case "minotaur":
	case "uruk":
		return "The smell of alcohol is unmistakable in this frothy dark "
		+ "beer.  You drool anxiously in anticipation of guzzling this "
		+ "aromatic, fresh brew.";
	break;

	case "presence":
		return "This isn't the best form in which to enjoy this drink.";
	break;
    
    case "human":
	case "half-human":
	case "dwarf":
	case "drow":
	case "hobbit":
	case "kender":
    default:
		return "The smell of a frothy dark beer fills your senses.  Your "
		+ "mouth waters in anticipation of this masterfully crafted, "
		+ "fresh brew.";
	break;

	}
}

string
race_smell_do()
{
	if (TP->query_guild_name_occ() == "Vampires of Emerald")
	{
		return C(HE(TP)) + " smells " + HIS(TP) + " " + short() + " with "
		+ "a detached interest.";
	}

	else if (TP->query_guild_name_occ() == "Morgul Mages")
	{
		return C(HE(TP)) + " narrows " + HIS(TP) + " eyes as " + HE(TP)
		+ " sniffs at the " + short() + ".";
	}

	else if (TP->query_guild_name_race() == "Noldor of Imladris")
	{
		return C(HE(TP)) + " waves " + HIS(TP) + " nose over the " + short()
		+ "as " + HE(TP) + " breathes the beer's aroma in.";
	}

	else switch(cofrace)
	{

	case "elf":
	case "noldor":
	case "half-elf":
	case "gnome":
		return C(HE(TP)) + " waves " + HIS(TP) + " nose over the " + short()
		+ "as " + HE(TP) + " breathes the beer's aroma in.";
	break;

	case "goblin":
	case "orc":
	case "hobgoblin":
	case "minotaur":
	case "uruk":
		return C(HE(TP)) + " snorts " + HIS(TP) + " nostrils thirstily as "
		+ HE(TP) + " begins to drool in anticipation.";
	break;

	case "presence":
		return C(HE(TP)) + " displays little expression from the "
		+ "experience.";
	break;

	case "human":
	case "half-human":
	case "dwarf":
	case "drow":
	case "hobbit":
	case "kender":
    default:
		return C(HE(TP)) + " nods " + HIS(TP) + " head anxiously as "
		+ HIS(TP) + " eyes widen in anticipation.";
	break;
	}
}

string
race_sip()
{
	if (TP->query_guild_name_occ() == "Vampires of Emerald")
	{
		return "Despite containing no blood whatsoever, you put on a "
		+ "good show of sipping the beer anyway.  That's the spirit!";
	}

	else if (TP->query_guild_name_occ() == "Morgul Mages")
	{
		return "That's a fair mug of well crafted, fresh brewed, dark, "
		+ "frothy brew.";
	}

	else if (TP->query_guild_name_race() == "Noldor of Imladris")
	{
		return "That's a fair mug of well crafted, fresh brewed, dark, "
		+ "frothy brew for humans that is.";
	}

	else switch(cofrace)
	{

	case "elf":
	case "noldor":
	case "half-elf":
	case "gnome":
		return "That's a fair mug of well crafted, fresh brewed, dark, "
		+ "frothy brew.";
	break;

	case "goblin":
	case "orc":
	case "hobgoblin":
	case "minotaur":
	case "uruk":
		return "Ahh, good tasting and frothy like a real beer, but what "
		+ "are you?  Some kind of dandelion-eater?  It's time to glug!";
	break;

	case "presence":
		return "This isn't the best form in which to enjoy this drink.";
	break;
    
    case "human":
	case "half-human":
	case "dwarf":
	case "drow":
	case "hobbit":
	case "kender":
    default:
		return "The masterfully crafted, frothy topped, dark brown beer "
		+ "goes down smoothly with a distinct and fresh flavour.  Ahh, "
		+ "now that's a beer.";
	break;

	}
}

string
race_sip_do()
{
	if (TP->query_guild_name_occ() == "Vampires of Emerald")
	{
		return C(HE(TP)) + " pretends to sip " + HIS(TP) + " " + short()
		+ ", smiling as " + HE(TP) + " lets it dribble down " + HIS(TP)
		+ " chin.";
	}

	else if (TP->query_guild_name_occ() == "Morgul Mages")
	{
		return C(HE(TP)) + " nods " + one_of_list(({"knowingly", "coldly", "grimly",
		"surreptitiously", "mystically", "slightly", "slowly"})) + " from "
		+ "within " + HIS(TP) + " hooded black robes.";
	}

	else if (TP->query_guild_name_race() == "Noldor of Imladris")
	{
		return C(HE(TP)) + " nods slightly.";
	}

	else switch(cofrace)
	{

	case "elf":
	case "noldor":
	case "half-elf":
	case "gnome":
		return C(HE(TP)) + " smiles thoughtfully.";
	break;

	case "goblin":
	case "orc":
	case "hobgoblin":
	case "minotaur":
	case "uruk":
		return C(HE(TP)) + " grunts approvingly as " + HE(TP) + " sips, "
		+ "letting some of the beer dribble " + HIS(TP) + " chin.";
	break;

	case "presence":
		return C(HE(TP)) + " displays little expression from the "
		+ "experience.";
	break;

	case "human":
	case "half-human":
	case "dwarf":
	case "drow":
	case "hobbit":
	case "kender":
    default:
		return C(HE(TP)) + " grins approvingly as " + HE(TP) + " wipes some " 
		+ "beer from " + HIS(TP) + " chin.";
	break;

	}
}

string
race_drink()
{
	if (TP->query_guild_name_occ() == "Vampires of Emerald")
	{
		return "Despite containing no blood whatsoever, you put on a "
		+ "good show of sipping the beer anyway.  That's the spirit!";
	}

	else if (TP->query_guild_name_occ() == "Morgul Mages")
	{
		return "That's a fair mug of well crafted, fresh brewed, dark, "
		+ "frothy brew.";
	}

	else if (TP->query_guild_name_race() == "Noldor of Imladris")
	{
		return "That's a fair mug of well crafted, fresh brewed, dark, "
		+ "frothy brew for humans that is.";
	}

	else switch(cofrace)
	{

	case "elf":
	case "noldor":
	case "half-elf":
	case "gnome":
		return "That's a fair mug of well crafted, fresh brewed, dark, "
		+ "frothy brew.";
	break;

	case "goblin":
	case "orc":
	case "hobgoblin":
	case "minotaur":
	case "uruk":
		return "Ahh, aside from getting you drunk quickly, this well "
		+ "crafted, frothy topped, dark brown beer tastes real good and "
		+ "fresh like a real beer should.";
	break;

	case "presence":
		return "This isn't the best form in which to enjoy this drink.";
	break;
    
    case "human":
	case "half-human":
	case "dwarf":
	case "drow":
	case "hobbit":
	case "kender":
    default:
		return "The masterfully crafted, frothy topped, dark brown beer "
		+ "goes down smoothly with a distinct and fresh flavour.  Ahh, "
		+ "now that's a beer.";
	break;

    }
}

string
race_drink_do()
{
	if (TP->query_guild_name_occ() == "Vampires of Emerald")
	{
		return C(HE(TP)) + " pretends to sip " + HIS(TP) + " " + short()
		+ ", smiling as " + HE(TP) + " lets it dribble down " + HIS(TP)
		+ " chin.";
	}

	else if (TP->query_guild_name_occ() == "Morgul Mages")
	{
		return C(HE(TP)) + " nods " + one_of_list(({"knowingly", "coldly", "grimly",
		"surreptitiously", "mystically", "slightly", "slowly"})) + " from "
		+ "within " + HIS(TP) + " hooded black robes.";
	}

	else if (TP->query_guild_name_race() == "Noldor of Imladris")
	{
		return C(HE(TP)) + " nods slightly.";
	}

	else switch(cofrace)
	{

	case "elf":
	case "noldor":
	case "half-elf":
	case "gnome":
		return C(HE(TP)) + " smiles thoughtfully.";
	break;

	case "goblin":
	case "orc":
	case "hobgoblin":
	case "minotaur":
	case "uruk":
		return C(HE(TP)) + " grunts approvingly as " + HE(TP) + " guzzles, "
		+ "letting some of the beer dribble " + HIS(TP) + " chin.";
	break;

	case "presence":
		return C(HE(TP)) + " displays little expression from the "
		+ "experience.";
	break;

	case "human":
	case "half-human":
	case "dwarf":
	case "drow":
	case "hobbit":
	case "kender":
    default:
		return C(HE(TP)) + " grins approvingly as " + HE(TP) + " wipes some " 
		+ "beer from " + HIS(TP) + " chin.";
	break;

	}
}

string
query_recover()
{
    return MASTER + ":" + query_keep_recover();
}

void
init_recover(string arg)
{
    init_keep_recover(arg);
}
