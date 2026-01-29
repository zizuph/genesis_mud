#include "outroom.h"
 
create_outroom() {
    set_short("In a tall tree");
    set_long("You are climbing in the tall tree by the rocky " +
        "wall. From this spot you have an excellent view over " +
        "the whole area. ");
    ADD_EXA("view,area",
        "You are now sitting in a tree. Looking westwards you " +
        "can see plains in front of the rocky wall, and a " +
        "ghastly lake while on the other side you see the path. " +
        "Further to the west you see the land of Eregion. South " +
        "of the lake you see the dam, which lies in between the " +
        "valley's cliffs. To the east you see only the Misty " +
        "Mountains as they rise high into the sky. Nothing but " +
        "eagles' wings can probably bring you across that way.");
    DOWN("tree_n");
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
    reset_shire_room();
}

void
reset_shire_room()
{
/*
    object quiver;

        if (!present("quiver",TO))
    {
        quiver = clone_object("/d/Shire/scav_hunt/quiver");
        quiver->add_prop(OBJ_I_HIDE, 10 + random(10));
        quiver->move(TO);
    }
*/
}
