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
    set_adj(({"dark", "choc", "chocolate", "graham"}));
	set_short("dark chocolate graham cookie");
    set_pshort("dark chocolate graham cookies");
    set_long("This crisp, crunchy graham cracker cookie is lavishly coated "
	+ "in a thick layer of rich dark chocolate.\n");
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
	if (!str || !parse_command(str, ({}), "[dark] [choc] [chocolate] [graham] 'cookie' / 'cookies' "))
	return 0;

    TP->catch_msg("You smell the cookie getting a hint of its "
	+ "dark chocolate graham goodness.\n");
    tell_room(E(TP), QCTNAME(TP)+ " lifts " + HIS(TP) + " dark chocolate "
	+ "graham cookie to " + HIS(TP) + " nose sniffing it "
	+ "for a moment as " + PRONOUN(TP) + " inhales its aroma.\n",
		({TO, TP}));

    return 1;
}

void
special_effect(int n)
{
	write("You bite into your cookie getting a taste of its "
	+ "dark chocolate graham goodness.\n");
	tell_room(E(TP), QCTNAME(TP)+ " bites into " + HIS(TP) + " dark "
	+ "chocolate graham cookie.\n",
		({TO, TP}));
}
