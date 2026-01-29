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
    set_short("In the eastern part of the Dining Room");
    set_long("You now stand in the east part of a very long "+
    "room. This appears to be the dining room. A very long "+
    "wooden table is placed here, stretching all the way down "+
    "to the west end of this room. Various nobles and their "+
    "guests sit at the table eating food. The walls in here are "+
    "lined with candles, and a large and intricate glass ball "+
    "is hanging overhead. To the south, you see the "+
    "main entrance hall. To the north is the ball room.\n");
 
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

    add_exit(NOBLE(aemilius/m4),"north",0,-1,-1);
    add_exit(NOBLE(aemilius/m1),"south",0,-1,-1);
    add_exit(NOBLE(aemilius/m6),"west",0,-1,-1);
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
    guard->set_house_name("Aemilius");
    guard->set_color_name("red");
    guard->arm_me();
    guard->move_living("xxx",TO);
        
    guard2 = clone_object(NOBLE(npc/house_guard));
    guard2->set_house_name("Aemilius");
    guard2->set_color_name("red");
    guard2->arm_me();
    guard2->move_living("xxx",TO);
    
    guard3 = clone_object(NOBLE(npc/house_guard));
    guard3->set_house_name("Aemilius");
    guard3->set_color_name("red");
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


