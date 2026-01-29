#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include <macros.h>
#include <stdproperties.h>
int gate_closed;

#define KILL_LOGGER CALATHIN_DIR + "obj/kill_logger"
#define IN_GATE CALATHIN_DIR + "in_south_gate"

int query_gate();
int enemy_check();
void open_gate();



/*
 * Function name: query_object_list
 * Description:   return list of objects to clone at each reset.
 */
public string*
query_object_list()
{
    return ({CALATHIN_DIR + "npc/std_gate_guard",
                 CALATHIN_DIR + "npc/std_gate_guard"});
}


public void
create_room()
{
    gate_closed = 1;

    set_short("The south gate of Calathin");
    set_long("This is the south gate of Calathin. Before you stands a tall wooden "+
                   "gate through the timber walls thats surround the town. Above, "+
                   "you can see a few guards keeping watch over the entrance. The "+
                   "road leads back into the forest to the south. The town itself is "+
                   "surrounded by forest.\n");
 
    add_item(({"gate","gates"}), "The gates are made from pine trees that surround "+
                      "the town. The gates are two double doors that open and close by "+
                      "chain winches from above the gates. Some guards can be seen "+
                      "above watching and operating the winches. \n");
    add_item(({"wall","walls", "timber walls", "wooden walls"}),
                      "The walls of the town are made from pine trees found throughout "+
                      "the forests that surround Calathin. The walls serve to protect the "+
                      "town from invading goblins and other creatures that come down "+
                      "out of the mountains to the north.\n");
    add_item(({"ground","floor","road"}), "The ground has been hardened and packed "+
                      "down by the numerous travellers who have passed through. A "+
                      "mixture of mud and snow lines the sides of the road.\n");
    add_item(({"Calathin","calathin","town"}), "You can't make out much from here "+
                      "because the gates and walls block your view.\n");

    add_cmd_item(({"gate","gates"}), "open", "The gates can only be opened by the "+
                              "guards above them.\n");
    add_cmd_item(({"gate","gates","on gate","on gates"}), "knock",
                            "@@knock_gate");


    add_exit(CALATHIN_DIR + "in_south_gate", "north", "@@check_north");
    add_exit(CALATHIN_DIR + "roads/road_s01","south", 0);
    reset_room();

}



int
knock_gate()
{

    if(!query_gate())
    {
        write("The gate is already open.\n");
        return 1;
    }

    if(TP->query_prop(OBJ_I_INVIS))
    {
        write("The guards above look down but see nothing and go back about "+
                  "their business.\n");
        say("The guards above look down but see nothing and go back about "+
                  "their business.\n");
        return 1;
    }

    if(enemy_check())
    {
        write("The guards standing above the gate look down at you.\n");
        say("The guards standing above the gate look down at "+QCTNAME(TP)+".\n");

        write("The captain shakes his head and shouts: You're not welcome "+
                  "in Calathin!\n");
        say("The captain shakes his head and shouts down to "+QCTNAME(TP)+
              ": You're not welcome in Calathin!\n");

        return 1;
    }

    write("You knock on the gates.\n");
    say(QCTNAME(TP) + " knocks on the gates.\n");

    write("The guards above the gate peer down at you.\n");
    say("The guards above the gate peer down at "+QCTNAME(TP)+".\n");

    write("The captain waves his hand towards the other side of the gate.\n");
    say("The captain waves his hand towards the other side of the gate.\n");

    open_gate();
    set_alarm(8.0, -1.0, "close_gate");
    return 1;

}

void
open_gate()
{
    tell_room(TO,"The gates to the town slowly open.\n");
    tell_room(IN_GATE,"The gates of the town slowly open.\n");
    gate_closed = 0;
    return;
}
    
void
close_gate()
{
    if(query_gate())
    {
        return;
    }

    tell_room(TO,"The gates to the town close.\n");
    tell_room(IN_GATE, "The gates to the town close.\n");
    gate_closed = 1;
    return;
}
    
int
check_north()
{
    object guard;
    guard = present("cal_guard",TO);
    
    if(query_gate())
    {
        write("The gates of the town are closed.\n");
        return 1;
    }

    if(enemy_check() && TP->query_prop(OBJ_I_INVIS))
    {
        write("You pass through the southern gates of Calathin.\n");
        return 0;
    }

    if(enemy_check() && guard)
    {
        write("The guard will not let you pass into the town.\n");
        say(QCTNAME(TP) +" is stopped by the guard.\n");
        return 1;
    }
    if(enemy_check())
    {
        write("The guards above notice you moving towards the gate.\n");
        close_gate();
        return 1;
    }
    write("You pass through the southern gates of Calathin.\n");
    return 0;
}
       

int
enemy_check()
{
    object kill_logger = find_object(KILL_LOGGER);
    if(kill_logger->query_killer(TP->query_name()))
    {
        return 1;
    }
    return 0;

}

int 
query_gate()
{
    return gate_closed;
}


