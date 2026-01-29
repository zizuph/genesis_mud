#include "/d/Rhovanion/defs.h"
inherit "/d/Rhovanion/lib/room";
inherit RHUN_DIR+"tower/inside/guard";

void create_room()
{
    set_short("Balcony");
    set_long("You stand on the balcony outside the second level of this "+
        "tall tower of dark red stone.  Around you, forest extends.  "+
        "Beyond its edges stand the vast plains of far eastern Rhovanion "+
        "to the east and north.  The balcony extends around the "+
        "building to the east and west here.\n");

    add_exit(RHUN_DIR+"tower/inside/2balcony5","east",0);
    add_exit(RHUN_DIR+"tower/inside/2balcony7", "west", 0);

    reset_room();
}
