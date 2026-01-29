#pragma save_binary

inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"

void reset_room()
{
    if(!present("ltown_mayor"))
    {
      object mayor;
      seteuid(getuid());
      mayor = clone_object(RHUN_DIR + "npc/ltown_ne_mayor");
      mayor->add_name("ltown_mayor");
      mayor->arm_me();
      mayor->move(TO,1);
    }
}

void create_room()
{
  set_short("Mayor's house");
  set_long("This is the home of the mayor of this"
	+" large town.  It is spacious and nicely furnished.  While"
	+" some of his citizens may be poor, the mayor is apparently"
	+" quite rich."
	+"  You may exit his domicile back to the north.\n");

  add_exit(RHUN_DIR+"ltown_ne/streets/st6","north",0);

  add_prop(ROOM_I_INSIDE,1);

  reset_room();
}
