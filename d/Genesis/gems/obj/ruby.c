inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"

void
create_gems()
{
    config_gems("ruby", "rubies", "red", 3456, 
        GEM_VERY_RARE, 1, 2);
    set_long("@@default_gem_long@@  Ruby is the red "+
        "variety of the mineral corundum.  Though it "+
        "may range in colour from a yellowish red to "+
        "a deep red-violet, the most highly valued "+
        "colour is a pure spectral red with the faintest "+
        "hint of blue. It is a very brilliant, hard, and "+
        "durable stone.\n");
}


