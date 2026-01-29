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
    set_amount(90);
    set_name("head");
    set_pname("heads");
	add_name(({"meat", "boar", "pork"}));
	add_pname(({"meats", "boars", "porks"}));
    set_adj(({"roast"}));
	add_adj("whole");
	set_short("roast boar head");
	set_pshort("roast boar heads");
    set_long("This a dark brown boar's head from a whole, roast "
	+ "boar.  It stares up at you with succulent glazed eyes.\n");

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
	if (!str || !parse_command(str, ({}), "[whole] [roast] 'meat' / 'head' / 'boar' / 'pork'"))
	return 0;

    TP->catch_msg("You smell " + short() + ".  The scent of "
	+ "freshly carved, roast boar fills your senses.\n");
    tell_room(E(TP), QCTNAME(TP)+ " lifts " + HIS(TP) + " " + short()
	+ " to " + HIS(TP) + " nose sniffing it for a moment as " + PRONOUN(TP)
	+ " inhales its scents.\n", ({TO, TP}));
    return 1;
}

void
special_effect(int n)
{
	write("You begin consuming " + short() + ", its juices and "
	+ "flavours filling your mouth with the taste of freshly carved, "
	+ "roast boar head.\n");
	tell_room(E(TP), QCTNAME(TP) + " begins consuming " + HIS(TP) + " "
	+ short() + ", its juices spilling into " + HIS(TP) + " mouth and "
	+ "filling the air with the scent of freshly carved, roast boar "
	+ "head.\n", ({TO, TP}));
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
