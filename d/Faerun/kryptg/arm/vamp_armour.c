/*
 * Vampire armours
 * -- Finwe, Oct 2007
 */

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <formulas.h>
#include <language.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>
#include <wa_types.h>

inherit FAERUN_ARM_BASE;

#define ADJ1        "black"
#define ADJ2        "steel"
#define ARMOUR      "platemail"
#define BOD_TYPE    A_TORSO
#define AC_MOD      0,0,0

int ac =  39;

void create_faerun_armour()
{
    set_name("armour");
    add_name(ARMOUR);
    set_adj(ADJ1);
    set_adj(ADJ2);
    set_short(ADJ1 + " " + ADJ2 + " " + ARMOUR); 

    set_long("This is a " + query_short() + ". It fits over the torso and protects the body. The armour is made of plates of steel which is very durable and has a dark luster to it.\n");

    set_at(BOD_TYPE);
    set_ac(ac);

    set_am(({ AC_MOD}));

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(ac, BOD_TYPE));
    add_prop(OBJ_I_VOLUME, F_WEIGHT_DEFAULT_ARMOUR(ac, BOD_TYPE) / 5);

    set_af(this_object());
}