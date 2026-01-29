/*
 * Shield from the Kryptgarden
 * -- Finwe, August 2007
 */
#include "/d/Faerun/defs.h"
#include "defs.h"
#include <formulas.h>
#include <language.h>
#include <stdproperties.h>
#include <wa_types.h>

inherit FAERUN_ARM_BASE;

#define ADJ1        "large"
#define ADJ2        "spiked"
#define ARMOUR      "shield"
#define BOD_TYPE    A_SHIELD
#define AC_MOD      -2,1,1

int ac =  30 + random(10);

void create_faerun_armour()

{
    set_name("shield");
    add_name(ARMOUR);
    set_adj(ADJ1);
    set_adj(ADJ2);
    set_short(ADJ1 + " " + ADJ2 + " " + ARMOUR); 
    set_long("This  is a " + query_short() + ". It is medium sized with a large spike in the center. It is very heavy, but gives good protection. The shield is oblong shaped and looks battered from constant battles.\n");
 
    set_at(BOD_TYPE);
    set_ac(ac);
    set_am(({AC_MOD}));

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(ac, BOD_TYPE));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 3);
    add_prop(OBJ_I_VALUE, 600 + random(250));
}

public int *
query_shield_slots()
{
    return (::query_shield_slots() + ({ A_BODY, A_LEGS }) );
}
