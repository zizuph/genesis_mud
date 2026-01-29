#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include <macros.h>
#include <stdproperties.h>

inherit SANCOUTROOM;

void
create_sanction_room()
{
    set_short("on a path north of Sanction");
    set_extra_long("You stand on a path leading up towards North " +
        "Pass, one of the few land exits out of Sanction. Up a hill to " +
        "your west is a small temple of greying stone, long abandoned.");

    add_item(({"north pass","pass"}),
        "To the north of Sanction is one of the few exits out of this " +
        "wretched city, leading through the mountain ranges of Taman " +
        "Busuk to the lands of Estwilde and Solamnia.\n");

    add_item(({"small temple","temple","stone","greying stone","hill",
        "temple of huerzyd","huerzyd"}),
        "Up a hill to your west is a small temple. Made of white marble, " +
        "it has since darkened and greyed since from the smoke of nearby " +
        "volcanoes. It looks like it has long been abandoned, and strangely " +
        "has been avoided by the Dragonarmy forces.\n");

    add_exit(SCITY + "sanction_entry","northeast",0);
    add_exit(SCITY + "huerzyd", "west", "@@enter_temple");
    add_exit(SCITY + "street24","southeast",0);

}

int
enter_temple()
{
    write("You walk up the hill to the abandoned temple and make your " +
        "way through through the entry.\n");
    say(QCTNAME(TP)+ " walks up the hill to an abandoned temple and " +
        "enters it.\n");
    return 0;
}
