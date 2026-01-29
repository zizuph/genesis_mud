// file name:        /d/Avenir/common/obj/gems/fire_opal.c
// creator(s):       Lilith, Jan 2000
// revisions:
// purpose:         Sacred to Sair. She is always depicted with fire-opals for eyes.
// note:           
// bug(s):
// to-do:
// revisions:
//    Lucius Dec 2007: Gave more realistic weight/volume.

/*
 * Renamed to /d/Genesis/gems/obj/opal_fire.c
 *
 * This way the gem can be used in the AoE-eggs, too.
 *
 * Mercade, August 14, 2002
 */

inherit "/d/Genesis/gems/gem";

#include "/d/Genesis/gems/gem.h"
#include "/d/Avenir/include/deities.h"

void
create_gems()
{
    config_gems("opal", "opals", "fire", 1100, 
        GEM_RARE, 5, 5);
    set_long("@@default_gem_long@@ This is a "+
        "rare stone of unique red-gold colouration that "+
        "glimmers and flashes in even the poorest light.  "+
        "It is rather large for an opal of such beauty and "+
        "purity, inspiring awe in the minds of those who "+
        "have an appreciation for gemstones.  This gem "+
        "would appear to have formed naturally into "+
        "a perfectly three-dimensional octagon. Extremely "+
        "rare, all such gems are considered sacred to Sair.\n");

    add_prop(SAIR_OFFERING, 1);   
}

