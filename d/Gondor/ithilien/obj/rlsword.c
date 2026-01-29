inherit "/std/weapon";
#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"

create_weapon() {
  set_name(({"longsword","sword","long sword"}));
  set_adj("steel");
  set_adj("ranger");
  set_adj("fine");
  set_short("steel longsword");
  set_pshort("steel longswords");
  set_long(break_string("This solid steel longsword was crafted in the forges of Minas Tirith " +
  "for the rangers of Ithilien. It looks to be a very fine weapon.\n",75));
  set_default_weapon(25,30,W_SWORD,W_SLASH | W_IMPALE,W_NONE,0);
  add_prop(OBJ_I_WEIGHT, 5000);
  add_prop(OBJ_I_VOLUME, 600);
  add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(25,30) + random(500) - 100);
}

query_recover()
{
  return MASTER+":"+query_wep_recover();
}

init_recover(arg) { init_wep_recover(arg); }

