#pragma save_binary

inherit "/d/Gondor/common/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

void
create_room()
{
    set_short("small room");
    set_long(BSN(
        "This is a hastily constructed underground room. It has " +
        "been built underground to avoid the chaos in the Gondor " +
        "Fort above. It seems that some agent of the East has " +
        "managed to wreak havoc on this guildhall! Have no fear, " +
        "however, for the Free Peoples will not be so easily " +
        "defeated!"));

    add_exit("/d/Gondor/common/guild/startchamber","up","@@ranger_test", 2);
    add_exit("/d/Gondor/common/guild/boardhall","northeast");
}

int
ranger_test()
{
    if (IS_RANGER(TP))
        return 0;
    WRITE("Since you're not a Ranger, you feel unwelcome there " +
        "and turn back.");
    return 1;
}