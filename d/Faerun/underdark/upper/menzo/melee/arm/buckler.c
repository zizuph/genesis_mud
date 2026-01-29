/*
 *  faerun/underdark/upper/menzo/melee/arm/buckler.c
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

    set_name("buckler");
    add_name("shield");
    set_adj( "black" );
    set_adj( "adamantine" );
    set_short("black adamantine buckler");
    set_long("A common drow-crafted buckler made of solid adamantine, " +
             "the dark metal has been molded to a perfect circular shape. " +
             "A large crimson spider covers the front of the buckler in " +
             "a decorative manner.\n");

    set_ac(15);
    set_at(A_SHIELD);

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(15));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(15, A_SHIELD));

}