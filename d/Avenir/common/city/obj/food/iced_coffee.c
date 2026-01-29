#pragma strict types
// file name:	/d/Avenir/common/city/obj/food/iced_coffee.c
// creator(s): 
// notes(s):
// 	Based on: /d/Avenir/common/bazaar/museum/obj/coffee.c
// last update:
//	Lucius May 2009: Some cleanups, added sobriety enhancement.
//
inherit "/std/drink";
inherit "/d/Avenir/common/lib/sober";

#include <macros.h>
#include <stdproperties.h>

public void
create_drink(void)
{
    set_name("kahve");
    add_name(({"coffee", "ikahve"}));
    set_adj(({"sybarun", "iced"}));
    set_short("iced sybarun kahve");
    set_pshort("iced sybarun kahves");
    set_long("This dark, aromatic kahve has been poured over ice "+
         "and topped with a dollop of thick cream. It can be "+
         "swallowed quickly, or savoured slowly, as you wish.\n");

    set_soft_amount(250);
    set_alco_amount(0);
    set_drink_msg("Mmmm... The slightly bitter coffee is surprisingly "+
        "refreshing when served cold.\n");

    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop("_drink_created", time());
}

public int 
do_sip(string str)
{
    if (str != "kahve" && str != "coffee") {
        return notify_fail("Sip what?\n");
    }

    write("You close your eyes and sigh as the delightfully "+
	"cool kahve slides across your tongue, leaving "+
	"a refreshingly bitter taste on your palate.\n");
    say(QCTNAME(this_player()) +" seems very pleased with "+
	this_player()->query_possessive() +" iced sybarun kahve.\n");

    return 1;
}

public void
special_effect(int num)
{
    set_alarm(0.0, 0.0, &make_sober(this_player(), 0));
}

public void
init(void)
{
    ::init();

    add_action(do_sip, "savour");
    add_action(do_sip, "savor");
}
