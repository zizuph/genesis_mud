inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"

void
create_gems()
{
    config_gems("pyrite", "pyrites", "golden", 12, 
        GEM_EXTREMELY_COMMON, 46, 109);
    add_name("fools gold");
    add_adj("fools");
    set_long("@@default_gem_long@@  This mineral has a "+
        "crystalline structure but the metallic sheen of gold, "+
        "and has been a source of consternation amongst amateur "+ 
        "miners for millennia. Known as both pyrite and fools "+
        "gold, it is rather brittle and thus is rarely used as "+
        "a gemstone.\n");
}
