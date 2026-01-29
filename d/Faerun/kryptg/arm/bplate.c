/*
 * Armour for Insectman in Kryptgarden
 * -- Finwe, August 2007
 */
#include "/d/Faerun/defs.h"
#include "defs.h"
#include <formulas.h>
#include <language.h>
#include <stdproperties.h>
#include <wa_types.h>

inherit FAERUN_ARM_BASE;

#define ADJ1        "ornamented"
#define ADJ2        "burnished"
#define ARMOUR      "breastplate"
#define BOD_TYPE    A_TORSO | A_NECK
#define AC_MOD      0,0,0

int ac =  30 + random(10);

void create_faerun_armour()
{
    set_name("armour");
    add_name(ARMOUR);
    set_adj(ADJ1);
    set_adj(ADJ2);
    set_short(ADJ1 + " " + ADJ2 + " " + ARMOUR); 
    set_long("This " + short() + " is made of steel. It is polished to a deep golden color. The " + ARMOUR + " looks durable and able to protect during battles. The top of the " + ARMOUR + " flares up to protect the neck.\n");
 
    set_at(BOD_TYPE);
    set_ac(ac);
    set_am(({AC_MOD}));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(ac, BOD_TYPE));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
}
