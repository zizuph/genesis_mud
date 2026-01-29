/* Mortis 01.2006
 *
 * Drink sold at the Green Twitch Inn in Palanthas.
 * Has mental effect that is increased when consumed en masse.
 */

#include "/sys/stdproperties.h"
#include <language.h>
#include <macros.h>
#include "../../local.h"

inherit "/std/drink";
inherit "/lib/keep";

string race_smell();
string race_smell_do();
string race_drink();
string race_drink_do();

void
create_drink()
{
    set_soft_amount(30);
    set_alco_amount(20);
    set_name("meade");
	set_pname("meades");
    add_name(({"mug", "drink"}));
	add_pname(({"mugs", "drinks"}));
    set_adj("twitch");
    set_short("mug of black meade");
    set_pshort("mugs of black meade");
    set_long("A small mug of pure, golden yellow meade from the Green Twitch "
	+ "Inn.  Wisps of golden yellow vapor rise from the meade.\n");
    add_prop(OBJ_I_WEIGHT, 45);
    add_prop(OBJ_I_VOLUME, 40);

    seteuid(getuid());
}

void
init()
{
    ::init();
    ADA("smell");
	ADA("sip");
}

int
smell(string str)
{
    NF("Smell what?\n");

    if (!str)
		return 0;

    if (!parse_command(str, ({}), "[mug] [of] [black] 'meade'") && str != "mug")
		return 0;

    TP->catch_msg("The golden vapors tickle your nose, tingling their way "
	+ "inside as you inhale the meade's aroma getting a distinct hint of "
	+ "honey along with its strong aroma of alcohol." + race_smell() + "\n");
    tell_room(E(TP), QCTNAME(TP) + " lifts " + HIS(TP) + " mug of black meade "
	+ "to " + HIS(TP) + " nose sniffing it for a moment as " + HE(TP)
	+ " inhales its aroma." + race_smell() + "\n", ({TO, TP}));
    return 1;
}

int
sip(string str)
{
	NF("Sip what?\n");

	if (!str)
		return 0;

    if (!parse_command(str, ({}), "[mug] [of] [black] 'meade'") && str != "mug")
		return 0;

	TP->catch_msg("This is no sipping drink, my friend.  Black meade is to "
	+ "be thrown back and the more the merrier.\n");
	return 1;
}

string
race_smell()
{
	string cofrace = QRACE(TP);

	if (TP->query_guild_name_occ() == "Vampires of Emerald")
	{
		return "  There is no blood in this drink, but you do detect "
		+ "something else.  These humans have added blackroot to this "
		+ "meade which would explain the drink's name.";
	}

	else if (TP->query_guild_name_race() == "Noldor of Imladris")
	{
		return "  But what's this?  These humans have added blackroot to "
		+ "this meade which would explain the drink's name.";
	}

	else switch(cofrace)
	{

	case "elf":
	case "noldor":
	case "hobbit":
	case "drow":
	case "hobgoblin":
		return "  But what's this?  These humans have added blackroot to "
		+ "this meade which would explain the drink's name.";
	break;

	case "presence":
		return "This isn't the best form in which to enjoy this drink.";
	break;

	case "human":
	case "half-human":
	case "half-elf":
	case "dwarf":
	case "kender":
	case "gnome":
	case "goblin":
	case "orc":
	case "minotaur":
	case "uruk":
	default:
		return "";
	break;
	}
}

