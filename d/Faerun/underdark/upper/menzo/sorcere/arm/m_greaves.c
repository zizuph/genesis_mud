/*
 *  faerun/underdark/upper/menzo/sorcere/arm/m_greaves.c
 *
 *  A masters greaves in Underdark
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
    set_name("greaves");
    set_adj( "mithril" );
    set_adj( "leather-padded" );

    set_long("These greaves are made of mithril and they look " +
             "rather comfortable, since they have a soft black " +
             "leather padding underneath the metal. " +
             "The mithril gleams with almost a mirror-like " +
             "brilliance and must have been newly polished by " +
             "some snirfneblin slaves.\n");
    set_short("leather-padded mithril greaves");

    set_ac(25);
    set_at(A_LEGS);

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(25));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(25, A_LEGS));

}

