/* boarskin  */
inherit "/std/armour";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"

create_armour() {
  set_name(({"skin","boarskin","leather","armour"}));
  set_pname("skins");
  add_pname("boarskins");
  add_pname("leathers");
  set_short("brown boar skin");
  set_pshort("brown boar skins");
  set_long("A prickly brown boarskin, from a wild wood boar of Dunland.\n");
  set_adj(({"prickly","brown","leather","dunlending","boar's","boar"}));
  set_ac(11);
  set_at(A_BODY);
  set_am(({-1,3,2}));
  add_prop(OBJ_I_WEIGHT,(1000+(random(600))));
  add_prop(OBJ_I_VOLUME,(700+(random(600))));
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(11)+random(30)-10);
 }

