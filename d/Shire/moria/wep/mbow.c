/* Mithril bow for trolls in moria
 * Finwe, July 2004
 */

#include "/d/Shire/sys/defs.h"  
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>


inherit "/std/bow";
//inherit "/lib/keep";

#define HIT 50
#define PEN 60


public void
create_bow()
{
    FIXEUID;
    add_name("bow");
    set_adj(({"light", "mithril"}));
    add_name("bow");
    set_short("bow");
    set_long("This " + short() + " was forged by the dwarves of Dwarrowdelf. " +
        "It is smooth and lightweight, and unadorned. A thick handle is set " +
        "in the center of the bow, between both limbs. @@check_string@@\n");

    add_prop(OBJ_I_WEIGHT, 1200);
    add_prop(OBJ_I_VOLUME, 4250);
    set_hit(HIT);
    set_pen(PEN);
    stringed = 0;
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN) + random(20) -10);

    add_item(({"limbs", "top limb", "bottom limb", "upper limb", "lower limb"}),
        "The limbs are the top and bottom ends of the bow. They are thicker " +
        "to absorb vibrations when the bow is shot. @@check_limbs@@\n");
    add_item(({"handle"}),
        "This is the center of the bow, and often called the grip. It " +
        "does not bend while shooting the arrow and quite thick.\n");

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

string check_limbs()
{
    if(stringed == 0)
        return "straight as the bow is not strung.\n";
    else 
       return "curve inwards from the bowstring stretched between them.\n";
}
