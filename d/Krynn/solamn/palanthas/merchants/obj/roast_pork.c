/*
 * Food available from Green Twitch Inn in Palanthas.
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
    set_amount(70);
    set_name("pork");
    set_pname("porks");
	add_name(({"shred", "meat"}));
	add_pname(({"shreds", "meats"}));
    set_adj(({"shredded"}));
	add_adj(({"roast", "roasted"}));
	set_short("shredded roast pork");
	set_pshort("shreds of roast pork meat");
    set_long("Juicy and shredded, this roast pork has been pulled from a "
	+ "rotisserie cooked pig at a pig pickin'.\n");

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
	if (!str || !parse_command(str, ({}), "[shreds] [of] [shredded] [roast] [roasted] 'meat' / 'pork'"))
	return 0;

    TP->catch_msg("You smell " + short() + ".  The scent of "
	+ "freshly pulled, rotisserie style roast pork flavoured with barbecue "
	+ "spices fills your senses.\n");
    tell_room(E(TP), QCTNAME(TP)+ " lifts " + HIS(TP) + " " + short()
	+ " to " + HIS(TP) + " nose sniffing it for a moment as " + PRONOUN(TP)
	+ " inhales its scents.\n", ({TO, TP}));
    return 1;
}

void
special_effect(int n)
{
	write("You begin consuming " + short() + ", its juices and flavours "
	+ "filling your mouth with the taste of freshly pulled, rotisserie "
	+ "style, roast pork flavoured with barbecue spices.\n");
	tell_room(E(TP), QCTNAME(TP) + " begins consuming " + HIS(TP) + " "
	+ short() + ", its juices spilling into " + HIS(TP) + " mouth and "
	+ "filling the air with the scent of freshly pulled, rotisserie style, "
	+ "roast pork flavoured with barbecue spices.\n", ({TO, TP}));

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
