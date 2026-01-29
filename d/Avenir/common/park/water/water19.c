// Underwater room beneath the fountain
// under the park
//  -Cirion, Jan 1996

inherit "/d/Avenir/inherit/water";
#include "/d/Avenir/common/common.h"

public void
create_room()
{
    underwater_room();

    set_short("dead end");
    set_long("The rocky tunnel around you is dark and "
      +"shadowy in the gloom, and the water "
      +"weighs down on you like a menacing hand. You have "
      +"reached a dead end at a solid wall of rock. The "
      +"only way back is to the south.\n");

    add_item(({"wall", "walls", "rock"}),"The rocky walls "
      +"around you are rough and unhewn, implying "
      +"that this passage is naturally formed.\n");    

    add_prop(ROOM_I_LIGHT, -4);
    IN_IN;

    add_exit(PK + "water/water6", "south");
}
