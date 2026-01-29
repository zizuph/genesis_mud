inherit "/std/armour";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

void create_armour()
{
    set_name("pants");
    add_name(({"pair","pair of pants"}));
    add_adj(({"rugged","pair"}));
    set_short("pair of rugged pants");
    set_pshort("pairs of rugged pants");
    set_long("This "+short()+" looks like effective clothing for working long days in the fields.\n");
    set_ac(10);
    set_am( ({ -1, 0, 1}) );
    set_at(A_LEGS | A_WAIST);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(10) - random(5));
    add_prop(OBJ_I_WEIGHT, 1000 + random(500));
    add_prop(OBJ_I_VOLUME, 300 + random(100));
}
