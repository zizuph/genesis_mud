/* Taken from the Rivendell Elven bow for sale in Rivendell
 * Tomas, Dec 2017
 */

#include "/d/Shire/sys/defs.h"  
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>


inherit "/std/bow";

#define HIT 35
#define PEN 40


public void
create_bow()
{
    FIXEUID;
    add_name("bow");
    set_adj(({"white", "ash"}));
    set_short("hornbeam bow");
    set_long("This " + short() + " was made from a single white ash stave. @@check_string@@\n");

    add_prop(OBJ_I_WEIGHT, 1400);
    add_prop(OBJ_I_VOLUME, 4250);
    set_hit(HIT);
    set_pen(PEN);
    stringed = 0;
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT, PEN) + random(20) -10);

    add_item(({"white","ash"}),
        "A simple white ash bow constructed from the white ash tree.\n");
    add_item(({"limbs"}),
        "The limbs are the top and bottom ends of the bow and @@check_limbs@@\n");
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
       return "curve inwards from the string stretched between them.\n";
}
