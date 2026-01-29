/* scimitar  */
inherit "/std/weapon";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"

create_weapon() {
  set_name(({"scimitar","sword","weapon"}));
  set_short("ornate brass scimitar");
  set_pshort("scimitars");
  set_long("A curved sharp easterling sword, made of ornate brass.\n");
  set_adj("easterling");
  set_adj("ornate");
  set_adj("brass");
  set_adj("curved");
  set_adj("sharp");
  set_default_weapon(16,7,W_SWORD,W_SLASH,W_RIGHT,0);
  add_prop(OBJ_I_WEIGHT,6000);
  add_prop(OBJ_I_VOLUME,750);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(16,7)+random(200)-100);
}

query_recover() { return MASTER+":"+query_wep_recover(); }
init_recover(arg) { init_wep_recover(arg); }
