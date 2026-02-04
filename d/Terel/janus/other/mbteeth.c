/* teeth from a bear  */
/* janus 920621  */
inherit "/std/weapon";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/d/Terel/common/terel_std_rec.h"

create_weapon() {
  set_name(({"bearteeth","teeth"}));
  set_short("set of large bearteeth");
  set_pshort("teeth");
  set_long("A set of of large, sharp, and discolored teeth taken from a \n"+
	   "large bear. Could be used as a weapon in an emergency.\n");
  set_adj(({"sharp","discolored","large"}));
  set_default_weapon(8,10,W_SWORD,W_IMPALE,W_ANYH,0);
  add_prop(OBJ_I_WEIGHT,600);
  add_prop(OBJ_I_VOLUME,380);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(8,10)+random(400));
 }



