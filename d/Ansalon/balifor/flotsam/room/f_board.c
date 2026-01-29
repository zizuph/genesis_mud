#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit FLOTSAM_IN;

void
reset_flotsam_room()
{
    return;
}

create_flotsam_room()
{
    set_short("Adventurers Guild");
    set_long("@@long_descr");

    add_exit(FROOM + "f_guild","south",0);
    add_exit(FROOM + "street32","west","@@out",0);
    add_exit("/d/Genesis/room/common","common",0);

    clone_object(FOBJ + "normal_board")->move(TO);

    reset_flotsam_room();
}

string
long_descr()
{
    return "You stand in the Adventurers Guild in Flotsam, " +
    "where seasoned mariners and experienced hunters come " +
    "to rest and share stories of great and bold adventures. " +
    "Here you can exchange tales and pick up bits of information " +
    "from fellow travellers. To the south is a room where you " +
    "can train your skills. To the west you can return to the " +
    "streets of Flotsam. \n";
}

int
out()
{
    write("You enter the streets of Flotsam...\n");
}
