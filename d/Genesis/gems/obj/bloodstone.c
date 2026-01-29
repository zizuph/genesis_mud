inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"

void
create_gems()
{
    config_gems("bloodstone", "bloodstones", "shining", 432, 
        GEM_SLIGHTLY_RARE, 30, 44);
    set_long("@@default_gem_long@@  Bloodstone is a green "+
        "variety of chalcedony spotted with tear-shaped "+
        "drops of red jasper. The depth and lustre of the "+
        "stone makes it appear that blood is welling up "+
        "from within, which is the source of its name. It "+
        "is a lustrous, medium-hard stone, easily cut and "+
        "polished, but durable. What makes this particular "+
        "specimen unusual is that it is fairly large, about "+
        "the size of a small plum.\n");

}


