// WEAPON:  Splended Dagger
//      DOME_WEAPONS + splen_dagger

    /*  Calia Domain

        HISTORY
        19aug99 Created by Khon.

        PURPOSE
        This is a weapon of good quality, one normally worn
        by a hedonist. They are the average weapon produced
        by weaponsmiths.

        WEAPON HISTORY
        A step above an average weapon, it's a work of art,
        beautifully and lovingly crafted by a weaponsmith
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
    set_adj("splendid", "steel", "good", "parrying", "knife");
    set_short("splendid parrying dagger");
    set_pshort("splendid parrying daggers"); 
    set_long("This is a long, slender dagger designed for " +
        "parrying, although it's quite capable of thrusting " +
        "and slashing. This splendid blade was " +
        "created by a weaponsmith who loved his craft. " +
        "Superbly balanced, it allows for accurate and " +
        "swift parries. The blade is made of quality steel " +
        "that has been etched with " +
        "intricate scrollwork, while the hilt is carved " +
        "from a single piece of horn.\n");

// WEAPON VALUES
    set_default_weapon(

// Weapon Hit
    35,

// Weapon Penetration
    14,

// Weapon Type
    W_KNIFE,

// Damage Type
    W_IMPALE | W_SLASH,

// Weapon Handedness
    W_ANYH);

// PROPERTIES
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(35,14));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT));
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(35, 14)*2);

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
