/*
 * Orc camp tower
 * By Finwe, December 2007
 */

#include "defs.h"

inherit OC_TOWER_BASE;


void
create_tower_room()
{
    setuid(); 
    seteuid(getuid());

    reset_faerie_room();

    set_short("Second level of the tall tower");
    set_long(short() + ". The walls have scratches in them and claw marks. They are made of logs and tied together with thick strips of leather. Crude holes are cut into them and offer a limited view of the camp. A ladder leads up and down through the tower.\n");

    add_tower_stuff();

    add_exit(OC_DIR + "undert02", "up");
    add_exit(OC_DIR + "undert", "down");
}


public void
init()
{
    ::init();

}
void
reset_faerie_room()
{
    create_orcs(ORC_SOLDIER, NO);
}
