/*
 *  faerun/underdark/upper/menzo/sorcere/arm/s_circlet.c
 *
 *  Mithril circlet in Underdark
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
    set_name("circlet");
    set_adj( "braided" );
    set_adj( "mithril" );
    set_long("This exquisite circlet is made out of several " +
             "interwoven thick mithril threads. Small decorative " +
             "mithril spiders are attached around the circlet. " +
             "Very thin threads of mithril has been spun into " +
             "a spiderweb, which hangs from the sides of the circlet " +
             "and down around the back.\n");
    set_short("braided mithril circlet");

    set_ac(10);
    set_at(A_HEAD);

    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(10));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(10, A_HEAD));

}