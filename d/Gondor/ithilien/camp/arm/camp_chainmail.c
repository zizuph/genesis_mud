inherit "/std/armour";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"

create_armour() {
  set_name(({"chainmail","chain mail","mail"}));
  set_pname("chainmails");
  add_pname("mails");
  set_short("camouflaged chainmail");
  set_pshort("camouflaged chainmails");
  set_adj("camouflaged");
  add_adj("chain");
  set_long("The camouflaged chainmail is made of painted metal rings.\n"+
    "It is very difficult to make out against a forest background.\n");
  set_default_armour(25,A_BODY,0,0);
  add_prop(OBJ_I_WEIGHT,9500);
  add_prop(OBJ_I_VOLUME,700);
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(25)+random(200)-100);
  add_prop(GONDOR_M_RANGERS_NO_SELL,1);
  add_prop(GONDOR_M_TIRITH_NO_SELL,1);
}
