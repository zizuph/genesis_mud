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
        "   Two giant ruby rings.\n");
    add_item(({"rings","ruby rings"}),"Each ring is made out of "+
        "platinum, and a large ruby is placed in the center of them. "+
        "The rubies sparkle with an inner light.\n");
    add_prop(OBJ_M_NO_GET,"A strange magical force is protecting it.\n");
    add_item(({"fourth plaque","4th plaque","plaque 4","plaques"}),
        "These rings were captured "+
        "by Kabal when he was in battle with the foul dark elves of "+
        "Undraeth. They beloned to the two mightiest generals of the "+
        "Drow armies, and were taken when Kabal and Talen invaded and "+
        "killed them.\n");
}

