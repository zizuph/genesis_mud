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
      +"shadowy in the gloom, and the water "
      +"weighs down on you like a menacing hand.\n");

    add_item(({"wall", "walls", "rock"}),"The rocky walls "
      +"around you are rough and unhewn, implying "
      +"that this passage is naturally formed. The tunnel "
      +"takes a sharp turn from the northeast to the "
      +"east here.\n");    

    add_prop(ROOM_I_LIGHT, 0);
    IN_IN;

    add_exit(PK + "water/water8", "east");
    add_exit(PK + "water/water5", "northeast");
}
