/*
 *  faerun/underdark/upper/menzo/melee/arm/s_mask.c
 *
 *  Face mask in Melee-magthere
 *
 *  Created by Midnight, 15-4-2004
 */

#include <formulas.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "defs.h"

inherit P_MENZO_MELEE + "std/base_armour";

/*
 * Function name: create_melee_armour
 * Description  : Construct a armour for the Sorcere part of Menzoberranzan
 */
void create_melee_armour()
{
    set_name("mask");
    set_adj( "black" );
    set_adj( "leather" );
    set_short("black leather mask");
    set_long("This face mask is made of leather, which " +
             "has been treated to a hardness resembling wood." +
             "It has been treated with dark tree oils, which " +
             "has coloured the hardened leather to a deep black " +
             "colour. The mask is secured in the back with braided " +
             "black leather bands.\n");
    

    set_ac(10);
    set_at(A_HEAD);

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(10));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(10, A_HEAD));

}