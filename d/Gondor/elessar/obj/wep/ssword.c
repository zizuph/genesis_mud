/* shortsword  */
inherit "/std/weapon";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"

create_weapon() {
  set_name(({"shortsword","sword","weapon"}));
  set_short("bluegrey steel shortsword");
  set_pshort("shortswords");
  set_long("A small dunedain stabbing sword, made of alloyed bluegrey steel.\n");
  set_adj("stabbing");
  set_adj("bluegrey");
  set_adj("steel");
  set_adj("small");
  set_adj("dunedain");
  set_default_weapon(12,18,W_SWORD,W_SLASH|W_IMPALE,W_ANYH,0);
  add_prop(OBJ_I_WEIGHT,4000);
  add_prop(OBJ_I_VOLUME,640);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(12,18)+random(400)-100);
 }

query_recover() { return MASTER+":"+query_wep_recover(); }

init_recover(arg) { init_wep_recover(arg); }
