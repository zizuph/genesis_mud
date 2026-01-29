inherit "/d/Kalad/room_std";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Kalad/defs.h"

void
create_room()
{
    set_short("Sewers");
    set_long("You are travelling deep in the sewers now, away from "
        +"the friendly light of the surface. The walls are "
        +"covered with the a slick fungus and condensation from the "
        +"damp sewer. The odor here is still unusual, but you are "
        +"getting used to it.\n");
    add_item(({"wall","walls"}),"The walls are slick with a shiny fungus "
        +"and condensation from the damp sewer.\n");
    add_item(({"odor"}),"The odor is uncharacteristic of any sewer you "
        +"have ever been in, almost alien to this place. "
        +"But you aren't really an expert on sewers, so "
        +"you can't be sure.\n");
    add_exit(TRADE(sewers/s2),"east");
    add_exit(TRADE(sewers/s4),"south");
    add_exit(TRADE(sewers/s8),"north");
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,0);
    add_prop(ROOM_NO_TIME_DESC,1);
}
