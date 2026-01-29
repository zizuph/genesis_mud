/*
 * Orc mail - Sarn Ford
 * Varian - February 2015
 */

inherit "/std/armour";

#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>

void
create_armour()
{
    set_name("cloak");
    set_pname("cloaks");
    set_short("heavy, canvas cloak");
    set_long("This heavy, canvas cloak looks like it could help protect you " +
        "in combat. The cloak seems to be covered in scratches and cuts, with " +
        "the occasional rip for good measure, but you still think that it " +
        "could be useful.\n");
    	    
    add_adj("heavy");
    add_adj("canvas");
    
    set_at(A_ROBE);
    set_ac(10);
    set_am(({ 0, 0, 0 }));
    
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(10));
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, 2000);
    
}
