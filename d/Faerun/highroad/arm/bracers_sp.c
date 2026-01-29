/*
 * Spiked Bracers
 * From Mere of Dead Men
 * -- Finwe, August 2006
 */
#include "/d/Faerun/defs.h"
#include "defs.h"
#include <formulas.h>
#include <language.h>
#include <stdproperties.h>
#include <wa_types.h>

inherit FAERUN_ARM_BASE;

#define AC      30
#define ADJ1    "studded"
#define ADJ2    "iron"

void create_faerun_armour()
{
     set_name(({"greaves", "pair of bracers"}));
     set_pname(({"armours","pairs of bracers"}));
     set_adj(({ADJ1, ADJ2}));
     set_short("pair of " + ADJ1 + " " + ADJ2 + " bracers");
     set_pshort("pairS of " + ADJ1 + " " + ADJ2 + " bracers");
     set_long("This is a " + short() + ". Heavy, blunt spikes are " +
        "arranged across the bracers. The bracers cover and protect " +
        "the arms and shoulders, and look ancient looking.\n");

     set_default_armour(AC + random(5), A_ARMS, 0, 0);
}
