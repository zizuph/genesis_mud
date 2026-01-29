inherit "/std/weapon";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"

create_weapon() {
  set_name("dagger");
  set_short("sharp dagger");
  set_pshort("sharp daggers");
  set_long("This long, sharp dagger looks just like the sort of dagger a\n"+
    "knife-throwing expert would use.\n");
  set_default_weapon(13,15,W_KNIFE,W_SLASH | W_IMPALE,W_NONE,0);
  add_prop(OBJ_I_WEIGHT,600);
  add_prop(OBJ_I_VOLUME,90);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(13,15)+random(20)-10);
}

query_recover() { return MASTER+":"+query_wep_recover(); }
init_recover(arg) { init_wep_recover(arg); }
