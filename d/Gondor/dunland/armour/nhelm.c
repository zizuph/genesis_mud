/* helm  */
inherit "/std/armour";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"

create_armour() {
  set_name(({"helm","helmet","armour"}));
  set_short("nasalled iron helm");
  set_pshort("helms");
  set_long("A nasalled rohirrim helm, made of grey iron.\n");
  set_adj(({"grey","iron","nasalled","rohirrim"}));
  set_ac(24);
  set_at(A_HEAD);
  set_am(({-1,2,0}));
  add_prop(OBJ_I_WEIGHT,1300);
  add_prop(OBJ_I_VOLUME,180);
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(24)+random(400)-100);
 }

