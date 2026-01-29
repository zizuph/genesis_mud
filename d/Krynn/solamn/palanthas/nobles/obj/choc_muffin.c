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
    set_adj(({"choc", "chocolate", "cream", "cheese"}));
	set_short("chocolate cream cheese muffin");
    set_pshort("chocolate cream cheese muffins");
    set_long("A freshly baked and rather large, decadent muffin thick with "
	+ "rich, dark chocolate and topped with a crusty sprinkling of rough "
	+ "grained sugar surrounding a pool of cream cheese.\n");
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
	if (!str || !parse_command(str, ({}), "[choc] [chocolate] [cream] [cheese] 'muffin' / 'muffins' "))
	return 0;

    TP->catch_msg("The smell of rich, dark chocolate perfectly "
	+ "paired with a sweet, creamy hint of cream cheese fills your senses.\n");
    tell_room(E(TP), QCTNAME(TP)+ " lifts " + HIS(TP) + " cranberry orange "
	+ "muffin to " + HIS(TP) + " nose sniffing it "
	+ "for a moment as " + PRONOUN(TP) + " inhales its aroma.\n",
		({TO, TP}));

    return 1;
}

void
special_effect(int n)
{
	write("You crunch through the sugar rimmed cream cheese top and get "
	+ "a taste of the moist, sweet muffin center with its rich, dark "
	+ "chocolate perfectly complimented by the sweet, cream cheese.\n");
	tell_room(E(TP), QCTNAME(TP)+ " crunches through the sugar encrusted "
	+ "top of " + HIS(TP) + " chocolate cream cheese muffin.\n", ({TO, TP}));
}
