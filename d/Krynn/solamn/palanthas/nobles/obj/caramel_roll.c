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
    set_amount(70);
    set_name("roll");
    set_pname("rolls");
    set_adj(({"caramel", "pecan", "sticky"}));
	set_short("caramel pecan sticky roll");
    set_pshort("caramel pecan sticky rolls");
    set_long("This subtly-spicy cinnamon roll with a sweet pecan-and-caramel "
	+ "topping perfectly compliments a cup of coffee.\n");
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
	if (!str || !parse_command(str, ({}), "[caramel] [pecan] [sticky] 'roll' / 'rolls' "))
	return 0;

    TP->catch_msg("You smell the sticky roll getting a hint of its "
	+ "rich caramel and pecans.\n");
    tell_room(E(TP), QCTNAME(TP)+ " lifts " + HIS(TP) + " caramel pecan "
	+ "sticky roll to " + HIS(TP) + " nose sniffing it "
	+ "for a moment as " + PRONOUN(TP) + " inhales its aroma.\n",
		({TO, TP}));

    return 1;
}

void
special_effect(int n)
{
	write("You crunch into your sticky roll getting a taste of its "
	+ "rich caramel and pecans.\n");
	tell_room(E(TP), QCTNAME(TP)+ " crunches into " + HIS(TP) + " caramel "
	+ "pecan sticky roll.\n", ({TO, TP}));
}
