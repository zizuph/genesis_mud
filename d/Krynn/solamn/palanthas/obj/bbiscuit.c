/* Mortis 07.2005
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
    set_amount(50);
    set_name("biscuit");
    set_pname("biscuits");
    set_adj("thin");
	set_adj("wheat");
    set_short("thin wheat biscuit");
    set_pshort("thin wheat biscuits");
    set_long("This thin, flaky biscuit has been baked recently and is "
	+ "still warm.  It has a grainy texture from the whole wheat that "
	+ "was used to bake it which adds to it a wheaty smell.\n");
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

    if (str != "biscuit" && str != "thin biscuit" && str != "thin wheat biscuit"
	    && str != "wheat biscuit")
	return 0;

    TP->catch_msg("The smell of warm, moist wheat fills your senses, but "
	+ "there's something else beneath it, a hint of cinnamon you think.\n");
    tell_room(E(TP), QCTNAME(TP)+ " lifts " + HIS(TP) + " thin wheat biscuit "
	+ "to " + HIS(TP) + " nose sniffing it "
	+ "for a moment as " + PRONOUN(TP) + " inhales its aroma.\n",
		({TO, TP}));

    return 1;
}

void
special_effect(int n)
{
    TP->catch_msg("Flaky on the outside, the biscuit is warm and moist "
	+ "with a hearty wheat taste inside.  You detect a hint of cinnamon "
	+ "there as well.\n");
}
