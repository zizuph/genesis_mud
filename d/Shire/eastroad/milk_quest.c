/*
 * Routines specific for milking quest
 * - Finwe Nov 2000
 */

#include "/d/Shire/sys/defs.h"
inherit "/std/object";

//Global defs
#define STOOL_SIT  "i_am_sitting_on_a_milking_stool"
#define QUEST_NAME "milk"

void
init()
{
    ::init();
    add_action("do_sit","sit");
    add_action("do_stand","stand");
    add_action("do_nothing","north");
    add_action("do_nothing","south");
    add_action("do_nothing","east");
    add_action("do_nothing","west");
    add_action("do_nothing","up");
    add_action("do_nothing","down");
    add_action("do_nothing","southeast");
    add_action("do_nothing","southwest");
    add_action("do_nothing","northeast");
    add_action("do_nothing","northwest");
    add_action("do_nothing", "kill");

}

int
do_sit(string str)
{
    if(str != "on stool")
    {
        write("Sit on what?\n");
        return 1;
    }

    if(TP->query_prop(STOOL_SIT))
    {
        write("You're already sitting down!\n");
        return 1;
    }
    TP->add_prop(STOOL_SIT,1);
    TP->add_prop(LIVE_S_EXTRA_SHORT, " is sitting on a wooden stool");
    add_prop(OBJ_M_NO_GET, QCTNAME(TP)+" is sitting on it!\n");
    write("You sit down on the stool, a bit uncomfortably.\n");
    say(QCTNAME(TP)+ " sits down on a wooden stool.\n");
    return 1;
}


int
do_stand()
{
    write("You stand up from the stool.\n");
    TP->remove_prop(STOOL_SIT);
    TP->remove_prop(LIVE_S_EXTRA_SHORT);
    remove_prop(OBJ_M_NO_GET);
    say(QCTNAME(TP)+ " jumps up from a wooden stool.\n");
    return 1;

}

int
do_nothing()
{
    if (TP->query_prop(STOOL_SIT)) 
    {
        write("You must stand up from the stool before you can do that.\n");
        return 1;
    }

    return 0;

}
