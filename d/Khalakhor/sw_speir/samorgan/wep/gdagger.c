/*
 * Courier's dagger
 * Tapakah, 04/2021
 */

#include <wa_types.h>
#include "../defs.h"

inherit SM_WEAPON;

void
create_weapon ()
{
  set_name("dagger");
  set_pname("daggers");

  set_adj("plain");
  set_adj("steel");

  set_short("plain steel dagger");
  set_long("This dagger is made of plain steel. While being pretty simple, " +
           "it still looks reliable enough to provide a deadly stab to its "+
           "opponent.\n");

  set_wt(W_KNIFE);
           
}
