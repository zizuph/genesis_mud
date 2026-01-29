/* orc-club  */
inherit "/std/weapon";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"

create_weapon() {
  set_name(({"club","weapon","orc-club"}));
  set_short("hard wooden orc-club");
  set_pshort("wooden clubs");
  set_long("A normal one-handed orcish club, made out of some sort of wood.\n");
  set_adj("orc");
  set_adj("heavy");
  set_adj("wooden");
  set_adj("normal");
  set_adj("one-handed");
  set_default_weapon(15,14,W_CLUB,W_BLUDGEON,W_ANYH,0);
  add_prop(OBJ_I_WEIGHT,8000);
  add_prop(OBJ_I_VOLUME,8300);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(15,14)+random(200)-100);
}

query_recover() { return MASTER+":"+query_wep_recover(); }

init_recover(arg) { init_wep_recover(arg); }
