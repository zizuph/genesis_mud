inherit "/d/Shire/std/room";

#include "/d/Shire/sys/defs.h"

void
create_shire_room()
{
    set_short("Before a cave on the edge of the Trollshaws");
    set_long("The high walls of the river bank loom "+
        "above you on three sides. To the northwest you can "+
        "make out the running waters of the Hoarwell. The "+
        "muddy trail winds its way north around the cove. "+
        "A large cave invites exploration directly to the "+
        "south.\n");

    add_exit("/d/Shire/common/trollsh/new/cove2","north",0,3);
    add_exit("/d/Shire/common/trollsh/new/cave1","south",0,1);
    add_exit("/d/Shire/common/trollsh/new/bank3","northwest",0,3);
}
