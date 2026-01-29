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
    set_name("biscotti");
    set_pname("biscottis");
    set_adj(({"vanilla", "almond"}));
	set_short("vanilla almond biscotti");
    set_pshort("vanilla almond biscottis");
    set_long("A dry, traditional dipping cookie that absorbs and complements "
	+ "coffee, espresso, tea and wine. The biscotti pairs delicate vanilla "
	+ "with crunchy almonds in a sweet pairing that's a classic part of the "
	+ "espresso experience.\n");
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
	if (!str || !parse_command(str, ({}), "[vanilla] [almond] 'biscotti' / 'biscottis' "))
	return 0;

    TP->catch_msg("You smell the biscotti getting a hint of its "
	+ "vanilla and almonds.\n");
    tell_room(E(TP), QCTNAME(TP)+ " lifts " + HIS(TP) + " vanilla "
	+ "almond biscotti to " + HIS(TP) + " nose sniffing it "
	+ "for a moment as " + PRONOUN(TP) + " inhales its aroma.\n",
		({TO, TP}));

    return 1;
}

void
special_effect(int n)
{
	write("You crunch into your biscotti getting a taste of its "
	+ "vanilla and almonds.\n");
	tell_room(E(TP), QCTNAME(TP)+ " crunches into " + HIS(TP) + " vanilla "
	+ "almond biscotti.\n", ({TO, TP}));
}
