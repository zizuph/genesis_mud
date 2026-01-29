/* troll's cape  */
inherit "/std/armour";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"

create_armour() {
  set_name(({"cape","leather","armour"}));
  set_short("large leather cape");
  set_pshort("leather capes");
  set_long("A large leather cape, made by a troll out of the hides of his victims.\n"+
    "The foul smell of the leather cape repulses you.\n");
  set_adj("large");
  set_adj("leather");
  set_adj("stiff");
  set_adj("troll");
  set_ac(6);
  set_at(A_BODY);
  set_am(({-1,0,-1}));
  add_prop(OBJ_I_WEIGHT,4300);
  add_prop(OBJ_I_VOLUME,3600);
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(5)+random(100)-100);
}

query_recover() { return MASTER+":"+query_arm_recover(); }
init_recover(arg) { init_arm_recover(arg); }
