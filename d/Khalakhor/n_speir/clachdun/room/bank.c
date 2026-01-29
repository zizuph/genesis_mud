#include "local.h"

inherit BUILDING_BASE;

void
create_building()
{
    set_up_cords(7,16);
    add_exit(ROOM_DIR + "building_8_15", "northeast");

    reset_room();
}

void
reset_room()
{
    object deposit;

    ::reset_room();
    if (!present("_Clachdun_deposit"))
    {
	setuid(); seteuid(getuid());
	deposit = clone_object("/d/Genesis/obj/deposit");
	deposit->add_name("_Clachdun_deposit");
	deposit->move(this_object(), 1);
    }
}
