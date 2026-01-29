inherit "/std/object";
#include "/d/Kalad/defs.h"
/* sarr */

void
create_object()
{
    set_name("case");
    set_adj("glass");
    set_short("glass case");
    set_long("This is a wooden table with a glass case over it. "+
        "Underneath the glass you see an artifact being displayed. A"+
        " silver plaque is placed under it.\n"+
        "The glass case contains:\n"+
        "   An emerald sword.\n");
    add_item(({"sword","emerald sword"}),"A smooth, emerald-bladed "+
        "longsword. The hilt is made out of pure silver, and it looks "+
        "polished and new. The hilt has black leather strips around it "+
        "for a better grip. The blade is made out of what looks like "+
        "pure emerald. You can see the light reflecting off its surface.\n");
    add_prop(OBJ_M_NO_GET,"A strange magical force is protecting it.\n");
    add_item(({"fifth plaque","5th plaque","plaque 5","plaques"}),
        "The sword of Talen"+
        "Darkstorm, Lieutenant General of Kabal's elite. He was the right "+
        "hand man of Kabal, and helped found the city.\n");
}

