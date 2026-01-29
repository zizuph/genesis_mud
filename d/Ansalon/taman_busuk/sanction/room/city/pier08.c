#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"

inherit SANCTION_OUT;

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
    set_short("Southern piers in the harbour of Sanction");
    set_extra_long("This is the west end of a pier stretching from " +
        "the waterfront of Sanction and westwards, out here, into " +
        "the center of the harbour basin. Numerous small ships lies " +
        "randomly scattered along the piers. Vast clouds of steam " +
        "obscure the view to the shores along the harbour.");

    add_item("waterfront","To the east is the waterfront of " +
        "Sanction, and from there piers stretch out into the water.\n");
    add_harbour_items();
    
    add_exit(SCITY + "pier07", "east");

    reset_room();
}
