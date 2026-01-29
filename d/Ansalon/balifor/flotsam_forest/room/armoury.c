#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"

inherit FOREST_IN;

create_flotsam_room()
{
    set_short("Armoury of the Knight Circle");
    set_long("@@long_descr");

    add_prop(ROOM_I_NO_CLEANUP, 1);
    add_exit(FROOM + "startroom", "south");

}

string
long_descr()
{
    return "This room is very plain, but serves its purpose as the "+
    "armoury well enough. Equipment is placed in this room by "+
    "the Knights stationed here for other Knights similarly "+
    "stationed to use.\n";
}
