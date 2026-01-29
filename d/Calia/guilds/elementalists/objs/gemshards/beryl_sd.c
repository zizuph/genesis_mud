inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"
#include <stdproperties.h>

void
create_gems()
{
    config_gems("shard of beryl", "shards of beryl", "yellow", 40, 
        GEM_SLIGHTLY_RARE, 3, 5);
    set_long("@@default_gem_long@@ The shard is from a lustrous, "+
        "transparent family of gemstones, including emerald "+
        "and aquamarine. It is colourless in its pure form, "+
        "but is also found in green, yellow, pink, and blue. "+
        "The rarest and most expensive is the red beryl.\n");
    add_name("shard");
    add_pname("shards");
    add_name("beryl");
    add_name("beryl shard");
    add_name("beryl shards");
    add_pname("beryls");
    add_name("beryl_shard");
    add_prop(OBJ_I_NO_SELL, "You can't sell a shattered gem.\n");

    // Need to properly set the gem name
    gem_name = "beryl";
}


