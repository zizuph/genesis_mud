inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"

void
create_gems()
{
    config_gems("opal", "opals", "iridescent", 864, 
        GEM_SOMEWHAT_RARE, 3, 5);
    set_long("@@default_gem_long@@  There are few gemstones "+
        "to rival the opal for beauty and variety in appearance "+
        "and colour. There are no two stones alike, though the "+
        "most outstanding characteristic of this unqiue gem is "+
        "the unusual, intense display of colours flashing out "+
        "like mini-rainbows in even the poorest light.\n");
}


