inherit "/std/armour";
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>

create_armour()
{
   set_name("boots");
   set_adj("grey");
   add_adj("thin-soled");
   set_short("grey thin-soled boots");
   set_long("Made of some form of animal hide, these grey boots "
	+"are soft to the touch and their thin-soles help the "
	+"wearer to move quickly and silently when others would "
	+"be unable to.\n");
   set_ac(20);
   set_am(({0,1,1}));
   set_at(A_FEET);
   add_prop(MAGIC_AM_MAGIC, ({ 20, "life" }));
   add_prop(MAGIC_AM_ID_INFO, ({"The helm is enchanted with  "
	+"transmutation magic, allowing the wearer to move more "
	+"quickly and sneak effectively.\n",5,
	}));
   add_prop(OBJ_S_WIZINFO, "When worn, the boots gives the wearer the "
	+"LIVE_I_QUICKNESS property at strength 50 and add 10 to the "
	+"wearer's sneak.\n");
   add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
   add_prop(OBJ_I_WEIGHT,10);
   add_prop(OBJ_I_VOLUME,200);
    set_wf(TO);
}

public mixed
wear(object wep)
{
    object wr = TP;
    wr->set_skill_extra(SS_SNEAK, TP->query_skill_extra(SS_SNEAK) + 10);
    wr->catch_tell("You slide your feet into the boots.\n");
   wr->add_prop(LIVE_I_QUICKNESS,wr->query_prop(LIVE_I_QUICKNESS) + 25);
    return 1;
}

public mixed
remove(object wep)
{
    object wr = TO->query_worn();
    wr->catch_tell("You take the grey boots from your feet.\n");
    wr->set_skill_extra(SS_SNEAK, TP->query_skill_extra(SS_SNEAK) -10);
  wr->add_prop(LIVE_I_QUICKNESS,wr->query_prop(LIVE_I_QUICKNESS) - 25);
    return 1;
}


