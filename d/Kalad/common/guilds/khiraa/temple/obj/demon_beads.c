#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/raum/std/jewelry.h"

inherit RAUM(std/jewelry);

/*
 * /d/Kalad/common/guilds/khiraa/temple/obj/demon_beads.
 * Purpose    : This is a magical ward used in rites of the Khiraa
 * Located    : Can be taken from sacrifice room.
 * Created By : Sarr  24.Apr.97
 * Modified By: 
 */



void
create_jewelry()
{
    set_name("beads");
    add_name("chain");
    add_adj("demon-warding");
    set_short("chain of demon-warding beads");
    set_ok_jewelry_slots(({ANSALON_JEWELRY_NECK}));
    set_long("These are a bunch of odd-shaped beads. Some are small, "+
    "some are large. They are all enchanted and magical, used in "+
    "special rites of the Khiraa. They are used for protection against "+
    "powerful demons.\n");

    set_jewelry_value(0);
}
