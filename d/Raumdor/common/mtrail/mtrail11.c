/* Mountain trail room, credit to Sarr */
#pragma strict_types
#include "defs.h"
inherit MTRAIL_ROOM;

int dial,
    cooldown = 0;

void
create_room()
{
    type = "east";
    roadWest = "west";
    roadEast = "east";
    ::create_room();
    remove_item("rocks");
    add_item("rocks","Hard, jagged rocks formed by the mountains. "+
        "Looking closer, you see one odd shaped rock.\n");
    add_item(({"rock","odd rock","odd shaped rock"}),"It is very "+
        "smooth and round and dome shaped, like it is covering something. " +
        "You would have to lift it to investigate.\n");
    add_item("dial","@@dial");
    add_exit(MTRAIL_DIR + "mtrail10", roadWest, "@@up", 2);
    add_exit(MTRAIL_DIR + "mtrail12", roadEast, "@@down", 2);
}

void
init()
{
    add_action("do_lift", "lift");
    add_action("do_turn", "turn");
    add_action("do_press", "press");
    add_action("do_press", "push");
    ::init();
}
 
int
do_lift(string str)
{
    NF("Lift what?\n");
    if(str != "rock")
        return 0;
    write("You lift up the rock and you see a strange dial beneath it.\n");
    say(QCTNAME(TP)+" lifts up a strange rock.\n");
    return 1;
}
 
string
dial()
{
    if (dial == 0)
        return 
            "-------------O-------O------------\n"+
            "|            |___ ___|            |\n"+
            "|                v                |\n"+
            "|                                 |\n"+
            "|                                 |\n"+
            "O------                     ------O\n"+
            "|Dakar >   -----(*)        < Gylar|\n"+
            "O------                     ------O\n"+
            "|                                 |\n"+
            "|                                 |\n"+
            "|            ___ ^ ___            |\n"+
            "|           |  Drakan |           |\n"+
            "------------O---------O-----------|\n"+
            "Who do we worship above all? Turn  \n"+
            " the dial and press the stone to   \n"+
            "         reveal your fate.         \n";

    if (dial == 1)
        return 
            "-------------O-------O------------\n"+
            "|            |___ ___|            |\n"+
            "|                v                |\n"+
            "|                |                |\n"+
            "|                |                |\n"+
            "O------          |          ------O\n"+
            "|Dakar >        (*)        < Gylar|\n"+
            "O------                     ------O\n"+
            "|                                 |\n"+
            "|                                 |\n"+
            "|            ___ ^ ___            |\n"+
            "|           |  Drakan |           |\n"+
            "------------O---------O-----------|\n"+
            "Who do we worship above all? Turn  \n"+
            " the dial and press the stone to   \n"+
            "         reveal your fate.         \n";

    if (dial == 2)
        return 
            "-------------O-------O------------\n"+
            "|            |___ ___|            |\n"+
            "|                v                |\n"+
            "|                                 |\n"+
            "|                                 |\n"+
            "O------                     ------O\n"+
            "|Dakar >        (*)-----   < Gylar|\n"+
            "O------                     ------O\n"+
            "|                                 |\n"+
            "|                                 |\n"+
            "|            ___ ^ ___            |\n"+
            "|           |  Drakan |           |\n"+
            "------------O---------O-----------|\n"+
            "Who do we worship above all? Turn  \n"+
            " the dial and press the stone to   \n"+
            "         reveal your fate.         \n";

    return 
            "-------------O-------O------------\n"+
            "|            |___ ___|            |\n"+
            "|                v                |\n"+
            "|                                 |\n"+
            "|                                 |\n"+
            "O------                     ------O\n"+
            "|Dakar >        (*)        < Gylar|\n"+
            "O------          |          ------O\n"+
            "|                |                |\n"+
            "|                |                |\n"+
            "|            ___ ^ ___            |\n"+
            "|           |  Drakan |           |\n"+
            "------------O---------O-----------|\n"+
            "Who do we worship above all? Turn  \n"+
            " the dial and press the stone to   \n"+
            "         reveal your fate.         \n";
}

int
do_turn(string str)
{
     NF("Turn what?\n");
     if(!str)
         return 0;
     NF("Turn the what which way?\n");
     if(str == "dial right")
     {
         write("You turn the dial to the right once.\n");
         say(QCTNAME(TP)+" turns the dial to the right once.\n");
         if(dial == 3)
             dial = 0;
         else
             dial = dial + 1;
         return 1;
     }
     if(str == "dial left")
     {
        write("You turn the dial to the left once.\n");
        say(QCTNAME(TP)+" turns the dial to the left once.\n");
        if(dial == 0)
            dial = 3;
        else
           dial = dial - 1;
        return 1;
     }
    return 0;
}

int
do_press(string str)
{
    notify_fail(CAP(query_verb()) + " what?\n");
    if(str != "stone")
        return 0;
    write("You press the stone!\n");
    TELL_SEEN(TP, QCTNAME(TP)+" presses a stone!\n");
    set_alarm(3.0,0.0,"check_dial",TP, dial);
    return 1;
}

void
check_dial(object ob, int position)
{
    object mon;

    if(position == 1)
    {
        if (present(ob, TO))
        {
            TELL_SEEN(ob, QCTNAME(ob) + " disappears from view.\n");
            ob->catch_msg("You feel yourself transported!\n");
            ob->move_living("M",MTRAIL_DIR + "secret1");
            TELL_SEEN(ob, QCNAME(ob) + " suddenly appears.\n");
        }
        return;
    }

    if (cooldown)
    {
        write("Nothing happens.\n");
        return;
    }
  
    if (position == 0)
        mon = clone_object(COMMON_NPC_DIR + "revenant");
    else if (position ==  2)
        mon = clone_object(COMMON_NPC_DIR + "druj");
    else
        mon = clone_object(COMMON_NPC_DIR + "spectre");

    tell_room(TO,"You hear evil laughter.\n");
    mon->move_living("xxx",TO);
    mon->add_prop(LIVE_O_ENEMY_CLING,ob);

    cooldown = 1;
}

void
reset_room()
{
    cooldown = 0;
}
