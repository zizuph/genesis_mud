inherit "/d/Kalad/room_std";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Kalad/defs.h"

void
create_room()
{
set_short("A dark alley");
set_long("The alley is not as short as you first thought, but so far "
        +"in Kabal not many things have been what you first thought. "
        +"There are doors to both sides of you, and the alley continues "
        +"north.\n");
add_exit(TRADE(cliff_connect),"south");
add_exit(TRADE(cliff_connect3),"north");
add_exit(TRADE(house1),"east");
add_exit(TRADE(house2),"west");
add_item(({"door","doors"}),"They are both light wooden doors which a"
	+"re open.\n");
hear_bell = 1;
}
