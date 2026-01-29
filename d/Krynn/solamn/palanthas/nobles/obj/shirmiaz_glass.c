/* Mortis 12.2005
 *
 * These glasses are worth five(5) sips at twenty(20) alco
 * a piece.  They are the magically created glasses poured
 * by shirmiaz_wine.c, the reward bottle for helping Gui
 * the vintner off the Court d'Plaisiri a second time.
 */

#include "../../local.h"
#include <macros.h>

inherit "/std/object";
inherit "/lib/keep";

int alco = 100; /* Equivalent of set_alco.  This is what's dipped
				  * into with each sip/drink. */
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
    set_name("wine");
	add_name(({"glass", "shirmiaz", "drink"}));
	add_pname(({"glasses", "shirmiazi", "drinks"}));
    set_adj(({"large"}));
    set_short("large glass of Shirmiaz");
    set_pshort("large glasses of Shirmiaz");
    set_long("This large wine glass contains a dark, red Shirmiaz wine.\n");

    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 650);
    add_prop(OBJ_M_NO_SELL, 1);

    seteuid(getuid());
}

void
init()
{
    ::init();
    ADA("smell");
	ADA("sip");
	ADA("drink");
}

int
smell(string str)
{
	cofrace = QRACE(TP);

    NF("Smell what?\n");

    if (!str)
	return 0;

    if (!parse_command(str, ({}), "[large] 'glass' / 'wine' / 'shirmiaz'"))
	return 0;

    write("You swirl your " + short() + " around in small circles and smell "
	+ "its bouquet.  " + race_smell() + "\n");
    tell_room(E(TP), QCTNAME(TP)+ " swirls " + HIS(TP) + " " + short()
	+ " and smells its bouquet.  " + race_smell_do() + "\n", ({TO, TP}));

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
	   "[from] [large] 'glass' / 'wine' / 'shirmiaz'"))
	return 0;

	if (TP->drink_alco(1, 0))
	{
	TP->drink_alco(1, 0);

    write("You take a sip from your " + short() + ".  " + race_sip() + "\n");
    tell_room(E(TP), QCTNAME(TP) + " takes a sip from " + HIS(TP)
	+ " " + short() + ".  " + race_sip_do() + "\n", ({TO, TP}));
	
	alco--;
	if (alco <= 0) 	{ sippin_cof(); }

	}

	else write("You are too inebriated to drink any more.\n");

    return 1;
}

public mixed
sippin_cof()
{
	TP->catch_msg("You turn up the glass and the last drop of wine falls on "
	+ "your tongue.  The glass wavers out of existence as it evaporates into "
	+ "thin air.\n");
	tell_room(E(TP), QCTNAME(TP) + " turns up " + HIS(TP) + " " + short()
	+ " allowing the last drop of wine to fall on " + HIS(TP) + " tongue.  "
	+ "The glass wavers out of existence as it evaporates into thin air.\n",
		({TO, TP}));
	TO->remove_object();
}

