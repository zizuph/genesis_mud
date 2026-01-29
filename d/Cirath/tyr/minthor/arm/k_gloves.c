inherit "/std/armour";
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>

create_armour()
{
   set_name("gloves");
   set_adj("black");
   add_adj("supple");
   set_short("black supple gloves");
   set_long("This is a pair of black gloves made of some material "
	+"that makes them incredibly soft and supple.  The feel very "
	+"thin, and probably would fit like a second skin.\n");
   set_ac(25);
   set_am(({1,1,0}));
    set_at(A_HANDS);
   add_prop(MAGIC_AM_MAGIC, ({ 20, "life" }));
   add_prop(MAGIC_AM_ID_INFO, ({"These gloves make the wearer more "
	+"dextrous and aid him in some abilities and skills.\n",5,
	}));
   add_prop(OBJ_S_WIZINFO, "The gloves give the wearer an extra 20 "
	+"points in dex and +10 to both the climb and pick pockets "
	+"skill.\n");
   add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
   set_wf(TO);
}

public mixed
wear(object wep)
{
    object wr = TP;
    wr->catch_tell("You slide your hands into the gloves.\n");
    wr->set_skill_extra(SS_CLIMB,  TP->query_skill_extra(SS_CLIMB) + 10);
    wr->set_skill_extra(SS_PICK_POCKET,  TP->query_skill_extra(SS_PICK_POCKET) + 10);
    return 1;
}

public mixed
remove(object wep)
{
    object wr = TO->query_worn();
    wr->catch_tell("You pull the gloves on your hand.\n");
    wr->set_skill_extra(SS_CLIMB,  TP->query_skill_extra(SS_CLIMB) - 10);
    wr->set_skill_extra(SS_PICK_POCKET,  TP->query_skill_extra(SS_PICK_POCKET) - 10);
    return 1;
}


