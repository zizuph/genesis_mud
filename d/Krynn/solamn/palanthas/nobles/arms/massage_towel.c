/* Mortis 02.2006
 *
 * Towel required to be worn for massages at the
 * Laethorian dayspa of Palanthas' Plaisir district.
 *
 */

inherit "/std/armour";

#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <cmdparse.h>
#include <language.h>
#include <composite.h>
#include <std.h>
#include "../../local.h"

#define NUD_SUBLOC			"_i_wear_nothing_but_a_towel"

inherit "/cmd/std/command_driver";

/* prototypes */
public string show_subloc(string subloc, object pl, object for_obj);

public void
create_armour()
{
	set_name("towel");
	set_pname("towels");
	add_name("_laethorian_massage_towel");
	set_adj("white");
	add_adj(({"short", "massage"}));
	set_short("short white towel");
	set_pshort("short white towels");
	set_long("This short white towel is fluffy and comfortable.  It is "
	+ "worn around the waist when getting a massage at the Laethorian and "
	+ "can be worn with nothing else.  When you are finished with it, you "
	+ "may <return> it to its hamper.\n");

	set_ac(1);
	set_at(A_WAIST);

	add_prop(OBJ_I_VOLUME, 350);
	add_prop(OBJ_I_WEIGHT, 400 + random(50));
	add_prop(OBJ_I_VALUE, 0);
	add_prop(OBJ_I_NO_DROP, "If you are done with your towel, please "
	+ "<return> it to its hamper.\n");
}

void
init()
{
    ::init();
    ADD("return_towel", "return");
	ADA("wear");
	ADA("remove");
}

int
return_towel(string str)
{
	NF("Return what to the hamper?\n");
	if (!str)
		return 0;

	if (!parse_command(str, ({}), "[the] [short] [white] [massage] 'towel' [to] [its] [the] [hamper]"))
		return 0;
	
	if (TO->query_worn())
	{
		TP->catch_msg("You unfold the towel from your waist...\n");
		say(QCTNAME(TP) + " unfolds the towel from " + HIS(TP)
		+ " waist...\n");
		TP->command("remove towel");
		TP->catch_msg("...and toss it into the hamper.\n");
		say(QCTNAME(TP) + "...and tosses it into the hamper.\n");
	}
	else
	{
		TP->catch_msg("You toss your towel into the hamper.\n");
		say(QCTNAME(TP) + " tosses " + HIS(TP) + " towel into the "
		+ "hamper.\n");
	}
	remove_object();
	return 1;
}

public mixed
wear(string str)
{
	if (TO->query_worn())
	{
		write("You cannot wear anything with the massage towel.\n");
		return 1;
	}

	if (sizeof(TP->query_armour(-1))
		&& parse_command(str, ({}), "[short] [white] [massage] 'towel' / 'towels'"))
	{
		write("You must remove everything you are wearing in order to wear "
		+ "the massage towel.\n");
		return 1;
	}
	else if (sizeof(TP->query_armour(-1)))
	{
		write("test1\n");
		return 0;
	}

	if (!parse_command(str, ({}), "[short] [white] [massage] 'towel' / 'towels'"))
	{
		write("test\n");
		return 0;
	}

	else
	{
	write("You fold your short white towel around your waist.\n");
	say(QCTNAME(TP) + " folds " + HIS(TP) + " short white towel around "
	+ HIS(TP) + " waist.\n");
	TP->add_subloc(NUD_SUBLOC, TO);
	}
	return 0;
}

mixed
remove(string str)
{
	if (parse_command(str, ({}), "[short] [white] [massage] 'towel' / 'towels' / 'all'"))
		TP->remove_subloc(NUD_SUBLOC);
    return 0;
}

public string
show_subloc(string subloc, object pl, object for_obj)
{
	string name;

	if (TP->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	{
		return "";
	}

	if (subloc != NUD_SUBLOC)
	{
		return pl->show_subloc(subloc, pl, for_obj);
	}

	if (for_obj != pl)
	{
		return capitalize(pl->query_pronoun()) +
		" is completely naked except for a short white towel around "
		+ HIS(pl) + " waist.\n";
	}
	return "You are completely naked except for a short white towel around "
		+ "your waist.\n";
}
