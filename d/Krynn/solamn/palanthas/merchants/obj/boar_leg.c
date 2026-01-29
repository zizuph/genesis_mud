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
    set_name("leg");
    set_pname("legs");
	add_name(({"meat", "boar", "pork"}));
	add_pname(({"meats", "boars", "porks"}));
    set_adj(({"roast"}));
	add_adj("whole");
	set_short("roast boar leg");
	set_pshort("roast boar legs");
    set_long("This a dark brown boar's leg from a whole, roast "
	+ "boar.  Its skin is crisp and flaky concealing succulent meat "
	+ "within.\n");

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
	if (!str || !parse_command(str, ({}), "[whole] [roast] 'meat' / 'leg' / 'boar' / 'pork'"))
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
	+ "roast boar leg.\n");
	tell_room(E(TP), QCTNAME(TP) + " begins consuming " + HIS(TP) + " "
	+ short() + ", its juices spilling into " + HIS(TP) + " mouth and "
	+ "filling the air with the scent of freshly carved, roast boar "
	+ "leg.\n", ({TO, TP}));
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
