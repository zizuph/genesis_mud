/* claymore  */
#pragma save_binary

inherit "/std/weapon";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include <macros.h>

create_weapon() {
  set_name(({"cutlass","sword","weapon"}));
  set_short("sharp bronze cutlass");
  set_pshort("cutlasses");
  set_long("This is a long, sharp, broad-bladed sword specially designed for\n"+
    "slashing people in large chunks. Looks like the typical seafarer or\n"+
    "pirates weapon.\n");
  set_adj("sharp");
  set_adj("bronze");
  set_default_weapon(18,22,W_SWORD,W_SLASH,W_RIGHT,0);
  add_prop(OBJ_I_WEIGHT,3700);
  add_prop(OBJ_I_VOLUME,3000);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(18,22)+random(20)-10);
 }

query_recover()  { return MASTER + ":" + query_wep_recover(); }
init_recover(arg) { init_wep_recover(arg); }