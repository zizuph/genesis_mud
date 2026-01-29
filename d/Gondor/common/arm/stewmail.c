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
  set_short("sparkling silver chainmail");
  set_pshort("sparkling silver chainmails");
  set_adj("silver");
   add_adj("sparkling");
set_long("A silver chainmail, with interlocking rings. Some " +
   "of the rings are burnished black, so that the mail reflects " +
   "and sparkles magnificently.\n");
  set_default_armour(25,A_BODY,0,0);
  add_prop(OBJ_I_WEIGHT,9500);
  add_prop(OBJ_I_VOLUME,700);
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(25)+random(200)-100);
  add_prop(GONDOR_M_TIRITH_NO_SELL,1);
}
