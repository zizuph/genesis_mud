/*
 *  Tea for the Wizards of High Sorcercy
 *  Modified by Kentari from Teth's workroom tea - 96/12/2
 */

inherit "/std/drink";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

public void
create_drink()
{
    set_soft_amount(2);
    set_alco_amount(0);
    set_name("tea");
    set_adj("soothing");
    set_long("This hot drink has a cloying scent, that both refreshes and " +
        "soothes. This is definitely a sipping tea, for it is much to hot " +
	"to gulp.\n");
    set_short("soothing tea");
    set_pshort("soothing teas");
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200);
}

init ()
{
    ::init();
    ADA("sip");
    ADA("gulp");
}

static int sip(string str)
{
    if ((str=="tea")||(str=="soothing tea"))
    {
        write("You sip some of the soothing hot tea. It tastes " +
            "marvellous, as though you have never known how good " +
            "tea could taste.\n");
        say(QCTNAME(TP)+ " sips some delicious tea, and looks " +
            "extremely delighted and relaxed because of it.\n");
        return 1;
    }
    NF("Sip what?\n");
    return 0;
}

static int gulp(string str)
{
    if ((str=="tea")||(str=="soothing tea"))
    {
	write("As you foolishly try to gulp down the hot tea, you " +
		"burn your whole mouth and your chest hurts for a " +
		"few moments.  What's the rush anyway?\n");
	say(QCTNAME(TP)+ " foolishly tries to gulp down the hot tea " +
		"and gets burned because of it.\n");
	return 1;
    }
    NF("Sip what?\n");
    return 0;
}
