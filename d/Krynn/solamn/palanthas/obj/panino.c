/* 
 * Palanthas food by Mortis 09.2005
 */

#pragma save_binary
#pragma strict_types

inherit "/std/food.c";
#include <macros.h>
#include <composite.h>
#include "../local.h";

public void
create_food()
{
    set_amount(140);
    set_name("panino");
    set_pname("paninos");
	set_adj("turkey");
    set_short("turkey panino");
    set_pshort("turkey paninos");
    set_long("A hot sandwich consisting of strips of turkey breast, "
	+ "sauteed, roasted peppers, and aged provolone cheese all wedged "
	+ "into a pocket of hearty, wheat bread and grilled until its outer "
	+ "crust is dark, flakey crispy.\n");
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
    NF("Smell what?\n");

    if (!str)
	return 0;

    if (str != "sandwich" && str != "turkey panino" && str != "panino")
	return 0;

    TP->catch_msg("The spicy smells of sauteed, roasted peppers, provolone "
	+ "cheese, turkey, and dark toasted bread fill your senses.\n");
    tell_room(E(TP), QCTNAME(TP)+ " lifts " + HIS(TP) + " turkey panino "
	+ "to " + HIS(TP) + " nose sniffing it "
	+ "for a moment as " + PRONOUN(TP) + " inhales its aroma.\n",
		({TO, TP}));

    return 1;
}

void
special_effect(int n)
{
    TP->catch_msg("Your first bite of the hot panino crunches through its "
	+ "dark, flakey crispy outer crust filling your mouth with sauteed, "
	+ "roasted green and red peppers, melted provolone cheese, and grilled "
	+ "turkey.\n");
}
