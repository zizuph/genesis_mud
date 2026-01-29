inherit "/std/room";
inherit "/d/Calia/sea/water_base";

#include <macros.h>
#include <stdproperties.h>
#define WADE "/d/Calia/sea/level0/"

void
create_room()
{

	::create_surface_room();
   add_item((({"rocks", "boulders", "line of boulders",
      "rock", "boulder"})),
      "Directly to your north a line of granite boulders blocks "+
      "swimming in that direction. Here the rocks are too jagged "+
      "and rough to climb however.\n");

   add_tell("A beautiful, haunting melody floats over "+
      "the sound of the waves...\n");

}

string
long_msg1()
{
    return "To the north you see a barrier of large granite "+
        "boulders that block swimming in that direction.  You "+
        "can wade off to the east from here as the water is "+
        "not as deep in that direction.\n";
}

void
init()
{
    ::init();
    add_action("to_wade","wade");
}

int
to_wade(string where)
{
    if ((where=="east")||(where=="e"))
    {
        write("You wade off to the east.\n");
        tell_room(environment(this_player()),QCTNAME(this_player())+
            "wades off to the east.\n",this_player());
        this_player()->move_living("M",WADE+"wade_2_3",1);
        tell_room(WADE+"wade_2_3",QCTNAME(this_player())+" wades in.\n",this_player());
        return 1;
    }
    notify_fail("You can't wade in that direction!\n");
    return 0;
}
