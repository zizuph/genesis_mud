
/*  The travel-cloaks of the rangers of the north */
inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/formulas.h"

public void
create_armour()
{
  set_name("cloak");
  add_name("robe");
  add_name("armour");
  set_adj("ranger");
  set_adj("travel-stained");
  set_adj("heavy");
  set_adj("dark-green");
  set_short("travel-stained, dark-green cloak made of heavy cloth");
  set_long("This is a travel-stained, hooded cloak made of heavy dark-green cloth.\n");
  set_default_armour(3, A_ROBE, (({ 0, 0, 1})), 0);
  add_prop(OBJ_I_WEIGHT, 360);   /* 360 gram */
  add_prop(OBJ_I_VOLUME, 250);   /* 0,25 liter */
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(3)+random(20));
}

