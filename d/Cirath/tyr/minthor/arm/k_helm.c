inherit "/std/armour";
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>

create_armour()
{
   set_name("helm");
   set_adj("deathmask");
   set_short("deathmask helm");
   set_long("A grinning face of bone and gore graces the front "
	+"of this helm.  Horribly misshapen features, open mouth "
	+"hanging chunks of flesh adorn the helm.  It looks to be "
	+"actually made of some form of metal, with the skull on "
	+"the front attached by some magical means.\n");
   set_ac(25);
    set_at(A_HEAD);
   add_prop(MAGIC_AM_MAGIC, ({ 20, "death" }));
   add_prop(MAGIC_AM_ID_INFO, ({"This helm can grant the wearer to "
	+"see the unseen and generally recognize his surroundings "
	+"better.\n",5,
	}));
   add_prop(OBJ_S_WIZINFO, "The helm adds the prop LIVE_I_SEE_INVIS "
	+"at strength 5 to the wearer along with +20 to awareness.\n");
   add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
   set_wf(TO);
}

public mixed
wear(object wep)
{
    object wr = TP;
    wr->catch_tell("You place the helm on your head.\n");
    wr->set_skill_extra(SS_AWARENESS,  TP->query_skill_extra(SS_AWARENESS) + 20);
  wr->add_prop(LIVE_I_SEE_INVIS,wr->query_prop(LIVE_I_SEE_INVIS) + 1);
    return 1;
}

public mixed
remove(object wep)
{
    object wr = TO->query_worn();
    wr->catch_tell("You lift the helm from your head.\n");
    wr->set_skill_extra(SS_AWARENESS,  TP->query_skill_extra(SS_AWARENESS) - 20);
  wr->add_prop(LIVE_I_SEE_INVIS,wr->query_prop(LIVE_I_SEE_INVIS) - 1);
    return 1;
}


