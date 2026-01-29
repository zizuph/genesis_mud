/*
 * Tom Bombadill's Hat
 * By Finwe, January 2002
 */

inherit "/std/armour";
 
#include "/sys/macros.h"
#include <stdproperties.h>
#include <wa_types.h>
#include "/sys/formulas.h"
 
void
create_armour()
{ 
    set_name("hat");
    set_short("brown hat");
    set_long("This large brown hat has a wide yellow band "+
        "wrapping around it. There is a battered feather stuck in it.\n");
    set_adj(({"large","brown","feathered"}));
    set_ac(20);
    set_at(A_HEAD);
    set_am(({1,-1,0}));
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(20));
    add_prop(OBJ_I_VOLUME,95);
    add_prop(OBJ_I_WEIGHT,250);
}
