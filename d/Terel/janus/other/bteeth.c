/* teeth from a bear  */
/* janus 920620  */
inherit "/std/weapon";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/d/Terel/common/terel_std_rec.h"

create_weapon() {
  set_name(({"bearteeth","weapon"}));
  set_short("set of large bearteeth");
  set_pshort("teeth");
  set_long("A set of teeth taken from a large bear. Could be used as a weapon in\n"+
           "an emergency.\n");
  set_adj(({"sharp","discolored","large"}));
  set_default_weapon(4,5,W_KNIFE,W_IMPALE,W_ANYH,0);
  add_prop(OBJ_I_WEIGHT,200);
  add_prop(OBJ_I_VOLUME,180);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(4,5)+random(200));
 }

