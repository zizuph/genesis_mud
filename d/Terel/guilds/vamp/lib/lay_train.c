
#include "../guild.h"

inherit LIB_DIR+"train_ob";

#include <ss_types.h>


public void create_object()
{
    ::create_object();
    
    sk_add_train(VAMP_SKILL_BITE, "bite an opponent", "savage", 100, 100);

    sk_add_train(SS_AWARENESS, "perceive", "awareness", 0, 60);
    sk_add_train(SS_TRACKING, "track your prey", "tracking", 0, 60);

    sk_add_train(SS_LOC_SENSE, "track your location", 
                              "location sense", 0, 60);
    sk_add_train(SS_APPR_MON, "appraise your enemy", 
                              "appraise monster", 0, 60);

}

public int
sk_hook_allow_train(object who, string str, string verb)
{
    return who->query_bloodguard();
}
