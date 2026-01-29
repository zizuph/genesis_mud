/* dagger  */
inherit "/std/weapon";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"

create_weapon() {
  set_name(({"dagger","knife","weapon"}));
  set_short("fine steel dagger");
  set_pshort("daggers");
  set_long("A long leaf-bladed elvish knife, made of fine steel.\n");
  set_adj("elvish");
  set_adj("fine");
  set_adj("steel");
  set_adj("long");
  set_adj("leaf-bladed");
  set_default_weapon(15,9,W_KNIFE,W_SLASH|W_IMPALE,W_ANYH,0);
  add_prop(OBJ_I_WEIGHT,1000);
  add_prop(OBJ_I_VOLUME,180);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(15,9)+random(400)-100);
}

query_recover() { return MASTER+":"+query_wep_recover(); }
init_recover(arg) { init_wep_recover(arg); }
