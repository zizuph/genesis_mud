inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"

void
create_gems()
{
    config_gems("peridot", "peridots", "green", 369, 
        GEM_SOMEWHAT_RARE, 6, 13);
    add_name("olivine");
    set_long("@@default_gem_long@@  Peridot is a transparent "+
        "yellowish-green variety of olivine.  While not particularly " +
        "brilliant, it is rather easily faceted to display the " +
        "exceptional richness of its colour.\n");

}


