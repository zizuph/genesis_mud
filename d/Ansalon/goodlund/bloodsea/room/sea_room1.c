#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/bloodsea/local.h"
#include <stdproperties.h>
#include <macros.h>

inherit BLOODSEA_OUT;

void
reset_bloodsea_room()
{
    return;
}

create_bloodsea_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_row_exit("/w/arman/workroom_base", "west", 0, 1);

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    reset_bloodsea_room();

}

void
set_sink_path(string sp)
{
    sink_path = "/d/Ansalon/balifor/flotsam/room/bottom_of_bay";
}

string
short_descr()
{
    return bloodsea_short();
}
 
string
long_descr()
{
    return bloodsea_desc()+
    "\n";
}