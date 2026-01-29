inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"
#include <stdproperties.h>

void
create_gems()
{
    config_gems("shard of lapis lazuli", "shards of lapis lazuli", "blue", 58, 
        GEM_SOMEWHAT_RARE, 2, 3);
    set_long("@@default_gem_long@@  The shard is from a "+
        "semi-precious gemstone with a vivid blue hue. "+
        "It is opaque, with areas of lighter blue and "+
        "spider-silk fine veins of pyrite. In antiquity, "+
        "this stone was called sapphire.\n");
    
    add_name("shard");
    add_pname("shards");
    add_name("lapis lazuli");
    add_name("lapis lazuli shard");
    add_pname("lapis lazuli shards");
    add_pname("lapis lazulis");
    add_name("lapis_lazuli_shard");
    add_prop(OBJ_I_NO_SELL, "You can't sell a shattered gem.\n");

    // Need to properly set the gem name
    gem_name = "lapis lazuli";
}


