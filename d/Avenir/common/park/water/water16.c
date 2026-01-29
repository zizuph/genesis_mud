// Underwater room beneath the fountain
// under the park
//  -Cirion, Jan 1996

inherit "/d/Avenir/inherit/water";
#include "/d/Avenir/common/common.h"

public void
create_room()
{
    underwater_room();

    set_short("underwater tunnels");
    set_long("The rocky tunnel around you is dark and "
      +"shadowy in the gloom. The water is so icy "
      +"here it is painful to swim through. A heavy "
      +"current is pushing down from above.\n");

    add_item(({"wall", "walls", "rock"}),"The rocky walls "
      +"around you are rough and unhewn, implying "
      +"that this passage is naturally formed.\n");    

    add_prop(ROOM_I_LIGHT, -2);
    IN_IN;

    add_exit(PK + "water/water15", "up");
    add_exit(PK + "water/water17", "east");
}
