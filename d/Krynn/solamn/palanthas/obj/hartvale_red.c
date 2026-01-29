/* Mortis 12.2005
 */

inherit "/std/drink";

#include "/sys/stdproperties.h"
#include <macros.h>
#include "../local.h"

create_drink()
{
    set_soft_amount(40);
    set_alco_amount(24);
    set_name("wine");
    add_name(({"red", "hartvale", "hartvale red", "glass"}));
	add_pname(({"reds", "hartvales", "hartvale reds", "glasses"}));
    add_adj(({"red", "hartvale", "glass of", "hartvale red"}));
    set_short("glass of Hartvale Red");
    set_pshort("glasses of Hartvale Red");
    set_long("A classic and tasteful glass of bright to dark red wine "
	+ "from the Light Hart cafe in Palanthas.  It is from the Hartvale "
	+ "Vineyard outside of the city.\n");
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 50);
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

    if (str != "wine" && str != "red" && str != "hartvale red"
	    && str != "glass" && str != "hartvale wine")
	return 0;

    TP->catch_msg("The Hartvale Red has a bright yet rich flavour with "
	+ "a hint of black cherry.\n");
    tell_room(E(TP), QCTNAME(TP)+ " lifts " + HIS(TP) + " glass of Hartvale "
	+ "Red to " + HIS(TP) + " nose sniffing it for a moment while swirling "
	+ HIS(TP) + " glass as " + PRONOUN(TP) + " inhales its aroma.\n",
		({TO, TP}));

    return 1;
}

void
special_effect(int numofdrinks)
{
    TP->catch_msg("The Hartvale Red goes down in a pleasant, unassuming "
	+ "way leaving only the slightest aftertaste with a hint of black "
	+ "cherry.\n");
}
