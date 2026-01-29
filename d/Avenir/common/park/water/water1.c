// Underwater room beneath the fountain
// under the park
//  -Cirion, Jan 1996

inherit "/d/Avenir/inherit/water";
#include "/d/Avenir/common/common.h"

public void
create_room()
{
    underwater_room();

    set_short("beneath the fountain");
    set_long("You are in a mass of dark water just "
      +"beneath a gaping hole that leads up "
      +"into the fountain above. A small amount "
      +"of light filters down from above, but it "
      +"quickly fades to inky darkness below.\n");

    add_item(({"wall", "walls", "rock"}),"The rocky walls "
      +"around you are rough and unhewn, implying "
      +"that this passage is naturally formed.\n");    

    add_prop(ROOM_I_LIGHT, 1);
    IN_IN;

    add_exit(PK + "fountain", "up");
    add_exit(PK + "water/water2", "down");
}
