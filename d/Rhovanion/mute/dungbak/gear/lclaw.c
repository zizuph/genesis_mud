inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
void
create_weapon() {
   set_name("claw");
   set_adj("bladed");
   set_adj("steel");
   set_long("This weapon is worn similarly to a gauntlet, but " +
      "is far more deadly.  It is constructed of a fine leather " +
      "glove, very thick, with harder strips of black leather " +
      "reinforcing its rigidity and strength.  The fingers are " +
      "extended with razor sharp, steel claws which appear to be " +
      "capable of slicing through even the strongest of hides.\n" +
      "If you can use a knife you just might know how to use this.\n");
   set_hit(20);
   set_pen(30);
   set_wt(W_KNIFE);
   set_dt(W_SLASH);
   set_hands(W_LEFT);
   add_prop(OBJ_I_WEIGHT, 1300);
   add_prop(OBJ_I_VOLUME, 1500);
}
string
query_recover() {
   return MASTER + ":" + query_wep_recover();
}
void
init_recover(string arg) {
   init_wep_recover(arg);
}
