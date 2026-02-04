/*
 * main_gate.c  Entrance to the dwarven stronghold which protects the pass 
 *              leading into the northern mountains.
 *
 * Tomas  -- Dec. 1999
 */



#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include <macros.h>
#include <stdproperties.h>
int gate_closed;

#define IN_GATE MOUNTAIN_DIR + "stronghld/in_main_gate"
#define S_CHAINRM MOUNTAIN_DIR + "stronghld/walk7"

int query_gate();
int goblin_check();
int was_attacked();
void open_gate();

object warrior1;
object warrior2;

public void
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
    gate_closed = 1;

    set_short("Dwarven Stronghold main gates");
    set_long("You stand in awe before the massive mithril gates of the " +
      "dwarven stronghold known as Stonekeep. Stonekeep, is known throughout " +
      "Terel as the center of power, protecting southern Terel from " +
      "the vast wilderness beyond. Legends say that the mighty fortress " +
      "has never fallen to the forces of evil. Two large " +
      "statues stand on either side of the gate embedded into the walls.\n");

    add_item(({"gates","gate","mithril gate","mithril gates"}),
       "The massive gates are made of solid mithril bars augmented " +
       "with steel and solid oak cross members. The gates stand " +
       "close to 30 meters high and about five meters thick.\n");
 
    add_item(({"wall","walls","fortress"}),
       "The massive stone walls stand nearly 30 meters high and " +
       "appear to be about 5 meters thick of solid stone. The " +
       "texture of the walls looks very smooth denying anyone " +
       "the opportunity of climbing them.\n");

    add_item(({"statues","statue"}),
       "The massive stone statues resemble ancient dwarven war gods. " +
       "Both dressed in heavy armours carrying double-bladed stone " +
       "axes. The statues stand almost as tall as the walls themselves. " +
       "You note something strange about the hollow eye sockets.\n");
 
    add_item(({"eyes","eye","eye sockets","sockets"}),
       "The eye sockets of the statues appear to be hollow as if the " +
       "masons who carved them forgot to add eyes.\n");


    add_cmd_item(({"wall","walls"}),({"scale","climb"}),
       "You dont seem to find a decent looking hand or foothold. " +
       "You cant climb the walls.\n");

    add_cmd_item(({"gate","gates"}), "open", 
       "The gates can only be opened by the guards above them.\n");
 
   add_cmd_item(({"gate","gates","on gate","on gates"}), "knock",
                            "@@knock_gate");


      add_exit("/d/Terel/mountains/elderwood/road/road35", "south",0);
    add_exit(MOUNTAIN_DIR + "stronghld/in_main_gate", "north", "@@check_north");

    reset_room();

}


int
goblin_check()
{
    if(TP->query_race() == "goblin" && TP->query_alignment() <= 910)
    { 
       return 1;
    }
    return 0;
}


int
was_attacked()
{
    if (TP->query_prop("_stonehld_attacked"))
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
        write("The eyes of the statues suddenly flash bright red, " +
              "flicker slightly then fade out.\n");
        say("The eyes of the statues suddenly flash bright red, " +
              "flicker slightly then fade out.\n");

        write("The guards above glance over at the statues then " +
              "down below, but see nothing and go back about "+
              "their business.\n");
        say("The guards above glance over at the statues then down " +
            "below, but see nothing and go back about "+
            "their business.\n");
        return 1;
    }

  if(goblin_check())
    {
        write("The eyes of the statues suddenly flash bright red, " +
              "flicker slightly then fade out.\n");

        write("The guards standing above the gate look at the statues " +
              "then down at you.\n");
        say("The guards standing above the gate look at the statues then " +
            "down at "+QCTNAME(TP)+".\n");

        write("One of the guards above flips you the middle-finger and " +
                  "shouts: Yer not welcome here, Gobbo! Go find a rock n " +
                  "crawl under it!\n");
        say("One of the guards above flips the middle-finger and shouts down " +
              "to "+QCTNAME(TP)+ ": Yer not welcome here, Gobbo! Go find a " +
              "rock n crawl under it!\n");

        return 1;
    }


   if(was_attacked())
     {
        write("The eyes of the statues suddenly flash bright red, " +
              "flicker slightly then fade out.\n");

        write("The guards standing above the gate look at the statues " +
              "then down at you.\n");
        say("The guards standing above the gate look at the statues then " +
            "down at "+QCTNAME(TP)+".\n");
        write("One of the guards above shouts down at you saying: " + 
              "Are you stupid? You attack us then expect to be allowed " +
              "back in?! GET LOST!!\n");
        say("One of the guards above shouts down to " +QCTNAME(TP)+ ": " +
            "Are you stupid? You attack us then expect to be allowed " +
            "back in? GET LOST!!\n");

        return 1;
     }

    write("You knock on the gates.\n");
    say(QCTNAME(TP) + " knocks on the gates.\n");

    write("The guards above the gate peer down at you.\n");
    say("The guards above the gate peer down at "+QCTNAME(TP)+".\n");

    write("A guard signals the other side of the gate.\n");
    say("A guard signals the other side of the gate.\n");

    set_alarm(2.0, -1.0, "open_gate");
    set_alarm(8.0, -1.0, "close_gate");
    return 1;

}

void
open_gate()
{
    tell_room(TO,"The massive gates open slowly.\n");
    tell_room(IN_GATE,"The chains begin to rumble as the massive " +
       "counter weights begin to raise opening the massive gates slowly.\n");
    tell_room(S_CHAINRM,"The huge windless begins to turn as the iron " +
       "chain lowers the counter weights below.\n");
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

    tell_room(TO,"The massive gates close.\n");
    tell_room(IN_GATE, "The chains begin to rumble as the massive " +
       "counter weights lower closing the gate.\n");
    tell_room(S_CHAINRM,"The huge windless begins to turn as the iron " +
       "chain raises the counter weights below.\n");
    gate_closed = 1;
    return;
}
    
int
check_north()
{
    object guard;
    guard = present("std_dwf_warrior",TO);
    
    if(query_gate())
    {
        write("The gates of the town are closed.\n");
        return 1;
    }

    if(goblin_check() && TP->query_prop(OBJ_I_INVIS))
    {
        write("You pass through the northern gates of the dwarven stronghold.\n");
        return 0;
    }

    if(goblin_check() && guard)
    {
        write("The guard will not let you pass into the stronghold.\n");
        say(QCTNAME(TP) +" is stopped by the guard.\n");
        return 1;
    }
    if(goblin_check())
    {
        write("The guards above notice you moving towards the gate.\n");
        close_gate();
        return 1;
    }
    write("You pass through the main gates of the dwarven stronghold.\n");
    return 0;
}
       

