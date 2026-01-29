/*
 * SM girl dress
 * Tapakah, 04/2021
 */

#include "../defs.h"
#include <wa_types.h>      /* contains weapon/armour related definitions */
inherit KSTDARMOUR;

void
create_khalakhor_armour ()
{
  set_name("dress");
  set_pname("dresses");
  
  set_adj("plain");
  set_adj("woolen");
  
  set_short("plain woolen dress");
  set_pshort("plain woolen dresses");
  
  set_long("This dress is made of plain white wool, clearly designed "+
           "to provide its wearer with two basics: cover and warmth.\n");

  set_default_armour(5, A_CHEST|A_BACK, ({0,0,0}));
}
