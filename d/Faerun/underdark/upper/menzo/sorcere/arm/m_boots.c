/*
 *  faerun/underdark/upper/menzo/sorcere/arm/m_boots.c
 *
 *  Sorcere master boots in Underdark
 *
 *  Created by Midnight, 21-2-2004
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
    set_name("boots");
    set_adj( "decorated" );
    set_adj( "snake-skin" );
    set_long("These boots are made of glistening dark snakeskin, " +
             "and they feel cold to the touch and the material " +
             "moves lightly under the stroke of your hand, just " +
             "a living snake. The material is much like leather, " +
             "very supple and formfitting. A thin silvery chain " +
             "with small rubies twists around the snakeskin.\n");
    set_short("decorated snake-skin boots");

    set_ac(15);
    set_at(A_FEET);

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(15));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(15, A_FEET));

}