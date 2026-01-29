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
      +"weighs down on you like a menacing hand. The "
      +"tunnel is level here, with passages "
      +"leading to the northwest and southwest. A massive "
      +"opening lies overhead, leading into complete "
      +"darkness.\n");

    add_item(({"wall", "walls", "rock"}),"The rocky walls "
      +"around you are rough and unhewn, implying "
      +"that this passage is naturally formed.\n");    
    add_item(({"opening"}),"There seems to be a current "
      +"flowing from it.\n");

    add_prop(ROOM_I_LIGHT, 0);
    IN_IN;

    add_exit(PK + "water/water4", "up");
    add_exit(PK + "water/water6", "northwest");
    add_exit(PK + "water/water7", "southwest");
}
