inherit "/d/Shire/std/room";

#include "/d/Shire/sys/defs.h"

void
create_shire_room()
{
    set_short("By a small cove in the Trollshaws");
    set_long("Water gently laps upon the shore of this well "+
        "protected cove. The river banks rise high above "+
        "your head to the southeast and north. Atop these "+
        "banks, as if a great fence, stand the towering trees "+
        "of the Trollshaws. A large cave can be seen in "+
        "the wall of the southeastern bank.\n");

    add_exit("/d/Shire/common/trollsh/new/bank2","southwest",0,3);
    add_exit("/d/Shire/common/trollsh/new/cove","southeast",0,1);
}
