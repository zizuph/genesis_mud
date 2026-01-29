// ARMOUR:  crimson cuirboilli boots
//      DOME_ARMOURS + boots2

    /*  Calia Domain

        HISTORY
        02nov98 Created by Khon.

        PURPOSE
        This is a basic armour template of a pair of
        heavy(for the domers) boots. Worn by those
        expecting serious fighting or those trying for
        the tough heroic look.

        WEAPON HISTORY
        Stock cuirboilli boots with some pizazz.
        Cuirboilli is leather boiled in oil or wax.
        This treatment makes the leather become hard
        as wood. These are lined with soft silk and
        dyed a heroic crimson colour.

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
    set_adj(({"crimson","cuirboilli"}));
    set_short("crimson cuirboilli boots");
    set_pshort("crimson cuirboilli boots"); 
    set_long("A pair of calf high boots made of " +
        "cuirboilli, stiff leather as hard as wood. " +
        "They're a brilliant crimson colour, waxed and " +
        "polished to a brilliant shine. The inside of " +
        "the boot is lined with silk to make it " +
        "comfortable to wear.\n");

// ARMOUR VALUES
    set_ac(

// Armour value
    14,

// Set armour modifiers
    set_am(({

// vs impale damage
    -1,

// vs slash damage
     0,

// vs bludgeon damage
     1
    }));

// Where the armour protects
    set_at(A_FEET);

// PROPERTIES
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(14, A_FEET));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(12)*2);

// Starting Corrosion

// Starting Damage

}
