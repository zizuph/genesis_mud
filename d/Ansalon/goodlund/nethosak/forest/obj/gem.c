inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"

void
create_gems()
{
    config_gems("ruby", "rubies", "transparent", 0, 
        GEM_VERY_RARE, 0, 0); 
    set_name("_ansalon_magic_gem_");    set_long("This is a small transparent ruby. Though the "+
             "color may range from a yellowish red to a deep "+
             "red-voilet, this one seems to be completely "+
             "transparent. The only thing that gives this "+
             "gem a bit of color is the bright blue center "+
             "that sends bright rays of blue light.\n"); 

}

