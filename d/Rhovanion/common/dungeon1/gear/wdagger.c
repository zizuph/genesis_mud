inherit "/std/weapon";
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
void
create_weapon() {
   set_name("dagger");
   set_adj("copper");
   set_adj("brilliant");
   set_long("This small dagger has a very ornate handle " +
      "with a solid copper pommel and blade.  The copper has " +
      "been polished to a brilliant gleam and is quite " +
      "pleasing to behold besides being quite sharp.\n");
   set_hit(20);
   set_pen(15);
   set_wt(W_KNIFE);
   set_dt(W_SLASH | W_IMPALE);
   set_hands(W_ANYH);
   add_prop(OBJ_I_WEIGHT, 1000);
   add_prop(OBJ_I_VOLUME,  500);
   add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(20,15));
}
string
query_recover() {
   return MASTER + ":" + query_wep_recover();
}
void
init_recover(string arg) {
   init_wep_recover(arg);
}
