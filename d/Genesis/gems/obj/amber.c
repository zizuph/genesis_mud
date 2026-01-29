inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"

void
create_gems()
{
    config_gems("amber", "ambers", "yellow", 144, 
        GEM_COMMON, 4, 7);
    set_long("@@default_gem_long@@  This piece of amber is "+
        "fossilized tree sap. Its use as a gemstone stems from "+
        "the odd inclusions which lend a unique character to "+
        "the translucent yellow resin. It is very easily cut "+
        "and very lightweight.\n");

}
