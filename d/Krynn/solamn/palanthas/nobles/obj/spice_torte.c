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
    set_name("torte");
	add_name(({"square", "piece"}));
    set_pname("tortes");
	add_pname(({"squares", "pieces"}));
    set_adj(({"spice", "apple", "square", "piece", "piece", "of"}));
	set_short("square piece of spice apple torte");
    set_pshort("square pieces of spice apple torte");
    set_long("This square shaped apple compote sits on a crunchy crust "
	+ "topped with a cranberry-apricot crumble\n");
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
	if (!str || !parse_command(str, ({}), "[square] [piece] [of] [spice] [apple] 'torte' / 'tortes' "))
	return 0;

    TP->catch_msg("You smell the square piece of torte getting a hint of its "
	+ "spicy apple compote and crunchy crust topped with cranberry-apricot "
	+ "crumble.\n");
    tell_room(E(TP), QCTNAME(TP)+ " lifts " + HIS(TP) + " square piece of "
	+ "spice apple torte to " + HIS(TP) + " nose sniffing it "
	+ "for a moment as " + PRONOUN(TP) + " inhales its aroma.\n",
		({TO, TP}));

    return 1;
}

void
special_effect(int n)
{
	write("You bite into your square piece of torte getting a taste of its "
	+ "spicy apple compote and crunchy crust topped with cranberry-apricot "
	+ "crumble.\n");
	tell_room(E(TP), QCTNAME(TP)+ " bites into " + HIS(TP) + " square piece "
	+ "of spice apple torte.\n",
		({TO, TP}));
}
