/* iron mail */
inherit "/std/armour";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"

create_armour() {
  set_name(({"ironmail","iron mail","mail","ringmail"}));
  set_pname("mails");
  add_pname("ringmails");
  add_pname("ironmails");
  set_short("iron ringmail");
  set_pshort("iron ringmails");
  add_adj(({"iron"}));
  set_long("The iron ringmail is made of small iron rings.\n");
  set_default_armour(21,A_BODY,0,0);
  add_prop(OBJ_I_WEIGHT,4900);
  add_prop(OBJ_I_VOLUME,700);
  add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(22)+random(400)-100);
}
