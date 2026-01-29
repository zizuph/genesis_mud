// file name:        /d/Avenir/common/obj/gems/sea_agate.c
// creator(s):       Lilith, Jan 2000
// revisions:
// purpose:         Seamonster treasure
// note:           
// bug(s):
// to-do:
inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"
#include "/d/Avenir/include/deities.h"

void
create_gems()
{
    config_gems("agate", "agates", "sea", 1728, 
        GEM_RARE, 10, 15);
    set_long("@@default_gem_long@@  This rare agate "+
        "swirls with the colours of the sea: blue-green, grey, "+
        "and violet.  This stone is mostly translucent, with "+
        "opaque white inclusions that look like the foamy "+
        "crests of waves.\n  It sings to you of the mysteries "+
        "of the Sea of Sybarus, from whence it came.\n");

    add_prop(HIZARBIN_OFFERING, 1);
    add_prop(SAIR_OFFERING, 1);   
}

