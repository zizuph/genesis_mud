/* /d/Terel/mountains/ghastly_keep/rooms/in_tree.c
 *
 * One of the rooms in the Ghastly Keep.
 *
 * Znagsnuf
 *
 * - Language tweak complete (Gorboth)
 *
 */
 
#include <stdproperties.h>
#include <macros.h>
#include "defs.h";
#include <ss_types.h>

//Herbs in the room.
#include "/d/Terel/include/herb_arrs.h"
inherit "/d/Terel/std/herbsearch.c";
 
inherit GKEEP_STD_ROOM;

int do_climb(string str);

/*
 * Function name: create_gkeep_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_gkeep_room()
{

    set_area(GKEEP_INTREE);

    update_longdesc();

    // Add blackbird
    add_npc(GKEEP_NPC + "g_blackbird", 1);

    add_cmd_item( ({ "nest", "nests", "blackbirds nest", "blackbird's nest" }), 
                  ({"take", "get", "steal"}), "The blackbird's nest "
                  + "is somehow connected to the tree, making it "
                  + "impossible to remove.\n");

    // Add herbs to the tree.
    set_up_herbs( ({(TER_HERB + "whitehorn"),
                    (TER_HERB + "sebre"),
                    ONE_OF_LIST(MOUNT_HERBS),}),
                   ({ "tree", "trees", "here" }), 4);

    set_no_exit_msg( ({ "northeast", "northwest", "north", "east", 
                        "south", "southeast", "southwest", "west" }),
                        "The branches are thick, and covered in snow. "
                       + "Moving in that direction is not possible.\n");

    reset_room();
}

/*
 * Function name: reset_room()
 * Description  : Resets the room
 */
void
reset_room()
{
    
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
}

/*
 * Function name: do_climb())
 * Description  : Transport the player to the next room.
 */
int do_climb(string str)
{
    if (TP->query_prop("_live_o_steed"))
    {
        notify_fail("You need to dismount first.\n");
        return 0;
    }

    if(!(str == "down"))
    {
        notify_fail("Climb what?\n");
        return 0;  
    }     

    if((TP->query_skill(SS_CLIMB)) < 29)
    {

      write("\nYou try to climb down the snow covered tree, but fail.\n\n");
      say(QCTNAME(TP) + " tries to climb down the snow covered tree, "
           + "but fails.\n");  
      return 1;
    }

    write("\nYou climb the down snow covered tree.\n\n");
    say(QCTNAME(TP) + " climbs down the snow covered tree.\n");

    // Send a notification to the next room.
    tell_room(GKEEP + "gkeep_ent", QCTNAME(TP) + " arrives climbing "
             + "down the tree.\n");

    TP->move_living("M", GKEEP + "gkeep_ent",1,0);
    
    return 1;
}