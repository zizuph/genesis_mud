/* deerskin  */
inherit "/std/armour";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"

create_armour() {
  set_name("deer fur");
  add_name("fur");
  add_name("deerfur");
  add_name("deer skin");
  add_name("skin");
  set_short("shiny, red brown deer fur");
  set_pshort("furs");
  set_long("A shiny, red brown deer fur from a wild deer of the plains of Rohan.\n");
  set_adj(({"red","brown","red brown","shiny","deer's","deer"}));
  set_ac(9);
  set_at(A_BODY);
  set_am(({-2,2,1}));
  add_prop(OBJ_I_WEIGHT,(800+(random(600))));
  add_prop(OBJ_I_VOLUME,(600+(random(600))));
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(9)+random(40)-50);
 }

