inherit "/std/weapon";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"

create_weapon() {
  set_name(({"axe","cleaver","meat cleaver"}));
  set_adj("meat");
  set_adj("large");
  set_adj("haradrim");
  set_short("large meat cleaver");
  set_pshort("meat cleavers");
  set_long(break_string("This is a large meat cleaver. It has probably been made " +
    "to cut up dead meat, but when used like an axe, it will do great harm against " +
    "living flesh, too!\n",75));
  set_default_weapon(25,30,W_AXE,W_SLASH | W_BLUDGEON,W_NONE,0);
  add_prop(OBJ_I_WEIGHT, 5000);
  add_prop(OBJ_I_VOLUME, 600);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(25,30) - random(500) + 100);
}

query_recover() { return MASTER+":"+query_wep_recover(); }
init_recover(arg) { init_wep_recover(arg); }

