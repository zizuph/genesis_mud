
/*  The cloaks of the rangers of Ithilien */
inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"

create_armour()
{
  set_name("pair of gauntlets");
  add_name("gauntlets");
  add_name("armour");
  add_name("pair");
  set_adj("ranger");
  set_adj("green");
  set_short("pair of green gauntlets");
  set_long(break_string("This is a pair of green gauntlets. \n",75));
  set_default_armour(16, A_HANDS, (({ -1, -1, 2})), 0);
  add_prop(OBJ_I_WEIGHT, 360);   /* 360 gram */
  add_prop(OBJ_I_VOLUME, 250);   /* 0,25 liter */
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(16)+random(20));
}

query_recover() { return MASTER+":"+query_arm_recover(); }
init_recover(arg) { init_arm_recover(arg); }
