inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

/* Sarr */

object ob,ob2;
int inro;
void reset_room();
int locked = 1;

void
check_knock_door(object pob)
{
    object cob;
    if(ob || ob2)
    {
        if(ob)
            cob = ob;
        else
            cob = ob2;
        if(pob->query_guild_name() == "Thanarian human race guild")
        {
            tell_room(E(pob),"The door unlocks and opens.\n");
            tell_object(pob,"You step through the door.\n");
            tell_room(E(pob),QCTNAME(pob)+" leaves north.\n",pob);
            pob->move_living("M",NOBLE(alexander/m16));
            tell_room(E(pob),QCTNAME(pob)+" enters the room.\n",pob);
            cob->command("say Were you able to find out anything, my Lord?");
            return;
        }
        if(pob->query_race_name() != "human")
        {
            if(inro)
                return;
            tell_room(E(pob),"The door unlocks and opens.\n");
            locked = 0;
            if(ob)
                ob->command("south");
            if(ob2)
                ob2->command("south");
            cob->command("shout Hey you scum! How did you get in "+
            "here! Die, you foul "+pob->query_race_name()+"!");
            if(ob)
                ob->command("kill "+lower_case(pob->query_name()));
            if(ob2)
                ob2->command("kill "+lower_case(pob->query_name()));
            cob->command("emote locks the door.");
            inro = 1;
            locked = 1;
            return;
        }
        tell_room(E(pob),"The door unlocks and opens.\n");
        tell_object(pob,"You step through the door.\n");
        tell_room(E(pob),QCTNAME(pob)+" leaves north.\n",pob);
        pob->move_living("M",NOBLE(alexander/m16));
        tell_room(E(pob),QCTNAME(pob)+" enters the room.\n",pob);
        cob->command("say I hope you can help us....");
    }
}

int
query_door_locked()
{
    if(locked == 1)
        return 1;
    return 0;
}

void
create_room()
{
    ::create_room();
    set_short("A short hall");
    INSIDE;
    set_long("You are in short hallway. Small paintings hang on the "+
    "walls here. To the north and south, there are bedrooms. The "+
    "one to the south looks intresting, as the door is closed shut. "+
    "You can head back to the center to the east.\n");
    add_item("door", "The bedroom door looks very solid.\n");
    add_exit(NOBLE(alexander/m17),"east",0,0,0);
    add_exit(NOBLE(alexander/m13),"north",0,0,0);
    add_exit(NOBLE(alexander/m19),"south","@@check@@",0,0);
    reset_room();
}

void
init()
{
    ::init();
    AA(do_unlock,unlock);
}

int
do_unlock(string str)
{
    object key;
    NF("Unlock what?\n");
    if(str != "door")
        return 0;
    key = present("_kalad_free_goblin_door_",TP);
    NF("You don't have the key to open it.\n");
    if(!key)
        return 0;
    say(QCTNAME(TP)+" unlocks the door.\n");
    write("You unlock the door.\n");
    locked = 0;
    return 1;
}

int
check()
{
    object cob;
    if(TP->id("guard"))
        return 0;
    if(ob || ob2)
    {
        if(ob)
            cob = ob;
        else
            cob = ob2;
        if(TP->query_guild_name() == "Thanarian human race guild")
        {
            cob->command("say Hail Thanar!");
            cob->command("emote unlocks the door.\n");
            write("You step inside the room.\n");
            return 0;
        }
        if(TP->query_race_name() != "human")
        {
            cob->command("say Get out of here, you worthless "+
            TP->query_race_name()+"!");
            write("The "+cob->short()+" won't let you in.\n");
            return 1;
        }
        cob->command("hmm");
        cob->command("say Ok...I'll let you in. Maybe you can help us.");
        cob->command("emote unlocks the door.");
        write("You step into the room.\n");
        return 0;
    }
    if(query_door_locked())
    {
        write("You try to open the door, and go south, but its locked.\n");
        return 1;
    }
    write("You open the door and step in.\n");
    return 0;
}


void
reset_room()
{
    if(!ob)
    {
        ob = clone_object(NOBLE(npc/brutal_guard1));
        ob->set_house_name("Alexander");
        ob->set_color_name("black");
        ob->arm_me();
        ob->move(TO);
    }
    if(!ob2)
    {
        ob2 = clone_object(NOBLE(npc/brutal_guard1));
        ob2->set_house_name("Alexander");
        ob2->set_color_name("black");
        ob2->arm_me();
        ob2->move(TO);
    }
    locked = 0;
    if(E(ob) != TO)
        ob->command("north");
    if(E(ob2) != TO)
        ob2->command("north");
    locked = 1;
    inro = 0;
    ob->team_join(ob2);
}

