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
        "   An orange globe.\n");
    add_item(({"globe","orange globe"}),"This is a large, round "+
        "ball made of strange, orange colored glass. It is perfectly "+
        "sphericle, and has no scratches on it.\n");
    add_prop(OBJ_M_NO_GET,"A strange magical force is protecting it.\n");
    add_item(({"second plaque","2nd plaque","plaque 2","plaques"}),
        "This is an ancient, magical "+
        "relic of the Sun elves. It is said to have been used by the "+
        "magical elf wizards in their unholy rites when they populated the "+
        "lands.\n");
}

