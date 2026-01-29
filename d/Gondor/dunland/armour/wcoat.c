/* coat  */
inherit "/std/armour";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"

create_armour() {
  set_name(({"coat","wool","armour"}));
  set_short("brown wool coat");
  set_pshort("coats");
  set_long("A thick brown coat, made of fine dunlending sheep's wool.\n");
  set_adj(({"thick","brown","fine","dunlending","sheep's","wool"}));
  set_ac(8);
  set_at(A_BODY);
  set_am(({-1,1,1}));
  add_prop(OBJ_I_WEIGHT,2500);
  add_prop(OBJ_I_VOLUME,2800);
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(8)+random(100)-100);
 }

