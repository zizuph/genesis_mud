#include "defs.h"
inherit SECRET_ROOM;
/* SARR */


void
create_room()
{
    ::create_room();
    set_long("You are now in a small little cave, with a pasageway "+
    "leading back west. Looking around, you see lots of broken old "+
    "bones lying about, probably unfortunate explorers. A cold "+
    "feeling shoots up your back. A large lever protrudes out of "+
    "the east wall. A single torch burns here.\n");
    add_item(({"torch","torches"}),"They burn on the wall, and look like "+
    "they are taken care of, by who, you have know idea.\n");
    add_item("lever","It is in the up position right now. It looks to be " +
    "made of ivory, or possibly polished bone, and sits waiting for you to "+
    "pull.\n");
    add_item("bones","There are many scattered about the room. They "+   
    "look so old and dusty, they must have been here for years. You "+
    "think they would crumble to your touch.\n");
    add_exit(MTRAIL_DIR + "secret3","west",0);
}

void
init()
{
    ::init();
    add_action("do_touch", "touch");
    add_action("do_pull", "pull");
}

int
do_touch(string str)
{
   NF("Touch what?\n");
   if(str != "bones")
       return 0;
   write("You reach down to touch one of the bones on the ground.\n");
   write("The bone you touch is surprisingly sturdy! In fact, as you "+
   "closly examine the bone, you see its just a hard piece of polished "+
   "wood made up to look like and old bone! False bones! Hah!\n");
   say(QCTNAME(TP)+" examines a bone on the ground. You are surprised "+
   "that it does not crumble.\n");
   return 1;
}

int
do_pull(string str)
{
    NF("Pull what?\n");
    if(str != "lever")
        return 0;
    write("You pull the lever!\n");
    TELL_SEEN(TP, QCTNAME(TP) + " pulls the lever!\n");
    set_alarm(0.0,0.0,"do_react",TP);
    return 1;
}

void
do_react(object victim)
{
    object dungeon = find_object(MTRAIL_DIR + "dungeon");
    say("You hear something snap!\n");
    victim->catch_msg("A trapdoor drops open underneath you and you fall into "+
    "blackness!\n");
    TELL_SEEN(victim, "A trapdoor opens under " +QTNAME(victim) +
        " and "+ HE(victim) + " falls down into blackness.\n");
    victim->move_living("M",dungeon);
    victim->catch_msg("You land hard on jagged stone!\n");
    tell_room(dungeon, "You hear a snap from above!\n", victim);
    TELL_SEEN(victim, QCTNAME(victim) + 
        " falls from above and lands hard on the jagged stone!\n");
    tell_room(dungeon, "There is a loud thud!\n", victim); 
    victim->heal_hp(-1500);
    if(victim->query_hp() <= 0)
        victim->do_die(TO);
    set_alarm(1.0,0.0,"do_land");
}

void
do_land()
{
    TELL_CAN_SEE(TO, "The trapdoor closes.\n");
}

