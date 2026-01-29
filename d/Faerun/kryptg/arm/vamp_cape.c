/*
 * The cape worn by the vampires of Kryptgarden.
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

#define ADJ1        "long"
#define ADJ2        "black"
#define ARMOUR      "cape"
#define BOD_TYPE    A_ROBE
#define AC_MOD      0,1,1

int ac =  30;

void create_faerun_armour()
{
    set_name("armour");
    add_name(ARMOUR);
    set_adj(ADJ1);
    set_adj(ADJ2);
    set_short(ADJ1 + " " + ADJ2 + " " + ARMOUR); 
    set_long("This is a " + query_short() + ". It is long and goes down to the ground. The cape is black with a high collar. The inside of the cape is blood-red.\n");

    set_at(BOD_TYPE);
    set_ac(ac);

    set_am(({ 0, 0, 0}));

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(ac, BOD_TYPE));
    add_prop(OBJ_I_VOLUME, F_WEIGHT_DEFAULT_ARMOUR(ac, BOD_TYPE) / 5);

    set_af(this_object());
}