/*
 * Varian - February 5 2016
 */

inherit "/std/armour";

#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>

void
create_armour()
{
    set_name("shield");
    set_short("painted wooden shield");
    set_adj(({"painted", "wooden", }));
    set_long("You notice the image of a howling wolf, covered in flames, " +
        "painted on the face of this wooden shield.\n");
    	        
    set_at(A_SHIELD);
    set_ac(34);
    set_am(({ 0, 0, 0 }));
    
    add_prop(OBJ_I_VOLUME, 600);
    add_prop(OBJ_I_WEIGHT, 3000);
    
}
