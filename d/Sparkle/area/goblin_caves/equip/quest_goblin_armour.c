/*
 * Armour for goblin armour quest
 * - Boreaulam, April 2012
 */
inherit "/std/armour";

#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>

/*
 * Function name:        create_armour
 * Description  :        constructor for the object
 */
void
create_armour()
{

    set_name("armour");
    add_name("platemail");
    add_name(LEVEL1_QUEST_PLATEMAIL);
    set_short("shattered iron platemail");
    set_adj("shattered");
    set_adj("iron");
    set_long("This is a " + short() + ". It is made from hammered plates " +
        "of iron but holes in plate made but multiple hits make this armour " +
        "useless. This looks like it might be the armour that the goblin " +
        "trainer wanted you to find. Perhaps you should return it to him.\n");
    set_ac(1);
    set_at(A_TORSO);
    set_am(({0,0,0}));

    add_prop(OBJ_I_VALUE, 250);
    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_I_WEIGHT, 3000);
} /* create_armour */