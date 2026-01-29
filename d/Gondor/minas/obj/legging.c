inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

create_armour()
{
  set_name("leggings");
  add_name("pair");
  add_name("pair of leggings");
  set_adj("pair");
  set_adj("of");
  set_adj("muslin");
  set_adj("well-worn");
  set_adj("faded");
  set_short("pair of muslin leggings");
  set_pshort("pairs of muslin leggings");
   set_long(
   "A pair of well-worn muslin leggings, as worn by the working " +
   "people, men and women alike. They are very utilitarian, " +
   "with a loose cut and drawstring waist. The hems are " +
   "embroidered with ivy motifs.\n");
  set_default_armour(3,A_LEGS,0,0);
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(3)+random(40));
}

query_recover() { return MASTER + ":" + query_arm_recover(); }
init_recover(arg) { init_arm_recover(arg); }
