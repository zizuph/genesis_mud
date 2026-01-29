/* Mortis 09.2005
 */

#pragma save_binary
#pragma strict_types

inherit "/std/food.c";
#include <macros.h>
#include <composite.h>
#include "../local.h"

public void
create_food()
{
    set_amount(60);
    set_name("muffin");
    set_pname("muffins");
    set_adj(({"lemon", "poppy-seed", "poppy", "seed", "poppy seed"}));
	set_short("lemon poppy-seed muffin");
    set_pshort("lemon poppy-seed muffins");
    set_long("A freshly baked and rather large, fluffy, yellow muffin "
	+ "thick with dark, blue-black poppy seeds and topped with a crusty "
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
    NF("Smell what?\n");

    if (!str)
	return 0;

    if (str != "muffin" && str != "lemon muffin" && str != "poppy muffin"
	    && str != "poppy-seed muffin" && str != "lemon poppy-seed muffin")
	return 0;

    TP->catch_msg("The smell of lemon and moist, sweet cake fills your "
	+ "nose, but you also detect a hint of poppies.\n");
    tell_room(E(TP), QCTNAME(TP)+ " lifts " + HIS(TP) + " lemon poppy-seed "
	+ "muffin to " + HIS(TP) + " nose sniffing it "
	+ "for a moment as " + PRONOUN(TP) + " inhales its aroma.\n",
		({TO, TP}));

    return 1;
}

void
special_effect(int n)
{
	write("You crunch through the sugar encrusted muffin top and get "
	+ "a taste of the moist, lemony yellow muffin center with its "
	+ "refined flavour of tiny poppy seeds.\n");
	tell_room(E(TP), QCTNAME(TP)+ " crunches through the sugar encrusted "
	+ "top of " + HIS(TP) + " lemon-poppy seed muffin.\n", ({TO, TP}));
}
