/* A ringmail for the kargs at Gont */

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>

public void
create_armour()
{
    set_name("ringmail");
    set_pname("ringmails");
    set_adj("bronze");
    set_short("bronze ringmail");
    set_pshort("bronze ringmails");
    set_long("A ringmail made from hard leather "+
        "tightly sewn with rings of bronze. It is made to cover "+
        "the chest and shoulders, and bears an insignia of "+
        "Karego-At over the breast bone.\n");
    set_default_armour(30, A_TORSO, ({-1, 2, -1}));
    add_prop(OBJ_I_WEIGHT, 6000);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, 530 + random(100));  
}
