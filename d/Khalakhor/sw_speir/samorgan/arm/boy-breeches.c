/*
 * SM boy breeches
 * Tapakah, 04/2021
 */

#include "../defs.h"
#include <wa_types.h>      /* contains weapon/armour related definitions */

inherit KSTDARMOUR;

void
create_khalakhor_armour ()
{
  set_name("breeches");
  set_pname("breeches");

  set_adj("thick");
  set_adj("woolen");
  
  set_short("pair of thick woolen breeches");
  set_pshort("pairs of thick woolen breeches");

  set_long("These breeches have been made from sheep's wool and dyed brown. "+
           "They are made thick, to withstand intensive physical working.\n");

  set_default_armour(5, A_LEGS, ({0,0,0}));
}
