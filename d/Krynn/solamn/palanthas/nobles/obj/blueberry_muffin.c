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
    set_adj(({"blueberry"}));
	set_short("blueberry muffin");
    set_pshort("blueberry muffins");
    set_long("A freshly baked and rather large, fluffy, bluish muffin "
	+ "thick with dark blueberries and topped with a crusty "
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
	if (!str || !parse_command(str, ({}), "[blueberry] 'muffin' / 'muffins' "))
	return 0;

    TP->catch_msg("The smell of blueberries and moist, sweet cake fills your "
	+ "nose.\n");
    tell_room(E(TP), QCTNAME(TP)+ " lifts " + HIS(TP) + " blueberry muffin "
	+ "to " + HIS(TP) + " nose sniffing it "
	+ "for a moment as " + PRONOUN(TP) + " inhales its aroma.\n",
		({TO, TP}));

    return 1;
}

void
special_effect(int n)
{
	write("You crunch through the sugar encrusted muffin top and get "
	+ "a taste of the moist, sweet muffin center with its traditional "
	+ "blueberries.\n");
	tell_room(E(TP), QCTNAME(TP)+ " crunches through the sugar encrusted "
	+ "top of " + HIS(TP) + " blueberry muffin.\n", ({TO, TP}));
}
