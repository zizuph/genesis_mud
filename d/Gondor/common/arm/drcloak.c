
/*  The travel-cloaks of the rangers of the north */
inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"

create_armour()
{
  set_name("cloak");
  add_name("robe");
  add_name("armour");
  set_pname("cloaks");
  add_pname("robes");
  set_adj("ranger");
  add_adj("travel-stained");
  add_adj("heavy");
  add_adj("dark-green");
  set_short("travel-stained dark-green cloak");
  set_pshort("travel-stained dark-green cloaks");
  set_long("This is a travel-stained, hooded cloak made of heavy dark-green cloth.\n");
  set_default_armour(3, A_ROBE, (({ 0, 0, 1})), 0);
  add_prop(OBJ_I_WEIGHT, 360);   /* 360 gram */
  add_prop(OBJ_I_VOLUME, 250);   /* 0,25 liter */
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(3)+random(20));
  add_prop(GONDOR_M_RANGERS_NO_SELL,1);
}
