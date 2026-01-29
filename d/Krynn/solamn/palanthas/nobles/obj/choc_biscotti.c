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
    set_adj(({"chocolate", "hazelnut", "choc"}));
	set_short("chocolate hazelnut biscotti");
    set_pshort("chocolate hazelnut biscottis");
    set_long("A dry, traditional dipping cookie that absorbs and complements "
	+ "coffee, espresso, tea and wine. This pairing of rich chocolate and "
	+ "hazelnuts is a classic part of the espresso experience.\n");

	add_prop("_gui_likes_this_biscotti", 1);
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
	if (!str || !parse_command(str, ({}), "[choc] [chocolate] [hazelnut] 'biscotti' / 'biscottis' "))
	return 0;

    TP->catch_msg("You smell the biscotti getting a hint of its "
	+ "chocolate and hazelnuts.\n");
    tell_room(E(TP), QCTNAME(TP)+ " lifts " + HIS(TP) + " chocolate "
	+ "hazelnut biscotti to " + HIS(TP) + " nose sniffing it "
	+ "for a moment as " + PRONOUN(TP) + " inhales its aroma.\n",
		({TO, TP}));

    return 1;
}

void
special_effect(int n)
{
	write("You crunch into your biscotti getting a taste of its "
	+ "chocolate and hazelnuts.\n");
	tell_room(E(TP), QCTNAME(TP)+ " crunches into " + HIS(TP) + " chocolate "
	+ "hazelnut biscotti.\n", ({TO, TP}));
}
