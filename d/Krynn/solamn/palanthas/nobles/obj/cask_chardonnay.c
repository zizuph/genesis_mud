/* Mortis 12.2005
 *
 * Vintner sells these off the Court d'Plaisiri.
 * I want to sell glasses at the glassblower's (new shop)
 * that you can fill by pouring a glass from these casks.
 * Then you could take maybe a dozen sips or so.
 */

#include "../../local.h"
#include <macros.h>

inherit "/std/object";
inherit "/lib/keep";

int alco = 10000; /* Equivalent of set_alco.  This is what's dipped
				  * into with each sip/drink. */
int empty = 0;
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
    set_name("cask");
	add_name(({"chardonnay", "wine"}));
	add_pname(({"chardonnays", "wines"}));
    set_adj(({"east", "solace"}));
    set_short("cask of East Solace chardonnay");
    set_pshort("casks of East Solace chardonnay");
    set_long("This small cask is built of strips of pale oak and bound "
	+ "with strips of iron near its ends.  On one end is a corked spout "
	+ "for drinking and pouring, and its side has been branded with a "
	+ "hot iron to read:\n"
	+ "         \"East Solace Vineyards\"\n"
	+ "              \"Chardonnay\"\n"
	+ "                 \"347\"\n");

    add_prop(OBJ_I_WEIGHT, 20000);
    add_prop(OBJ_I_VOLUME, 18000);
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

	NF("There's no wine left in the " + short() + " to smell.\n");
	if (empty == 1)
	return 0;

    NF("Smell what?\n");

    if (!str)
	return 0;

    if (!parse_command(str, ({}),
	   "[east] [solace] 'cask' / 'chardonnay' / 'wine'"))
	return 0;

    write("You pull the cork from the spout on your " + short() + " and "
	+ "smell the wine within.  " + race_smell() + "\n");
    tell_room(E(TP), QCTNAME(TP)+ " pulls the cork from " + HIS(TP)
	+ " " + short() + " and smells the wine within.  " + race_smell_do()
	+ "\n", ({TO, TP}));

    return 1;
}

int
sip(string str)
{
	cofrace = QRACE(TP);

	NF("There's no wine left in the " + short() + " to sip.\n");
	if (empty == 1)
	return 0;

	NF("Sip what?\n");

    if (!str)
	return 0;

    if (!parse_command(str, ({}),
	   "[from] [east] [solace] 'cask' / 'chardonnay' / 'wine'"))
	return 0;

	if (TP->drink_alco(1, 0))
	{
	TP->drink_alco(1, 0);

    write("You pull the cork from the spout on your " + short() + " and "
	+ "take a sip.  " + race_sip() + "\n");
    tell_room(E(TP), QCTNAME(TP) + " pulls the cork from " + HIS(TP)
	+ " " + short() + ", turns it up, and takes a sip.  " + race_sip_do()
	+ "\n", ({TO, TP}));
	
	alco--;
	if (alco <= 0) 	{ sippin_cof(); }

	}

	else write("You are too inebriated to drink any more.\n");

    return 1;
}

public mixed
sippin_cof()
{
	TP->catch_msg("You turn up the cask and the last drop of wine falls on "
	+ "your tongue.\n");
	tell_room(E(TP), QCTNAME(TP) + " turns up " + HIS(TP) + " " + short()
	+ " allowing the last drop of wine to fall on " + HIS(TP) + " tongue.\n",
		({TO, TP}));
	empty = 1;
	set_short("empty " + short());
	set_pshort("empty " + query_plural_short());
}

