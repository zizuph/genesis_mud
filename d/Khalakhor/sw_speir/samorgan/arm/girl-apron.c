/*
 * SM girl apron
 * Tapakah, 04/2021
 */

#include "../defs.h"
#include <wa_types.h>      /* contains weapon/armour related definitions */

inherit KSTDARMOUR;
inherit "/lib/wearable_item" wi;

static mixed
check_slot (int slot)
{
  wi::check_slot(slot);
}

void
create_khalakhor_armour ()
{
  set_name("apron");
  set_pname("aprons");
  
  set_adj("plain");
  set_adj("linen");
  
  set_short("plain linen apron");
  set_pshort("plain linen aprons");
  
  set_long("This apron is made of linen, and it looks like a very useful "+
           "cloth to wear when doing house chores. \n");

  set_default_armour(5, A_CHEST|A_WAIST, ({0,0,0}));
  config_wearable_item(A_CHEST|A_WAIST, 1, 10);
}
