/*
 *  faerun/underdark/upper/menzo/sorcere/arm/ns_armour.c
 *
 *  A nightscale armour in Underdark
 *
 *  Created by Midnight, 21-2-2004
 */

#include <formulas.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Faerun/defs.h"
#include "defs.h"

inherit FAERUN_ARM_BASE;

#define AC 35

void create_faerun_armour()
{
    set_name("armour");
    set_adj( "studded" );
    set_adj( "nightscale" );
    set_long("This armour" + short() + " is made of glistening dark snakeskin, " +
             "which has been treated with mysterious " +
             "alchemical mixtures. It feels cold to " +
             "the touch and it moves lightly under the stroke " +
             "of your hand. The material is much like leather, " +
             "very supple and formfitting.\n");
    set_short("studded nightscale armour");

    set_ac(AC + random(5));
    set_at(A_TORSO);

    add_prop(OBJ_I_IS_MAGIC_ARMOUR,1);
    add_prop(MAGIC_AM_MAGIC,({20,"enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,({"This armour has been " +
    "magically enchanted through alchemy to protect you " +
    "well, despite the thin and light material.\n",40}));

    add_prop(OBJ_I_WEIGHT, 2950);


}