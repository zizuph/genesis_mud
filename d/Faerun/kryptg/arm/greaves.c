/*
 * Iron Greaves
 * -- Finwe, August 2007
 */
#include "/d/Faerun/defs.h"
#include "defs.h"
#include <formulas.h>
#include <language.h>
#include <stdproperties.h>
#include <wa_types.h>

inherit FAERUN_ARM_BASE;

#define AC      30
#define ADJ1    "black"
#define ADJ2    "iron"

void create_faerun_armour()
{
     set_name(({"greaves", "pair of greaves"}));
     set_pname(({"armours","pairs of greaves"}));
     set_adj(({ADJ1, ADJ2}));
     set_short("pair of " + ADJ1 + " " + ADJ2 + " greaves");
     set_pshort("pairs of " + ADJ1 + " " + ADJ2 + " greaves");
     set_long("This is a " + query_short() + ". They were forged of iron and polished. The greaves protect the legs and look like were forged ages ago.\n");

     set_default_armour(AC + random(5), A_LEGS, 0, 0);
}
