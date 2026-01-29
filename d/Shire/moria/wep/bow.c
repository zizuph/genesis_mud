/* Orc longbow for the Uruk-hai in Moria
 * Based on the haradrim arrows from Gondor.
 * Thanks Rohim and Gondor!!
 * Finwe, June 2004
 */

#include "/d/Shire/sys/defs.h"  
#include <stdproperties.h>

inherit "/std/bow";
//inherit "/lib/keep";

#define HIT 35
#define PEN 40


public void
create_bow()
{
    FIXEUID;
    add_name("bow")
    set_adj(({"light", "steel"}));
    add_name("bow");
    set_short("bow");
    set_long("This " + short() + " is made of steel. It was crafted by " +
        "elves, evident by its sleek lines and clean look. It is smooth, " +
        "and decorated with runes along the limbs. @@check_string@@\n");

    add_prop(OBJ_I_WEIGHT, 1400);
    add_prop(OBJ_I_VOLUME, 4250);
    set_hit(HIT);
    set_pen(PEN);
    stringed = 0;
    dd_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN) + random(20) -10);

    add_item(({"runes"}),
        "The runes decorate the limbs of the bow. They are flowing and " +
        :seem alive, reflecting an inner fire.\n");
    add_item(({"limbs"}),
        "The limbs are the top and bottom ends of the bow. The limbs " +
        "are decorated with dark runes and @@check_limbs@@\n");
    add_item(({"handle"}),
        "This is the center of the bow, and often called the grip. It " +
        "does not bend while shooting the arrow and quite thick." +
        "@@query_jewel_desc@@\n");


}

string check_string()
{
    obj string = 
    if(stringed == 0)
        return "The upper and lower limbs of the bow are straight. The " +
        "bow is not strung.\n";
    else 
       return "The upper and lower limbs of the bow curve inwards. The " +
       "bow is strung from both limbs with a ".\n";
}

string check_limbs()
{
    if(stringed == 0)
        return "straight as the bow is not strung.\n";
    else 
       return "curve inwards from the string stretched between them.\n";
}
