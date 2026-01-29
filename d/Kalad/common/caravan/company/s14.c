#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_hear_bell(1);

    add_prop(ROOM_I_INSIDE, 1);

    set_short("Corner");
    set_long("You've reached a corner of the Company building.\n"+
      "From here, two empty hallways lead away. One passage heads to the "+
      "west while another one goes southwards. Both hallways are devoid of "+
      "any furnishings, the only thing of note in either one is the marble "+
      "floor.\n");

    add_item(({ "marble floor", "floor" }), "The ground is covered in "+
      "marble tiles so brilliantly white that you are nearly blinded when "+
      "you look at them.\n");

    add_exit(CVAN + "company/s13", "west");
    add_exit(CVAN + "company/s31", "south");
}
