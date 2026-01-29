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
        "   A brilliant white, platinum chain necklace.\n");
    add_item(({"necklace","platinum chain necklace","chain necklace"}),
        "A chain necklace made of platinum. In the center, a symbol of "+
        "a dark sun hangs.\n");
    add_prop(OBJ_M_NO_GET,"A strange magical force is protecting it.\n");
    add_item(({"third plaque","3rd plaque","plaque 3","plaques"}),
        "This once belonged to Kabal, "+
        "given to him by Thanar.\n");
}

