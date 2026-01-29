/*
 * Armour for orcmaker
 * -- Finwe, August 2006
 */
#include "/d/Faerun/defs.h"
#include "defs.h"
#include <formulas.h>
#include <language.h>
#include <stdproperties.h>
#include <wa_types.h>

inherit FAERUN_ARM_BASE;

#define ADJ1        "small"
#define ADJ2        "round"
#define ARMOUR      "buckler"
#define BOD_TYPE    A_SHIELD
#define AC_MOD      0,0,0
#define AC          20 + random(5)


void create_faerun_armour()
{
    set_name("armour");
    add_name("shield");
    add_name(ARMOUR);
    set_adj(ADJ1);
    set_adj(ADJ2);
    set_short(ADJ1 + " " + ADJ2 + " " + ARMOUR);
    set_long("This is a " + short() + ". It protects the arms during battles. The shield is made of plates of iron that have been hammered across a trinagular shaped frame.\n");
 
    set_at(BOD_TYPE);
    set_ac(AC);
    set_am(({AC_MOD}));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(AC, BOD_TYPE));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(AC));
}

