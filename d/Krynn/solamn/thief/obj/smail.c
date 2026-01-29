/* created by Aridor, 03/04/94 */

inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

void
create_armour()
{
    set_name("mail");
    add_name("splintmail");
    set_short("splint mail");
    set_pshort("splint mails");
    set_ac(15);
    set_am(({4,-3,-1}));
    set_at(A_BODY);
    add_adj("splint");
    set_long("An ordinary splint mail. This is the " +
	     "typical armour a normal dwarf would wear in " +
	     "everyday life.\n");
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_WEIGHT, 3000);
}

string
query_recover()
{
    return MASTER + ":" + query_arm_recover();
}

void
init_recover(string arg)
{
    init_arm_recover(arg);
}

