/*
 * Helm for Dwarven Guards
 * Twire, based oon Finwe, December 2015
 */

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <formulas.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

inherit FAERUN_ARM_BASE;

#define ADJ1        "horned"
#define ADJ2        "steel"
#define ARMOUR      "helmet"
#define BOD_TYPE    A_HEAD
#define AC_MOD      0,0,0

int ac =  25;

void create_faerun_armour()
{
    set_name("armour");
    add_name("helm");
    add_name(ARMOUR);
    set_adj(ADJ1);
    set_adj(ADJ2);
    set_short(ADJ1 + " " + ADJ2 + " " + ARMOUR); 

    set_long("The helmet very strong looking and made of steel. Even though it is finely crafted, the helmet is dented and scratched from recent use.\n");

    set_at(BOD_TYPE);
    set_ac(ac);

    set_am(({ AC_MOD}));

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(ac, BOD_TYPE));
    add_prop(OBJ_I_VOLUME, F_WEIGHT_DEFAULT_ARMOUR(ac, BOD_TYPE) / 5);

// used for special wear/remove messages
    set_af(this_object());
}