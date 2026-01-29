/* helm  */
inherit "/std/armour";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"

create_armour() {
  set_name(({"helm","helmet","armour"}));
  set_short("black steel helm");
  set_pshort("helms");
  set_long("A black and silver dunedain helm, made of enamelled steel.\n");
  set_adj(({"silver","steel","black","dunedain"}));
  set_ac(30);
  set_at(A_HEAD);
  set_am(({-1,1,1}));
  add_prop(OBJ_I_WEIGHT,1100);
  add_prop(OBJ_I_VOLUME,175);
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(30)+random(1000)+100);
 }

