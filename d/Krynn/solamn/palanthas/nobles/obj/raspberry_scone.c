/* Mortis 12.2005
 */

#pragma save_binary
#pragma strict_types

inherit "/std/food.c";
#include <macros.h>
#include <composite.h>
#include "../../local.h"

public void
create_food()
{
    set_amount(65);
    set_name("scone");
    set_pname("scones");
    set_adj(({"raspberry"}));
	set_short("raspberry scone");
    set_pshort("raspberry scones");
    set_long("Rich, buttery, and bursting with the ripe fresh taste of "
	+ "raspberries, this classic pastry is a satisfying way to start off "
	+ "your day or as an afternoon accompaniment to your favorite "
	+ "Mer-cantile beverage.\n");
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
	if (!str || !parse_command(str, ({}), "[raspberry] 'scone' / 'scones' "))
	return 0;

    TP->catch_msg("You smell the scone getting a hint of its "
	+ "buttery richness and raspberries.\n");
    tell_room(E(TP), QCTNAME(TP)+ " lifts " + HIS(TP) + " raspberry scone "
	+ "to " + HIS(TP) + " nose sniffing it "
	+ "for a moment as " + PRONOUN(TP) + " inhales its aroma.\n",
		({TO, TP}));

    return 1;
}

void
special_effect(int n)
{
	write("You crunch into your scone getting a taste of its "
	+ "buttery richness and tangy sweet raspberries.\n");
	tell_room(E(TP), QCTNAME(TP)+ " crunches into " + HIS(TP) + " raspberry "
	+ "scone.\n",
		({TO, TP}));
}
