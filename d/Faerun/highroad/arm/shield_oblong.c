/*
 * Armour from the Mere of Dead Men
 * -- Finwe, August 2006
 */
#include "/d/Faerun/defs.h"
#include "defs.h"
#include <formulas.h>
#include <language.h>
#include <stdproperties.h>
#include <wa_types.h>

inherit FAERUN_ARM_BASE;

#define ADJ1        "large"
#define ADJ2        "steel"
#define ARMOUR      "shield"
#define BOD_TYPE    A_SHIELD
#define AC_MOD      0,0,0

int ac =  20 + random(5);

void create_faerun_armour()

{
    set_name("shield");
    add_name(ARMOUR);
    set_adj(ADJ1);
    set_adj(ADJ2);
    set_short(ADJ1 + " " + ADJ2 + " " + ARMOUR); 
    set_long("This " + short() + " was forged from several steel plates. " +
        "They are hammered over a wooden frame and offer good protection " +
        "to the body. The shield is oblong shaped and looks battered " +
        "from constant battles.\n");
 
    set_at(A_SHIELD);
    set_ac(ac);
    set_am(({AC_MOD}));

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(ac, BOD_TYPE));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 3);
    add_prop(OBJ_I_VALUE, 500 + random(250));
}

