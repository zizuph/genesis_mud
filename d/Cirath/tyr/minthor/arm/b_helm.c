inherit "/std/armour";
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>

create_armour()
{
   set_name("helm");
   set_adj("bone");
   add_adj("winged");
   set_short("winged bone helm");
   set_long("This helm is beautiful.  Apparently crafted from a "
	+"combination of bone and hide, it is very lightweight, yet "
	+"seems to offer good protection.  It has bone wings tipped "
	+"with black feathers projecting upwards at 45 degree angles "
	+"on each side of the head.  It also come down over the eyes "
	+"and nose giving added protection.\n");
   set_ac(30);
   set_am(({0,4,4}));
   set_at(A_HEAD);
   add_prop(MAGIC_AM_MAGIC, ({ 40, "life" }));
   add_prop(MAGIC_AM_ID_INFO, ({"The helm is enchanted with life "
	+"magic, allowing its wearer to see in the dark.\n",5,
	}));
   add_prop(OBJ_S_WIZINFO, "When worn, the helm gives the wearer the "
   +"LIVE_I_SEE_DARK property at strength 5.\n");
   add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
   add_prop(OBJ_I_WEIGHT,10);
   add_prop(OBJ_I_VOLUME,200);
   add_prop(OBJ_I_VALUE,5000);
   set_wf(TO);
   may_not_recover(0);
}


public mixed
wear(object wep)
{
    object wr = TP;
    wr->catch_tell("You place the helm upon your head.\n");
   wr->add_prop(LIVE_I_SEE_DARK, 3);
   wr->add_mana(-300);
   return 0;
}

public mixed
remove(object wep)
{
   object wr = TO->query_worn();
    wr->catch_tell("You lift the helm from your brow.\n");
   return 0;
}


