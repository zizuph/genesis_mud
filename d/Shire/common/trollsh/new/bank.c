inherit "/d/Shire/std/room";

#include "/d/Shire/sys/defs.h"

void
create_shire_room()
{
    set_short("Near the foundations of the Last Bridge");
    set_long("You stand on the eastern bank of the Hoarwell "+
        "near the western edge of the Trollshaws.\n");

    add_exit("/d/Shire/common/trollsh/new/bank2","northeast",0,1);
    add_exit("/d/Shire/eastroad/eastern/erb38","up",0,3);
}
