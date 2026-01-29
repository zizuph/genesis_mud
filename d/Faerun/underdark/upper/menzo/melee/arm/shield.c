/*
 *  faerun/underdark/upper/menzo/melee/arm/shield.c
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

    set_name("shield");
    set_adj( "mithril" );
    set_adj( "ornamented" );
    set_short("ornamented mithril shield");
    set_long("This is quite an unusual shield for being in drow possesion, " +
             "since it seems to be of typical duargar origin. " +
             "It must have been taken during on of the drow raids on " +
             "the duargar.\n");

    set_ac(15);
    set_at(A_SHIELD);

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(15));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(15, A_SHIELD));

}