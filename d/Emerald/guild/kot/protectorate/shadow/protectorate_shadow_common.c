#include "../guild.h"

inherit KOT_SHADOW_DIR + "kot_shadow_common";

#include <ss_types.h>
#include <wa_types.h>
#include "/d/Emerald/sys/skills.h"

mixed
protectorate_wield(object wep, object wielder)
{
#ifdef SS_PROT_2H_SWORD
    if ((wep->query_wt() == SS_WEP_SWORD) &&
        (wep->query_hands() == W_BOTH))
    {
        int extra = ftoi(itof(wielder->query_skill(SS_PROT_2H_SWORD)) * 
            TWOH_SWORD_WEIGHT);
        mixed ret;

        if (extra)
        {
            wielder->set_skill_extra(SS_WEP_SWORD,
                wielder->query_skill_extra(SS_WEP_SWORD) + extra);

            ret = wielder->wield(wep);

            wielder->set_skill_extra(SS_WEP_SWORD,
                wielder->query_skill_extra(SS_WEP_SWORD) - extra);

            return ret;
        }
    }
#endif

    return wielder->wield(wep);
}

int
query_kot_protectorate_member()
{
    return 1;
}
