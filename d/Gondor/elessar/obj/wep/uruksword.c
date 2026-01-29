/* The typical sword of Uruk-hais */
inherit "/std/weapon";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"

create_weapon() {
  set_name(({"sword","weapon","shortsword"}));
  set_short("short broad-bladed sword");
  set_pshort("black shortswords");
  set_long("A short, black broad-bladed sword, the standard equipment of an Uruk-hai.\n"+
    "The black blade is saw-edged, and looks extremely nasty.\n");
  set_adj("uruk-hai");
  set_adj("broad");
  set_adj("saw-edged");
  set_adj("black");
  set_adj("short");
  set_adj("broad-bladed");
  set_default_weapon(19,26,W_SWORD,W_SLASH,W_ANYH,0);
  add_prop(OBJ_I_WEIGHT,6000);
  add_prop(OBJ_I_VOLUME,2500);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(19,26)+random(200)-100);
}

query_recover() { return MASTER+":"+query_wep_recover(); }
init_recover(arg) { init_wep_recover(arg); }
