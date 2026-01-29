/* Shield on ground */
inherit "/std/armour";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include <macros.h>

create_armour() {
  set_name("shield");
  set_pname("shields");
  set_adj("wooden");
  add_adj("small");
  set_short("small shield");
  set_pshort("small shields");
  set_long("This is a small, wooden shield.\n");
/*  set_default_armour(10,A_SHIELD,({ 0, 0, 0 }),0); */
  set_ac(10);
  set_at(A_SHIELD);
  add_prop(OBJ_I_WEIGHT,1000);
  add_prop(OBJ_I_VOLUME,1100);
  add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(10)+random(10)-5);
  add_prop(OBJ_S_WIZINFO,
    "This shield is AC 10 following the armour_guide:\n"+
    "wooden shield is AC 15, -5 for being small.\n");
 }
