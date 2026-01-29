inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"
#include <stdproperties.h>

void
create_gems()
{
    config_gems("shard of chalcedony", "shards of chalcedony", "striped", 15, 
        GEM_COMMON, 4, 7);
    set_long("@@default_gem_long@@  The shard is from a "+
        "variety of banded quartz. It is usally opaque and "+
        "banded with a variety of colours that create a "+
        "beautiful surreal landscape for the eye. It is a "+
        "lustrous, medium-hard stone, easily cut and polished, "+
        "but durable.\n");
    add_name("shard");
    add_pname("shards");
    add_name("chalcedony");
    add_pname("chalcedonies");
    add_name("chalcedony_shard");
    add_name("chalcedony shard");
    add_pname("chalcedony shards");
    add_name("shard_chalcedony");
    add_prop(OBJ_I_NO_SELL, "You can't sell a shattered gem.\n");

    // Need to properly set the gem name
    gem_name = "chalcedony";
}
