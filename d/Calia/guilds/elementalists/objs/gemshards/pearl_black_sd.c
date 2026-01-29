inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"
#include <stdproperties.h>

void
create_gems()
{
    config_gems("shard of pearl", "shards of pearl", "black", 173, 
        GEM_RARE, 2, 4);
    set_long("@@default_gem_long@@  The shard is from a bead as black "+
        "as the underdark. It is lustrous and perfectly "+
        "round, making it a very rare and very expensive "+
        "pearl.\n");
    add_name("shard");
    add_pname("shards");
    add_name("pearl");
    add_pname("pearls");
    add_name("pearl_shard");
    add_name("pearl shard");
    add_name("shard_pearl");
    add_pname("pearl shards");
    add_name("black_pearl_shard");
    add_prop(OBJ_I_NO_SELL, "You can't sell a shattered gem.\n");

    // Need to properly set the gem name
    gem_name = "black pearl";
}


