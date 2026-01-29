inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include <macros.h>

create_weapon()
{
    set_name("battleaxe");
    add_name("axe");
    set_adj("gnomish");
    add_adj("metal");  /* added by Gorboth, July 2007 */

    set_short("gnomish battleaxe");
    set_long("A brutal weapon of mass destruction.  Double edged and made " +
	"with gnomish skill.\nA label has been stamped on it.\n");
    set_wt(W_AXE);
    set_dt(W_BLUDGEON | W_SLASH);
    set_hands(W_BOTH);
    set_hit(20);
    set_pen(22);
}

init()
{
    ::init();
    add_action("do_read", "read");
    add_action("brandish", "brandish");
}

brandish()
{
    if (!query_wielded(TO))
    {
    	write("You have to wield the axe to use the emote!\n");
    	return 1;
    }
    write("You brandish your axe fiercely.\n");
    say(QCTNAME(TP) + " brandishes " + TP->query_possessive() +
	" axe fiercely.\n");
    return 1;
}

read()
{
    return "The label reads: A product of Gnomish Industries.\n" +
    	"This product can: 'brandish'" +
    	"\n";
}

do_read(str)
{
    if (str == "label" || str == "label on battleaxe")
    {
    	write(read());
	return 1;
    }
    notify_fail("Read what?\n");
    return 0;
}
