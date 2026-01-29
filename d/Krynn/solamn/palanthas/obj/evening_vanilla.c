inherit "/std/object";
inherit "/lib/keep";

#include <macros.h>
#include "../local.h"

int sips = 9 + random(4);
//int cofremove;
string cofrace;
string race_smell();
string race_smell_do();
string race_sip();
string race_sip_do();
void sippin_cof();

create_object()
{
//    set_soft_amount(6);
//    set_alco_amount(0);
    set_name("roast");
	add_name("coffee");
    set_adj(({"evening", "vanilla"}));
    set_short("evening vanilla roast");
    set_pshort("evening vanilla roasts");
    set_long("Served in a sturdy, brown paper cup, curls of steam rise "
	+ "from this moderately dark coffee.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);

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

    if (!parse_command(str, ({}),
	   "[evening] [vanilla] 'roast' / 'coffee'"))
	return 0;

    write("You lift the evening roast to your nose, and smell "
	+ "its aroma catching a hint of nuts and distinct vanilla flavour "
	+ "roasted with the beans.  " + race_smell() + "\n");
    tell_room(E(TP), QCTNAME(TP)+ " raises a brown cup of coffee to "
	+ HIS(TP) + " nose smelling its aroma.  " + race_smell_do() + "\n",
		({TO, TP}));

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
	   "[evening] [vanilla] 'roast' / 'coffee'"))
	return 0;

	if (TP->drink_soft(6, 0))
	{
	TP->drink_soft(6, 0);

    write("Your eyelids lower slowly as the hot, vanilla flavours "
	+ "in the rich evening brew flow past your lips accompanied by a mild "
	+ "hint of nuts.  " + race_sip() + "\n");
    tell_room(E(TP), QCTNAME(TP) + "'s eyelids lower slowly as " + HE(TP)
	+ " takes a sip of the evening vanilla roast.  " + race_sip_do()
	+ "\n", ({TO, TP}));
	sips--;
	if (sips <= 0) 	{ sippin_cof(); }

	}

	else write("You are full and cannot drink any more.\n");

    return 1;
}

public mixed
sippin_cof()
{
	TP->catch_msg("You turn up the cup and the last drop falls on "
	+ "your tongue.\n");
	tell_room(E(TP), QCTNAME(TP) + " turns up " + HIS(TP) + " cup of brown "
	+ "coffee allowing the last drop to fall on " + HIS(TP) + " tongue.\n",
		({TO, TP}));
/*	cofremove = TO->num_heap();
	cofremove--;*/
	TO->remove_object();
}

int
drink(string str)
{
	if (!str)
	return 0;

    if (!parse_command(str, ({}),
	   "[evening] [vanilla] 'roast' / 'coffee'"))
	return 0;

	if (sips > 0)
	{
		TP->catch_msg("You try to drink too much at once and end up burning the tip "
		+ "of your tongue most painfully.\n");
		tell_room(E(TP), QCTNAME(TP) + " cries out in pain as " + PRONOUN(TP) + " burns "
		+ HIS(TP) + " tongue trying to drink hot evening coffee too quickly:  "
		+ "Nooooo!  Why?!?" + "\n", ({TO, TP}));
		return 1;
	}
}

string
race_smell()
{

	if (TP->query_guild_name_occ() == "Vampires of Emerald")
	{
		return "Though hot, there is no blood in this drink.";
	}

	else if (TP->query_guild_name_occ() == "Morgul Mages")
	{
		return "The smell of earth is strong in this drink.  It may "
		+ "enhance that sphere of elemental magic.";
	}

	else if (TP->query_guild_name_race() == "Noldor of Imladris")
	{
		return "As you breathe in the vapors, you feel a strangely "
		+ "pleasant warmth spread through you.";
	}

	else switch(cofrace)
	{

	case "elf":
	case "noldor":
	case "drow":
		return "As you breathe in the vapors, you feel a strangely "
	    + "pleasant warmth spread through you.";
	break;

	case "hobbit":
	case "kender":
	case "gnome":
		return "This fine roast has been tended to by a master at every "
	    + "stage of its life.  Its flavours are well worth further "
		+ "scrutinization.";
	break;

	case "goblin":
	case "orc":
	case "hobgoblin":
	case "minotaur":
		return "Something is definitely wrong... are the humans trying to "
		+ "poison you with this brew?";
	break;

	case "presence":
		return "This isn't the best form in which to enjoy this drink.";
	break;

	case "human":
	case "half-human":
	case "half-elf":
	case "dwarf":
    default:
		return "This is a fine coffee.";
	break;


	}
}

string
race_smell_do()
{
	if (TP->query_guild_name_occ() == "Vampires of Emerald")
	{
		return QCTNAME(TP) + " turns " + HIS(TP) + " nose up in disinterest "
		+ "at the drink.";
	}

	else if (TP->query_guild_name_occ() == "Morgul Mages")
	{
		return QCTNAME(TP) + " raises an eyebrow as " + HE(TP) + " broods "
		+ "deep in thought.";
	}

	else if (TP->query_guild_name_race() == "Noldor of Imladris")
	{
		return QCTNAME(TP) + "'s face flushes red momentarily as " + HE(TP)
		+ " breathes in slowly, " + HIS(TP) + " eyes rolling up under "
		+ HIS(TP) + " eyelids.";
	}

	else switch(cofrace)
	{


	case "elf":
	case "noldor":
	case "drow":
		return QCTNAME(TP) + "'s face flushes red momentarily as " + HE(TP)
		+ " breathes in slowly, " + HIS(TP) + " eyes rolling up under "
		+ HIS(TP) + " eyelids.";
	break;

	case "hobbit":
	case "kender":
	case "gnome":
		return QCTNAME(TP) + " closes " + HIS(TP) + " eyes for a moment "
		+ "and smiles, obviously enjoying " + HIMSELF(TP) + ".";
	break;

	case "goblin":
	case "orc":
	case "hobgoblin":
	case "minotaur":
		return QCTNAME(TP) + " squints one eye and stares suspiciously "
		+ "down at the cup with " + HIS(TP) + " other.";
	break;

	case "presence":
		return QCTNAME(TP) + " displays little expression from the "
		+ "experience.";
	break;

    case "human":
	case "half-human":
	case "half-elf":
	case "dwarf":
    default:
        return QCTNAME(TP) + " closes " + HIS(TP) + " eyes for a moment "
		+ "as " + HIS(TP) + " eyebrows rise a tad.";
	break;

	}
}

