/*
 * SM guard helmet
 * Tapakah, 04/2021
 */

#include <wa_types.h>

#include "../defs.h"

inherit SM_ARMOUR;

void
create_armour()
{
  set_name("helmet");
  set_pname("helmets");
  
  set_adj("plain");
  set_adj("steel");
  
  set_short("plain steel helmet");
  set_pshort("plain steel helmets");
  
  set_long("This helmet is made of plain steel plates that seem to hold "+
           "together pretty well. Not too heavy and not too stiff, it "+
           "provides a decent defense for its bearer.\n");
  set_at(A_HEAD);  
}
