#include "/d/Rhovanion/defs.h"
inherit "/d/Rhovanion/lib/room";
inherit RHUN_DIR+"tower/inside/guard";

void create_room()
{
    set_short("Balcony");
    set_long("You stand on the balcony outside the second level of this "+
        "tall tower of dark red stone.  Around you, forest extends.  "+
        "Beyond its edges stand the vast plains of far eastern Rhovanion "+
        "to the east, north, and south.  The balcony extends around the "+
        "building to the north and south, or you may "+
        "re-enter the dim hallways by heading west.\n");

    add_exit(RHUN_DIR+"tower/inside/2balcony5", "north", 0);
    add_exit(RHUN_DIR+"tower/inside/2balcony3","south",0);
    add_exit(RHUN_DIR+"tower/inside/2e", "west", 0);

    reset_room();
}
