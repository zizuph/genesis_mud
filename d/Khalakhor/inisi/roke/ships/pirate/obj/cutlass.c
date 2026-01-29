/* gresolle -92 */

#pragma save_binary

inherit "/std/weapon";

#include "/sys/wa_types.h"
#include <macros.h>
#include <stdproperties.h>

create_weapon()
{
  set_short("cutlass");
  set_name("cutlass");
  add_name("sword");

  set_long("The cutlass is made of polished steel.\n");

  set_hit(25);
  set_pen(15);

  set_wt(W_SWORD);
  set_dt(W_SLASH | W_BLUDGEON);
  set_hands(W_RIGHT);
}

query_recover()
{
  return MASTER+":"+query_wep_recover();
}

init_recover(arg)
{
  init_wep_recover(arg);
}