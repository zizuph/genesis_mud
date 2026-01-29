// -*-C++-*-
// file name:    yark short bow
// creator(s):   Lilith  Jun 2004
// last update:
// purpose:      Something to help out the fledgling archers 
// note:
// bug(s):
// to-do: 

inherit "/std/bow";

#include <stdproperties.h>
#include "/d/Avenir/include/defs.h"

void
create_bow()
{
    set_short("yarkwood short bow");
    add_name(({"short bow", "bow"}));
    set_adj(({"yark", "yarkwood", "short"}));
    set_long("This is a short bow, so called because it is less than "+
        "half the height of the bowyer who uses it. It is ideally "+
        "suited for mounted combat, for use while kneeling, and in "+
        "close melee combat where the ability to swiftly draw and "+
        "fire arrows is necessary. It is made from the wood of the "+
        "yark bush native to parts of the Sybarun Isles, a wood "+
        "known both for its tensile strength and flexibility, as well "+
        "as the nasty thorns which grow in a spiral around the limbs. "+
        "The thorns have been removed from the limb from which this "+
        "bow was made, leaving behind an interesting spiral pattern.\n");
    add_item(({"wood", "yarkwood", "yark", "yark wood"}),
        "The wood is from the yark bush that is native to parts of "+
        "the Sybarun Isles. It is favoured for clubs because it is "+
        "lightweight and thorny, and for bows because it is flexible "+
        "and strong.\n");
    add_item(({"pattern", "spiral", "spiral pattern"}),
        "The spiral pattern results from the removal of the thorns "+
        "that normally grow on this wood.\n");

    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 1500);
    set_hit(38 + random(3));
    set_pen(37 + random(4));  
    seteuid(getuid(TO));
}
