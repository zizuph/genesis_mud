// filename:        /d/Avenir/common/holm/cape.c    
// creator(s):      Lilith  01/21/97
// revision(s):
// purpose:         Something for the Hunters to wear     
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/inherit/cloth_arm";
#include "/d/Avenir/common/holm/holm.h"
#include "/sys/wa_types.h"

void
create_armour()
{
    set_name("alb");
    add_name("robe");
    set_short("ankle-length white alb");
    add_adj(({"ankle-length", "white"}));
    set_long ("This alb is made of white webcloth."+
        "It is a lightweight ankle-length tunic with long sleeves "+
        "and a hood, it falls gracefully from the neck and shoulders "+
        "leaving the legs unencumbered.\n");
    set_at(A_ROBE);
    set_ac(3 + random (3));
}


