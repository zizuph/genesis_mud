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
    set_adj("black");
    add_name("longbow");
    set_short("black longbow");
    set_long("This longbow is crudely carved of wood. It was made by " +
        "orcs but still looks deadly and is painted black. The upper " +
        "and lower limb of the bow curve inwards. @@check_string@@\n");

    add_prop(OBJ_I_WEIGHT, 1400);
    add_prop(OBJ_I_VOLUME, 4250);
    set_hit(41);
    set_pen(49);
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
