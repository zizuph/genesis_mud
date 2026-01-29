/*
 *  faerun/underdark/upper/menzo/sorcere/arm/ns_armband.c
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

#define AC 30

inherit FAERUN_ARM_BASE;

void create_faerun_armour()
{
    set_name("armband");
    add_name("band");
    set_adj( "dark" );
    set_adj( "nightscale" );
    set_short("pair of dark nightscale armbands");
    set_long("This " + short() + " is made of glistening dark snakeskin, " +
             "which has been treated with mysterious " +
             "alchemical mixtures. It feels cold to " +
             "the touch and it moves lightly under the stroke " +
             "of your hand. The material is much like leather, " +
             "very supple and form fitting.\n");
    set_short("dark nightscale armband");

    set_ac(AC + random(5));
    set_at(A_ARMS);

    add_prop(OBJ_I_IS_MAGIC_ARMOUR,1);
    add_prop(MAGIC_AM_MAGIC,({20,"enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,({"This armour has been " +
    "magically enchanted to protect you " +
    "well, despite the thin and light material.\n",40}));

    add_prop(OBJ_I_WEIGHT, 2800);

}