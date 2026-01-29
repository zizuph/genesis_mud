//   Added keepability functionality   -Igneous

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <formulas.h>

inherit BASE_ARMOUR;
inherit "/lib/keep";

object wearer;

CONSTRUCT_ARMOUR
{
   set_name( ({"armour", "hauberk"}) );
   set_short("chain hauberk");
   set_adj( ({ "chain" }) );
   set_long("This is a heavy chain hauberk which can be worn like a robe.\n");
   set_ac( 19 );
   set_at( A_ROBE );
   set_am( ({ 2, 2, -4}) );
   set_af( this_object() );
   
   add_prop(OBJ_I_WEIGHT, 6700); /* 6.7 kg */
   add_prop(OBJ_I_VALUE,  7*12*12); /* 2 plats */
   add_prop(OBJ_I_VOLUME, 1300);
   add_prop(MAGIC_AM_MAGIC, ({ 30, "enchantment" }));
   add_prop(MAGIC_AM_ID_INFO,
      ({
            "The chain hauberk seems magically enchanted.\n", 1,
            "It resists acids quite well.\n", 50
       }) );
   
   add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
}

int *
query_slots()
{
   return ({ A_ROBE });
}

int *
query_shield_slots()
{
   return ({ A_BODY, A_LEGS, A_L_ARM, A_R_ARM });
}

int query_magic_protection(mixed prop, object for_who)
{
   if (for_who == wearer) 
      if (prop == MAGIC_I_RES_ACID)
      return 40 + random(20);
   else
      return 0;
   else
      return ::query_magic_protection(prop, for_who);
}

wear(object to)
{
   wearer = TP;
   wearer->add_magic_effect();
}

remove(object to)
{
   wearer->remove_magic_effect();
   wearer = 0;
}

string
query_recover()
{
   return MASTER+":"+ query_arm_recover() + query_keep_recover();
}

void
init_recover(string arg)
{
   init_arm_recover(arg);
   
   init_keep_recover(arg);
}
