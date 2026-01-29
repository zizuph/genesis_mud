inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"
#include <stdproperties.h>

void
create_gems()
{
    config_gems("shard of amethyst", "shards of amethyst", "purple", 43, 
        GEM_SLIGHTLY_RARE, 3, 5);
    set_long("@@default_gem_long@@ The shard is from a trans"+
        "parent purple variety of quartz. It is available "+
        "in shades from lavender to royal purple. It is "+
        "relatively hard, fairly brilliant, and overall a "+
        "good, versatile gemstone. This particular specimen "+
        "is both fairly large and free of occlusions.\n");
    add_name("shard");
    add_pname("shards");
    add_name("amethyst");
    add_pname("amethysts");
    add_name("amethyst shard");
    add_pname("amethyst shards");
    add_name("amethyst_shard");
    add_prop(OBJ_I_NO_SELL, "You can't sell a shattered gem.\n");

    // Need to properly set the gem name
    gem_name = "amethyst";
}


