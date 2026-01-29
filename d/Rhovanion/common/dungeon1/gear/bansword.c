inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
void
create_weapon() {
   set_name("long sword");
   add_name("sword");
   set_adj("battle scathed");
   set_long("This once fine sword bears the inevitable scars " +
      "and nicks that mark all good swords used long in battle.  The " +
      "hilt,  is wrapped, perhaps re-wrapped, in dark, oiled leather " +
      "and your battle-tested hand feels that the hilt is also " +
      "counterbalanced to allow for quicker slashes and parries. " +
      "With a little work this weapon could be partially restored.\n");
   set_hit(30);
   set_pen(25);
   set_dull(2);
   set_wt(W_SWORD);
   set_dt(W_SLASH | W_IMPALE);
   set_hands(W_ANYH);
   add_prop(OBJ_I_WEIGHT, 3000);
   add_prop(OBJ_I_VOLUME, 1000);
   add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(30,25));
}
string
query_recover() {
   return MASTER + ":" + query_wep_recover();
}
void
init_recover(string arg) {
   init_wep_recover(arg);
}
