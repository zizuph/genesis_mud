inherit "/std/armour";
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>

create_armour()
{
   set_name("greaves");
   set_adj("steel");
   add_adj("plate");
    set_short("steel plate greaves");
   set_long("These greaves are a part of a suit of steel plate mail. "
	+"They have intricate damasked designs on them, and have been "
	+"designed to be incredibly light. Steel is extremely rare in "
	+"Athas, so these must be worth a fortune there.  When worn "
	+"they make you feel stronger.\n");
    set_ac(35);
   set_am(({-2,2,1}));
   set_at(A_LEGS);
   add_prop(MAGIC_AM_MAGIC, ({ 20, "life" }));
   add_prop(MAGIC_AM_ID_INFO, ({"These greaves are enchanted with "
   +"life magic, granting the wearer a higher strength.\n",5,
	}));
   add_prop(OBJ_S_WIZINFO, "When worn, the greaves increase the "
   +"wearer's strength by 25.\n");
   add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
   set_wf(TO);
}

public mixed
wear(object wep)
{
    object wr = TP;
    wr->catch_tell("You strap the greaves to your legs.\n");
   wr->set_stat_extra(SS_STR,15);
    return 1;
}

public mixed
remove(object wep)
{
   object wr = TO->query_worn();
    wr->catch_tell("You release the straps and remove the greaves.\n");
   wr->set_base_stat(SS_STR,wr->query_base_stat(SS_STR) - 15);
    return 1;
}



