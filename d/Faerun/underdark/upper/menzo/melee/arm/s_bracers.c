/*
 *  faerun/underdark/upper/menzo/melee/arm/s_bracers.c
 *
 *  A students chainmail in Underdark
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
 * Description  : Construct a armour for the Melee-magthere
 */
void create_melee_armour()
{
    set_name("bracers");
    set_adj( "adamantine" );
    set_adj( "dark" );
    set_short("dark adamantine bracers");
    set_long("These bracers are constructed of adamantine, " +
             "an alloy of adamantite. The solid metal is  " +
             "perfectly crafted to provide protection for " +
             "the arms. The colour is " +
             "completely matted, so the metal has no shine to it. " +
             "Along the edges, a black leather padding " +
             "has been attached to the bracers to make them more " +
             "comfortable to wear.\n");
    


    set_ac(20);
    set_at(A_ARMS);

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(20));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(20, A_ARMS));

}
