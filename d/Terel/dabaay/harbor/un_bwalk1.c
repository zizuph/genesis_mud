/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * un_bwalk1.c
 *
 * Under the boardwalk
 *
 * Goldberry August, 2000
 * Modified 05132002 Goldberry
 *    adding entrance
 */

#include "/d/Terel/include/Terel.h"
#include <tasks.h>
#include <ss_types.h>

#define DAB_HARB DABAAY_DIR + "harbor/"
#define DAB_NPC DABAAY_DIR + "npc/"
#define CAVE_1 DAB_HARB + "cave_1"
#define KICK_LOG "/d/Terel/dabaay/log/kick"

#define FOUND_STONE "_dabaay_stone"

inherit DAB_HARB + "port_room";


init()
{
    add_action("kick", "kick");
    ::init();
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Under the boardwalk");
    set_long(
        "You are on a muddy strip of sand under a wooden "+
        "boardwalk. Above you are the beams and planks that "+
        "that make up the walkway. The base of the jetty can "+
        "be seen to the west.\n");
    
    add_item("jetty",
        "A solid structure crafted from large stones.\n");

    add_item(({"stones","large stones"}),
        "Large, heavy-looking grey stones cemented together "+
        "to create a jetty.\n");

    add_item(({"stone"}),
        "One of many stones cemented together to create a jetty.\n");

    add_item(({"cement"}),
        "The dark-grey material that forms the joints between "+
        "the stones.\n");

    add_item("planks",
        "Rough-sawn and weather-beaten, the planks appear "+
        "to be less sturdy when looking at them from below.\n");

    add_item(({"pier", "wooden pier"}), 
        "It's a well-built wooden pier. It will withstand the " +
        "worst of storms.\n");

    add_item(({"boardwalk", "wooden boardwalk"}), 
        "It's a well-built wooden pier. It will withstand the " +
        "worst of storms.\n");
    
    add_item(({"bay"}),	
        "You can see some fishing boats that have anchored in the "+
        "midst of the bay. Out towards the east and past some other "+
        "piers, the bay opens into the sea. From this distance, you "+
        "can barely make out what appears to be a stone wall "+
        "stretching from the north shore into the bay.\n");
    
    add_item(({"sea"}), "It looks cold and blue.\n");
    add_item(({"sand","mud","muddy strip"}),
        "White to tan-coloured sand, wet from the seawater.\n");

    add_item(({"loose stone","black stone","loose black stone"}),"@@bstone");

    add_prop(OBJ_S_SEARCH_FUN, "search_cement");

    add_exit(DAB_HARB + "un_bwalk2", "east", 0,4);
}


kick(string str)
{
     string kicker;
     if ((str!="black stone") && str!="loose stone")
       return 0;
     
     if(!TP->query_prop(FOUND_STONE))
       return 0;

     write("You kick at the loose black stone.\n");
     write("The sand beneath your feet suddenly sinks "+
           "down, taking you with it!\n");
     say(QCTNAME(this_player()) + " is swallowed up by the sand!\n");

     tell_room(CAVE_1, 
       QCTNAME(this_player()) + " falls from above.\n");
     this_player()->move_living("M", CAVE_1);
    
     kicker = TP->query_name() + "[" +TP->query_average_stat() + "]";
     write_file(KICK_LOG, kicker + " (" + ctime(time()) + ")\n");
     return 1;
}

string
search_cement(object me, string arg)
{
    int success;

    if(arg != "cement")
    {
        return "";
    }
    success = TP->resolve_task(TASK_DIFFICULT, ({TS_INT, SS_AWARENESS}));
    if(success > 0)
    {
       TP->add_prop(FOUND_STONE,1);
       return " You find a black stone with which seems to be loose.\n";
    }
    return "Your search reveals nothing special.\n";
}

string
bstone()
{
    if (!TP->query_prop(FOUND_STONE))
      return 0;

           
    return "This particular black stone, appears to be free of the cement "+
           "holding the others in place.\n";
}