int
drink(string str)
{
	cofrace = QRACE(TP);

	if (!str)
	return 0;

    if (!parse_command(str, ({}),
	   "[from] [large] 'glass' / 'wine' / 'shirmiaz'"))
	return 0;

	if (TP->drink_alco(20, 0))
	{
	TP->drink_alco(20, 0);

	if (alco > 0)
	{
		TP->catch_msg("You take a drink from your " + short()
		+ ", breathing in its rich bouquet.  " + race_drink() + "\n");
		tell_room(E(TP), QCTNAME(TP) + " takes a drink from " + HIS(TP)
		+ " " + short() + ", breathing in its rich bouquet.  "
		+ race_drink_do() + "\n",
		({TO, TP}));

	alco = alco - 20;
	if (alco <= 0) 	{ sippin_cof(); }

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
		+ "Shirmiaz grapes with a hint of pomegranate.";
	}

	else if (TP->query_guild_name_occ() == "Morgul Mages")
	{
		return "The smell of rich, Shirmiaz grapes with a hint of "
		+ "pomegranate fills your senses.";
	}

	else if (TP->query_guild_name_race() == "Noldor of Imladris")
	{
		return "The smell of rich, Shirmiaz grapes is strong in this "
		+ "wine, and if your keen nose is correct, the grapes grew "
		+ "alongside pomegranates and picked up a hint of their "
		+ "fragrance.";
	}

	else switch(cofrace)
	{

	case "elf":
	case "noldor":
	case "drow":
		return "The smell of rich, Shirmiaz grapes is strong in this "
		+ "wine, and if your keen nose is correct, the grapes grew "
		+ "alongside pomegranates and picked up a hint of their "
		+ "fragrance.";
	break;

	case "hobbit":
	case "kender":
	case "gnome":
		return "Mmmmm, is that a hint of pomegranate alongside the fragrant "
		+ "and rich Shirmiaz grapes in this wine?";
	break;

	case "goblin":
	case "orc":
	case "hobgoblin":
	case "minotaur":
	case "uruk":
		return "The smell of alcohol is unmistakable in this rich wine made "
		+ "from Shirmiaz grapes.";
	break;

	case "presence":
		return "This isn't the best form in which to enjoy this drink.";
	break;

	case "human":
	case "half-human":
	case "half-elf":
	case "dwarf":
    default:
		return "The smell of rich, Shirmiaz grapes with a hint of "
		+ "apricot fills your senses.";
	break;

	}
}

string
race_smell_do()
{
	if (TP->query_guild_name_occ() == "Vampires of Emerald")
	{
		return C(HE(TP)) + " smells " + HIS(TP) + " " + short() + " in "
		+ "disinterest.";
	}

	else if (TP->query_guild_name_occ() == "Morgul Mages")
	{
		return C(HE(TP)) + " narrows " + HIS(TP) + " eyes as " + HE(TP)
		+ " sniffs at the " + short() + ".";
	}

	else if (TP->query_guild_name_race() == "Noldor of Imladris")
	{
		return C(HE(TP)) + " waves " + HIS(TP) + " nose over the " + short()
		+ "as " + HE(TP) + " breathes the wine's bouquet in slowly.";
	}

	else switch(cofrace)
	{

	case "elf":
	case "noldor":
	case "drow":
		return C(HE(TP)) + " waves " + HIS(TP) + " nose over the " + short()
		+ "as " + HE(TP) + " breathes the wine's bouquet in slowly.";
	break;

	case "hobbit":
	case "kender":
	case "gnome":
		return C(HE(TP)) + " smiles and nods " + HIS(TP) + " head "
		+ "in contemplation.";
	break;

	case "goblin":
	case "orc":
	case "hobgoblin":
	case "minotaur":
	case "uruk":
		return C(HE(TP)) + " snorts " + HIS(TP) + " nostrils thirstily.";
	break;

	case "presence":
		return C(HE(TP)) + " displays little expression from the "
		+ "experience.";
	break;
    
	case "human":
	case "half-human":
	case "half-elf":
	case "dwarf":
    default:
		return C(HE(TP)) + " nods " + HIS(TP) + " head contemplatively.";
	break;

	}
}

string
race_sip()
{
	if (TP->query_guild_name_occ() == "Vampires of Emerald")
	{
		return "Despite containing no blood whatsoever, you put on a "
		+ "good show of sipping the wine anyway.  That's the spirit!";
	}

	else if (TP->query_guild_name_occ() == "Morgul Mages")
	{
		return "Hints of pomegranate subtly influence the rich, "
		+ "red grape flavour of the Shirmiaz.";
	}

	else if (TP->query_guild_name_race() == "Noldor of Imladris")
	{
		return "Hints of pomegranate subtly influence the rich, "
		+ "red grape flavour of the Shirmiaz.";
	}

	else switch(cofrace)
	{

	case "elf":
	case "noldor":
	case "drow":
		return "Hints of pomegranate subtly influence the rich, "
		+ "red grape flavour of the Shirmiaz.";
	break;

	case "hobbit":
	case "kender":
	case "gnome":
		return "Hints of pomegranate subtly influence the dark, rich, red "
		+ "grape flavour of the Shirmiaz.  Very drinkable.";
	break;

	case "goblin":
	case "orc":
	case "hobgoblin":
	case "minotaur":
	case "uruk":
		return "Ahh, this dark, rich, red wine will get you drunk fast "
		+ "enough and washes down with an aftertaste of pomegranates.";
	break;

	case "presence":
		return "This isn't the best form in which to enjoy this drink.";
	break;

	case "human":
	case "half-human":
	case "half-elf":
	case "dwarf":
    default:
		return "Hints of pomegranate subtly influence the rich, "
		+ "red grape flavour of the Shirmiaz.  Very drinkable.";
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
	case "drow":
		return C(HE(TP)) + " nods slightly.";
	break;

	case "hobbit":
	case "kender":
	case "gnome":
		return C(HE(TP)) + " nods smilingly.";
	break;

	case "goblin":
	case "orc":
	case "hobgoblin":
	case "minotaur":
	case "uruk":
		return C(HE(TP)) + " grunts approvingly.";
	break;

	case "presence":
		return C(HE(TP)) + " displays little expression from the "
		+ "experience.";
	break;

    case "human":
	case "half-human":
	case "half-elf":
	case "dwarf":
    default:
		return C(HE(TP)) + " nods solemnly.";
	break;

	}
}

string
race_drink()
{
	cofrace = QRACE(TP);

	if (TP->query_guild_name_occ() == "Vampires of Emerald")
	{
		return "Despite containing no blood whatsoever, you put on a "
		+ "good show of sipping the wine anyway.  That's the spirit!";
	}

	else if (TP->query_guild_name_occ() == "Morgul Mages")
	{
		return "Hints of pomegranate subtly influence the rich, "
		+ "red grape flavour of the Shirmiaz.";
	}

	else if (TP->query_guild_name_race() == "Noldor of Imladris")
	{
		return "Hints of pomegranate subtly influence the rich, "
		+ "red grape flavour of the Shirmiaz.";
	}

	else switch(cofrace)
	{

	case "elf":
	case "noldor":
	case "drow":
		return "Hints of pomegranate subtly influence the rich, "
		+ "red grape flavour of the Shirmiaz.";
	break;

	case "hobbit":
	case "kender":
	case "gnome":
		return "Hints of pomegranate subtly influence the dark, rich, red "
		+ "grape flavour of the Shirmiaz.  Very drinkable.";
	break;

	case "goblin":
	case "orc":
	case "hobgoblin":
	case "minotaur":
	case "uruk":
		return "Ahh, this deep, red wine will get you drunk fast "
		+ "enough and washes down with an aftertaste of pomegranates.";
	break;

	case "presence":
		return "This isn't the best form in which to enjoy this drink.";
	break;

	case "human":
	case "half-human":
	case "half-elf":
	case "dwarf":
    default:
		return "Hints of pomegranate subtly influence the rich, "
		+ "red grape flavour of the Shirmiaz.  Very drinkable";
	break;

	}
}

string
race_drink_do()
{
	cofrace = QRACE(TP);

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
	case "drow":
		return C(HE(TP)) + " nods slightly.";
	break;

	case "hobbit":
	case "kender":
	case "gnome":
		return C(HE(TP)) + " nods smilingly.";
	break;

	case "goblin":
	case "orc":
	case "hobgoblin":
	case "minotaur":
	case "uruk":
		return C(HE(TP)) + " grunts approvingly.";
	break;

	case "presence":
		return C(HE(TP)) + " displays little expression from the "
		+ "experience.";
	break;

	case "human":
	case "half-human":
	case "half-elf":
	case "dwarf":
    default:
		return C(HE(TP)) + " nods solemnly.";
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
