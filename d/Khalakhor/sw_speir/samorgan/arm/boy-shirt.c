/*
 * SM boy shirt
 * Tapakah, 05/2021
 */

#include "../defs.h"
#include <wa_types.h>      /* contains weapon/armour related definitions */

inherit KSTDARMOUR;

void
create_khalakhor_armour ()
{
  set_name("shirt");
  set_pname("shirts");
  
  set_adj("laced");
  set_adj("cotton");
  
  set_short("laced cotton shirt");
  set_pshort("laced cotton shirts");
  
  set_long("This shirt is made of plain white cotton. The chest has little "+
           "holes in it through which laces run. It provides enough cover "+
           "for its wearer without hindering the movements.\n");

  set_default_armour(5, A_CHEST|A_BACK, ({0,0,0}));
}
