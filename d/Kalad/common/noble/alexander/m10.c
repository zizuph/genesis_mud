inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* Sarr */

object ob,ob2,ob3;
object guard,guard2,guard3;
int guard_done;
void reset_room();
void call_guards(object enemy);

void
create_room()
{
    set_short("In the dining room");
    set_long("You are now in a small dining room. A large table "+
    "sits at the center of the room, surrounded by chairs. The "+
    "guests are eating and having a merry time. A large ball "+
    "hangs overhead. The sounds of cooking can be heard from "+
    "the north, while to the east, is the ball room.\n");
 
    add_item("candles","They burn giving light.\n");
    add_item(({"guests","nobles"}),"They chow down on food.\n");
    add_item("ball","A wonderful looking ball, it is made out of "+
    "different colored glass, resulting in a giant ball mirror that "+
    "reflects many different colored lights. It is beautiful.\n");
    add_item("table","A very beautiful and ornately decorated table. "+
    "An intricatly decorated table cloth covers it. Many fine "+
    "dishes and platters are scattered about, with warm steamy food "+
    "on it.\n");
    add_item("dishes","Fine china and crystal goblets.\n");
    add_item("platters","Silver platters with food on them.\n");

    INSIDE;

    add_exit(NOBLE(alexander/m9),"north",0,-1,0);
    add_exit(NOBLE(alexander/m11),"northeast",0,-1,0);
    add_exit(NOBLE(alexander/m12),"east",0,-1,0);
    add_exit(NOBLE(alexander/m7),"southwest",0,-1,0);
    reset_room();
}

void
reset_room()
{
    if(!ob)
    {
        ob = clone_object(NOBLE(npc/yf_dinner_noble));
        ob->arm_me();
        ob->move_living("xxx",TO);
    }
    if(!ob2)
    {
        ob2 = clone_object(NOBLE(npc/ym_dinner_noble));
        ob2->arm_me();
        ob2->move_living("xxx",TO);
    }
    if(!ob3)
    {
        ob3 = clone_object(NOBLE(npc/ym_dinner_noble));
        ob3->arm_me();
        ob3->move_living("xxx",TO);
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
        if(guard3)
            guard3->command("kill "+lower_case(enemy->query_name()));
        return;  /* No more guards can be called */
    }
    guard = clone_object(NOBLE(npc/house_guard));
    guard->set_house_name("Alexander");
    guard->set_color_name("black");
    guard->arm_me();
    guard->move_living("xxx",TO);
        
    guard2 = clone_object(NOBLE(npc/house_guard));
    guard2->set_house_name("Alexander");
    guard2->set_color_name("black");
    guard2->arm_me();
    guard2->move_living("xxx",TO);
    
    guard3 = clone_object(NOBLE(npc/house_guard));
    guard3->set_house_name("Alexander");
    guard3->set_color_name("black");
    guard3->arm_me();
    guard3->move_living("xxx",TO);
    
    guard->team_join(guard2);
    guard->team_join(guard3);

    guard->command("shout Die trouble maker!");
    guard->command("kill "+lower_case(enemy->query_name()));
    guard2->command("kill "+lower_case(enemy->query_name()));
    guard3->command("kill "+lower_case(enemy->query_name()));

    guard_done = 1;
}


