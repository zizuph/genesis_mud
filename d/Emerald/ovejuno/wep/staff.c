inherit "/std/weapon";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"

#define WEAPON_HIT 10
#define WEAPON_PEN 15


void
create_weapon()
{
  set_name("staff");
  set_pname("staffs");

  set_adj("shepherd");

  set_short("shepherd's staff");
  set_pshort("shepherd staffs");
  
  set_long("A shepherd staff. As tall as a person, this staff " +
	   "allows a shepherd to rest his legs. It is also quite " +
	   "effective as a weapon.\n");

  set_hit(WEAPON_HIT);
  set_pen(WEAPON_PEN);
  set_wt(W_POLEARM);
  set_dt(W_BLUDGEON);
  set_hands(W_BOTH);
  
  add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(WEAPON_HIT,WEAPON_PEN) + random(20));
  add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(WEAPON_HIT,WEAPON_PEN) + random(50) - 25);
  
  add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/5);
}

string
query_recover()
{
  return MASTER + ":" + query_wep_recover();
}

void
init_recover(string arg)
{
    init_wep_recover(arg);
}
