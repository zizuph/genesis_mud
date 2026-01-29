/*
 *  faerun/underdark/upper/menzo/melee/arm/m_greaves.c
 *
 *  A masters greaves in Melee-magthere
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
 * Description  : Construct a armour for the Sorcere part of Menzoberranzan
 */
void create_melee_armour()
{
    set_name("greaves");
    set_adj( "adamantine" );
    set_adj( "decorated" );

    set_long("These greaves are made of dark adamantine, " +
             "an alloy of adamantite. They look rather " +
             "comfortable, since they have a soft black " +
             "leather padding underneath the metal. " +
             "Exquisite decorations of spiderwebs has been " +
             "crafted with great precision into the dark metal. "+
             "The metal is dark and has been matted by daily use.\n");
    set_short("decorated adamantine greaves");

    set_ac(30);
    set_at(A_LEGS);

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(30));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(30, A_LEGS));

}