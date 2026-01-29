/*
 * SM guard shield
 * Tapakah, 04/2021
 */

#include "../defs.h"
inherit SM_ARMOUR;

void
create_armour()
{
  set_name("shield");
  set_pname("shields");
  
  set_adj("round");
  set_adj("steel");
  
  set_short("round steel shield");
  set_pshort("round steel shields");
  
  set_long("This shield is made of round steel plate that had been hammered "+
           "into a convex shape. Not too heavy and not too clunky, it "+
           "provides a decent defense for its bearer.\n");
}
