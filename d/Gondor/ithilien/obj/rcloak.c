
/*  The cloaks of the rangers of Ithilien */
inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"

create_armour()
{
  set_name("cloak");
  add_name("robe");
  add_name("armour");
  set_adj("ranger");
  set_adj("spotted");
  set_adj("heavy");
  set_adj("dark-green");
  set_short("dark-green spotted cloak");
  set_long(break_string("This is a hooded cloak made of heavy dark-green cloth. " +
    "To help the wearer to walk unseen through glades and forests, the cloak " +
    "is spotted in various hues of brown and green.\n",75));
  set_default_armour(3, A_ROBE, (({ 0, 0, 1})), 0);
  add_prop(OBJ_I_WEIGHT, 360);   /* 360 gram */
  add_prop(OBJ_I_VOLUME, 250);   /* 0,25 liter */
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(3)+random(20));
}

query_recover() { return MASTER+":"+query_arm_recover(); }
init_recover(arg) { init_arm_recover(arg); }
