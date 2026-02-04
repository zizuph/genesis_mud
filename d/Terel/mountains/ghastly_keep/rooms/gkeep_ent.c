/* /d/Terel/mountains/ghastly_keep/rooms/gkeep_ent.c
 *
 * One of the rooms in the Ghastly Keep.
 *
*  Date:                      What is done:                            By whom:            
*  ----------------------------------------------------------------------------
*  28/04-17                   The Ghastly Keep is opened!              Znagsnuf
*  12/06-17                   Made the tree climbable                  Znagsnuf
*  08/05-19                   REmoved inherit of command driver        Shanoga
*
*/

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "defs.h";

//Herbs in the room.
#include "/d/Terel/include/herb_arrs.h"
inherit "/d/Terel/std/herbsearch.c";

inherit GKEEP_STD_ROOM;

int do_climb(string str);
int do_shake(string str);

//The tree has 3 pinecones
int pinecone = 3;

/*
 * Function name: create_gkeep_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_gkeep_room()
{
    set_extra_longdesc("Intricate patterns of ice float weightlessly "
                      + "downward from a large snow covered tree, "
                      + "each flake swirling and dancing as an icy wind "
                      + "carries it towards the ground.");
    
    set_area(GKEEP_OUTDOOR);

    update_longdesc();

    add_item( ({ "path", "road", "track", "tracks" }), "You notice "
               + "two sets of fresh tracks on the ground between "
               + "the snow covered branches. They are leading both "
               + "east and west.\n");

    add_item( ({ "tree", "trees" }), "The snow "
               + "hugs the tree. Between the branches you spot a "
               + "blackbird's nest. @@check_branch@@\n");
    
    add_item( ({ "nest", "blackbirds nest", "nests",
                 "blackbird nest", "blackbird's nest" }), "High above "
               + "the ground you see a blackbird's nest. Maybe it's "
               + "accessible if you climb the tree?\n");

    add_item( ({ "blackbird", "blackbirds" }), "You see a blackbird "
               + "sitting in it's nest in the tree far above.\n");

    add_item( ({ "pinecone", "pinecones" }), "@@check_branch2@@\n");

    // Need to follow tracks.
    set_noshow_obvious(1);
    add_exit(GKEEP + "gkeep_ent2",  "east");
    add_exit(GKEEP + "gkeep1",      "west");

    set_no_exit_msg( ({ "northeast", "northwest", "north", "southeast", 
                        "south", "southwest" }),
                        "There is no path leading in that direction.\n");

    // Add herbs to the tree.
    set_up_herbs( ({(TER_HERB + "whitehorn"),
                    (TER_HERB + "sebre"),
                    ONE_OF_LIST(MOUNT_HERBS),}),
                  ({ "tree", "trees", "here" }), 4);

    reset_room();
}

/*
 * Function name: reset_room()
 * Description  : Resets the room
 */
void
reset_room()
{
    pinecone = 3;    
}

/*
 * Function name: check_branch()
 * Description  : See if the branch has a pinecone
 */
public string
check_branch()
{

    if (pinecone)
    {
        return "A few pinecones hang from one of the branches, unreachable "
             + "from the ground.";
    }

    return "";
}

/*
 * Function name: check_branch2()
 * Description  : See if the branch has a pinecone
 */
public string
check_branch2()
{

    if (pinecone)
    {
        return "A few pinecones look like they could be loose enough to fall "
         +     "if the tree were shaken.";
    }

    return "You find no pinecone.";
}


/*
 * Function name: init
 * Description  : Add commands to the player on the deck
 */
void
init() 
{
    ::init();
    add_action(do_climb, "climb");
    add_action(do_shake, "shake");
    add_action(do_shake, "kick");
}

/*
 * Function name: do_climb())
 * Description  : Transport the player to the next room.
 */
int do_climb(string str)
{
  
    notify_fail("Climb what?\n");
    if(!str)
        return 0;

    notify_fail("Climb what?\n");
    if (!parse_command(str, ({ }), " [the] " + "'tree' / 'trees'"))
        return 0;   

    notify_fail("This snow covered tree is not possible to climb "
               + "while mounted.\n");
      if (TP->query_prop("_live_o_steed"))
      return 0;  

    if(TP->query_skill(SS_CLIMB) < 29)
    {
        write("\nYou try to climb the snow covered tree, but fail.\n\n");
        say(QCTNAME(TP) + " tries to climb the snow covered tree, "
        + "but fails.\n");  
        return 1;
    }

    write("\nYou climb the snow covered tree.\n\n");
    say(QCTNAME(TP) + " climbs the snow covered tree.\n");

    // Send a notification to the next room.
    tell_room(GKEEP + "in_tree", QCTNAME(TP) + " arrives climbing.\n");

    TP->move_living("M", GKEEP + "in_tree",1,0);
    
    return 1;
}

/*
 * Function name: do_shake())
 * Description  : Shake the tree
 */
int do_shake(string str)
{

    notify_fail(CAP(query_verb())+ " what?\n");
    if(!str)
        return 0;

    notify_fail(CAP(query_verb())+ " what?\n");
    if (!parse_command(str, ({ }), " [the] " + "'tree' / 'trees'"))
        return 0;   

    if(pinecone)
    {
      write("\nYou shake the snow covered tree. A brown pinecone "
           + "falls down to the ground.\n\n");
      say(QCTNAME(TP) + " shakes the snow covered tree, and "
           + "suddenly a brown pinecone falls down to the ground.\n");

      // Remove one pinecone at the time
      pinecone--;

      setuid();
      seteuid(getuid());
      clone_object(GKEEP_OBJ + "g_pinecone")->move(ENV(TP));
      return 1;
    }  
    else
    {
      write("\nYou shake the snow covered tree, but nothing happens.\n");
      say(QCTNAME(TP) + " shakes the snow covered tree, but nothing "
                      + "happens.\n");
    }
    
    return 1;
}
