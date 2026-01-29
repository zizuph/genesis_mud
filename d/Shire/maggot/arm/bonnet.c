inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

void create_armour()
{
    set_name("bonnet");
    add_adj(({"white","cotton"}));
    set_short("white cotton bonnet");
    set_pshort("white cotton bonnets");
    set_long("This bonnet is made from plain white cotton.\n");
    set_ac(5);
    set_am( ({ 0, 0, 0}) );
    set_at(A_HEAD);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(5) - random(2));
    add_prop(OBJ_I_WEIGHT, 100 + random(50));
    add_prop(OBJ_I_VOLUME, 100 + random(20));
}
