/*
 * SM boy shoes
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
  set_adj("sturdy");
  set_adj("leather");
  
  set_short("pair of sturdy leather shoes");
  set_pshort("pairs of sturdy leather shoes");

  set_long("These shoes have been repaired recently. They look sturdy, "+
           "and will likely last a while, especially if the wearer "+
           "does not abuse them.\n");

  set_default_armour(5, A_FEET, ({0,0,0}));
}
