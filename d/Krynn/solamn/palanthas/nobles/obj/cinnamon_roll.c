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
    set_name("roll");
    set_pname("rolls");
    set_adj(({"cinnamon"}));
	set_short("cinnamon roll");
    set_pshort("cinnamon rolls");
    set_long("This subtly-spicy classic is a traditional favorite. It comes "
	+ "crowned with a rich layer of cream cheese icing.\n");
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
	if (!str || !parse_command(str, ({}), "[cinnamon] 'roll' / 'rolls' "))
	return 0;

    TP->catch_msg("You smell the roll getting a hint of its "
	+ "spicy cinnamon and sweet icing.\n");
    tell_room(E(TP), QCTNAME(TP)+ " lifts " + HIS(TP) + " cinnamon "
	+ "chip scone with icing to " + HIS(TP) + " nose sniffing it "
	+ "for a moment as " + PRONOUN(TP) + " inhales its aroma.\n",
		({TO, TP}));

    return 1;
}

void
special_effect(int n)
{
	write("You bite into your roll getting a taste of its "
	+ "spicy cinnamon and sweet, cream cheese icing.\n");
	tell_room(E(TP), QCTNAME(TP)+ " bites into " + HIS(TP) + " cinnamon "
	+ "roll.\n", ({TO, TP}));
}
