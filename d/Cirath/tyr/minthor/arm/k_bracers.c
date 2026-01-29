inherit "/std/armour";
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>

create_armour()
{
   set_name("bracers");
   set_adj("studded");
   add_adj("leather");
   set_short("studded leather bracers");
   set_long("This set of studded leather bracers looks to have "
	+"studs made of adamantium or mithril.  The leather itself "
	+"is supple and soft, and they fit your forearms like a "
	+"second skin.  You can almost feel some sort of energy "
	+"flowing through the leather and into your body.\n");
   set_ac(35);
   set_am(({1,1,1}));
   set_at(A_ARMS);
   add_prop(MAGIC_AM_MAGIC, ({ 20, "life" }));
   add_prop(MAGIC_AM_ID_INFO, ({"This set of bracers enables the "
	+"wearer to move more quickly in combat and increases both "
	+"the attack and defensive skills of the wearer .\n",5,
	}));
   add_prop(OBJ_S_WIZINFO, "The bracers add 30 to LIVE_I_QUICKNESS, "
	+"as well as 15 to SS_2H_COMBAT and 20 to SS_PARRY.\n");
   add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
   set_wf(TO);
}

public mixed
wear(object wep)
{
    object wr = TP;
    wr->catch_tell("You fasten the studded leather bracers to your "
	+"forearms.\n");
    wr->set_skill_extra(SS_2H_COMBAT, TP->query_skill_extra(SS_2H_COMBAT) + 15);
    wr->set_skill_extra(SS_PARRY,  TP->query_skill_extra(SS_PARRY) + 20);
    wr->add_prop(LIVE_I_QUICKNESS,wr->query_prop(LIVE_I_QUICKNESS) + 15);
   wr->set_stat_extra(SS_DEX,15);
    return 1;
}

public mixed
remove(object wep)
{
    object wr = TO->query_worn();
    wr->catch_tell("You release the clasps on the bracers and remove them.\n");
    wr->set_skill_extra(SS_2H_COMBAT, TP->query_skill_extra(SS_2H_COMBAT) -15);
    wr->set_skill_extra(SS_PARRY,  TP->query_skill_extra(SS_PARRY) - 20);
    wr->add_prop(LIVE_I_QUICKNESS,wr->query_prop(LIVE_I_QUICKNESS) - 15);
   wr->set_base_stat(SS_DEX,wr->query_base_stat(SS_DEX) - 15);
    return 1;
}


