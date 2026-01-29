inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"
#include <stdproperties.h>

void
create_gems()
{
    config_gems("shard of bloodstone", "shards of bloodstone", "shining", 44, 
        GEM_SLIGHTLY_RARE, 3, 5);
    set_long("@@default_gem_long@@  The shard is from a green "+
        "variety of chalcedony spotted with tear-shaped "+
        "drops of red jasper. The depth and lustre of the "+
        "stone makes it appear that blood is welling up "+
        "from within, which is the source of its name. It "+
        "is a lustrous, medium-hard stone, easily cut and "+
        "polished, but durable. What makes this particular "+
        "specimen unusual is that it is fairly large, about "+
        "the size of a small plum.\n");
    add_name("shard");
    add_pname("shards");
    add_name("bloodstone");
    add_pname("bloodstones");
    add_name("bloodstone shard");
    add_pname("bloodstone shards");
    add_name("bloodstone_shard");
    add_prop(OBJ_I_NO_SELL, "You can't sell a shattered gem.\n");

    // Need to properly set the gem name
    gem_name = "bloodstone";
}


