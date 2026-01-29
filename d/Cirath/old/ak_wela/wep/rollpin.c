inherit "/std/weapon.c";
#include "/sys/wa_types.h"
#include "defs.h"

create_weapon()
{
   set_name("rolling-pin");
   set_adj("marble");
   set_long("This is a marble rolling-pin. Although it is commonly "
	+"used while baking, you suspect it can make nasty damage to "
	+"someones head if used in battle.\n");
   add_name("club");
   set_hit(35);
   set_pen(20);
   set_hands(W_RIGHT);
   set_wt(W_CLUB);
   set_dt(W_BLUDGEON);
   add_prop(OBJ_I_WEIGHT,5000);
   add_prop(OBJ_I_VOLUME,3000);
   add_prop(OBJ_M_NO_SELL, "That is a rolling-pin, I won't buy that.\n");
}

