/* Leather armour for smaller kargs of Gont */

#pragma strict_types

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>

public void
create_armour()
{
    set_name("armour");
    set_pname("armours");
    set_adj("leather");
    set_short("leather armour");
    set_pshort("leather armours");
    set_long("An armour covering the chest and shoulders "+
        "that is made from leather hardened by boiling in oil. It is "+
        "shaped to the pectoral muscles of the chest and bears "+
        "a brand of Karego-At.\n");
    set_default_armour(20, A_TORSO, ({-1, 0, -1}));
    add_prop(OBJ_I_WEIGHT, 4000);
    add_prop(OBJ_I_VOLUME, 800);
    add_prop(OBJ_I_VALUE, 295 + random(50));    
}
