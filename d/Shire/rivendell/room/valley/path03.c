/*
 * Path to Rivendell
 * By Finwe, November 1997
 */
 
#include "local.h"
 
inherit VALLEY_BASE;

void
create_valley_room()
{
 
    set_extraline("You are west of a great bridge. Even though " +
        "the path passes through here to the House, it still " +
        "remains a quiet place where many elves come to relax " +
        "and listen to the waterfall. East takes you to the great " +
        "bridge while west takes you back into the valley." +
        "\nA stone bench.");
 
    add_item(({"bridge", "great bridge"}),
        "The bridge is large and gray, spanning a river.\n");
    add_item ("glade",
        "The glade is roughly circular. Benches are placed " +
        "around the perimeter of the area. Large branches " +
        "shelter the area from the sun.\n");
    add_item("bench",
        "They are made of stone with intricate carvings of " +
        "trees, stars, and elves carved into them. Some of the " +
        "benches are occupied by elves who have come here " +
        "to relax.\n");
    add_item(({"house", "last homely house", "house of elrond", 
            "last homely house of the east", 
            "last homely house east of the sea"}),        
        "The house stands in the distance in the center of the " +
        "valley. Details can't be made out from this distance " +
        "other than it looks large.\n");
    add_item("stones",
        "Examine what? Stones on the ground or stones of the bridge?\n");
    add_item("stones of the bridge",
        "The stones of the bridge are large blocks of grey " +
        "stone. They are smooth and fitted tightly " +
        "together, forming a strong structure that spans the " +
        "river.\n");
    add_item(({"stones on the ground", "pebbles", "rocks"}),
        "Very few stones can be found on the ground. What " +
        "you do see are round and smoothed by the passing " +
        "of countless feet.\n");
 
    add_exit(VALLEY_DIR + "bridge", "east");
    add_exit(VALLEY_DIR + "path02",  "west");
 
}
 
string short_desc()
{
    return "A path in the valley of Imladris";
}

void
init()
{   
    ::init();
    add_action("drink_it",      "drink");
    add_action("do_sit",        "sit");
    add_action("do_stand",      "stand");
    add_action("do_nothing",    "east");
    add_action("do_nothing",    "west");
    add_action("do_nothing",    "jump");
    add_action("do_nothing",    "tackle");
    add_action("do_nothing",    "dance");
    add_action("do_nothing",    "bow");
    add_action("do_nothing",    "curtsey");
    add_action("do_nothing",    "wiggle");
    add_action("do_nothing",    "strut");
    add_action("do_nothing",    "kill");
 
}
 
 
int
do_sit(string str)
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
 
int
do_stand()
{
    if(!TP->query_prop("i_am_sat"))
    {
        write("But you're not sitting down!\n");
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

int drink_it(string s)
{
 
int amount;
 
   if(s=="water" || s=="water from river")
       {
           amount = TP->query_prop(LIVE_I_MAX_DRINK) / 20;
           if (TP->drink_soft(amount))
           {
           TP->catch_msg("You kneel before the river, dipping " +
                "your cupped hands into the river and get a " +
                "drink of the clear icy water. Its taste " +
                "refreshes your mind and body.\n");
 
           say(QCTNAME(TP)+" kneels before the river and gets a " +
                "drink.\n");
           
           }
           else
           {
           write("You cannot drink more water.\n");
           }
 
            return 1;
        }
    else
            NF("Drink what?\n");
}
