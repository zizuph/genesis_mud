/*
 * An underground river near the beach in Faerie
 * By Finwe, April 2005
 */

#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit WATER_BASE;
inherit SEA_CAVE_BASE;

void exit_cave(object player, int stage);

void
create_sea_cave_room()
{
    set_short("An underground tunnel");
    set_long(short() + ". The tunnel opens into a large cavern. The river " +
        "empties out under some large boulders to the northeast. Light " +
        "filters in from the behind the boulders. Fresh air blows in " +
        "from that direction, too.\n");
    
    add_item(({"boulders", "boulder"}),
        "They are heavy and large. They look like they were once part of " +
        "the tunnel, but have fallen from the ceiling. The river flows " +
        "under them though a crack in the ground.\n");
    add_item(({"crack"}),
        "It is a narrow opening under the boulders. It has been worn " +
        "away by the river and very smooth. It looks like you may be " +
        "able to crawl or wriggle through the crack.\n");

    set_add_stream();
    reset_room();

// sets drinking functions
    set_drink_from( ({ "river", "stream"}) );   
    add_prop(OBJ_I_CONTAIN_WATER, 1000000);  

    add_exit(FOREST_DIR + "river05", "west",0,3);

}

public void
init()
{
    ::init();
    init_drink();
    add_action("enter_crack","crawl");
    add_action("enter_crack","wriggle");
    add_action("enter_crack","enter");
    add_action("enter_crack","climb");

}

int
enter_crack(string str)
{
    if (str =="through crack" || str =="through the crack" ||  
        str =="under boulders" || str =="crack" || str =="under boulder")
    {
    write("You very carefully crawl under the boulders and get stuck!\n");

    say(QCTNAME(TP) + " disappears under the boulders.\n");
    
    set_alarm(1.0,0.0, &exit_cave(TP, 1));

    return 1;
    }

        write("Crawl through what?\n");
        return 1;

}

void exit_cave(object player, int stage)
{
    float time;

    set_this_player(player);
    switch (stage)
    {
    case 1:
        write("The water begins to build up behind you!\n");
        say("Water begins to build up behind " + HIM_HER(TP) + "\n",TP);
        time = 4.0;
        break;
    case 2:
        write("The cave begins flooding...\n");
        say("The cave starts to flood...\n",TP);
        time = 2.5;
        break;
    case 3:
        write("All of a sudden, you hear a large rumble and feel yourself " +
            "sliding down the crack...\n");
        say("A large rumble fills the cave, and all at once, it empties!\n");
        time = 2.0;
        break;
    case 4:
        write("You are shot out of the cave followed by a large column " +
            "of water.\n");
        time = 1.0;
        break;
    case 5:
        write("You tumble to the ground and roll a couple of times " +
            "before stopping.\n\n");
    
        TP->move_living("M",FOREST_DIR + "beach00",1,0);
        say(QCTNAME(TP) +" suddenly comes flying out from the south in a " +
            "spray of water. " + CAP(HE_SHE(TP)) + " rolls down the beach a " +
            "little ways and stops.\n");
       return;
    }
    set_alarm(time, 0.0, &exit_cave(player, ++stage));
}

