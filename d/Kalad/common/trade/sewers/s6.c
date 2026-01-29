inherit "/d/Kalad/room_std";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Kalad/defs.h"

void
create_room()
{
    set_short("Sewers");
    set_long("The brackish waters are lukewarm here, growing warmer "
        +"towards the south, and chillier towards the north. "
        +"The walls that act as your guide stretch forth both north "
        +"and south, both ways leading into darkness. The strange odor "
        +"that has nagged your sense of smell is still present, making "
        +"this sewer seem to be more than it appears to be.\n");
    add_item(({"wall","walls"}),"The walls are slick with a shiny fungus "
        +"and condensation from the damp sewer.\n");
    add_item(({"odor"}),"The odor is uncharacteristic of any sewer you "
        +"have ever been in, almost alien to this place. "
        +"But you aren't really an expert on sewers, so "
        +"you can't be sure.\n");
    add_exit(TRADE(sewers/s7),"south");
    add_exit(TRADE(sewers/s5),"north");
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,0);
    add_prop(ROOM_NO_TIME_DESC,1);
}
