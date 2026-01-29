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
    add_name("platemail");
    set_ac(22);
    set_am(({8,-5,-3}));
    set_at(A_BODY);
    add_adj("plate");
    add_adj("ordinary");
    set_long("An ordinary splint mail. This is the " +
	     "typical armour a higher dwarf would wear in " +
	     "everyday life.\n");
	set_short("ordinary platemail");
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_WEIGHT, 6000);
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

