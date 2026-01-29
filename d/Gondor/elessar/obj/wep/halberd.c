/* halberd  */
inherit "/std/weapon";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/macros.h"
#include "/sys/formulas.h"

create_weapon() {
  set_name(({"halberd","polearm","weapon"}));
  set_short("blueblack iron halberd");
  set_pshort("halberds");
  set_long("A stout, oak-hafted gondorian polearm, made of tempered blueblack iron.\n"+
   "This is the kind of halberd used by the Guards of the Citadel in Minas\n"+
    "Tirith in Gondor.\n");
  set_adj("gondorian");
  set_adj("blueblack");
  set_adj("iron");
  set_adj("stout");
  set_adj("oak-hafted");
  set_default_weapon(26,39,W_POLEARM,W_SLASH|W_IMPALE,W_BOTH,0);
  add_prop(OBJ_I_WEIGHT,15000);
  add_prop(OBJ_I_VOLUME,4800);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(26,39)+random(200)-100);
 }

query_recover() { return MASTER+":"+query_wep_recover(); }

init_recover(arg) { init_wep_recover(arg); }
