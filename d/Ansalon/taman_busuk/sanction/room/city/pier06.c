#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"

inherit SANCTION_OUT;

object gob;

void
reset_sanction_room()
{
    if (!objectp(gob))
    {
	setuid();
	seteuid(getuid());
        gob = clone_object(SNPC + "goblin");
        gob->set_color(({"black","blue","red","green","white"})[random(5)]);
	gob->quiet_arm_me();
        gob->move_living("xxx",TO);
    }
}

void
create_sanction_room()
{
    set_short("Southern piers in the harbour of Sanction");
    set_extra_long("These solidly built piers have been shattered " +
        "by the violent tremors from the erupting volcanoes. The " +
        "piers stretch further northeast and west from here. There " +
        "are warehouses to the east and to the south.");

    add_harbour_items();

    add_item(({"warehouse","warehouses"}),
        "Large stone buildings constructed to hold various goods.\n");

    add_exit(SCITY + "pier05", "northeast");
    add_exit(SCITY + "warehouse02", "east");
    add_exit(SCITY + "warehouse01", "south");
    add_exit(SCITY + "pier07", "west");

    reset_room();
}
