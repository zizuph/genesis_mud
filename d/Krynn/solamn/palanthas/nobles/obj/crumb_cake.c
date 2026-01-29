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
    set_name("cake");
	add_name(({"square", "piece"}));
    set_pname("cakes");
	add_pname(({"squares", "pieces"}));
    set_adj(({"crumb", "square", "piece", "piece", "of"}));
	set_short("square piece of crumb cake");
    set_pshort("square pieces of crumb cake");
    set_long("This dense, sweet cake with vanilla undertones has a crumbly "
	+ "sugar and cinnamon topping.\n");
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
	if (!str || !parse_command(str, ({}), "[square] [piece] [of] [crumb] 'cake' / 'cakes' "))
	return 0;

    TP->catch_msg("You smell the square piece of cake getting a hint of its "
	+ "spicy cinnamon and sugar topping.\n");
    tell_room(E(TP), QCTNAME(TP)+ " lifts " + HIS(TP) + " square piece of "
	+ "crumb cake to " + HIS(TP) + " nose sniffing it "
	+ "for a moment as " + PRONOUN(TP) + " inhales its aroma.\n",
		({TO, TP}));

    return 1;
}

void
special_effect(int n)
{
	write("You bite into your square piece of cake getting a taste of its "
	+ "spicy cinnamon and sugar topping.\nA few crumbs from the topping "
	+ "tumble off.\n");
	tell_room(E(TP), QCTNAME(TP)+ " bites into " + HIS(TP) + " square piece "
	+ "of crumb cake.\nA few crumbs from the topping tumble off.\n",
		({TO, TP}));
}
