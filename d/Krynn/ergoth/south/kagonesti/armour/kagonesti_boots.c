#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>

inherit "/std/armour";

void create_armour()
{
    set_name("boots", 1);
    add_name("pair");
    set_adj(({"leather", "high"}));
    set_short("pair of leather high boots");
    set_pshort("pairs of leather high boots");
    set_long("These Kagonesti boots are made for life in the wilderness. They "
        + "are stiff and reach high up the leg to protect those traveling "
        + "through dense vegetation, but are thin enough to fit under other "
        + "clothing. The soles have been reinforced, making them both durable "
        + "and comfortable.\n");
    
    set_ac(6);
    set_at(A_FEET);
    set_am(({0, 1, -1}));
    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_I_WEIGHT, 600);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(6));
}
