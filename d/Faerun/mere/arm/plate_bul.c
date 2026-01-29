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
#define ADJ2        "turtle"
#define ARMOUR      "platemail"
#define BOD_TYPE    A_TORSO | A_LEGS
#define AC_MOD      1,1,-2

int ac =  25 + random(10);

void create_faerun_armour()
{
    set_name("armour");
    add_name(ARMOUR);
    set_adj(ADJ1);
    set_adj(ADJ2);
    set_short(ADJ1 + " " + ADJ2 + " " + ARMOUR); 
    set_long("This " + short() + " is made of large overlapping pieces " +
        "of steel. It fits over the head and hangs over the shoulders by " +
        "two large leather strips. The portions that protect the torso " +
        "are irregular shaped and bulge slightly like turtle shells. " +
        "It extends down over the legs, protecting them in battles.\n");
 
    set_at(BOD_TYPE);
    set_ac(ac);
    set_am(({AC_MOD}));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(ac, BOD_TYPE));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_I_VALUE, 2500 + random(250));
}
