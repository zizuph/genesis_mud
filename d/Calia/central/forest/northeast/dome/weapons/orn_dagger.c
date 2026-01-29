// WEAPON:  Ornamented Rapier
//      DOME_WEAPONS + ornamented_rapier

    /*  Calia Domain

        HISTORY
        19aug99 Created by Khon.

        PURPOSE
        This is an average quality weapon, one barely suitable
        for use by a hedonist. They are produced by the
        apprentice smiths as they struggle to become masters.

        WEAPON HISTORY
        Although only an average weapon, it's still a work of
        art, beautifully and lovingly crafted by a weaponsmith
        who enjoys his craft.

    */

// INCLUSIONS AND DEFINITIONS

inherit "/std/weapon";

#include <formulas.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "/sys/formulas.h"
#include "/sys/macros.h"

// WEAPON DEFINITION
void
create_weapon()
{
    set_name("dagger");
    set_adj("ornamented", "average", "knife", "parrying");
    set_short("ornamented parrying dagger");
    set_pshort("ornamented parrying daggers"); 
    set_long("This is a long, slender dagger designed for " +
        "parrying, although it can also thrust and slash " +
        "quite well. It's a work of art, created by a " +
        "weaponsmith who loved his craft. The blade is " +
        "made of quality steel that has been etched with " +
        "intricate scrollwork, while the hilt is " +
        "carved from a single piece of horn.\n");

// WEAPON VALUES
    set_default_weapon(

// Weapon Hit
    30,

// Weapon Penetration
    13,

// Weapon Type
    W_KNIFE,

// Damage Type
    W_IMPALE | W_SLASH,

// Weapon Handedness
    W_ANYH);

// PROPERTIES
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(30,13));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT));
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(30, 13)*2);

// Starting Corrosion - none
    add_prop(corroded, 0);

// Starting Damage - none
    add_prop(dull, 0);

}

string
query_recover()
{
    return MASTER + ":" + query_wep_recover();
}

void
init_recover(string arg)
{
    init_wep_recover(arg);
}
