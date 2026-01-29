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
	add_name(({"honeywine", "wine"}));
	add_pname(({"honeywines", "wines"}));
    set_adj(({"goodlund"}));
    set_short("cask of Goodlund honeywine");
    set_pshort("casks of Goodlund honeywine");
    set_long("This small cask is built of strips of pale oak and bound "
	+ "with strips of iron near its ends.  On one end is a corked spout "
	+ "for drinking and pouring, and its side has been branded with a "
	+ "hot iron to read:\n"
	+ "         \"Goodlund Vineyards\"\n"
	+ "              \"Honeywine\"\n"
	+ "                 \"346\"\n");

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
	   "[goodlund] 'cask' / 'honeywine' / 'wine'"))
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
	   "[from] [goodlund] 'cask' / 'honeywine' / 'wine'"))
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
	   "[from] [goodlund] 'cask' / 'honeywine' / 'wine'"))
	return 0;

	if (TP->drink_alco(22, 0))
	{
	TP->drink_alco(22, 0);

	if (alco > 0)
	{
		TP->catch_msg("You pull the cork from the spout on your " + short()
		+ ", turn it up, and quaff a mouthful.  " + race_drink() + "\n");
		tell_room(E(TP), QCTNAME(TP) + " pulls the cork from " + HIS(TP)
		+ " " + short() + ", turns it up, and quaffs a mouthful.  "
		+ race_drink_do() + "\n",
		({TO, TP}));

	alco = alco - 22;
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
		+ "fermented honey.";
	}

	else if (TP->query_guild_name_occ() == "Morgul Mages")
	{
		return "The smell of naturally sweet, fermented honey is strong "
		+ "in this drink.";
	}

	else if (TP->query_guild_name_race() == "Noldor of Imladris")
	{
		return "The smell of naturally sweet, fermented honey is strong "
		+ "in this drink, and if your keen nose is correct, it's made "
		+ "from clover honey.";
	}

	else switch(cofrace)
	{

	case "elf":
	case "noldor":
	case "drow":
		return "The smell of naturally sweet, fermented honey is strong "
		+ "in this drink, and if your keen nose is correct, it's made "
		+ "from clover honey.";
	break;

	case "hobbit":
	case "kender":
	case "gnome":
		return "Mmmmm, is that naturally sweet, fermented clover honey in "
		+ "this drink?  That's the best!";
	break;

	case "goblin":
	case "orc":
	case "hobgoblin":
	case "minotaur":
	case "uruk":
		return "The smell of alcohol is unmistakable in this naturally "
		+ "sweet, fermented honey drink.";
	break;

	case "presence":
		return "This isn't the best form in which to enjoy this drink.";
	break;

	case "human":
	case "half-human":
	case "half-elf":
	case "dwarf":
    default:
		return "The smell of naturally sweet, fermented honey is strong "
		+ "in this drink.";
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
		+ "energetically as " + HIS(TP) + " face flushes a deep red.";
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
		return "The naturally sweet, fermented honey taste fills your "
		+ "mouth and goes down smoothly despite its high alcohol "
		+ "content.";
	}

	else if (TP->query_guild_name_race() == "Noldor of Imladris")
	{
		return "The naturally sweet, fermented honey taste fills your "
		+ "mouth and goes down smoothly, its clover flavours masking "
		+ "the strong alcohol fluidly.";
	}

	else switch(cofrace)
	{

	case "elf":
	case "noldor":
	case "drow":
		return "The naturally sweet, fermented honey taste fills your "
		+ "mouth and goes down smoothly, its clover flavours masking "
		+ "the strong alcohol fluidly";
	break;

	case "hobbit":
	case "kender":
	case "gnome":
		return "Mmmmm, this is indeed naturally sweet, fermented clover "
		+ "honey this drink, the best kind!  A warmth spreads out from "
		+ "your belly making your cheeks flush.";
	break;

	case "goblin":
	case "orc":
	case "hobgoblin":
	case "minotaur":
	case "uruk":
		return "Ahh, this naturally sweet, honeywine will get you drunk fast "
		+ "and washes down nice and smoothly.";
	break;

	case "presence":
		return "This isn't the best form in which to enjoy this drink.";
	break;

	case "human":
	case "half-human":
	case "half-elf":
	case "dwarf":
    default:
		return "The naturally sweet, fermented honey taste fills your "
		+ "mouth and goes down smoothly despite the amount of alcohol "
		+ "it contains.";
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
		return HE(TP) + " grins wide as " + HIS(TP) + " cheeks flush a "
		+ "rosy hue.";
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
		return "The naturally sweet, fermented honey taste fills your "
		+ "mouth and goes down smoothly despite its high alcohol "
		+ "content.";
	}

	else if (TP->query_guild_name_race() == "Noldor of Imladris")
	{
		return "The naturally sweet, fermented honey taste fills your "
		+ "mouth and goes down smoothly, its clover flavours masking "
		+ "the strong alcohol fluidly.";
	}

	else switch(cofrace)
	{

	case "elf":
	case "noldor":
	case "drow":
		return "The naturally sweet, fermented honey taste fills your "
		+ "mouth and goes down smoothly, its clover flavours masking "
		+ "the strong alcohol fluidly.";
	break;

	case "hobbit":
	case "kender":
	case "gnome":
		return "This is indeed naturally sweet, fermented clover "
		+ "honey this drink, the best kind!  A warmth spreads out from "
		+ "your belly making your cheeks flush.  Mmmmm, honeywine.";
	break;

	case "goblin":
	case "orc":
	case "hobgoblin":
	case "minotaur":
	case "uruk":
		return "Ahh, this naturally sweet, honeywine will get you drunk fast "
		+ "and washes down nice and smoothly.";
	break;

	case "presence":
		return "This isn't the best form in which to enjoy this drink.";
	break;

	case "human":
	case "half-human":
	case "half-elf":
	case "dwarf":
    default:
		return "The naturally sweet, fermented honey taste fills your "
		+ "mouth and goes down smoothly despite its high alcohol "
		+ "content.";
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
		return HIS(TP) + " cheeks flush a bright, rosy hue as " + HE(TP)
		+ " " + one_of_list(({"drops " + HIS(TP) + " jaw, " + HIS(TP)
		+ " tongue lolling out as " + HIS(TP) + " eyes spin.",
		  "flicks " + HIS(TP) + " tongue hungrily, sloppily, and noisily "
		+ "all over " + HIS(TP) + " lips getting every last drop.",
		  "moans pleasurably while squeezing " + HIS(TP) + " thighs "
		+ "together and hopping on one leg.",
		  "goes, \"Oh yes, mmmmm, yes yes yes, uhhhhhh...\" and shudders.",
		  "moans out, \"Oh honeywine, mmmmmm, yes yes yes, nubby num num."}));
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
