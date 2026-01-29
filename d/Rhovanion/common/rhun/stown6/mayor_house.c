#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"
inherit "/d/Rhovanion/lib/room";

reset_room()
{
  if(!present("s6_mayor"))
    {
      object mayor;
      seteuid(getuid(TO));
      mayor = clone_object(RHUN_DIR + "npc/stown6_mayor");
      mayor->add_name("s6_mayor");
      mayor->move(TO, 1);
    }
}

create_room()
{
    set_short("Mayor's house");
    set_long("This is the home of the mayor of this little town.  It is " +
        "a bit more well-furnished than others in town, though still " +
        "not especially impressive. It looks really dirty in here, as if"
	     + " the owner is particularily lazy.\n");

    add_exit(RHUN_DIR + "stown6/guard_house", "south");

    add_prop(ROOM_I_INSIDE, 1);

    reset_room();
}



