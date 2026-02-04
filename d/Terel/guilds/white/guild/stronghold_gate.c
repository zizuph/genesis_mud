#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include "/d/Terel/guilds/white/lib/white.h"
#include <macros.h>
#include <stdproperties.h>


int gate_closed;


#define N_GATE WHITE + "guild/in_stronghold_gate"

init()
{
    add_action("place", "place");
    ::init();
}

public void
create_room()
{
    set_short("Gate of the stronghold");
    set_long("Gate of the stronghold.\n");

    add_item(({"wall","walls", "timber walls", "wooden walls"}),
                      "The walls of the town are made from pine trees found throughout "+
                      "the forests that surround Calathin. The walls serve to protect the "+
                      "town from invading goblins and other creatures that come down "+
                      "out of the mountains to the north.\n");

    add_item(({"gate","gates"}), "The gates are made from pine trees that surround "+
                      "the town. The gates are two double doors that open and close by "+
                      "chain winches from above the gates. Some guards can be seen "+
                      "above watching and operating the winches. \n");
    add_item(({"ground","floor","road"}), "The ground has been hardened and packed "+
                      "down by the numerous travellers who have passed through. A "+
                      "mixture of mud and snow lines the sides of the road.\n");



    add_cmd_item(({"gate","gates"}), "open", "The gates cannot be opened.\n");
    add_cmd_item(({"gate","gates","on gate","on gates"}), "knock",
                            "@@knock_gate");


    add_exit(WHITE + "guild/in_stronghold_gate", "north", "@@check_north");
    add_exit(WHITE + "roads/road_n07", "south",0);
    reset_room();
}

int
place(string str)
{
    if(!str) 
        return 0;
    if(str == "my right hand upon the seal" || str == "my right hand on the seal" ||
        str == "my right palm upon the seal" || str == "my right palm on the seal")
    {
        if(TP->query_alignment() < -200)
        {
            write("You place your hand on the seal.\n");
            say(QCTNAME(TP) + " places "+POSSESSIVE(TP)+" hand on the seal.\n");

            write("Blue flames erupt from the seal!\n");
            say("Blue flames erupt from the seal!\n");

            write("The flames engulf you!\n");
            say(QCTNAME(TP) + " is engulfed by the flames!\n");

            TP->command("scream");
            TP->heal_hp(-500 -(random(1000)));
            if(TP->query_hp() < 1)
            {
                TP->do_die(TO);
            }
            return 1;
        }
        if(TP->query_prop(WHITE_SEAL))
        {
            write("You place your hand upon the seal.\n");
            say(QCTNAME(TP) +" places "+POSSESSIVE(TP)+" hand on the seal.\n");

            (N_GATE)->open_gate();
            set_alarm(8.0, -1.0, "close_gate");
            return 1;
        }
        
        write("You place your hand upon the seal.\n");
        say(QCTNAME(TP) +" places "+POSSESSIVE(TP)+" hand on the seal.\n");
        return 1;

    }
    return 0;
}


int
knock_gate()
{

    if(!(N_GATE)->query_gate())
    {
        write("The gate is already open.\n");
        return 1;
    }

    write("You knock on the gates.\n");
    say(QCTNAME(TP) + " knocks on the gates.\n");
    return 1;
}

void
close_gate()
{
    (N_GATE)->close_gate();
    return;
}

int
check_north()
{
    
    if((N_GATE)->query_gate())
    {
        write("The gates of the stronghold are closed.\n");
        return 1;
    }

    write("You pass through the gates of the stronghold.\n");
    return 0;
}
  

