inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

/* Sarr */
object guard4,guard1,guard2,guard3,captain;
void reset_room();

void
aid_the_queen(object enemy)
{
    if(captain)
    {
        captain->command("west");
        captain->command("shout For the Lady!");
        captain->command("kill "+lower_case(enemy->query_name()));
    }
    if(guard1)
        guard1->command("kill "+lower_case(enemy->query_name()));
    if(guard2)
        guard2->command("kill "+lower_case(enemy->query_name()));
    if(guard3)
        guard3->command("kill "+lower_case(enemy->query_name()));
    if(guard4)
        guard4->command("kill "+lower_case(enemy->query_name()));
}

void
create_room()
{
    ::create_room();
    set_short("In a hall of the Castle of the High-Lord");
    INSIDE;
    set_long("You find yourself in the middle of a hallway. "+
    "The walls around you are decorated with paintings. There "+
    "is a guarded exit to the west.\n");
    add_item("paintings","Surreal pictures of the Ancient Wars of "+
    "Legend.\n");
    add_item("carpet","The red carpet is soft and warm.\n");
    add_exit(NOBLE(castle/c45),"north",0,-1,-1);
    add_exit(NOBLE(castle/c49),"west",0,-1,-1);
    add_exit(NOBLE(castle/c55),"south",0,-1,-1);
    reset_room();
}

void
reset_room()
{
    if(!captain)
    {
        captain = clone_object(NOBLE(npc/castle_captain));
        captain->arm_me();
        captain->move_living("xxx",TO);
    }
    if(!guard1)
    {
        guard1 = clone_object(NOBLE(npc/castle_guard));
        guard1->arm_me();
        guard1->move_living("xxx",TO);
    }
    if(!guard2)
    {
        guard2 = clone_object(NOBLE(npc/castle_guard));
        guard2->arm_me();
        guard2->move_living("xxx",TO);
    }
    if(!guard3)
    {
        guard3 = clone_object(NOBLE(npc/castle_guard));
        guard3->arm_me();
        guard3->move_living("xxx",TO);
    }
    if(!guard4)
    {
        guard4 = clone_object(NOBLE(npc/castle_guard));
        guard4->arm_me();
        guard4->move_living("xxx",TO);
    }
    captain->team_join(guard1);
    captain->team_join(guard2);
    captain->team_join(guard3);
    captain->team_join(guard4);
}


