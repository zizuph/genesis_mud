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
        "   A crystal sculpture of an eagle.\n");
    add_item(({"crystal sculpture","sculpture"}),"A beautifully "+
        "crafted sculpture of an eagle. It is awsomely detailed, and you "+
        "can see every feather and claw on it. Its wings are spread apart "+
        "and it looks like it is ready to strike.\n");
    add_prop(OBJ_M_NO_GET,"A strange magical force is protecting it.\n");
    add_item(({"plaque","first plaque","plaque 1","plaque","plaques"}),
        "This was crafted by "+
        "Thunan Hammerstone, the leader of the dwarven kingdom when the "+
        "dwarves populated the lands. It was captured by Kabal, and kept "+
        "by him as a reminder of his trimuphent wars againts the dwarves.\n");
}

