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
    set_short("In the Ball Room of the House of Alexander");
    set_long("You now find yourself in north side of what "+
    "appears to be a giant ball room. The floor beneath you is "+
    "made of polished wood for dancing. There are nobles here "+
    "dancing and having a good time. The ball room stretches out "+
    "to your south.\n");

    INSIDE;

    add_exit(NOBLE(alexander/m9),"west",0,-1,0);
    add_exit(NOBLE(alexander/m10),"southwest",0,-1,0);
    add_exit(NOBLE(alexander/m12),"south",0,-1,0);
    reset_room();
}

void
reset_room()
{
    if(!ob)
    {
        ob = clone_object(NOBLE(npc/yf_ball_noble));
        ob->arm_me();
        ob->move_living("xxx",TO);
    }
    if(!ob2)
    {
        ob2 = clone_object(NOBLE(npc/yf_ball_noble));
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
    guard->set_house_name("Alexander");
    guard->set_color_name("black");
    guard->arm_me();
    guard->move_living("M",TO);
        
    guard2 = clone_object(NOBLE(npc/house_guard));
    guard2->set_house_name("Alexander");
    guard2->set_color_name("black");
    guard2->arm_me();
    guard2->move_living("M",TO);
    
    tell_room(TO,"A pair of guards run in to the rescue!\n");
    guard->team_join(guard2);

    guard->command("shout Die trouble maker!");
    guard->command("kill "+lower_case(enemy->query_name()));
    guard2->command("kill "+lower_case(enemy->query_name()));

    guard_done = 1;
}


