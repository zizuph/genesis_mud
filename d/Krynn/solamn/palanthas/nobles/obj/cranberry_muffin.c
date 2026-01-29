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
    set_adj(({"cranberry", "orange"}));
	set_short("cranberry orange muffin");
    set_pshort("cranberry orange muffins");
    set_long("A freshly baked and rather large, fluffy muffin thick with "
	+ "pieces of cranberry and orange and topped with a crusty "
	+ "sprinkling of rough grained sugar.\n");
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
	if (!str || !parse_command(str, ({}), "[cranberry] [orange] 'muffin' / 'muffins' "))
	return 0;

    TP->catch_msg("The smell of tart, tangy cranberries are perfectly "
	+ "complimented with the citrus-fresh hint of orange and moist, sweet "
	+ "cake.\n");
    tell_room(E(TP), QCTNAME(TP)+ " lifts " + HIS(TP) + " cranberry orange "
	+ "muffin to " + HIS(TP) + " nose sniffing it "
	+ "for a moment as " + PRONOUN(TP) + " inhales its aroma.\n",
		({TO, TP}));

    return 1;
}

void
special_effect(int n)
{
	write("You crunch through the sugar encrusted muffin top and get "
	+ "a taste of the moist, sweet muffin center with its tart, tangy "
	+ "cranberries perfectly complimented by the citrus-fresh taste of "
	+ "orange.\n");
	tell_room(E(TP), QCTNAME(TP)+ " crunches through the sugar encrusted "
	+ "top of " + HIS(TP) + " cranberry orange muffin.\n", ({TO, TP}));
}
