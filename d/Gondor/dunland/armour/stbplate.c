/* breastplate  */
inherit "/std/armour";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"

create_armour() {
  set_name(({"breastplate","plate","armour"}));
  set_short("black steel breastplate");
  set_pshort("breastplates");
  set_long("A black and silver dunedain breastplate, made of enamelled steel.\n");
  set_adj(({"steel","black","dunedain"}));
  set_ac(30);
  set_at(A_BODY);
  set_am(({1,1,0}));
  add_prop(OBJ_I_WEIGHT,7500);
  add_prop(OBJ_I_VOLUME,1200);
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(30)+random(1000)+100);
 }

