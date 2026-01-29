/*
 *  faerun/underdark/upper/menzo/melee/arm/ss_boots.c
 *
 *  Snakeskin boots in Underdark
 *
 *  Created by Midnight, 21-2-2004
 */

#include <formulas.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "defs.h"

inherit P_MENZO_MELEE + "std/base_armour";

/*
 * Function name: create_melee_armour
 * Description  : Construct a armour for the Melee-magthere
 */
void create_melee_armour()
{
    set_name("boots");
    set_adj( "scaled" );
    set_adj( "snake-skin" );
    set_short("pair of scaled snake-skin boots");
    set_long("These boots are made of glistening dark snakeskin, " +
             "and they feel cold to the touch and the material " +
             "moves lightly under the stroke of your hand, just " +
             "a living snake. The material is much like leather, " +
             "very supple and formfitting.\n");
    

    set_ac(10);
    set_at(A_FEET);

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(10));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(10, A_FEET));

}