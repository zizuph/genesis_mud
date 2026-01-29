/*
 *  Coffee for the Wizards of High Sorcercy
 *  Modified by Kentari from Teth's workroom tea - 96/12/2
 */

inherit "/std/drink";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

public void
create_drink()
{
    set_soft_amount(50);
    set_alco_amount(0);
    set_name("coffee");
    set_adj("huge barrel of");
    set_long("This hot drink has a strong scent, that both refreshes and " +
        "soothes. This is definitely a sipping coffee, for it is much too " +
	"hot to gulp.\n");
    set_short("huge barrel of coffee");
    set_pshort("huge barrels of coffee");
    add_prop(OBJ_I_WEIGHT, 1500);
    add_prop(OBJ_I_VOLUME, 1500);
}

init ()
{
    ::init();
    ADA("sip");
    ADA("gulp");
}

static int sip(string str)
{
    if ((str=="coffee")||(str=="refreshing coffee"))
    {
        write("You sip some of the refreshing hot coffee. It tastes " +
            "marvellous, as if you never tasted anything before until " +
            "now.\n");
        say(QCTNAME(TP)+ " sips some wonderful coffee from the huge "+
	    "barrel, and looks extremely delighted and rejuvenated "+
	    "because of it.\n");
        return 1;
    }
    NF("Sip what?\n");
    return 0;
}

static int gulp(string str)
{
    if ((str=="coffee")||(str=="refreshing coffee"))
    {
	write("As you thirstily down the hot coffee, you " +
		"burn your whole mouth and your chest hurts for a " +
		"few moments. Only a dragon can survive that!\n");
	say(QCTNAME(TP)+ " impressively gulps down the whole " +
		"barrel of coffee.\n");
	return 1;
    }
    NF("Sip what?\n");
    return 0;
}
