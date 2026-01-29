/*  The apron of the cook in the Haradrim camp */
inherit "/std/armour";
#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"

create_armour()
{
  set_name("apron");
  add_name("robe");
  add_name("armour");
  set_adj("blood-stained");
  set_adj("dirty");
  set_adj("heavy");
  set_short("blood-stained apron");
  set_long(break_string("This dirty apron is covered with blood stains everywhere. " +
    "You notice that is had been padded with hard leather in the front and on the " +
    "shoulders.\n",75));
  set_default_armour(6, A_LEGS, (({ 0, 0, 1})), 0);
  add_prop(OBJ_I_WEIGHT, 900);   /* 360 gram */
  add_prop(OBJ_I_VOLUME, 450);   /* 0,25 liter */
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(5)-random(20));
}

query_recover() { return MASTER+":"+query_arm_recover(); }
init_recover(arg) { init_arm_recover(arg); }
