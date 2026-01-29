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
    set_name("scone");
    set_pname("scones");
    set_adj(({"apricot", "currant"}));
	set_short("apricot currant scone");
    set_pshort("apricot currant scones");
    set_long("This dense, rich scone features the winning combination of "
	+ "sweet apricots and tart currants. Rich and buttery, these scones are "
	+ "a perfect alternative to the usual breakfast fare.\n");
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
	if (!str || !parse_command(str, ({}), "[apricot] [currant] 'scone' / 'scones' "))
	return 0;

    TP->catch_msg("You smell the buttery scone getting a hint of its "
	+ "apricots and currants.\n");
    tell_room(E(TP), QCTNAME(TP)+ " lifts " + HIS(TP) + " apricot currant "
	+ "cone to " + HIS(TP) + " nose sniffing it "
	+ "for a moment as " + PRONOUN(TP) + " inhales its aroma.\n",
		({TO, TP}));

    return 1;
}

void
special_effect(int n)
{
	write("You crunch into an apricot currant scone getting a taste of its "
	+ "tartly sweet apricots and currants.\n");
	tell_room(E(TP), QCTNAME(TP)+ " crunches into " + HIS(TP) + " apricot "
	+ "currant scone.\n", ({TO, TP}));
}
