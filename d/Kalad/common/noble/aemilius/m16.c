inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

/* Sarr */

object guard,captain;
void reset_room();

void
create_room()
{
    ::create_room();
    set_short("An intersection of the House of Aemilius");
    INSIDE;
    set_long("You now stand at an intersection of halls. To the "+
    "west, you see what appears to be a guards room, while to the "+
    "south and east, you see rooms. There is a window above, "+
    "letting sunshine spill into the room. The floor is warm "+
    "and carpeted.\n");
    add_item("window","You can see the blue sky through it.\n");
    add_item(({"floor","carpet"}),"It is made of fine wool.\n");
    add_exit(NOBLE(aemilius/m15),"north",0,-1,-1);
    add_exit(NOBLE(aemilius/m13),"east",0,-1,-1);
    add_exit(NOBLE(aemilius/m14),"southeast",0,-1,-1);
    add_exit(NOBLE(aemilius/m17),"south",0,-1,-1);
    add_exit(NOBLE(aemilius/m19),"west",0,-1,-1);
    reset_room();
}

void
reset_room()
{
    if(!guard)
    {
        guard = clone_object(NOBLE(npc/house_guard));
        guard->set_house_name("Aemilius");
        guard->set_color_name("red");
        guard->arm_me();
        guard->move_living("xxx",TO);
    }
    if(!captain)
    {
        captain = clone_object(NOBLE(npc/house_guard_captain));
        captain->set_house_name("Aemilius");
        captain->set_color_name("red");
        captain->arm_me();
        captain->move_living("xxx",TO);
     }
     captain->team_join(guard);
}

void
emergency(object ob)
{
    if(captain)
    {
        object guard2;
        guard2 = clone_object(NOBLE(npc/house_guard));
        guard2->set_house_name("Aemilius");
        guard2->set_color_name("red");
        guard2->arm_me();
        guard2->move_living("xxx",TO);
        captain->team_join(guard2);
        captain->command("e");
        captain->command("shout My Lord! Fear not, I shall aid you!");
        captain->command("kill "+lower_case(ob->query_name()));
        if(guard)
            guard->command("kill "+lower_case(ob->query_name()));
        guard2->command("kill "+lower_case(ob->query_name()));
    }
}