string
race_smell_do()
{
	string cofrace = QRACE(TP);

	if (TP->query_guild_name_occ() == "Vampires of Emerald")
	{
		return C(HE(TP)) + " smells " + HIS(TP) + " " + short() + " with "
		+ "an odd interest.";
	}

	else if (TP->query_guild_name_occ() == "Morgul Mages")
	{
		return C(HE(TP)) + " narrows " + HIS(TP) + " eyes as " + HE(TP)
		+ " sniffs at the " + short() + ".";
	}

	else if (TP->query_guild_name_race() == "Noldor of Imladris")
	{
		return C(HE(TP)) + " waves " + HIS(TP) + " nose over the " + short()
		+ "as " + HE(TP) + " breathes in its aroma slowly.  " + C(HE(TP))
		+ " raises an eyebrow alarmingly.";
	}

	else switch(cofrace)
	{

	case "elf":
	case "noldor":
	case "drow":
		return C(HE(TP)) + " waves " + HIS(TP) + " nose over the " + short()
		+ "as " + HE(TP) + " breathes in its aroma slowly.  " + C(HE(TP))
		+ " raises an eyebrow alarmingly.";
	break;

	case "hobbit":
		return C(HE(TP)) + " suddenly raises an eyebrow intriguingly at "
		+ HIS(TP) + " mug.";
	break;

	case "kender":
	case "gnome":
		return C(HE(TP)) + " smiles and nods " + HIS(TP) + " head "
		+ "in contemplation.";
	break;

	case "goblin":
	case "orc":
	case "minotaur":
	case "uruk":
		return C(HE(TP)) + " snorts " + HIS(TP) + " nostrils thirstily.";
	break;

	case "hobgoblin":
		return C(HE(TP)) + " snorts " + HIS(TP) + " nostrils as he "
		+ "growls excitedly at " + HIS(TP) + " mug.";
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
race_drink()
{
	string cofrace = QRACE(TP);

	if (TP->query_guild_name_occ() == "Vampires of Emerald")
	{
		return "Despite containing no blood whatsoever, you put on a "
		+ "good show of drinking the meade anyway.  That's the spirit!";
	}

	else if (TP->query_guild_name_race() == "Noldor of Imladris")
	{
		return "  With no regard for the addition of blackroot, you swallow "
		+ "the meade.\nAlmost immediately, you feel a lightness in your "
		+ "limbs as a warmth flushes across your face and your pulse "
		+ "quickens.";
	}

	else switch(cofrace)
	{

	case "elf":
	case "noldor":
	case "hobbit":
	case "drow":
		return "  With no regard for the addition of blackroot, you swallow "
		+ "the meade.\nAlmost immediately, you feel a lightness in your "
		+ "limbs as a warmth flushes across your face and your pulse "
		+ "quickens.";
	break;

	case "hobgoblin":
		return "  Ahh, blackroot!  Almost immediately, you feel speed and "
		+ "strength enter your limbs as a good warmth flushes across your "
		+ "face, and your heart thumps along strongly.";
	break;

	case "presence":
		return "This isn't the best form in which to enjoy this drink.";
	break;

	case "human":
	case "half-human":
	case "half-elf":
	case "dwarf":
	case "kender":
	case "gnome":
	case "goblin":
	case "orc":
	case "minotaur":
	case "uruk":
    default:
		return "  Whew!  That was strong for such a small draught.\nYou feel "
		+ "a lightness in your limbs as a warmth flushes across your face.";
	break;
	}
}

string
race_drink_do()
{
	string cofrace = QRACE(TP);

	if (TP->query_guild_name_occ() == "Vampires of Emerald")
	{
		return "pretends to drink " + HIS(TP) + " " + short()
		+ ", smiling as " + HE(TP) + " lets it dribble down " + HIS(TP)
		+ " chin.";
	}

	else if (TP->query_guild_name_occ() == "Morgul Mages")
	{
		return "nods " + one_of_list(({"knowingly", "coldly", "grimly",
		"surreptitiously", "mystically", "approvingly", "slowly"})) + " from "
		+ "within " + HIS(TP) + " hooded black robes.";
	}

	else if (TP->query_guild_name_race() == "Noldor of Imladris")
	{
		return "eyes the meade suspiciously before turning it up with a "
		+ "shrug.  " + C(HIS(TP)) + " eyes roll back in " + HIS(TP) + " head "
		+ "before " + HE(TP) + " smiles " + one_of_list(({"dizzily",
		  "dreamily", "confusedly", "bizarrely", "confoundedly", "oozingly",
		  "roticlerianly"})) + " as " + HE(TP) + " " + one_of_list(({"waves "
		+ "a hand in front of " + HIS(TP) + " swiftly flushing face.", "flaps "
		+ HIS(TP) + " arms like a bird.", "rubs " + HIS(TP) + " face in "
		+ "disbelief.", "rubs " + HIS(TP) + " face and neck sensually.",
		"moans:  Ahhhhh!", "says:  Mmmmme likey."}));
	}

	else switch(cofrace)
	{

	case "elf":
	case "noldor":
	case "drow":
		return "eyes the meade suspiciously before turning it up with a "
		+ "shrug.  " + C(HIS(TP)) + " eyes roll back in " + HIS(TP) + " head "
		+ "before " + HE(TP) + " smiles " + one_of_list(({"dizzily",
		  "dreamily", "confusedly", "bizarrely", "confoundedly", "oozingly",
		  "roticlerianly"})) + " as " + HE(TP) + " " + one_of_list(({"waves "
		+ "a hand in front of " + HIS(TP) + " swiftly flushing face.", "flaps "
		+ HIS(TP) + " arms like a bird.", "rubs " + HIS(TP) + " face in "
		+ "disbelief.", "rubs " + HIS(TP) + " face and neck sensually.",
		"moans:  Ahhhhh!", "says:  Mmmmme likey."}));
	break;

	case "hobbit":
		return "shrugs, turns up " + HIS(TP) + " meade, and smiles "
		+ one_of_list(({"dizzily", "dreamily", "confusedly",
		"bizarrely", "confoundedly", "oozingly", "roticlerianly"})) + " as "
		+ HE(TP) + " " + one_of_list(({"waves a hand in front of " + HIS(TP)
		+ " swiftly flushing face.", "flaps " + HIS(TP) + " arms like a "
		+ "bird.", "rubs " + HIS(TP) + " face in disbelief.", "rubs "
		+ HIS(TP) + " face and neck vicariously.", "moans:  Ahhhhh!", "says:  "
		+ "So yummmmmy in my tummmmmy."}));
	break;

	case "goblin":
	case "orc":
	case "minotaur":
	case "uruk":
		return "grunts approvingly and smiles " + one_of_list(({"dizzily",
		"dreamily", "confusedly", "bizarrely", "confoundedly", "oozingly",
		"roticlerianly"})) + " as " + HE(TP) + " " + one_of_list(({"waves a "
		+ "hand in front of " + HIS(TP) + " swiftly flushing face.", "flaps "
		+ HIS(TP) + " arms like a roc.", "rubs " + HIS(TP) + " face in "
		+ "disbelief.", "rubs " + HIS(TP) + " face and neck harshly.",
		  "moans:  Rahhhhh!", "says:  Mhis goud!"}));
	break;

	case "hobgoblin":
		return " snorts " + HIS(TP) + " nostrils while growling "
		+ one_of_list(({"dizzily", "dreamily", "confusedly",
		"bizarrely", "confoundedly", "oozingly", "roticlerianly"})) + " as "
		+ HE(TP) + " " + one_of_list(({"waves a hand in front of " + HIS(TP)
		+ " swiftly flushing face.", "flaps " + HIS(TP) + " arms like a "
		+ "wyvern.", "rubs " + HIS(TP) + " face in disbelief.", "rubs "
		+ HIS(TP) + " face and neck brutally.", "moans:  Ahhhhh!", "says:  "
		+ "Mrogass ja!"}));
	break;

	case "presence":
		return "displays little expression from the experience.";
	break;

	case "human":
	case "half-human":
	case "half-elf":
	case "dwarf":
	case "kender":
	case "gnome":
    case "default":
		return "smiles " + one_of_list(({"dizzily", "dreamily", "confusedly",
		"bizarrely", "confoundedly", "oozingly", "roticlerianly"})) + " as "
		+ HE(TP) + " " + one_of_list(({"waves a hand in front of " + HIS(TP)
		+ " swiftly flushing face.", "flaps " + HIS(TP) + " arms like a "
		+ "bird.", "rubs " + HIS(TP) + " face in disbelief.", "rubs "
		+ HIS(TP) + " face and neck sensually.", "moans:  Ahhhhh!", "says:  "
		+ "Mmmmme likey."}));
	break;
	}
}

void
special_effect(int numofdrinks)
{
	string meades = LANG_WNUM(numofdrinks);
	object mef;

	if (numofdrinks == 1)
	{
		TP->catch_msg("The pure golden yellow liquid goes down far too "
		+ "smoothly, its golden vapors tingling in your nose as the honey "
		+ "sweet taste tickles your throat." + race_drink() + "\n");
		say(QCTNAME(TP) + " " + race_drink_do() + "\n");
	}

	if (numofdrinks > 1 && numofdrinks <= 5)
	{
		TP->catch_msg("You toss back " + meades + " mugs of black meade and "
		+ "let out a hissing belch as you spew a stream of golden yellow "
		+ "vapor out of your mouth!\n");
		say(QCTNAME(TP) + " tosses back " + meades + " mugs of black meade and "
		+ "lets out a hissing belch as " + HE(TP) + " spews a stream of "
		+ "golden yellow vapor out of " + HIS(TP) + " mouth!\n");
		mef = clone_object(MERCH + "obj/black_meffect1");
		mef->move(TP);
	}

	if (numofdrinks > 5 && numofdrinks <= 10)
	{
		TP->catch_msg("You hurl back " + meades + " mugs of black meade and "
		+ "let out a hissing Wi-La belch of power as you spew a stream of "
		+ "golden yellow vapor out of your mouth filling the room with a "
		+ "foggy, yellow cloud!\n");
		say(QCTNAME(TP) + " hurls back  " + meades + " mugs of black meade and "
		+ "lets out a hissing Wi-La belch of power as " + HE(TP) + " spews a "
		+ "stream of golden yellow vapor out of " + HIS(TP) + " mouth filling "
		+ "the room with a foggy, yellow cloud!  Oh the taint!\n");
		mef = clone_object(MERCH + "obj/black_meffect2");
		mef->move(TP);
	}

	if (numofdrinks > 10 && numofdrinks <= 20)
	{
		TP->catch_msg("You throw your head back and dump " + meades + " mugs "
		+ "of black meade down your throat.\nYou let out an ear shattering "
		+ "quantum-belch of heady might spraying everyone in the room in "
		+ "the face with bits of the last things you ate as golden yellow "
		+ "vapor pours out of your ears!\n");
		say(QCTNAME(TP) + " throws " + HIS(TP) + " head back and dumps "
		+ meades + " mugs of black meade down " + HIS(TP) + " throat.\n"
		+ QCTNAME(TP) + " lets out an ear shattering quantum-belch of "
		+ "heady might spraying you in the face with bits of "
		+ one_of_list(({"roast pork", "roast boar", "roast boar brains",
			"roast boar heart", "chicken gizzard", "rotisserie chicken",
			"chocolate biscotti", "blueberry muffin", "garlicky spinach",
			"poppy-seeds", "stomach grime", "ass berries", "cod heads",
			"chumbly narnwhiffers", "pizza and sausage"})) + " as golden "
		+ "yellow vapor pours out of " + HIS(TP) + " ears!\n");
		mef = clone_object(MERCH + "obj/black_meffect2");
		mef->move(TP);
	}

	if (numofdrinks > 20)
	{
		TP->catch_msg("You throw your head back, open your mouth wide "
		+ "enough to swallow a whole boar, and dump " + meades + " mugs "
		+ "of black meade into your gullet.\nYour stomach rumbles and hisses "
		+ "alarmingly as you erupt in a volcano like explosive belch "
		+ "of ungodly power and might spraying everyone in the room in "
		+ "the face with streams of bile and bits of the last things you "
		+ "ate while golden yellow liquid streams out of your ears!\n");
		say(QCTNAME(TP) + " throws " + HIS(TP) + " head back, opens "
		+ HIS(TP) + " mouth wide enough to swallow a whole boar, and dumps "
		+ meades + " mugs of black meade into " + HIS(TP) + " gullet.\n"
		+ QCTNAME(TP) + "'s stomach rumbles and hisses alarmingly as " + HE(TP)
		+ " erupts in a volcano like explosive belch of ungodly power "
		+ "and might spraying you in the face with streams of bile and "
		+ "bits of " + one_of_list(({"roast pork", "roast boar",
			"roast boar brains","roast boar heart", "chicken gizzard",
			"rotisserie chicken","chocolate biscotti", "blueberry muffin",
			"garlicky spinach", "poppy-seeds", "stomach grime", "ass berries",
			"cod heads", "chumbly narnwhiffers", "pizza and sausage"}))
		+ " while golden yellow liquid streams out of " + HIS(TP)
		+ " ears!\n");
		mef = clone_object(MERCH + "obj/black_meffect2");
		mef->move(TP);
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
