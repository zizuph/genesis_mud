/*
 *  faerun/underdark/upper/menzo/melee/arm/m_bracers.c
 *
 *  A masters bracers in Underdark
 *
 *  Created by Midnight, 16-4-2004
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
    set_adj( "decorated" );

    set_long("These bracers are constructed of adamantine, " +
             "an alloy of adamantite. The solid metal is  " +
             "perfectly crafted to provide protection for " +
             "the arms. The colour is " +
             "completely matted, so the metal has no shine to it. " +
             "Exquisite decorations of spiderwebs has been " +
             "crafted with great precision into the dark metal. "+
             "Along the edges, a black leather padding " +
             "has been attached to the bracers to make them more " +
             "comfortable to wear.\n");
    set_short("decorated adamantine bracers");


    set_ac(30);
    set_at(A_ARMS);

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(30));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(30, A_ARMS));

}
