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
    set_name("collar");
    set_pname("collars");
    set_short("metal collar");
   set_pshort("metal collars");
    set_ac(8);
    set_at(A_NECK);
    add_adj("metal");
    set_long("A metal collar, you can wear it around your neck.\n");
    set_keep(1);
    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(8));
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

