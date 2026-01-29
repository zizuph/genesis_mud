inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

void create_armour()
{
    set_name("greaves");
    add_adj(({"red-stained","platemail"}));
    set_short("red-stained platemail greaves");
    set_long("Scary greaves.\n");
    set_ac(10);
    set_am( ({ -1, 0, 1}) );
    set_at(A_LEGS);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(10) - random(5));
    add_prop(OBJ_I_WEIGHT, 1000 + random(500));
    add_prop(OBJ_I_VOLUME, 300 + random(100));
}
