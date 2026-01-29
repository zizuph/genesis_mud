/* deerskin  */
inherit "/std/armour";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"

create_armour() {
  set_name(({"skin","deerskin","leather","armour"}));
  set_short("brown deer skin");
  set_pshort("skins");
  set_long("A reddish brown deerskin, from a wild wood deer of Dunland.\n");
  set_adj(({"reddish","brown","leather","dunlending","deer's","deer"}));
  set_ac(9);
  set_at(A_BODY);
  set_am(({-2,2,1}));
  add_prop(OBJ_I_WEIGHT,(800+(random(600))));
  add_prop(OBJ_I_VOLUME,(600+(random(600))));
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(9)+random(25)-10);
 }

