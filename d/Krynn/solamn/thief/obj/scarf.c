/* created by Aridor, 03/04/94 */

inherit "/std/armour";
inherit "/lib/keep";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

void
create_armour()
{
    set_name("scarf");
   set_pname("scarves");
    set_short("silk scarf");
    set_pshort("silk scarves");
    set_ac(1);
    set_at(A_NECK);
    add_adj("silk");
    set_long("A silk scarf, very intricately woven.\n");
    set_keep(1);
    add_prop(OBJ_I_VOLUME, 5);
    add_prop(OBJ_I_WEIGHT, 2);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(3));
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

