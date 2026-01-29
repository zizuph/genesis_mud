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

int temp = 1;	// 1 is hot, 0 is warm

public void
create_food()
{
    set_amount(70);
    set_name("pheasant");
    set_pname("pheasants");
    set_adj(({"hot"}));
	add_adj("rotisserie");
    set_long("This " + "@@warm_hot@@" + " pheasant is dripping with its own "
	+ "juices, its golden brown skin concealing succulent meat within.\n");

	set_alarm(330.0, 0.0, "make_temp");
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
	if (!str || !parse_command(str, ({}), "[hot] [warm] [rotisserie] 'pheasant'"))
	return 0;

    TP->catch_msg("You smell " + short() + ".  The scent of "
	+ "freshly cooked, rotisserie style wild meat fills your senses.\n");
    tell_room(E(TP), QCTNAME(TP)+ " lifts " + HIS(TP) + " " + short()
	+ " to " + HIS(TP) + " nose sniffing it for a moment as " + PRONOUN(TP)
	+ " inhales its scents.\n", ({TO, TP}));
    return 1;
}

void
special_effect(int n)
{
	write("You begin consuming " + short() + ", its juices and "
	+ "oils filling your mouth with the taste of freshly caught, rotisserie "
	+ "style, wild meat.");
	tell_room(E(TP), QCTNAME(TP) + " begins consuming " + HIS(TP) + " "
	+ short() + ", its juices spilling into " + HIS(TP) + " mouth and "
	+ "filling the air with the scent of freshly caught, rotisserie style, "
	+ "wild meat.", ({TO, TP}));

	if (temp == 1)
	{
		write("  There's nothing like hot, rotisserie meat cooked over an "
		+ "open fire.\n");
		say("  " + QCTNAME(TP) + " smiles and nods in "
		+ "satisfaction.\n");
	}

	if (temp == 0)
	{
		write("  You can't help thinking it might have been better hot.\n");
		say("  " + QCTNAME(TP) + " nods half-heartedly.\n");
	}
}

int
make_temp()
{
	remove_adj("hot");
	set_adj("warm");
	set_short("warm rotisserie pheasant");
	temp = 0;
	write("Your rotisserie pheasant has cooled down a bit.\n");
	return 1;
}

string
warm_hot()
{
	if (temp == 1)
	{ return "hot"; }
		return "warm";
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
