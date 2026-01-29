inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

void create_armour()
{
    set_name("skirt");
    add_adj(({"patched","cotton"}));
    set_short("patched cotton skirt");
    set_pshort("patched cotton skirts");
    set_long("This "+short()+" is not fancy, but very practical and durable.\n");
    set_ac(5);
    set_am( ({ 0, 0, 0}) );
    set_at(A_LEGS | A_WAIST);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(5) - random(2));
    add_prop(OBJ_I_WEIGHT, 900 + random(400));
    add_prop(OBJ_I_VOLUME, 500 + random(100));
}
