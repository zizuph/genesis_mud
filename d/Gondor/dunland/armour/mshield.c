/* shield  */
inherit "/std/armour";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"

create_armour() {
  set_name(({"shield","buckler","armour"}));
  set_short("black steel shield");
  set_pshort("shields");
  set_long("A black and silver dunedain shield, made of enamelled steel.\n");
  set_adj(({"steel","black","dunedain"}));
  set_ac(30);
  set_at(A_SHIELD);
  set_am(({1,0,0}));
  add_prop(OBJ_I_WEIGHT,6000);
  add_prop(OBJ_I_VOLUME,900);
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(30)+random(1000)+100);
 }

