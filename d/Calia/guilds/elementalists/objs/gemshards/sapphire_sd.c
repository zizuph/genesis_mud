inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"
#include <stdproperties.h>

void
create_gems()
{
    config_gems("shard of sapphire", "shards of sapphire", "blue", 390,
        GEM_RARE, 2, 4);
    set_long("@@default_gem_long@@ The shard is from a gem "+
        "of great value, brilliance, and durability. The "+
        "finest sapphires are the blue variety, clear and "+
        "neither too pale nor too dark. It also comes in "+
        "other colours, especially yellow and pink, and "+
        "some beautiful shades of green. Like ruby, it is "+
        "a variety of corundum, second only to diamond in "+
        "hardness.\n");
    add_name("shard");
    add_pname("shards");
    add_name("sapphire");
    add_pname("sapphires");
    add_name("sapphire shard");
    add_pname("sapphire shards");
    add_name("sapphire_shard");
    add_name("shard_sapphire");
    add_prop(OBJ_I_NO_SELL, "You can't sell a shattered gem.\n");

    // Need to properly set the gem name
    gem_name = "sapphire";
}


