inherit "/std/weapon";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include <macros.h>

create_weapon() {
  set_name("scimitar");
  add_name(({"sword"}));
  set_short("iron scimitar");
  set_pshort("iron scimitars");
  set_long("This scimitar was made by orcs, and looks nasty. It's made of iron.\n");
  set_default_weapon(18,12,W_SWORD,W_SLASH | W_IMPALE,W_NONE,0);
  add_prop(OBJ_I_WEIGHT, 4000);
  add_prop(OBJ_I_VOLUME, 420);
  add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(18,12)+random(30)-15);
}

query_recover()  { return MASTER + ":" + query_wep_recover(); }
init_recover(arg) { init_wep_recover(arg); }
