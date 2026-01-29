inherit "/std/receptacle";
inherit "/lib/store_support";
#include "/d/Kalad/defs.h"
/* by Antharanos */
void
create_container()
{
   set_name("sack");
   set_adj("fine");
   add_adj("silk");
   set_long("A wonderfully-woven sack made of satiny silk. From the intricate "+
      "merchant symbol on it, whomever owned it must have been quite "+
      "wealthy.\n");
   add_prop(CONT_I_WEIGHT,2000);
   add_prop(CONT_I_MAX_WEIGHT,102000);
   add_prop(CONT_I_REDUCE_WEIGHT,500);
   add_prop(CONT_I_VOLUME,3000);
   add_prop(CONT_I_MAX_VOLUME,103000);
   add_prop(CONT_I_REDUCE_VOLUME,500);
   add_prop(OBJ_M_NO_SELL, "@@check_contents");
   add_prop(OBJ_I_VALUE,180);
   add_prop(OBJ_S_WIZINFO, break_string("This sack is the store-room of "+
         "the wandering merchant. It reduces the weight and volume of stuff "+
         "placed inside to 20% of its original value. However if this sack leaves "+
         "the merchant, those special properties are removed.", 75) + "\n");
}
void
enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);
   store_update(ob);
}
void
leave_env(object from, object to)
{
   ::leave_env(from, to);
   if (from && from->id("_wandering_merchant"))
      {
      remove_prop(CONT_I_REDUCE_VOLUME);
      remove_prop(CONT_I_REDUCE_WEIGHT);
      add_prop(CONT_I_CLOSED,1);
   }
}
mixed
check_contents()
{
   if(sizeof(all_inventory()))
      {
      return "You cannot sell the sack because it is not empty.\n";
   }
   return 0;
}
