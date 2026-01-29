/* testing armour */
inherit "/std/armour";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"

create_armour() {
  set_name(({"chainmail","chain mail","mail"}));
  set_short("smelly, grey chainmail");
  set_pshort("grey chainmails");
  set_long("The smelly, grey chainmail is made of small iron rings. It smells\n"+
    "so bad, you would guess it has been used by an orc or a goblin lately.\n");
  set_adj("smelly");
  set_adj("grey");
  set_adj("iron");
  set_default_armour(17,A_BODY,0,0);
  add_prop(OBJ_I_WEIGHT,5500);
  add_prop(OBJ_I_VOLUME,700);
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(17)+random(200)-100);
 }

