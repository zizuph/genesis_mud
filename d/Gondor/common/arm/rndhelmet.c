/* Helmet */
inherit "/std/armour";

#include <formulas.h>
#include <stdproperties.h>
#include <wa_types.h>

public void
create_armour()
{
    set_name(({"helmet","cuttinghelmet","cutting helmet"}));
    set_pname("helmets");
    set_short("pointy helmet");
    set_adj("pointy");
    set_pshort("pointy helmets");
    set_long("This is a very pointy helmet, or if you prefer, it has a\n"
           + "cutting edge. On the top of the helmet is tufted.\n");
    set_default_armour(9,A_HEAD,({ 3, 2, 5 }),0);
    add_prop(OBJ_I_WEIGHT,3560);
    add_prop(OBJ_I_VOLUME,736);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(9)+random(200)-100);
}

