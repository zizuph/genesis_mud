inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"
#include <stdproperties.h>

void
create_gems()
{
    config_gems("shard of ruby", "shards of ruby", "red", 576,
        GEM_VERY_RARE, 1, 2);
    set_long("@@default_gem_long@@ The shard is from a red "+
        "variety of the mineral corundum. Though it "+
        "may range in colour from a yellowish red to "+
        "a deep red-violet, the most highly valued "+
        "colour is a pure spectral red with the faintest "+
        "hint of blue. It is a very brilliant, hard, and "+
        "durable stone.\n");
    add_name("shard");
    add_pname("shards");
    add_name("ruby");
    add_pname("rubies");
    add_name("ruby shard");
    add_pname("ruby shards");
    add_name("ruby_shard");
    add_name("shard_ruby");
    add_prop(OBJ_I_NO_SELL, "You can't sell a shattered gem.\n");

    // Need to properly set the gem name
    gem_name = "ruby";
}


