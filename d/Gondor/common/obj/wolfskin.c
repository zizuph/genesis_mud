   /*
    *    A wolf skin
    */
inherit "/std/armour";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"

create_armour() {
  set_name("wolf skin");
  add_name("skin");
  add_name("wolfskin");
  add_name("fur");
  add_name("wolf fur");
  set_short("grey wolf skin");
  set_pshort("wolf skins");
  set_long("The skin of a grey wolf from the plains of Rohan.\n");
  set_adj(({"grey","wolf's","wolf"}));
  set_ac(12);
  set_at(A_BODY);
  set_am(({-2,2,1}));
  add_prop(OBJ_I_WEIGHT,(800+(random(600))));
  add_prop(OBJ_I_VOLUME,(600+(random(600))));
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(9)+random(40)-50);
}

