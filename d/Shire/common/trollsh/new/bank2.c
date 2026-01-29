inherit "/d/Shire/std/room";

#include "/d/Shire/sys/defs.h"

void
create_shire_room()
{
    set_short("Within the Trollshaws");
    set_long("You stand within the western fringes of the "+
        "Trollshaws along the banks of the Hoarwell. It is "+
        "very muddy and your progress is slowed somewhat. "+
        "A small cove can be seen up ahead.\n");

    add_exit("/d/Shire/common/trollsh/new/bank","southwest",0,3);
    add_exit("/d/Shire/common/trollsh/new/bank3","northeast",0,3);
}
