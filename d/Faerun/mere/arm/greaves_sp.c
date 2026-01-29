/*
 * Iron Greaves
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
     set_name(({"greaves", "pair of greaves"}));
     set_pname(({"armours","pairs of greaves"}));
     set_adj(({ADJ1, ADJ2}));
     set_short("pair of " + ADJ1 + " " + ADJ2 + " greaves");
     set_pshort("pairs of " + ADJ1 + " " + ADJ2 + " greaves");
     set_long("This is a " + short() + ". Heavy, blunt spikes are " +
        "arranged across the greaves. The greaves cover and protect " +
        "the legs and look ancient looking.\n");

     set_default_armour(AC + random(5), A_LEGS, 0, 0);
}
