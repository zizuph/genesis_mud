inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* Sarr */

object ob;
object ob2;
object guard,guard2;

int guard_done;
void reset_room();
void call_guards(object ob);

void
create_room()
{
    set_short("In the Ball Room of the House of Aemilius");
    set_long("You now find yourself in the east half of a small "+
    "ballroom. The floor beneath you is "+
    "made of polished wood for dancing. There are nobles here "+
    "dancing and having a good time. The ball room stretches out "+
    "to your west.\n");

    INSIDE;

    add_exit(NOBLE(aemilius/m5),"west",0,-1,-1);
    add_exit(NOBLE(aemilius/m3),"south",0,-1,-1);
    reset_room();
}

void
reset_room()
{
    if(!ob)
    {
        ob = clone_object(NOBLE(npc/ym_ball_noble));
        ob->arm_me();
        ob->move_living("xxx",TO);
    }
    if(!ob2)
    {
        ob2 = clone_object(NOBLE(npc/of_ball_noble));
        ob2->arm_me();
        ob2->move_living("xxx",TO);
    }
    guard_done = 0;
}

void
call_guards(object enemy)
{
    if(guard_done)
    {
        if(guard)
            guard->command("kill "+lower_case(enemy->query_name()));
        if(guard2)
            guard2->command("kill "+lower_case(enemy->query_name()));
        return;  /* No more guards can be called */
    }
    guard = clone_object(NOBLE(npc/house_guard));
    guard->set_house_name("Aemilius");
    guard->set_color_name("red");
    guard->arm_me();
    guard->move_living("M",TO);
        
    guard2 = clone_object(NOBLE(npc/house_guard));
    guard2->set_house_name("Aemilius");
    guard2->set_color_name("red");
    guard2->arm_me();
    guard2->move_living("M",TO);
    
    tell_room(TO,"A pair of guards run in to the rescue!\n");
    guard->team_join(guard2);

    guard->command("shout Die trouble maker!");
    guard->command("kill "+lower_case(enemy->query_name()));
    guard2->command("kill "+lower_case(enemy->query_name()));

    guard_done = 1;
}


