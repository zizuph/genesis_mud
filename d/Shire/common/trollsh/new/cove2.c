inherit "/d/Shire/std/room";

#include "/d/Shire/sys/defs.h"

void
create_shire_room()
{
    set_short("The northern edge of a small cove");
    set_long("The walls of the river bank rise above you "+
        "on all sides save the northwest. The muddy trail "+
        "continues off to the northwest and south.\n");

    add_exit("/d/Shire/common/trollsh/new/cove","south",0,3);
}
