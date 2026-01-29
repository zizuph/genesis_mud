inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"
#include <stdproperties.h>

void
create_gems()
{
    config_gems("shard of alexandrite", "shards of alexandrite", "vivid", 720,
        GEM_VERY_RARE, 1, 2);
    set_long("@@default_gem_long@@ The shard is from a rare "+
        "and unique variety of chrysoberyl. When viewed "+
        "in natural sunlight, it appears green to the eye, "+
        "but in incandescent light is red. It is one of the "+
        "most sought-after and expensive of gemstones.\n");
    add_name("shard");
    add_pname("shards");
    add_name("alexandrite");
    add_pname("alexandrites");
    add_name("alexandrite shard");
    add_pname("alexandrite shards");
    add_name("alexandrite_shard");
    add_name("shard_alexandrite");
    add_prop(OBJ_I_NO_SELL, "You can't sell a shattered gem.\n");

    // Need to properly set the gem name
    gem_name = "alexandrite";
}


