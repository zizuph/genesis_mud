/*
 * Food available from Green Twitch Inn in Palanthas.
 * Created when roast_boar is carved.
 *
 * Mortis 01.2006
 */

#pragma save_binary
#pragma strict_types

#include <macros.h>
#include <composite.h>
#include "../../local.h"

inherit "/std/food.c";
inherit "/lib/keep";

public void
create_food()
{
    set_amount(85);
    set_name("heart");
    set_pname("hearts");
	add_name(({"meat", "boar", "pork"}));
	add_pname(({"meats", "boars", "porks"}));
    set_adj(({"roast", "steaming"}));
	set_short("steaming roast boar heart");
	set_pshort("steaming roast boar hearts");
    set_long("This are the steaming heart from a whole, roast "
	+ "boar.  It is stewing in its own red juices.\n");

}

void
init()
{
    ::init();
    ADA("smell");
}

int
smell(string str)
{
	string cofrace = QRACE(TP);
	string cofguild = TP->query_guild_name_occ();

	if (!str || !parse_command(str, ({}), "[steaming] [roast] 'meat' / 'heart' / 'boar' / 'pork'"))
	return 0;

    TP->catch_msg("You smell " + short() + ".  The scent of "
	+ "freshly cooked, roast boar heart fills your senses.\n");
    tell_room(E(TP), QCTNAME(TP) + " lifts " + HIS(TP) + " " + short()
	+ " to " + HIS(TP) + " nose sniffing it for a moment as " + PRONOUN(TP)
	+ " inhales its scents.\n", ({TO, TP}));

	if (cofrace == "elf" || cofguild == "noldor" || cofrace == "half-elf")
	{
		write("Ick, do humans really eat this stuff?\n");
		say(QCTNAME(TP) + " shrivels " + HIS(TP) + " and exhales with "
		+ "an almost hissing noise.\n");
		return 1;
	}

	if (cofrace == "minotaur" || cofrace == "orc" || cofrace == "goblin" || cofrace == "hobgoblin")
	{
		write("Mmmmmm, heart!\n");
		say(QCTNAME(TP) + " grins hungrily.\n");
		return 1;
	}
    return 1;
}

void
special_effect(int n)
{
	string cofrace = QRACE(TP);
	string cofguild = TP->query_guild_name_occ();

	write("You begin consuming " + short() + ", its juices and "
	+ "flavours filling your mouth with the taste of freshly cooked, "
	+ "roast boar heart.\n");
	tell_room(E(TP), QCTNAME(TP) + " begins consuming " + HIS(TP) + " "
	+ short() + ", its juices spilling into " + HIS(TP) + " mouth and "
	+ "filling the air with the scent of freshly cooked, roast boar "
	+ "heart.\n", ({TO, TP}));

	if (cofrace == "elf" || cofguild == "noldor" || cofrace == "half-elf")
	{
		write("You cough, gagging on the steaming roast boar heart.  Ick!\n");
		say(QCTNAME(TP) + " coughs, gagging on the steaming roast boar hearts "
		+ "as tiny heart bits fly out of " + HIS(TP) + " mouth.\n");
		return;
	}
	
	if (cofrace == "minotaur" || cofrace == "orc" || cofrace == "goblin" || cofrace == "hobgoblin")
	{
		write("Mmmmmm, you smile as roast boar heart juices stream down your "
		+ "chin.  That was good roast heart.  Are there more?\n");
		say(QCTNAME(TP) + " grins ear to ear as roast boar heart juices "
		+ "stream down " + HIS(TP) + " chin..\n");
		return;
	}
    return;
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
