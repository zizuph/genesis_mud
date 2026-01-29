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
    set_name("meat");
    set_pname("meats");
	add_name(({"boar", "pork"}));
	add_pname(({"boars", "porks"}));
    set_adj(({"roast"}));
	add_adj("whole");
	set_short("roast boar meat");
	set_pshort("roast boar meats");
    set_long("This a dark brown boar's meat from a whole, roast "
	+ "boar.  It is particularly succulent and has been pulled into "
	+ "large shreds.\n");

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
	if (!str || !parse_command(str, ({}), "[whole] [roast] 'meat' / 'boar' / 'pork'"))
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
	+ "roast boar meat.\n");
	tell_room(E(TP), QCTNAME(TP) + " begins consuming " + HIS(TP) + " "
	+ short() + ", its juices spilling into " + HIS(TP) + " mouth and "
	+ "filling the air with the scent of freshly carved, roast boar "
	+ "meat.\n", ({TO, TP}));
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
