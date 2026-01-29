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

#define ADJ1        "tarnished"
#define ADJ2        "steel"
#define ARMOUR      "chainmail"
#define BOD_TYPE    A_TORSO | A_NECK
#define AC_MOD      -2,3,-1

int ac =  25 + random(10);

void create_faerun_armour()
{
    set_name("armour");
    add_name(ARMOUR);
    set_adj(ADJ1);
    set_adj(ADJ2);
    set_short(ADJ1 + " " + ADJ2 + " " + ARMOUR); 
    set_long("This " + short() + " is made of rings of steel. They are interconnected and form a layer of steel.  The " + ARMOUR + " looks durable and able to protect during battles. The top of the chainmail flares up to protect the neck.\n");
 
    set_at(BOD_TYPE);
    set_ac(ac);
    set_am(({AC_MOD}));
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(ac, BOD_TYPE));
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
}
