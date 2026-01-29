/*
 * SM guard chainmail
 * Tapakah, 04/2021
 */

#include "../defs.h"
inherit SM_ARMOUR;

void
create_armour ()
{
  set_name("chainmail");
  set_pname("chainmails");
  add_name("mail");
  
  set_adj("plain");
  set_adj("steel");
  
  set_short("plain steel chainmail");
  set_pshort("plain steel chainmails");
  
  set_long("This chainmail is made of plain steel links that seem to hold "+
           "together pretty well. Not too heavy and not too stiff, it "+
           "provides a decent defense for its bearer.\n");
}
