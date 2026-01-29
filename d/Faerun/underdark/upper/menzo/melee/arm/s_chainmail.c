/*
 *  faerun/underdark/upper/menzo/melee/arm/s_chainmail.c
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
    set_name("chainmail");
    set_adj( "adamantine" );
    set_adj( "dark" );
    set_short("dark adamantine chainmail");
    set_long("This chainmail is constructed of adamantine, " +
             "an alloy of adamantite. Dark flexible metal rings " +
             "are tightly linked together. This gives the chainmail " +
             "a solid, but yet very flexible structure. The colours are " +
             "completely matted, so the metal has no shine to it, " +
             "if fact it looks like the dark scales of a lizard. " +
             "Along the edges of the chainmail, a black leather padding " +
             "has been attached to the chainmail to make it more " +
             "comfortable.\n");
    

    set_ac(28);
    set_at(A_TORSO);

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(28));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(28, A_TORSO));

}

