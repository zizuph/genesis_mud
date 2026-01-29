inherit "/d/Kalad/room_std";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Kalad/defs.h"

void
create_room()
{
set_short("Sewers");
set_long("This tunnel leads south and north, slipping into the darkness "
	+"in both of the directions. Using the wall as a guide provides "
	+"the only safe way of traversing the tunnel, even light is of "
	+"relative little use. The strange odor that seems out of place "
	+"is still present, but it isn't too overpowering, just strange. "
	+"It is also incredibly damp here, a strange balmy dampness, "
	+"reminiscent of the sea.\n");
add_item(({"wall","walls"}),"The walls are slick with a shiny fungus "
                           +"and condensation from the damp sewer.\n");
add_item(({"odor"}),"The odor is uncharacteristic of any sewer you "
                   +"have ever been in, almost alien to this place. "
                    +"But you aren't really an expert on sewers, so "
                  +"you can't be sure.\n");
add_exit(TRADE(sewers/s6),"south");
add_exit(TRADE(sewers/s4),"north");
add_prop(ROOM_I_INSIDE,1);
add_prop(ROOM_I_LIGHT,0);
add_prop(ROOM_NO_TIME_DESC,1);
}
