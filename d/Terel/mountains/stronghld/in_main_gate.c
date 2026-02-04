#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include <macros.h>
#include <stdproperties.h>
int gate_closed;

#define M_GATE MOUNTAIN_DIR + "stronghld/main_gate"

int goblin_check();

object warrior1;
object warrior2;


reset_room()
{
    if (!warrior1) {
        warrior1=clone_object(MOUNTAIN_DIR + "stronghld/npc/std_dwf_warrior");
        warrior1->move(this_object());
    }

    if (!warrior2) {
        warrior2=clone_object(MOUNTAIN_DIR + "stronghld/npc/std_dwf_warrior");
        warrior2->move(this_object());
    }

    if ((warrior1) && (warrior2))
        warrior1->team_join(warrior2);
}


public void
create_room()
{
    set_short("Inside the main gate of Stonehold");
    set_long("You are standing inside the great southern wall " +
       "of Stonehold. On either side of the gates are massive stone " +
       "counter weights suspended using strong iron chains. As you " +
       "gaze at the ceiling, you notice notice the rough " +
       "outline of a trapdoor high above you. To the " +
       "north is the cobblestone road leading through Stonehold.\n");

    add_item(({"counter weights","weights","chains","iron chains"}),
       "The massive stone counter weights stand close to 6 meters " +
       "tall and nearly 3 meters in diameter. The weights are suspended " +
       "in the air by strong iron chains running the length of the gates " +
       "through large holes in the ceiling above you.\n");

    add_item(({"gate","gates","southern gate","southern gates","main gate",
               "main gates"}),
       "The northern gates leading to the wilderness beyond stand before you. " +
       "Perhaps, if you knock on them the guards above will raise them.\n");

    add_item(({"trapdoor","ceiling"}),"You can just make out the " +
       "indentation of a trapdoor high above you in the wooden " +
       "ceiling. The trapdoor looks to far to jump from.. Perhaps, " +
       "something might be lowered or dropped from above through " +
       "the trapdoor perhaps..\n");

    add_cmd_item(({"chains","chain"}),"climb","The chains are well " +
       "greased and are out of reach. You cannot climb them.\n");

    add_cmd_item(({"gate","gates"}),"climb","You cant seem to find " +
       "a decent hand or foothold. You cannot climb the gates.\n");

    add_cmd_item(({"gate","gates"}), "open", 
       "The gates can only be opened by the guards above them.\n");
    add_cmd_item(({"gate","gates","on gate","on gates"}), "knock",
                            "@@knock_gate");


    add_exit(MOUNTAIN_DIR + "stronghld/main_gate", "south", "@@check_south");
    add_exit(MOUNTAIN_DIR + "stronghld/roada", "north",0);
    reset_room();
}



int
knock_gate()
{

    if(!(M_GATE)->query_gate())
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

    if(goblin_check())
    {
        write("The guards standing above the gate look down at you.\n");
        say("The guards standing above the gate look down at "+QCTNAME(TP)+".\n");

        write("A guard shakes his head and shouts: Wrong way gobbo! "+
                  "ALERT, Goblins in da gate!!\n");
        say("A guard shakes his head and shouts down to "+QCTNAME(TP)+
              ": Wrong way gobbo! ALERT, Goblins in da gate!!\n");
        return 1;
    }
    write("You knock on the gates.\n");
    say(QCTNAME(TP) + " knocks on the gates.\n");

    write("The guards above the gate peer down at you.\n");
    say("The guards above the gate peer down at "+QCTNAME(TP)+".\n");

    write("A guard waves his hand towards another guard.\n");
    say("A guard waves his hand towards another guard.\n");

    (M_GATE)->open_gate();
    set_alarm(8.0, -1.0, "close_gate");
    return 1;

}

void
close_gate()
{
    (M_GATE)->close_gate();
    return;
}


int
check_south()
{
    object guard;
    guard = present("std_dwf_warrior",TO);
    
    if((M_GATE)->query_gate())
    {
        write("The gates of the stronghold are closed.\n");
        return 1;
    }

    if(goblin_check() && TP->query_prop(OBJ_I_INVIS))
    {
        write("You pass through the main gates leading into the dwarven " +
           "stronghold.\n");
        return 0;
    }

    if(goblin_check() && guard)
    {
        write("The guard will not let you leave the stronghold.\n");
        say(QCTNAME(TP) +" is stopped by the guard.\n");
        return 1;
    }

    if(goblin_check())
    {
        write("The guards above notice you moving towards the gate.\n");
        close_gate();
        return 1;
    }

    write("You pass through the main gates leaving the dwarven " +
       "stronghold behind you.\n");
    return 0;
}
  

int
goblin_check()
{
    if(TP->query_race() == "goblin" && TP->query_alignment() <= 1100)
    { 
       return 1;
    }
}
