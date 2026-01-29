inherit "/d/Shire/std/room";

#include "/d/Shire/sys/defs.h"

void
create_shire_room()
{
    set_short("Within a large crevice");
    set_long("You are turned sideways pressed against the walls "+
        "of this relatively large crevice. You are well concealed "+
        "from the sight of anyone passing by in the main tunnel.\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_exit("/d/Shire/common/trollsh/new/tt","out");
}
