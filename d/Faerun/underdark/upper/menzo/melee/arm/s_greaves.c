/*
 *  faerun/underdark/upper/menzo/melee/arm/s_greaves.c
 *
 *  A students greaves in Melee-magthere
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
    set_name("greaves");
    set_adj( "adamantine" );
    set_adj( "dark" );
    set_short("dark adamantine greaves");
    set_long("These greaves are made of dark adamantine, " +
             "an alloy of adamantite. They look rather " +
             "comfortable, since they have a soft black " +
             "leather padding underneath the metal. " +
             "The metal is dark and has been matted by daily use.\n");
    

    set_ac(20);
    set_at(A_LEGS);

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(20));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(20, A_LEGS));

}
