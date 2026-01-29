/*
 * Bracers for the halfling guards
 * Finwe, Dec 2015
 */
#include "/d/Faerun/defs.h"
#include "defs.h"
#include <formulas.h>
#include <language.h>
#include <stdproperties.h>
#include <wa_types.h>

inherit FAERUN_ARM_BASE;

#define AC      25
#define ADJ1    "runed"
#define ADJ2    "steel"

void create_faerun_armour()
{
     set_name(({"bracers", "pair of bracers"}));
     set_pname(({"armours","pairs of bracers"}));
     set_adj(({ADJ1, ADJ2}));
     set_short("pair of " + ADJ1 + " " + ADJ2 + " bracers");
     set_pshort("pairs of " + ADJ1 + " " + ADJ2 + " bracers");
     set_long("This is a pair of sturdy steel bracers. They are engraved with dwarven runes to protect the soldier who wears them. They are worn on the arms and look strong.\n");

     set_default_armour(AC, A_ARMS, 0, 0);
}
