inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* Sarr */

void move_back();
void reset_room();
object guard1,guard2,kid1;

void
move_guard(object guard, object enemy)
{
    if (!objectp(guard))
        return;

    if(E(guard) != TO)
    {
        guard->move_living("west", this_object());
    }

    guard->command("say Leave him alone you scum!");
    guard->command("kill " + OB_NAME(enemy));
}

void
aid_kid(object ob)
{
    if (!objectp(kid1))
        return;

    move_guard(guard1, ob);
    move_guard(guard2, ob);

    
    if (objectp(guard1) || objectp(guard2))
    {
        ob->stop_fight(kid1);
        kid1->stop_fight(ob);

        present("guard")->command("emote shoves you back out of the room.\n");
        ob->move_living("east",NOBLE(alexander/m21));

        set_alarm(35.0, 0.0, &move_back());
    }
}


void
move_back()
{
    if(guard1)
        guard1->command("east");
    if(guard2)
        guard2->command("east");
}

void
create_room()
{
    set_short("In the hall");
    set_long("You are in a stairwell in the house of Alexander. The "+
        "stairs lead down into the main floor. The walls around you "+
        "gleam from the black wood that dominates this house. The main "+
        "hub is to the north, while a guard's room is to the east.\n");
    
    add_item("walls","They are polished very well.\n");
    
    INSIDE;
    
    add_exit(NOBLE(alexander/m17),"north",0,-1,0);
    add_exit(NOBLE(alexander/m21),"east",0,-1,0);
    add_exit(NOBLE(alexander/m6),"down",0,-1,0);
    reset_room();
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
    if(!kid1)
        {
        kid1 = clone_object(NOBLE(npc/kid));
        kid1->move_living("xxx",TO);
    }
    guard1->team_join(guard2);
    guard1->command("east");
}

