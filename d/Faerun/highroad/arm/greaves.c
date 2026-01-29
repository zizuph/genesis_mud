/*
 * Plain Greaves
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

#define AC 35

void create_faerun_armour()
{
     set_name(({"greaves", "pair of greaves"}));
     set_pname(({"armours","pairs of greaves"}));
     set_adj(({"plain"}));
     set_short("pair of plain greaves");
     set_pshort("pairs of plain greaves");
     set_long("This is a " + short() + ". They are ancient looking and " +
        "are scratched from countless battles. They protect the legs " +
        "and are made of overlapping plates of steel.\n");

     set_default_armour(AC + random(5), A_LEGS, 0, 0);
}
