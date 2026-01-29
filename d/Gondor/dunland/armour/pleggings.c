/* chaps  */
inherit "/std/armour";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"

create_armour() {
  set_name(({"chaps","leather","armour"}));
  set_short("cowhide leather chaps");
  set_pshort("chaps");
  set_long("A pair of dunlending chaps, made of oiltanned cowhide leather.\n");
  set_adj(({"cowhide","leather","pair","dunlending"}));
  set_ac(10);
  set_at(A_LEGS);
  set_am(({-1,0,-1}));
  add_prop(OBJ_I_WEIGHT,1100);
  add_prop(OBJ_I_VOLUME,750);
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(10)+random(150)-100);
 }

