inherit "/d/Gondor/common/battle/battle.c";

#include "/d/Gondor/common/battle/battle.h"

void
create_battle()
{
    set_battle_name("test-battle");
    add_room("/d/Gondor/ithilien/osgiliath/eosg2.c",
        ({ 1, "uruk", 3, "orc", 4, "goblin" }));
    set_rq_stage(RQ_GANDALF_IN_BAGEND);
    set_extra_time(10);
}

void
battle_function()
{
    log_file("battles", ctime(time()) + " " + query_battle_name() +
        " battle run.\n");
}
