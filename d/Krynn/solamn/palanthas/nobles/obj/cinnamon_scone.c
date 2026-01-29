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
    set_adj(({"cinnamon", "chip", "scone", "iced", "icing"}));
	set_short("cinnamon chip scone with icing");
    set_pshort("cinnamon chip scones with icing");
    set_long("This buttery cream scone is laced with the fragrant taste "
	+ "of cinnamon for a perfect afternoon pick-me-up. Studded with rich "
	+ "cinnamon chips, it is capped off with a luscious layer of icing.\n");
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
	if (!str || !parse_command(str, ({}), "[cinnamon] [chip] 'scone' / 'scones' "))
	return 0;

    TP->catch_msg("You smell the scone getting a hint of its "
	+ "buttery richness and cinnamon chips.\n");
    tell_room(E(TP), QCTNAME(TP)+ " lifts " + HIS(TP) + " cinnamon "
	+ "chip scone with icing to " + HIS(TP) + " nose sniffing it "
	+ "for a moment as " + PRONOUN(TP) + " inhales its aroma.\n",
		({TO, TP}));

    return 1;
}

void
special_effect(int n)
{
	write("You crunch into your scone getting a taste of its "
	+ "buttery richness, cinnamon chips, and sweet icing.\n");
	tell_room(E(TP), QCTNAME(TP)+ " crunches into " + HIS(TP) + " cinnamon "
	+ "chip scone with icing.\n", ({TO, TP}));
}
