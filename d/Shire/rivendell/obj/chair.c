/*
 * stone chair/bench in valley
 * by finwe
 * based on old fogey's bench
 */

#include "local.h"
#include "/d/Shire/sys/defs.h"

void init()
{   
    ::init();
    add_action("drink_it",      "drink");
    add_action("do_sit",        "sit");
    add_action("do_stand",      "stand");
    add_action("do_nothing",    "north");
    add_action("do_nothing",    "southwest");
    add_action("do_nothing",    "jump");
    add_action("do_nothing",    "tackle");
    add_action("do_nothing",    "dance");
    add_action("do_nothing",    "bow");
    add_action("do_nothing",    "curtsey");
    add_action("do_nothing",    "wiggle");
    add_action("do_nothing",    "strut");
    add_action("do_nothing",    "kill");

}


int do_sit(string str)
{
    if(str != "on bench")
    {
        write("Sit down where? Perhaps on the bench?\n");
        return 1;;
    }

    TP->add_prop(LIVE_S_EXTRA_SHORT, " sitting on the stone bench");
    TP->add_prop("i_am_sat",1);
    write("You sit down on the ornate bench.\n");
    say(QCTNAME(TP)+ " sits down on the stone bench.\n");
    return 1;
 
}
 
int do_stand()
{
    if(!TP->query_prop("i_am_sat"))
    {
        write("But you are sitting down!\n");
        say(QCTNAME(TP)+ " looks at the river.\n");
        return 1;
    }
 
    TP->remove_prop("i_am_sat");
    TP->remove_prop(LIVE_S_EXTRA_SHORT);
    write("You stand up, refreshed and invigorated from the rest.\n");
    say(QCTNAME(TP)+ " arises from the bench and looks around.\n");
    return 1;

}
 
int
do_nothing()
{
    if(TP->query_prop("i_am_sat"))
    {
        write("You can't do that sitting down!\n");
        say(QCTNAME(TP)+ " looks around.\n");
        return 1;
    }
}
