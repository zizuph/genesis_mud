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
    set_name("ruff");
    set_pname("ruffs");
    set_ac(5);
    set_at(A_NECK);
    add_adj("leather");
    set_short("leather ruff");
    set_pshort("leather ruffs");
    set_long("A leather ruff, you can wear it around your neck.\n");
    set_keep(1);
    add_prop(OBJ_I_VOLUME, 40);
    add_prop(OBJ_I_WEIGHT, 15);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(5));
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