string
race_sip()
{
	if (TP->query_guild_name_occ() == "Vampires of Emerald")
	{
		return "Despite containing no blood whatsoever, you put on a "
		+ "good show of sipping the coffee anyway.  That's the spirit!";
	}

	else if (TP->query_guild_name_occ() == "Morgul Mages")
	{
		return "You feel the hot, earthy flavours spilling into you, "
		+ "imbuing your bones with the enhancing powers of earth and "
		+ "water.";
	}

	else if (TP->query_guild_name_race() == "Noldor of Imladris")
	{
		return "An unexpectedly strange but pleasant warmth spreads through "
	    + "your body overcoming your composure for a moment.  Mmmmmm.";
	}

	else switch(cofrace)
	{

	case "elf":
	case "noldor":
	case "drow":
		return "An unexpectedly strange but pleasant warmth spreads through "
	    + "your body overcoming your composure for a moment.  Mmmmmm.";
	break;

	case "hobbit":
	case "kender":
	case "gnome":
		return "What splendid flavours are these!  Oh, happy is the day "
		+ "you discovered this lovely brew.";
	break;

	case "goblin":
	case "orc":
	case "hobgoblin":
	case "minotaur":
		return "Bleh!  P'tooey!  What poisons are these you've been served?";
	break;

	case "presence":
		return "This isn't the best form in which to enjoy this drink.";
	break;

	case "human":
	case "half-human":
	case "half-elf":
	case "dwarf":
    default:
		return one_of_list(({"This is indeed a fine coffee.",
	       "The lady of the Light Hart knows her brewing.",
		   "This coffee alone leaves you impressed with Palanthas' brewing",
		   "Ahh, how pleasant!"}));
	break;

	}
}

string
race_sip_do()
{
	if (TP->query_guild_name_occ() == "Vampires of Emerald")
	{
		return QCTNAME(TP) + " pretends to sip " + HIS(TP) + " evening "
		+ "vanilla roast, smiling as " + HE(TP) + " lets it dribble down "
		+ HIS(TP) + " chin.";
	}

	else if (TP->query_guild_name_occ() == "Morgul Mages")
	{
		return QCTNAME(TP) + "'s eyes throb briefly with a red glow as "
		+ HE(TP) + " smiles " + one_of_list(({"knowingly", "coldly", "grimly",
		"surreptitiously", "mystically", "slightly", "slowly"})) + " from "
		+ "within " + HIS(TP) + " hooded black robes.";
	}

	else if (TP->query_guild_name_race() == "Noldor of Imladris")
	{
		return QCTNAME(TP) + "'s face flushes red momentarily as " + HE(TP)
		+ " exhales, " + HIS(TP) + " eyes rolling up under "
		+ HIS(TP) + " eyelids as " + HE(TP) + one_of_list(({
		  " moans quietly.",
		  " rubs " + HIS(TP) + " hand slowly down " + HIS(TP) + " stomach.",
		  " squeezes " + HIS(TP) + " legs together.",
		  " goes:  Mmmmmm.",
		  " licks " + HIS(TP) + " lips luxuriantly."}));
	}

	else switch(cofrace)
	{

	case "elf":
	case "noldor":
	case "drow":
		return QCTNAME(TP) + "'s face flushes red momentarily as " + HE(TP)
		+ " exhales, " + HIS(TP) + " eyes rolling up under "
		+ HIS(TP) + " eyelids as " + HE(TP) + one_of_list(({
		  " moans quietly.",
		  " rubs " + HIS(TP) + " hand slowly down " + HIS(TP) + " stomach.",
		  " squeezes " + HIS(TP) + " legs together.",
		  " goes:  Mmmmmm.",
		  " licks " + HIS(TP) + " lips luxuriantly."}));
	break;

	case "hobbit":
	case "kender":
	case "gnome":
		return QCTNAME(TP) + " closes " + HIS(TP) + " eyes for a moment "
		+ "and giggles, obviously enjoying " + HIMSELF(TP) + ".";
	break;

	case "goblin":
	case "orc":
	case "hobgoblin":
	case "minotaur":
		return QCTNAME(TP) + one_of_list(({
		" spits out a glob of brown spittle in disgust and horror!",
		" cries out, \"I've been poisoned!\" as brown coffee dribbles "
		+ "down " + HIS(TP) + " chin.",
		" groans as " + HE(TP) + " clutches " + HIS(TP) + " stomach, "
		+ "hurling brown glek on " + HIS(TP) + " shoes."}));
	break;

	case "presence":
		return QCTNAME(TP) + " displays little expression from the "
		+ "experience.";
	break;

	case "human":
	case "half-human":
	case "half-elf":
	case "dwarf":
    default:
		return QCTNAME(TP) + " closes " + HIS(TP) + " eyes for a moment "
		+ "as " + HE(TP) + " breaks a half smile, nodding.";
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
