/* 
 * Palanthas food by Mortis 09.2005
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
    set_amount(70);
    set_name("toast");
	add_name(({"slice", "aniseed"}));
    set_pname(({"toasts", "slices", "aniseeds"}));
	set_adj("aniseed");
    set_short("slice of aniseed toast");
    set_pshort("slices of aniseed toast");
    set_long("A dry slice of aniseed toast from a low, wide loaf only an "
	+ "inch high in its middle.  Though baked recently, its outside has "
	+ "dried and firmed.  It has a bright, spicy smell like licorice.\n");
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

    if (str != "toast" && str != "aniseed toast" && str != "aniseed"
		&& str != "slice")
	return 0;

    TP->catch_msg("The smell of aniseed in the firm slice of bread reminds "
	+ "you of licorice.  It is fresh and toasty.\n");
    tell_room(E(TP), QCTNAME(TP)+ " lifts " + HIS(TP) + " slice of aniseed "
	+ "toast to " + HIS(TP) + " nose sniffing it "
	+ "for a moment as " + PRONOUN(TP) + " inhales its aroma.\n",
		({TO, TP}));

    return 1;
}

void
special_effect(int n)
{
    TP->catch_msg("The herbal taste of aniseed gives the toast a unique "
	+ "and warm flavour reminiscent of licorice.  It would go well with a "
	+ "hot drink.\n");
}
