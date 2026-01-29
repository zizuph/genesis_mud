inherit "/std/armour";
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>

create_armour()
{
   set_name("breastplate");
   set_adj("shimmering");
   add_adj("crystal");
   set_short("shimmering crystal breastplate");
   set_long("A breastplate unlike one you have ever seen, it seems "
	+"to be made of a crystal that shimmers with rainbow colors "
	+"in the light.  You are unsure of where something like this "
	+"could have been created, but it is surely a work of art.\n");
   set_ac(45);
   set_at(A_BODY);
   add_prop(MAGIC_AM_MAGIC, ({ 20, "life" }));
   add_prop(MAGIC_AM_ID_INFO, ({"This breastplate makes the wearer "
	+"more resistant to magical attacks.\n",5,
	}));
   add_prop(OBJ_S_WIZINFO, "When worn, this breastplate confers upon "
	+"the wearer a 95% resistance to magic.\n");
   add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
   set_wf(TO);
}

public mixed
wear(object wep)
{
    object wr = TP;
  wr->add_prop(MAGIC_I_RES_MAGIC,wr->query_prop(MAGIC_I_RES_MAGIC) + 35);
   wr->catch_tell("You wear the crystal breastplate.\n");
    return 1;
}

public mixed
remove(object wep)
{
    object wr = TO->query_worn();
    wr->catch_tell("You unbuckle the breastplate and remove it.\n");
  wr->add_prop(MAGIC_I_RES_MAGIC,wr->query_prop(MAGIC_I_RES_MAGIC) - 35);
    return 1;
}


