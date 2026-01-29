inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

void
create_armour()
{
    set_name("leggings");
    set_default_armour(20, A_LEGS, ({ 5, -3, -2 }));
    add_adj("sturdy");
    set_short("pair of sturdy leggings");
    set_pshort("pairs of sturdy leggings");
    set_long("A pair of sturdy leggings, they are made of iron.\n");
    add_prop(OBJ_I_VOLUME, 450);
}

