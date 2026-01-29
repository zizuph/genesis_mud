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
    set_name("cookie");
    set_pname("cookies");
    set_adj(({"oatmeal", "raisin"}));
	set_short("oatmeal raisin cookie");
    set_pshort("oatmeal raisin cookies");
    set_long("This large, round cookie combines the goodness of oatmeal with "
	+ "lots of plump raisins and spices and baked to perfection.\n");
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
	if (!str || !parse_command(str, ({}), "[oatmeal] [raisin] 'cookie' / 'cookies' "))
	return 0;

    TP->catch_msg("You smell the cookie getting a hint of its "
	+ "plump raisins and spices.\n");
    tell_room(E(TP), QCTNAME(TP)+ " lifts " + HIS(TP) + " oatmeal raisin "
	+ "cookie to " + HIS(TP) + " nose sniffing it "
	+ "for a moment as " + PRONOUN(TP) + " inhales its aroma.\n",
		({TO, TP}));

    return 1;
}

void
special_effect(int n)
{
	write("You bite into your cookie getting a taste of its "
	+ "plump raisins, spices, and chewy oatmeal center.\n");
	tell_room(E(TP), QCTNAME(TP)+ " bites into " + HIS(TP) + " oatmeal "
	+ "raisin cookie.\n",
		({TO, TP}));
}
