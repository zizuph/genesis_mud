// ARMOUR:  padded silk boots
//      DOME_ARMOURS + boots1

    /*  Calia Domain

        HISTORY
        02nov98 Created by Khon.

        PURPOSE
        This is a basic armour template of a pair of
        padded silk and leather boots.

        WEAPON HISTORY
        Stock padded silk and leather boots.

    */

// INCLUSIONS AND DEFINITIONS

inherit "/std/armour";

#include <formulas.h>
#include <stdproperties.h>
#include <wa_types.h>
#include "/sys/formulas.h"
#include "/sys/macros.h"

// WEAPON DEFINITION
void
create_armour()
{
    set_name(({"boots", "armour", "armor"}));
    set_adj(({"silk","padded"}));
    set_short("padded silk boots");
    set_pshort("padded silk boots"); 
    set_long("A pair of calf high boots made of the " +
        "finest supple leather, then reinforced with " +
        "lightweight but very strong layers of silk. " +
        "They're extremely light and comfortable, " +
        "black and grey in colour.\n");

// ARMOUR VALUES
    set_ac(

// Armour value
    12,

// Set armour modifiers
    set_am(({

// vs impale damage
    -1,

// vs slash damage
    -1,

// vs bludgeon damage
     2
    }));

// Where the armour protects
    set_at(A_FEET);

// PROPERTIES
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(12, A_FEET)/2);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(12)*5);

// Starting Corrosion

// Starting Damage

}
