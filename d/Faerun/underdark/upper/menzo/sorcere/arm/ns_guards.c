/*
 *  faerun/underdark/upper/menzo/sorcere/arm/ns_guards.c
 *
 *  A nightscale armour in Underdark
 *
 *  Created by Midnight, 3-3-2004
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
    set_name("guards");
    set_adj( "shin" );
    set_adj( "nightscale" );
    set_long("This armour is made of shimmering dark snakeskin, " +
             "which has been treated with mysterious " +
             "alchemical mixtures. It feels cold to " +
             "the touch and it moves lightly under the stroke " +
             "of your hand. The material is much like leather, " +
             "very supple and formfitting.\n");
    set_short("nightscale shin guards");

    set_ac(30);
    set_at(A_LEGS);

    add_prop(OBJ_I_IS_MAGIC_ARMOUR,1);
    add_prop(MAGIC_AM_MAGIC,({60,"enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,({"This armour has been " +
    "magically enchanted through alchemy to protect you " +
    "well, despite the thin and light material.\n",40}));

    add_prop(OBJ_I_VALUE, 4200);
    add_prop(OBJ_I_WEIGHT, 800);

}