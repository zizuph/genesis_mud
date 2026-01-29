/* Mortis 12.2005
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
    set_amount(120);
    set_name("risotto");
	add_name(({"bowl", "rice"}));
    set_pname(({"risotto", "bowls", "rices"}));
    add_adj(({"risotto", "bowl of"}));
    set_short("bowl of risotto");
    set_pshort("bowls of risotto");
    set_long("Risotto is made from arborio rice imported from the south.  "
	+ "Though appearing like flat rice, it has the consistency and flavour "
	+ "of a rich pasta.  This risotto has a perfect firm but not dry "
	+ "consistency and is served in a light and creamy parmesan sauce.\n");
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

    if (str != "bowl" && str != "bowl of risotto" && str != "risotto")
	return 0;

    TP->catch_msg("The risotto has a light and creamy smell of parmesan and "
	+ "the fruity hint of the white wine in which it was cooked.\n");
    tell_room(E(TP), QCTNAME(TP)+ " lifts " + HIS(TP) + " bowl of risotto "
	+ "to " + HIS(TP) + " nose sniffing it "
	+ "for a moment as " + PRONOUN(TP) + " inhales its aroma.\n",
		({TO, TP}));

    return 1;
}

void
special_effect(int n)
{
    TP->catch_msg("As you taste your first spoonful of the rice you are "
	+ "reminded of pasta but quickly pass that thought by as you catch the "
	+ "fruity hints of the white wine in which it was cooked and the fresh "
	+ "parmesan in its light and creamy sauce.\n");
}
