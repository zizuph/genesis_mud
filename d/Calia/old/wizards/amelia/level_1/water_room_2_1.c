inherit "/std/room";
inherit "/d/Calia/sea/water_base";

#include <macros.h>
#include <stdproperties.h>
#define WADE "/d/Calia/sea/level0/"

void
create_room()
{

	::create_surface_room();

}

string
long_msg1()
{
    return "You can wade off to the east from here as the "+
        "water is not as deep in that direction.\n";
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
        this_player()->move_living("M",WADE+"wade_2_2",1);
        tell_room(WADE+"wade_2_2",QCTNAME(this_player())+" wades in.\n",this_player());
        return 1;
    }
    notify_fail("You can't wade in that direction!\n");
    return 0;
}
