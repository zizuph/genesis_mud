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

#define ADJ1        "small"
#define ADJ2        "round"
#define ARMOUR      "shield"
#define BOD_TYPE    A_SHIELD
#define AC_MOD      0,0,0

int ac =  25 + random(5);

void create_faerun_armour()
{
    set_name("shield");
    add_name(ARMOUR);
    set_adj(ADJ1);
    set_adj(ADJ2);
    set_short(ADJ1 + " " + ADJ2 + " " + ARMOUR); 
    set_long("This " + short() + " is rusty looking but still decent. " +
        "It is made from a piece of steel and hammered over a wooden " +
        "frame. The shield is round and looks like it can protect your " +
        "body well. \n");
 
    set_at(BOD_TYPE);
    set_ac(ac);
    set_am(({AC_MOD}));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(ac, BOD_TYPE));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_I_VALUE, 400 + random(250));
}


public int *
query_shield_slots()
{
    if (query_at() & A_SHIELD)
    {
        return (::query_shield_slots() + ({ A_BODY}) );
    }
    
    return ::query_shield_slots();
}
