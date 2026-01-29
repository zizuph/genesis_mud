/*
 *  faerun/underdark/upper/menzo/sorcere/arm/chainmail.c
 *
 *  A masters chainmail in Underdark
 *
 *  Created by Midnight, 25-2-2004
 */

#include <formulas.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "defs.h"

inherit P_MENZO_SORCERE + "std/base_armour";

/*
 * Function name: create_sorcere_armour
 * Description  : Construct a armour for the Sorcere part of Menzoberranzan
 */
void create_sorcere_armour()
{
    set_name("chainmail");
    set_adj( "crimson" );
    set_adj( "leather-lined" );

    set_long("This chainmail is made out of small and thin mithril " +
             "rings, which shifts between red and black, and they " +
             "are tightly linked together. This gives the chainmail " +
             "a crimson coloured appearance. The colours are " +
             "completely matted, so the metal has no shine to it, " +
             "if fact it looks like scales covered in dried blood. " +
             "Along the edges of the chainmail, a black leather padding " +
             "has been attached to the chainmail to make it more " +
             "comfortable.\n");
    set_short("leather-lined crimson chainmail");

    set_ac(35);
    set_at(A_TORSO);

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(35));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(35, A_TORSO));

}

