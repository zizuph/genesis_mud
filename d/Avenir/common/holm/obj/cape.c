// filename:        /d/Avenir/common/holm/cape.c    
// creator(s):      Lilith  01/21/97
// revision(s):
// purpose:         Something for the Hunters to wear     
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/inherit/cloth_arm";
#include "/d/Avenir/common/holm/holm.h"
#include <wa_types.h>

void
create_armour()
{
    set_name("cape");
    add_name("robe");
    set_short("short white cape");
    add_adj(({"short", "white"}));
    set_long ("This cape is made of white webcloth. It fastens at "+
        "the neck and falls loosely from the shoulders to waist-"+
        "height, leaving the legs unencumbered. It is both elegant "+
        "and functional.\n");
    set_at(A_ROBE);
    set_ac(3 + random (3));
}