int
drink(string str)
{
	NF("There's no wine left in the " + short() + " to drink.\n");
	if (empty == 1)
	return 0;

	if (!str)
	return 0;

    if (!parse_command(str, ({}),
	   "[from] [east] [solace] 'cask' / 'chardonnay' / 'wine'"))
	return 0;

	if (TP->drink_alco(20, 0))
	{
	TP->drink_alco(20, 0);

	if (alco > 0)
	{
		TP->catch_msg("You pull the cork from the spout on your " + short()
		+ ", turn it up, and quaff a mouthful.  " + race_drink() + "\n");
		tell_room(E(TP), QCTNAME(TP) + " pulls the cork from " + HIS(TP)
		+ " " + short() + ", turns it up, and quaffs a mouthful.  "
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
		return "There is no blood in this drink, only the sharp aroma of "
		+ "fermented white grapes.";
	}

	else if (TP->query_guild_name_occ() == "Morgul Mages")
	{
		return "The smell of apples strongly flavours the fruity, "
		+ "white grape bouquet of the chardonnay.";
	}

	else if (TP->query_guild_name_race() == "Noldor of Imladris")
	{
		return "The white grapes used in this chardonnay must have been "
		+ "grown near apple orchards for their strong hint flavours the "
		+ "wine's bouquet.";
	}

	else switch(cofrace)
	{

	case "elf":
	case "noldor":
	case "drow":
		return "The white grapes used in this chardonnay must have been "
		+ "grown near apple orchards for their strong hint flavours the "
		+ "wine's bouquet.";
	break;

	case "hobbit":
	case "kender":
	case "gnome":
		return "Mmm, apples flavour this fruity, white grape wine for "
		+ "sure.";
	break;

	case "goblin":
	case "orc":
	case "hobgoblin":
	case "minotaur":
	case "uruk":
		return "The smell of alcohol is unmistakable in this fruity, white "
		+ "wine.  You detect the hint of apples, too.";
	break;

	case "presence":
		return "This isn't the best form in which to enjoy this drink.";
	break;

	case "human":
	case "half-human":
	case "half-elf":
	case "dwarf":
    default:
		return "It has a fruity, white grape bouquet with a strong hint of "
		+ "apples.";
	break;

	}
}

string
race_smell_do()
{
	if (TP->query_guild_name_occ() == "Vampires of Emerald")
	{
		return HE(TP) + " wrinkles " + HIS(TP) + " nose in disinterest "
		+ "at the drink.";
	}

	else if (TP->query_guild_name_occ() == "Morgul Mages")
	{
		return HE(TP) + " narrows " + HIS(TP) + " eyes as " + HE(TP)
		+ " sniffs at the cask.";
	}

	else if (TP->query_guild_name_race() == "Noldor of Imladris")
	{
		return HE(TP) + " waves " + HIS(TP) + " nose over the spout as "
		+ HE(TP) + " breathes the wine's bouquet in slowly.";
	}

	else switch(cofrace)
	{

	case "elf":
	case "noldor":
	case "drow":
		return HE(TP) + " waves " + HIS(TP) + " nose over the spout as "
		+ HE(TP) + " breathes the wine's bouquet in slowly.";
	break;

	case "hobbit":
	case "kender":
	case "gnome":
		return HE(TP) + " smiles and nods " + HIS(TP) + " head "
		+ "thoughtfully.";
	break;

	case "goblin":
	case "orc":
	case "hobgoblin":
	case "minotaur":
		return HE(TP) + " snorts " + HIS(TP) + " nostrils thirstily.";
	break;

	case "presence":
		return HE(TP) + " displays little expression from the "
		+ "experience.";
	break;

	case "human":
	case "half-human":
	case "half-elf":
	case "dwarf":
    default:
		return HE(TP) + " nods " + HIS(TP) + " head thoughtfully.";
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
		return "The chardonnay has a smooth, fruity flavour with a strong "
		+ "aftertaste of apples.";
	}

	else if (TP->query_guild_name_race() == "Noldor of Imladris")
	{
		return "The chardonnay has a smooth, fruity flavour with a strong "
		+ "aftertaste of apples.  Not too sweet either.";
	}

	else switch(cofrace)
	{

	case "elf":
	case "noldor":
	case "drow":
		return "The chardonnay has a smooth, fruity flavour with a strong "
		+ "aftertaste of apples.  Not too sweet either.";
	break;

	case "hobbit":
	case "kender":
	case "gnome":
		return "The chardonnay has a fruity flavour with a strong aftertaste "
		+ "of apples.  Nice and smooth!";
	break;

	case "goblin":
	case "orc":
	case "hobgoblin":
	case "minotaur":
	case "uruk":
		return "Ahh, this fruity, white wine will get you drunk fast "
		+ "enough and washes down with an aftertaste of apples.";
	break;

	case "presence":
		return "This isn't the best form in which to enjoy this drink.";
	break;

	case "human":
	case "half-human":
	case "half-elf":
	case "dwarf":
    default:
		return "The chardonnay has a smooth, fruity flavour with a strong "
		+ "aftertaste of apples.";
	break;

	}
}

string
race_sip_do()
{
	if (TP->query_guild_name_occ() == "Vampires of Emerald")
	{
		return HE(TP) + " pretends to sip " + HIS(TP) + " " + short()
		+ ", smiling as " + HE(TP) + " lets it dribble down " + HIS(TP)
		+ " chin.";
	}

	else if (TP->query_guild_name_occ() == "Morgul Mages")
	{
		return HE(TP) + " nods " + one_of_list(({"knowingly", "coldly", "grimly",
		"surreptitiously", "mystically", "slightly", "slowly"})) + " from "
		+ "within " + HIS(TP) + " hooded black robes.";
	}

	else if (TP->query_guild_name_race() == "Noldor of Imladris")
	{
		return HE(TP) + " nods slightly.";
	}

	else switch(cofrace)
	{

	case "elf":
	case "noldor":
	case "drow":
		return HE(TP) + " nods slightly.";
	break;

	case "hobbit":
	case "kender":
	case "gnome":
		return HE(TP) + " nods smilingly.";
	break;

	case "goblin":
	case "orc":
	case "hobgoblin":
	case "minotaur":
	case "uruk":
		return HE(TP) + " grunts approvingly.";
	break;

	case "presence":
		return HE(TP) + " displays little expression from the "
		+ "experience.";
	break;

	case "human":
	case "half-human":
	case "half-elf":
	case "dwarf":
    default:
		return HE(TP) + " nods solemnly.";
	break;

	}
}

string
race_drink()
{
	if (TP->query_guild_name_occ() == "Vampires of Emerald")
	{
		return "Despite containing no blood whatsoever, you put on a "
		+ "good show of sipping the wine anyway.  That's the spirit!";
	}

	else if (TP->query_guild_name_occ() == "Morgul Mages")
	{
		return "The chardonnay has a smooth, fruity flavour with a strong "
		+ "aftertaste of apples.";
	}

	else if (TP->query_guild_name_race() == "Noldor of Imladris")
	{
		return "The chardonnay has a smooth, fruity flavour with a strong "
		+ "aftertaste of apples.  Not too sweet either.";
	}

	else switch(cofrace)
	{

	case "elf":
	case "noldor":
	case "drow":
		return "The chardonnay has a smooth, fruity flavour with a strong "
		+ "aftertaste of apples.  Not too sweet either.";
	break;

	case "hobbit":
	case "kender":
	case "gnome":
		return "The chardonnay has a fruity flavour with a strong aftertaste "
		+ "of apples.  Nice and smooth!";
	break;

	case "goblin":
	case "orc":
	case "hobgoblin":
	case "minotaur":
	case "uruk":
		return "Ahh, this fruity, white wine will get you drunk fast "
		+ "enough and washes down with an aftertaste of apples.";
	break;

	case "presence":
		return "This isn't the best form in which to enjoy this drink.";
	break;

	case "human":
	case "half-human":
	case "half-elf":
	case "dwarf":
    default:
		return "The chardonnay has a smooth, fruity flavour with a strong "
		+ "aftertaste of apples.";
	break;

	}
}

string
race_drink_do()
{
	if (TP->query_guild_name_occ() == "Vampires of Emerald")
	{
		return HE(TP) + " pretends to sip " + HIS(TP) + " " + short()
		+ ", smiling as " + HE(TP) + " lets it dribble down " + HIS(TP)
		+ " chin.";
	}

	else if (TP->query_guild_name_occ() == "Morgul Mages")
	{
		return HE(TP) + " nods " + one_of_list(({"knowingly", "coldly", "grimly",
		"surreptitiously", "mystically", "slightly", "slowly"})) + " from "
		+ "within " + HIS(TP) + " hooded black robes.";
	}

	else if (TP->query_guild_name_race() == "Noldor of Imladris")
	{
		return HE(TP) + " nods slightly.";
	}

	else switch(cofrace)
	{

	case "elf":
	case "noldor":
	case "drow":
		return HE(TP) + " nods slightly.";
	break;

	case "hobbit":
	case "kender":
	case "gnome":
		return HE(TP) + " nods smilingly.";
	break;

	case "goblin":
	case "orc":
	case "hobgoblin":
	case "minotaur":
	case "uruk":
		return HE(TP) + " grunts approvingly.";
	break;

	case "presence":
		return HE(TP) + " displays little expression from the "
		+ "experience.";
	break;

	case "human":
	case "half-human":
	case "half-elf":
	case "dwarf":
    default:
		return HE(TP) + " nods solemnly.";
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
