/*
 *  faerun/underdark/upper/menzo/sorcere/obj/example_armour.c
 *
 *  This is a sample armour, doesnt do much
 *
 *  Created by Wully, 12-2-2004
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
    set_name("platemail");
    set_adj( "grey" );
    set_long("It's an grey platemail.\n");
    set_short("grey platemail");

    set_ac(20);
    set_at(A_BODY);

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(20));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(20, A_BODY));
}