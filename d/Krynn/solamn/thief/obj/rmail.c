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
    add_name("ringmail");
    set_ac(11);
    set_am(({-6, 4, 2}));
    set_at(A_BODY);
    add_adj("ring");
    add_adj("ordinary");
    set_long("An ordinary ring mail, one that a lower dwarf " +
	     "would wear in everyday life.\n");
	set_short("ordinary ringmail");
    add_prop(OBJ_I_VOLUME, 1200);
    add_prop(OBJ_I_WEIGHT, 2000);
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

