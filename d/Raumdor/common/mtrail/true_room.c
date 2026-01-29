#include "defs.h"
inherit SECRET_ROOM;
/* SARR */


void
create_room()
{
    ::create_room();
    set_long("You are now in a small little cave with a passageway "+
    "leading back west. Looking around, you see lots of broken old "+
    "bones lying about, probably misfortunate explorers. A cold "+
    "feeling shoots up your back. A large lever protrudes out of "+
    "the east wall. A single torch burns here.\n");
    add_item(({"torch","torches"}),"They burn on the wall, and look like "+
    "they are taken care of, by who, you have know idea.\n");
    add_item("lever","It is in the up position right now. It is made of "+
    "ivory wood(or is it polished bone?) and sits waiting for you to "+
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
   write("As you touch it, it crumbles to dust.\n");
   say(QCTNAME(TP)+" reaches down to touch one of the bones on the "+
   "ground, and it crumbles as "+HE(TP)+" touches it.\n");
   return 1;
}

int
do_pull(string str)
{
    NF("Pull what?\n");
    if(str != "lever")
        return 0;
    write("You pull the lever!\n");
    say(QCTNAME(TP)+" pulls the lever!\n");
    set_alarm(3.0,0.0,"do_react",TP);
    return 1;
}

void
do_react(object victim)
{
    victim->catch_msg("The wall swings open and pulls you in!\n");
    tell_room(TO,QCTNAME(victim)+" is pulled into another room as "+
    "a secret door swings open and shut!\n",victim);
    victim->move_living("M",MTRAIL_DIR + "secret4");
}
