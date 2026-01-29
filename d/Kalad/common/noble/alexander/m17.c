inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* Sarr */

object guard1,guard2,guard3,guard4;
object captain;
void reset_room();

void
create_room()
{
    set_short("In the center hub hall");
    set_long("You now stand in the center of the hallway that "+
    "branches off to the various rooms in the upper part of "+
    "the House of Alexander. The walls here are polished "+
    "to a beautiful, black shine. There are paintings and "+
    "tapestries among the walls here. The ground is "+
    "covered with a plush fur rug.\n");
    
    add_item("rug","The rug seems to be made of bear fur.\n");
    add_item("walls","The walls are adorned with paintings and "+ 
    "tapestries.\n");
    add_item("paintings","There are several paintings of old "+
    "war heros, in positions of combat against foul legions of "+
    "demi-humans. There is one large painting in the center "+
    "of them all.\n");
    add_item("large painting","It is a giant painting of Lord "+
    "Kabal, with a giant claymore raised over his head.\n");
    add_item("tapestries","There are several beautiful "+
    "tapestries, each woven with intricate symbols and "+
    "colors.\n");
    
    INSIDE;

    add_exit(NOBLE(alexander/m14),"north",0,-1,0);
    add_exit(NOBLE(alexander/m15),"northeast","@@block@@",-1,0);
    add_exit(NOBLE(alexander/m18),"east",0,-1,0);
    add_exit(NOBLE(alexander/m20),"south",0,-1,-1);
    add_exit(NOBLE(alexander/m16),"west",0,-1,-1);
    reset_room();
}

int
block()
{
    object cob;
    cob = present("captain",TO);
    if(!cob)
        cob = present("guard",TO);
    if(!cob)
        return 0;
    if(TP->query_race_name() != "human")
    {
        cob->command("say You can't go see the High Lord Alexander, "+
        "you filthy "+TP->query_race_name()+"!");
        write("You are blocked from going that way.\n");
        return 1;
    }
    else
    {
       cob->command("say Ok...you can go see him.");
       return 0;
    }
}

void
reset_room()
{
    if(!guard1)
    {
        guard1 = clone_object(NOBLE(npc/house_guard));
        guard1->set_house_name("Alexander");
        guard1->set_color_name("black");
        guard1->arm_me();
        guard1->move_living("xxx",TO);
    }
    if(!guard2)
    {
        guard2 = clone_object(NOBLE(npc/house_guard));
        guard2->set_house_name("Alexander");
        guard2->set_color_name("black");
        guard2->arm_me();
        guard2->move_living("xxx",TO);
    }
    if(!guard3)
    {
        guard3 = clone_object(NOBLE(npc/house_guard));
        guard3->set_house_name("Alexander");
        guard3->set_color_name("black");
        guard3->arm_me();
        guard3->move_living("xxx",TO);
    }
    if(!guard4)
    {
        guard4 = clone_object(NOBLE(npc/house_guard));
        guard4->set_house_name("Alexander");
        guard4->set_color_name("black");
        guard4->arm_me();
        guard4->move_living("xxx",TO);
    }
    if(!captain)
    {
        captain = clone_object(NOBLE(npc/house_guard_captain));
        captain->set_house_name("Alexander");
        captain->set_color_name("black");
        captain->arm_me();
        captain->move_living("xxx",TO);
    }
    captain->team_join(guard1);
    captain->team_join(guard2);
    captain->team_join(guard3);
    captain->team_join(guard4);
}

