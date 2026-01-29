/*
 * SM girl shoes
 * Tapakah, 04/2021
 */

#include "../defs.h"
#include <wa_types.h>      /* contains weapon/armour related definitions */

inherit KSTDARMOUR;

void
create_khalakhor_armour ()
{
  set_name("shoes");
  add_name("shoe");
  set_adj("old");
  set_adj("leather");
  
  set_short("pair of old leather shoes");
  set_pshort("pairs of old leather shoes");

  set_long("These shoes have seen better days. They seem to be still intact, "+
           "but it looks like this leather is not going to last long.\n");

  set_default_armour(1, A_FEET, ({0,0,0}));
}
