#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include <macros.h>
#include <stdproperties.h>
int gate_closed;

#define KILL_LOGGER CALATHIN_DIR + "obj/kill_logger"
#define N_GATE CALATHIN_DIR + "east_gate"

int enemy_check();

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
    set_short("the east gate of Calathin");
    set_long("This is the east gate of Calathin. Large wooden gates stand before "+
                   "you, leading out through the walls of the town. Guards are posted "+
                   "above to operate the gates and keep watch. The road leads west "+
                   "into the town.\n");

    add_item(({"wall","walls", "timber walls", "wooden walls"}),
                      "The walls of the town are made from pine trees found throughout "+
                      "the forests that surround Calathin. The walls serve to protect the "+
                      "town from invading goblins and other creatures that come down "+
                      "out of the mountains to the north.\n");
    add_item(({"town","calathin","Calathin"}), 
                      "To the west lies the town of Calathin. Trees can be seen "+
                      "throughout the town lightly covered with snow. A number "+
                      "of buildings form the town square. To the south another "+
                      "gate leads out of the town. The view to the west is "+
                      "blocked by a large mansion to the northeast.\n");
    add_item(({"gate","gates"}), "The gates are made from pine trees that surround "+
                      "the town. The gates are two double doors that open and close by "+
                      "chain winches from above the gates. Some guards can be seen "+
                      "above watching and operating the winches. \n");
    add_item(({"ground","floor","road"}), "The ground has been hardened and packed "+
                      "down by the numerous travellers who have passed through. A "+
                      "mixture of mud and snow lines the sides of the road.\n");



    add_cmd_item(({"gate","gates"}), "open", "The gates can only be opened by the "+
                              "guards above them.\n");
    add_cmd_item(({"gate","gates","on gate","on gates"}), "knock",
                            "@@knock_gate");


    add_exit(CALATHIN_DIR + "east_gate", "east", "@@check_east");
    add_exit(CALATHIN_DIR + "roads/road_e16","west",0);
    reset_room();
}




int
knock_gate()
{

    if(!(N_GATE)->query_gate())
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

        write("The captain shakes his head and shouts: You'll not escape "+
                  "this way, scum!\n");
        say("The captain shakes his head and shouts down to "+QCTNAME(TP)+
              ": You'll not escape this way, scum!\n");
        return 1;
    }
    write("You knock on the gates.\n");
    say(QCTNAME(TP) + " knocks on the gates.\n");

    write("The guards above the gate peer down at you.\n");
    say("The guards above the gate peer down at "+QCTNAME(TP)+".\n");

    write("The captain waves his hand towards another guard.\n");
    say("The captain waves his hand towards another guard.\n");

    (N_GATE)->open_gate();
    set_alarm(8.0, -1.0, "close_gate");
    return 1;

}

void
close_gate()
{
    (N_GATE)->close_gate();
    return;
}

int
check_east()
{
    object guard;
    guard = present("cal_guard",TO);
    
    if((N_GATE)->query_gate())
    {
        write("The gates of the town are closed.\n");
        return 1;
    }

    if(enemy_check() && TP->query_prop(OBJ_I_INVIS))
    {
        write("You pass through the eastern gates of Calathin.\n");
        return 0;
    }

    if(enemy_check() && guard)
    {
        write("The guard will not let you leave the town.\n");
        say(QCTNAME(TP) +" is stopped by the guard.\n");
        return 1;
    }

    if(enemy_check())
    {
        write("The guards above notice you moving towards the gate.\n");
        close_gate();
        return 1;
    }

    write("You pass through the eastern gates of Calathin.\n");
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

