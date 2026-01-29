/* Mortis 07.2005
 */

inherit "/std/object";
inherit "/lib/keep";

#include <macros.h>
#include "../local.h"

int sips = 8 + random(4);
int cofremove;
void sippin_cof();


create_object()
{
    set_name("coffee");
    set_adj(({"strong", "morne"}));
    set_short("strong morne coffee");
    set_pshort("strong morne coffees");
    set_long("Served in a sturdy, white paper cup, this is a dark, "
	+ "aromatic coffee.\n");
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
    NF("Smell what?\n");

    if (!str)
	return 0;

    if (!parse_command(str, ({}),
	   "[strong] [morne] 'coffee'"))
	return 0;

    TP->catch_msg("You catch a mild hint of Rella berries within the "
	+ "strong coffee vapors indicating the beans are likely from "
	+ "Sancrist.\n");
    tell_room(E(TP), QCTNAME(TP)+ " stares reflectively down at " + HIS(TP)
	+ " strong morne coffee with " + HIS(TP) + " eyes "
	+ "for a moment as " + PRONOUN(TP) + " inhales its aroma.\n",
		({TO, TP}));

    return 1;
}

int
sip(string str)
{
    NF("Sip what?\n");

    if (!str)
	return 0;

    if (!parse_command(str, ({}),
	   "[strong] [morne] 'coffee'"))
	return 0;

	if (TP->drink_soft(5, 0))
	{
	TP->drink_soft(5, 0);

    TP->catch_msg("Your eyelids lift a tad as the hot, earthy flavours of "
	+ "a strong morning brew flow past your lips accompanied by a mild hint "
	+ "of Rella berries.\n");
	/*  enjoying..etc can be race specific */
    tell_room(E(TP), QCTNAME(TP) + "'s eyelids lift a tad as " + HE(TP)
	+ " takes a sip of the strong morne coffee.\n", ({TO, TP}));
	sips--;
	if (sips <= 0) 	{ sippin_cof(); }

	}

	else write("You are full and cannot drink any more.\n");

    return 1;
}

void
sippin_cof()
{
	TP->catch_msg("You turn up the cup and the last drop falls on "
	+ "your tongue.\n");
	tell_room(E(TP), QCTNAME(TP) + " turns up " + HIS(TP) + " cup of morne "
	+ "coffee allowing the last drop to fall on " + HIS(TP) + " tongue.\n",
		({TO, TP}));
	TO->remove_object();
}

int
drink(string str)
{
	if (!str)
	return 0;

    if (!parse_command(str, ({}),
	   "[strong] [morne] 'coffee'"))
	return 0;

	if (sips > 0)
	{
		TP->catch_msg("You try to drink too much at once and end up burning the tip "
		+ "of your tongue most painfully.\n");
		tell_room(E(TP), QCTNAME(TP) + " cries out in pain as " + PRONOUN(TP) + " burns "
		+ HIS(TP) + " tongue trying to drink hot morne coffee too quickly:  "
		+ "Nooooo!  Why?!?" + "\n", ({TO, TP}));
		return 1;
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
