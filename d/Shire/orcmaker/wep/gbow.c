/* Orc longbow for the Uruk-hai in Moria
 * Based on the haradrim arrows from Gondor.
 * Thanks Rohim and Gondor!!
 * Finwe, June 2004
 */

#include "/d/Shire/sys/defs.h"  
#include <stdproperties.h>

inherit "/std/bow";
//inherit "/lib/keep";

public void
create_bow()
{
    FIXEUID;
    
    add_name("orcbow");
    set_adj("wooden");
    set_short("wooden bow");
    set_long("This wooden bow is sturdy and made from a piece of strong " +
        "wood. It is a favored weapon of bigger orcs and looks able to " +
        "kill many foes. @@check_string@@\n");

    add_prop(OBJ_I_WEIGHT, 1400);
    add_prop(OBJ_I_VOLUME, 4250);
    set_hit(25);
    set_pen(35);
    stringed = 0;

}

string check_string()
{
    if(stringed == 0)
        return "The upper and lower limbs of the bow are straight. The " +
        "bow is not strung.\n";
    else 
       return "The upper and lower limbs of the bow curve inwards. The " +
       "bow is strung from both limbs with a string.\n";
}
