#include "/d/Rhovanion/defs.h"
inherit "/d/Rhovanion/lib/room";
inherit RHUN_DIR+"tower/inside/guard";

void create_room()
{
    set_short("Balcony");
    set_long("You stand on the balcony outside the second level of this "+
        "tall tower of dark red stone.  Around you, forest extends.  "+
        "Beyond its edges stand the vast plains of far eastern Rhovanion "+
        "to the east and south, and the Sea of Rhun to the west.  The "+
        "balcony extends around the building to the west, or you may "+
        "re-enter the dim hallways by heading north.\n");

    add_exit(RHUN_DIR+"tower/inside/2a", "north", 0);
    add_exit(RHUN_DIR+"tower/inside/2balcony1","west",0);

    reset_room();
}
