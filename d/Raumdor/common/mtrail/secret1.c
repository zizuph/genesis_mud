/* SARR */
#include "defs.h"
inherit SECRET_ROOM;

void
create_room()
{
    ::create_room();
    set_long("This is a small secret cave. You see hole up above "+
    "you that you could climb out of, and a small tunnel off to "+
    "the east. A torch burns on the north wall.\n");
    add_item("hole","It leads up.\n");
    add_item("torch","It gives this otherwise dark cave light.\n");
    add_item("tunnel","It heads into darkness.\n");
    add_exit(MTRAIL_DIR + "mtrail11","up","@@add");
    add_exit(MTRAIL_DIR + "secret2","east");
}

int
add()
{
    write("You climb up and out through a secret trapdoor and "+
    "find yourself on a trail.\nThe trapdoor closes and vanishes!\n");
    return 0;
}
