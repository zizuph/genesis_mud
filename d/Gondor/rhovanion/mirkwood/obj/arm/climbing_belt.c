/*
 * Belt in Mirkwood
 * Varian - June 2015
 */

#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include "../../defs.h"

inherit MIRKWOOD_OBJ_DIR + "arm/magical_armour";

void
create_magical_armour()
{
    set_name("belt");
    set_pname("belts");
    set_short("worn, leather belt");
    set_long("This is an old, worn belt which has certainly seen better " +
        "days. However, not only is the belt still functional, it has a " +
        "pouch attached to the side where you could perhaps store a few " +
        "coins. \n");
            
    add_adj("worn");
    add_adj("leather");
    
    set_at(A_WAIST);
    set_ac(1);
    set_am(({ 2, 2, -2 }));
    
    add_prop(OBJ_I_VALUE, 300);
    add_prop(OBJ_I_VOLUME, 4000);
    add_prop(OBJ_I_WEIGHT, 2000);
    
    setuid();
    seteuid(getuid());

    object effect = clone_object(MIRKWOOD_OBJ_DIR + "effects/skill_bonus_climb");
    effect->set_average_range(50, 70);
    effect->set_level(1);
    
    set_effect(effect);    
}
