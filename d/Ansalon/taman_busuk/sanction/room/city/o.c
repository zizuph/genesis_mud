#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"

inherit SANCOUTROOM;


void
create_sanction_room()
{
    set_short("A street in the southern parts of central Sanction");
    set_long("@@long_descr");
}


string
long_descr()
{
    return "A street in the southern parts of central Sanction.\n";
}
