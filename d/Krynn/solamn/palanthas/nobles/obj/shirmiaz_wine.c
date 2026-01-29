/* Mortis 01.2006
 *
 * Reward bottle of wine for helping Gui a second time.
 * Gui has enchanted the bottle to pour out glasses first,
 * then fill them with shirmiaz wine.  The glasses hold
 * eight sips.  Each glass poured will of course further
 * deplete the bottle.  Thus the only enchantment we are
 * dealing with is the fact the bottle creates its own
 * glasses to drink from.  There is no other effect so
 * this is not listed in the normal magic item list.  It
 * only has a magic prop so people casting 'identify', etc.
 * will get info about its enchantment.
 *
 * Add <smash> to allow owner to smash it over someone's
 * head for an emote?
 */

#include "../../local.h"
#include <macros.h>

inherit "/std/object";
inherit "/lib/keep";

int alco = 500; /* Equivalent of set_alco.  This is what's dipped
				 * into with each pour. I'm thinking five(5) glasses
				 * each with five(5) sips worth twenty(20) alco each. */
int empty = 0;
string cofrace;
string race_smell();
string race_smell_do();
string bottle_contents();

create_object()
{
    set_name("shirmiaz");
	set_pname("shirmiazi");
	add_name(({"bottle", "wine"}));
	add_pname(({"bottles", "wines"}));
    set_short("bottle of Shirmiaz");
    set_pshort("bottles of Shirmiaz");
    set_long("This green bottle " + "@@bottle_contents@@" + "  Its top is "
	+ "corked, and its side bears an ornately trimmed, off-white label that "
	+ "reads:\n"
	+ "       ~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
	+ "         \"House Bursus Bottling\"\n"
	+ "               \"Shirmiaz\"\n"
	+ "                  \"343\"\n"
	+ "       ~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    add_prop(OBJ_I_WEIGHT, 2500);
    add_prop(OBJ_I_VOLUME, 2100);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(MAGIC_AM_MAGIC,({30, "conjuration"}));
    add_prop(MAGIC_AM_ID_INFO,
            ({"This bottle is enchanted.", 10,          
              "  Its form of enchantment is based in conjuration.", 30,
              "  It has the ability to pour its own glasses and then "
			+ "fill them with wine.", 50,
              "  Your keen senses lead you to believe it was enchanted "
			+ "by someone versed in the arts of High Sorcery.\n", 60}) );
    add_prop(OBJ_S_WIZINFO, "This bottle doesn't do anything special to "
	+ "players.  It just pours its own glasses before filling them.\n");

    seteuid(getuid());
}

string
bottle_contents()
{
	if (alco <= 0)
	{
		return "contains a dark red wine within.";
	}
	return "once contained wine but is now empty.";
}

void
init()
{
    ::init();
    ADA("smell");
	ADA("sip");
	ADA("drink");
	ADA("pour");
}

int
smell(string str)
{
	cofrace = QRACE(TP);

	NF("There's no wine left in the " + short() + " to smell.\n");
	if (alco <= 0)
	return 0;

    NF("Smell what?\n");

    if (!str)
	return 0;

    if (!parse_command(str, ({}), "'bottle' / 'wine' / 'shirmiaz'"))
	return 0;

    write("You pull the cork from your " + short() + " and "
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
	string bottle = short();
	string sipper = QCTNAME(TP);

	NF("There's no wine left in the " + bottle + " to sip.\n");
	if (alco <= 0)
	return 0;

	NF("Sip what?\n");

    if (!str)
	return 0;

    if (!parse_command(str, ({}), "[from] 'bottle' / 'wine' / 'shirmiaz'"))
	return 0;

	TP->catch_msg("The " + bottle + " says:  Thou shalt not place thy lips upon "
	+ "my orifice, " + sipper + ".  What manner of bottle dost thou "
	+ "take me for?  Pour thyself a glass as any civilized "
	+ cofrace + " would do.\n");
	say(C(sipper) + "'s " + bottle + " says:  Thou shalt not place thy "
	+ "lips upon my orifice, " + sipper + ".  What manner of bottle "
	+ "dost thou take me for?  Pour thyself a glass as any civilized "
	+ cofrace + " would do.\n");

    return 1;
}

int
drink(string str)
{
	string bottle = short();

	cofrace = QRACE(TP);
	string insult = one_of_list(({"whose mother was a hamster and father "
	+ "smelt of elderberries", "whose mother was a pigdog and father stank "
	+ "of pigdog droppings", "whose loincloth bears many layers of brown "
	+ "streaks", "of questionable parentage", "without the good sense to "
	+ "remove thy loincloth before relieving thyself", "of spotty lineage",
	  "who would not recognize an excellent Shirmiaz if it were inserted "
	+ "into thy own orifice for thee"}));

	NF("There's no wine left in the " + short() + " to drink.\n");
	if (alco <= 0)
	return 0;

	if (!str)
	return 0;

    if (!parse_command(str, ({}), "[from] 'bottle' / 'wine' / 'shirmiaz'"))
	return 0;

	TP->catch_msg("You pull the cork from the " + bottle + " and turn it up "
	+ "as if to take a slug when it cries out:  Get thy lips from my orifice, "
	+ "uncivilized " + cofrace + " " + insult + "!  What manner of bottle "
	+ "dost thou take me for?  Pour thyself a glass, " + QCTNAME(TP)
	+ ".\n");
	say(QCTNAME(TP) + " pulls the cork from " + HIS(TP) + " " + bottle
	+ " and turns it up to take a slug when it shouts:  Thou shalt not place "
	+ "thy lips upon my orifice, " + QCTNAME(TP) + ".  Get thy lips from my "
	+ "orifice, uncivilized " + cofrace + " " + insult + "!  What manner of "
	+ "bottle dost thou take me for?  Pour thyself a glass, " + QCTNAME(TP)
	+ ".\n");

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
		+ "pomegrante fills your senses.";
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
        + "pomegrante fills your senses.";
    break;

	}
}

string
race_smell_do()
{
	if (TP->query_guild_name_occ() == "Vampires of Emerald")
	{
		return HE(TP) + " smells " + HIS(TP) + " " + short() + " in "
		+ "disinterest.";
	}

	else if (TP->query_guild_name_occ() == "Morgul Mages")
	{
		return HE(TP) + " narrows " + HIS(TP) + " eyes as " + HE(TP)
		+ " sniffs at the " + short() + ".";
	}

	else if (TP->query_guild_name_race() == "Noldor of Imladris")
	{
		return HE(TP) + " waves " + HIS(TP) + " nose over the " + short()
		+ "as " + HE(TP) + " breathes the wine's bouquet in slowly.";
	}

	else switch(cofrace)
	{

	case "elf":
	case "noldor":
	case "drow":
		return HE(TP) + " waves " + HIS(TP) + " nose over the " + short()
		+ "as " + HE(TP) + " breathes the wine's bouquet in slowly.";
	break;

	case "hobbit":
	case "kender":
	case "gnome":
		return HE(TP) + " smiles and nods " + HIS(TP) + " head "
		+ "in contemplation.";
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
		return HE(TP) + " nods " + HIS(TP) + " head contemplatively.";
	break;

	}
}

int
pour()
{
	string bottle = short();
	object glass;

	if (alco <= 0)
	{
		write("Alas, the bottle is empty of Shirmiaz wine.\n");
		return 1;
	}
	TP->catch_msg("You uncork the " + bottle + " and pour it into thin air.  "
	+ "A viscous, clear liquid streams out amid sparkling white and yellow "
	+ "dweomers forming a wine glass from the base up.  You take hold of "
	+ "the glass as it completes, and a stream of dark, red Shirmiaz wine "
	+ "spills into it leaving you with a large glass of Shirmiaz wine.\n");
	say(QCTNAME(TP) + " uncorks " + HIS(TP) + " " + bottle + " and pours "
	+ "it into thin air.  A viscous, clear liquid streams out amid sparkling "
	+ "white and yellow dweomers forming a wine glass from the base up.  "
	+ C(HE(TP)) + " takes hold of the glass as it completes, and a stream of "
	+ "dark, red Shirmiaz wine spills into it leaving " + HIM(TP) + " with a "
	+ "large glass of Shirmiaz wine.\n");

	glass = clone_object(NOBLE + "obj/shirmiaz_glass");
	glass->move(TP);

	alco = alco - 100;

	if (alco <= 0)
	{
		empty = 1;
		return 1;
	}
	return 1;
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
