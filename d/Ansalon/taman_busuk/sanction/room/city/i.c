#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"

inherit SANCINROOM;


void
create_sanction_room()
{
    set_short("Inside room in Sanction");
    set_long("@@long_descr");
}


string
long_descr()
{
    return "Inside room in Sanction.\n";
}
