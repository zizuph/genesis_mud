inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"
#include <stdproperties.h>

void
create_gems()
{
    config_gems("shard of opal", "shards of opal", "iridescent", 87, 
        GEM_SOMEWHAT_RARE, 3, 5);
    set_long("@@default_gem_long@@  The shard is from a gemstone, "+
        "which few rival for beauty and variety in appearance "+
        "and colour. There are no two stones alike, though the "+
        "most outstanding characteristic of this unqiue gem is "+
        "the unusual, intense display of colours flashing out "+
        "like mini-rainbows in even the poorest light.\n");
    add_name("shard");
    add_pname("shards");
    add_name("opal");
    add_pname("opals");
    add_name("opal shard");
    add_name("opal shards");
    add_name("shard_opal");
    add_name("iridescent_opal_shard");
    add_prop(OBJ_I_NO_SELL, "You can't sell a shattered gem.\n");

    // Need to properly set the gem name
    gem_name = "opal";
}


