#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include <macros.h>
#include <stdproperties.h>

inherit SANCOUTROOM;

void
create_sanction_room()
{
    set_short("on a street near the north slums of Sanction");
    set_extra_long("You stand on a street leading up towards North " +
        "Pass, one of the few land exits out of Sanction. On either " +
        "side of the street are slums.");

    add_item(({"north pass","pass"}),
        "To the north of Sanction is one of the few exits out of this " +
        "wretched city, leading through the mountain ranges of Taman " +
        "Busuk to the lands of Estwilde and Solamnia.\n");

    slum_descriptions();

    add_exit(SCITY + "street25","northwest",0);
    add_exit(SCITY + "street23","south",0);

}
