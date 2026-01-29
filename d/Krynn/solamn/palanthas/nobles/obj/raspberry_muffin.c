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
    set_name("muffin");
    set_pname("muffins");
    set_adj(({"raspberry", "cream", "cheese"}));
	set_short("raspberry cream cheese muffin");
    set_pshort("raspberry cream cheese muffins");
    set_long("A freshly baked and rather large, fluffy muffin thick with "
	+ "pieces of raspberry and topped with a crusty sprinkling of rough "
	+ "grained sugar around a center of cream cheese.\n");
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
	if (!str || !parse_command(str, ({}), "[rasp] [raspberry] [cream] [cheese] 'muffin' / 'muffins' "))
	return 0;

    TP->catch_msg("The smell of fresh raspberries are perfectly "
	+ "complimented with the rich cream cheese atop the moist, sweet "
	+ "cake.\n");
    tell_room(E(TP), QCTNAME(TP)+ " lifts " + HIS(TP) + " raspberry cream "
	+ "cheese muffin to " + HIS(TP) + " nose sniffing it "
	+ "for a moment as " + PRONOUN(TP) + " inhales its aroma.\n",
		({TO, TP}));

    return 1;
}

void
special_effect(int n)
{
	write("You crunch through the sugar encrusted and cream cheese filled "
	+ "muffin top and get a taste of the moist, sweet muffin center with "
	+ "its tangy, sweet raspberries perfectly complimented by the rich "
	+ "taste of cream cheese.\n");
	tell_room(E(TP), QCTNAME(TP)+ " crunches through the sugar encrusted "
	+ "top of " + HIS(TP) + " raspberry cream cheese muffin.\n", ({TO, TP}));
}
