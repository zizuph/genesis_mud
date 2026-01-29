inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"

void
create_gems()
{
    config_gems("jade", "jades", "green", 576, 
        GEM_SOMEWHAT_RARE, 40, 62);
    set_long("@@default_gem_long@@  The term 'jade' is "+
        "applied to two different minerals with nearly "+
        "identical appearance and properties. Jade is "+
        "fairly soft and yet quite durable, making it "+
        "useful in the carving of figurines and jewelry. "+
        "It ranges from semi-translucent to opaque and "+
        "occurs in a wide range of colours, usually shades "+
        "of green or violet.\n");
}


