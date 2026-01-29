inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"
#include <stdproperties.h>

void
create_gems()
{
    config_gems("shard of onyx", "shards of onyx", "black", 22, 
        GEM_SLIGHTLY_COMMON, 5, 9);
    set_long("@@default_gem_long@@  The shard is from a black variety "+
        "of chalcedony, often one solid colour, but usually "+
        "banded with white, red, or green chalcedony as well. "+
        "It is a lustrous, medium-hard stone, easily cut and "+
        "polished, but durable.\n");
    add_name("shard");
    add_pname("shards");
    add_name("onyx");
    add_pname("onyxes");
    add_name("onyx shard");
    add_pname("onyx shards");
    add_name("black_onyx_shard");
    add_prop(OBJ_I_NO_SELL, "You can't sell a shattered gem.\n");

    // Need to properly set the gem name
    gem_name = "onyx";
}

