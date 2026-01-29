#include "/d/Terel/include/Terel.h"
inherit STDROOM;
#include <macros.h>
#include <stdproperties.h>

object gguard;

public void
reset_room()
{
   if (gguard) return;
  
   seteuid(getuid());
   gguard = clone_object("/d/Terel/mountains/obj/gguard");
   gguard->move_living("xx",TO);
}

public void
create_room()
{
    set_short("Guard Hall");
    set_long(
         "This is a simple stone hall. The walls are covered with crude paintings\n"
         +"that depict sexual images. There is a large heap for a bed.\n");
    add_prop(ROOM_I_INSIDE, 1);

    add_exit("/d/Terel/mountains/quarters", "up",0);
    add_exit("/d/Terel/mountains/refuse", "down",0);
    
    add_item(({"paintings","images"}),
        "They are smeared on the walls in blood, they are fairly explicit.\n");
    reset_room();
}

