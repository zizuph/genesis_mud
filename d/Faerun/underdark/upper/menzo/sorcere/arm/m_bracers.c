/*
 *  faerun/underdark/upper/menzo/sorcere/arm/m_bracers.c
 *
 *  A masters bracers in Underdark
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
    set_name("bracers");
    set_adj( "mithril" );
    set_adj( "decorated" );

    set_long("These bracers looks more like thick decorative " +
             "bracelets than armour. They gleam with a mirror-like " +
             "brilliance and intricate decorations of spiderweb " +
             "has been engraved into the metal. There are small " +
             "black spider-shaped onyx stones which has been " +
             "inserted into web decorations on the mithril.\n");
    set_short("decorated mithril bracers");

    set_ac(25);
    set_at(A_ARMS);

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(25));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(25, A_ARMS));

}

