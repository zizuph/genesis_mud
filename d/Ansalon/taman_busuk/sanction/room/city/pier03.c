#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"

inherit SANCOUTROOM;

object merc;

void
reset_sanction_room()
{
    if (!objectp(merc))
    {
	setuid();
	seteuid(getuid());
        merc = clone_object(SNPC + "mercenary");
        merc->set_color(({"black","blue","red","green","white"})[random(5)]);
	merc->quiet_arm_me();
        merc->move_living("xxx",TO);
    }
}

void
create_sanction_room()
{
    set_short("On a pier in the harbour of Sanction");
    set_extra_long("These solidly built piers have been shattered " +
        "by the violent tremors from the erupting volcanoes. The " +
        "piers stretch further north, west and southeast from here.");

    add_harbour_items();

    add_exit(SCITY + "pier02", "north");
    add_exit(SCITY + "pier05", "southeast");
    add_exit(SCITY + "pier04", "west");

    reset_room();
}
