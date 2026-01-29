inherit "/d/Kalad/room_std";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Kalad/defs.h"
object ob1;
object ob2;

void
create_room()
{
    set_short("Sewers");
    set_long("You are in a dank sewer, beneath a tunnel leading upward. The walls "
        +"are slick with condensation and fungus. There is an odor here, not "
        +"of waste, but of decay, a filth that seems almost alien "
        +"to a normal sewer. The ladder that extends upward here "
        +"is surprisingly devoid of fungus, and is almost too clean. "
        +"All around you lies darkness, friend to thieves and the "
        +"night.\n");
    add_item(({"ladder"}),"This is a surprisingly clean ladder which leads "
        +"upward to the surface world.\n");
    add_item(({"darkness"}),"The darkness here is impenetrable, closing "
        +"in on you from all sides.\n");
    add_item(({"wall","walls"}),"The walls are slick with a shiny fungus "
        +"and condensation from the damp sewer.\n");
    add_item(({"odor"}),"The odor is uncharacteristic of any sewer you "
        +"have ever been in, almost alien to this place. "
        +"But you aren't really an expert on sewers, so "
        +"you can't be sure.\n");
    add_exit(TRADE(sewers/s2),"west");
    add_exit(TRADE(wall/sewent),"up");
    add_prop(ROOM_NO_TIME_DESC,1);
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,0);
    set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
    if (!ob1 || !ob2)
        {
        ob1 = clone_object("/d/Kalad/common/trade/thief.c");
        ob1 ->move_living("xxx", this_object());
        ob2 = clone_object("/d/Kalad/common/trade/thief.c");
        ob2 ->move_living("xxx", this_object());
        ob1->team_join(ob2);
    }
}
