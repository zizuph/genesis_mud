// WEAPON:  Duelling Dagger
//      DOME_WEAPONS + duel_dagger

    /*  Calia Domain

        HISTORY
        19aug99 Created by Khon.

        PURPOSE
        This is a weapon of the highest quality, one prized
        by a hedonist. They are only rarely produced by the
        most skilled of weaponsmiths.

        WEAPON HISTORY
        The highest quality weapon, it's elegantly simple,
        beautifully and lovingly crafted by a master
        weaponsmith who enjoys his craft.

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
    set_adj("duelling", "steel", "superb", "parrying", "knife");
    set_short("duelling dagger");
    set_pshort("duelling daggers"); 
    set_long("This is a long, slender dagger designed for " +
        "parrying, although it's quite capable of thrusting " +
        "and slashing. It's an elegantly simple blade in " +
        "design, obviously created by a weaponsmith who " +
        "loved his craft. " +
        "Perfectly balanced, it allows for accurate and " +
        "swift parries. The blade is made of quality steel " +
        "honed to a razor edge, while the hilt is carved " +
        "from a single piece of horn.\n");

// WEAPON VALUES
    set_default_weapon(

// Weapon Hit
    40,

// Weapon Penetration
    15,

// Weapon Type
    W_KNIFE,

// Damage Type
    W_IMPALE | W_SLASH,

// Weapon Handedness
    W_ANYH);

// PROPERTIES
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(40,15));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT));
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(40, 15)*2);

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
