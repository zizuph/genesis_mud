/*
 * Food available from Green Twitch Inn in Palanthas.
 * Created when roti_chicken is carved.
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
    set_name("meat");
    set_pname("meats");
	add_name(({"chicken", "leg"}));
	add_pname(({"chickens", "legs"}));
    set_adj("dark");
	add_adj(({"rotisserie", "large"}));
	set_short("large rotisserie chicken leg");
	set_pshort("large rotisserie chicken legs");
    set_long("This is a leg of juicy dark meat from a rotisserie "
	+ "chicken.  It is particularly large and succulent.\n");

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
	if (!str || !parse_command(str, ({}), "[dark] [large] [rotisserie] 'meat' / 'chicken' / 'leg'"))
	return 0;

    TP->catch_msg("You smell " + short() + ".  The scent of "
	+ "freshly carved, rotisserie style chicken fills your senses.\n");
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
	+ "rotisserie style chicken.\n");
	tell_room(E(TP), QCTNAME(TP) + " begins consuming " + HIS(TP) + " "
	+ short() + ", its juices spilling into " + HIS(TP) + " mouth and "
	+ "filling the air with the scent of freshly carved, rotisserie style "
	+ "chicken.\n", ({TO, TP}));
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
