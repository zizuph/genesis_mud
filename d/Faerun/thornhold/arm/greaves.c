/* Armour for Leilon guards
 * Finwe, Oct 2008 
 */
#include "/d/Faerun/defs.h"
#include "defs.h"
#include <formulas.h>
#include <language.h>
#include <stdproperties.h>
#include <wa_types.h>

inherit FAERUN_ARM_BASE;

#define AC      25
#define ADJ1    "steel"
#define ADJ2    "ringmail"

void create_faerun_armour()
{
     set_name(({"greaves", "pair of greaves"}));
     set_pname(({"armours","pairs of greaves"}));
     set_adj(({ADJ1, ADJ2}));
     set_short("pair of " + ADJ1 + " " + ADJ2 + " greaves");
     set_pshort("pairs of " + ADJ1 + " " + ADJ2 + " greaves");
     set_long("hey are made from rings of steel that have been linked together and enclose both legs.\n");

     set_default_armour(AC, A_LEGS, 0, 0);
}
