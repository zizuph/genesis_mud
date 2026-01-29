/*  This armour is used by common/guild/secret_room  */

inherit "/std/armour";

#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/sys/formulas.h"
#include "/sys/wa_types.h"

#define SNAME ({"helmet", "helmet", "robe", "shield", "plate"})
#define SADJ ({"bronze", "steel", "silk", "iron", "simple"})
#define SPROTECT ({A_HEAD, A_HEAD, A_ROBE, A_SHIELD, A_BODY})

create_armour() {
  int ran;

  ran = random(sizeof(SNAME));
  set_name(SNAME[ran]);
  set_short(SADJ[ran] + " " + SNAME[ran]);
  set_adj(SADJ[ran]);
  set_long("Consider this armour a token of Nob Nar's gratitude.\n");
  set_default_armour(
    9,
    SPROTECT[ran],
    W_IMPALE,
    0
  );
  add_prop(OBJ_I_WEIGHT, 1500);
  add_prop(OBJ_I_VOLUME, 2000);
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(9));
}


string query_recover()
{
    return MASTER + ":" + query_arm_recover();
}


void init_recover(string arg)
{
    init_arm_recover(arg);
}
