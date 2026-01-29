#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>

void
create_object()
{
    set_name("sign");
    add_name("gargoyle");
    add_name("statue");
    set_adj("dreadful");
    add_adj("stone");
    set_short("dreadful stone gargoyle");
    set_long("                                                                  \n"+
"                   __________                 __________          \n"+
"               ___/          \\___         ___/          \\___      \n"+
"             _/                  \\       /                  \\_    \n"+
"            /               ____  \\     /  ____               \\   \n"+
"           /              _/    \\_ \\   / _/    \\               \\  \n"+
"           |             /        \\/   \\/       \\              |  \n"+
"           |            /                        \\             |  \n"+
"           |            |                         |            |  \n"+
"           |            |        _/\\___/\\_        |            |  \n"+
"           |            |       /         \\       |            |  \n"+
"           |            |       | (-) (-) |       |            |  \n"+
"           |            \\       |  _____  |       /            |  \n"+
"           |             \\      | /|| ||\\ |      /             |  \n"+
"           |              \\     / ||| ||| \\     /              |  \n"+
"           \\    _________  \\___/  ||| |||  \\___/  _________    /  \n"+
"            \\  /         \\        |\\/ \\/|        /         \\  /   \n"+
"             \\ |   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@   | /    \n"+
"              ||   @                                   @   ||     \n"+
"              \\|   @        Welcome to Raumdor!        @   |/     \n"+
"               /  |@                                   @|  \\      \n"+
"              |  ([=> Beware traveller, souls remain  <=])  |     \n"+ 
"               \\ ([=> here from great strides past.   <=]) /      \n"+
"                \\([=> Alluring as they may be, tarry  <=])/       \n"+
"                 ([=> not, lest you become a permanent<=])        \n"+
"                  _@  resident, forever banished to    @_         \n"+
"                 / @  the realm of the...Unliving.     @ \\        \n"+
"                /  @                                   @  \\       \n"+
"               /   @                                   @   \\      \n"+
"               |   @         -= The Reaper =-          @   |      \n"+
"               |   @                                   @   |      \n"+
"               |   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@   |      \n"+
"               \\         /                      \\          /       \n"+
"                |        |                       |        |       \n"+
"                |________|                       |________|       \n");

   
    add_prop(OBJ_M_NO_GET, "The dreadful stone gargoyle is firmly embedded"
    +" in the ground.\n");
}
