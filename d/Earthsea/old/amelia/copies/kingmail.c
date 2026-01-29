#pragma save_binary

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

query_recover()
{
  return MASTER+":"+query_arm_recover();
}

init_recover(arg)
{
  init_arm_recover(arg);
}

create_armour()
{
  set_short("mithril platemail");
  set_long("This is an excellent piece of dwarven craftmanship.\n");

  set_name("platemail");
  add_name("mail");
  
  set_at(A_TORSO);
  add_prop(OBJ_I_WEIGHT,12000);
  add_prop(OBJ_I_VOLUME,10000);

  set_adj("mithril");
  add_adj("plate");

  set_ac(40);
}