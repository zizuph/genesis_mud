/*
 * Vampire armours
 * -- Finwe, August 2007
 */
#include "/d/Faerun/defs.h"
#include "defs.h"
#include <formulas.h>
#include <language.h>
#include <stdproperties.h>
#include <wa_types.h>

inherit FAERUN_ARM_BASE;

#define AC          20
#define ADJ1        "black"
#define ADJ2        "leather"
#define AC_MOD      0, 1, -1
#define BOD_TYPE    A_LEGS | A_FEET


void create_faerun_armour()
{
    set_name(({"boots", "pair of leather boots"}));
    set_pname(({"armours","pairs of leather boots"}));
    set_adj(({ADJ1, ADJ2}));
    set_short("pair of " + ADJ1 + " " + ADJ2 + " boots");
    set_pshort("pairs of " + ADJ1 + " " + ADJ2 + " boots");
    set_long("This is a " + query_short() + ". They come up to the knees and protect the legs. The boots are made of hardened black leather but still supple.\n");

    set_am(({ AC_MOD}));
    set_at(BOD_TYPE);
    set_ac(AC);
}
