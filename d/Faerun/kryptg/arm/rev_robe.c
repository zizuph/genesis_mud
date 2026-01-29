/*
 * The robe worn by the revenants of Kryptgarden.
 * -- Finwe, Oct 2007
 */

//inherit "/std/armour.c";
//inherit "/lib/keep";
#include "/d/Faerun/defs.h"
#include "defs.h"
#include <formulas.h>
#include <language.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>
#include <wa_types.h>

inherit FAERUN_ARM_BASE;

#define ADJ1        "heavy"
#define ADJ2        "canvas"
#define ARMOUR      "robe"
#define BOD_TYPE    A_ROBE
#define AC_MOD      0,1,1

int ac =  25 + random(5);

void create_faerun_armour()
{
    set_name("armour");
    add_name(ARMOUR);
    set_adj(ADJ1);
    set_adj(ADJ2);
    set_short(ADJ1 + " " + ADJ2 + " " + ARMOUR); 

    set_long("This is a " + query_short() + ". It is made canvas and looks heavier than normal. Woven into the fabric, in a criss-cross pattern, are thin iron threads.\n");

    set_at(BOD_TYPE);
    set_ac(ac);

    set_am(({AC_MOD}));

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(ac, BOD_TYPE));
    add_prop(OBJ_I_VOLUME, F_WEIGHT_DEFAULT_ARMOUR(ac, BOD_TYPE) / 5);

    set_af(this_object());
}