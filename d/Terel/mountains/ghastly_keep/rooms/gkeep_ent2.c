/* /d/Terel/mountains/ghastly_keep/rooms/gkeep_ent2.c
 *
 * One of the rooms in the Ghastly Keep.
 *
 *  Created by Znagsnuf.
 *
 *  Release date:
 *
 *  Date:                      What is done:                           By whom:            
 *  ---------------------------------------------------------------------------
 *  20/04-17                   Language tweak complete                  Gorboth  
 *  27/04-17                   Adding a notification                   Znagsnuf
 *  21/12-17                   Commented out debug statements          Lucius
 */
 
#include <stdproperties.h>
#include <macros.h>
#include "defs.h";

#define DEBUG	"znagsnuf"

//Herbs in the room.
#include "/d/Terel/include/herb_arrs.h"
inherit "/d/Terel/std/herbsearch.c";

inherit GKEEP_STD_ROOM;

/*
 * Function name: create_gkeep_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_gkeep_room()
{

    set_extra_longdesc("Intricate patterns of snow float weightlessly "
                      + "downward from a large snow covered tree close by, "
                      + "each flake swirling and dancing as an icy wind "
                      + "carries it towards the ground.");

    set_area(GKEEP_OUTDOOR);
    update_longdesc();

    add_item( ({"path", "road", "track", "tracks"}), "You notice "
               + "two sets of fresh tracks on the ground between "
               + "the snow covered branches. They are leading both "
               + "southeast and west.\n");

    add_item( ({"tree", "trees"}), "The large "
               + "snow covered tree is close, but too far away to "
               + "investigate.\n");

    add_item( ({"pattern", "patterns", "intricate patterns"}), "They "
               + "come in every shape and size, none alike.\n");

    add_item( ({ "nest", "blackbirds nest", "nests",
                 "blackbird nest", "blackbird's nest" }), "High "
               + "above the ground you see a blackbird's nest, seemingly "
               + "unreachable from where you stand now.\n");

    add_item( ({"blackbird", "blackbirds"}), "You see a blackbird "
               + "sitting in its nest in the tree close by.\n");

    // Need to follow tracks.
    set_noshow_obvious(1);
    
    add_exit("/d/Terel/mountains/ice13", "southeast");
    add_exit(GKEEP + "gkeep_ent",        "west");

    set_no_exit_msg( ({ "northeast", "northwest", "north", "east", 
                        "south", "southwest" }),
                        "There is no path leading in that direction.\n");

    // Add herbs to the tree.
    set_up_herbs( ({(TER_HERB + "whitehorn"),
                    (TER_HERB + "sebre"),
                    ONE_OF_LIST(MOUNT_HERBS),}),
                  ({ "tree", "trees", "here" }), 4);

    // Outside.
    add_prop(ROOM_I_INSIDE, 0);

    reset_room();
}

/* 
 * Function name: enter_inv
 * Description:   Called when objects enter this container or when an
 *                object has just changed its weight/volume/light status.
 * Arguments:     ob: The object that just entered this inventory
 *                from: The object from which it came.
 */
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

#ifdef DEBUG
    find_living(DEBUG)->catch_tell(CAP(TP->query_real_name()) + " enters "
              + "the Ghastly Keep area!\n");
#endif
}
