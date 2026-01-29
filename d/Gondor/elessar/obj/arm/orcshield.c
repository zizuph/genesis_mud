/* Shield of the normal/lesser Orcs */
inherit "/std/armour";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"

create_armour()
{
  set_name("shield");
  set_short("leather shield");
  set_pshort("leather shields");
  set_adj("orcish");
  set_adj("poor");
  set_adj("leather");
  set_long("This poor Orcish shield is made of toughened hide stretched over a\n"+
    "wooden frame.\n");
  set_default_armour(3,A_SHIELD,({ -2, 1, 1}),0);
  add_prop(OBJ_I_WEIGHT, 1300);
  add_prop(OBJ_I_VOLUME, 600);
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(3)+random(10)-20);
}
