/* lionskin  */
inherit "/std/armour";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"

create_armour() {
  set_name(({"skin","lionskin","leather","armour"}));
  set_short("tawny lion skin");
  set_pshort("skins");
  set_long("A spotted tawny lionskin, from a wild wood lion of Dunland.\n");
  set_adj(({"spotted","tawny","leather","dunlending","lion's","lion"}));
  set_ac(9+random(3));
  set_at(A_BODY);
  set_am(({-2,2,1}));
  add_prop(OBJ_I_WEIGHT,(1500+random(1000)));
  add_prop(OBJ_I_VOLUME,(1400+random(1000)));
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(11)+random(1100)+500);
 }

