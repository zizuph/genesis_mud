/*
 *  /d/Emerald/blackwall/delrimmon/tree_room.c
 *
 *  This file is inherited by forested rooms on the slopes of Del Rimmon
 *  in which players are allowed to climb trees.
 *
 *  Modified from Gnadnar's /d/Gondor/lebennin/sirith/farms/fields/pasture4.c
 *  
 *  Copyright (c) February 1997, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/del_rimmon";
inherit "/d/Emerald/blackwall/delrimmon/legacy/del_rimmon_room";
inherit "/d/Emerald/blackwall/delrimmon/legacy/room_chairs";
inherit "/d/Emerald/blackwall/delrimmon/lib/herb_search";

#include "/d/Emerald/blackwall/delrimmon/defs.h"
#include "/d/Emerald/blackwall/delrimmon/legacy/room_chairs.h"

public void     create_tree_room();
public void     create_del_rimmon();
public void     init();
public void     add_forest_herbs();
public int      do_climb(string arg);
public int      do_sit(string arg);
public int      do_hop(string arg);
public void     do_sit_msgs(object pl, string prep, string name);
public void     do_stand_msgs(object pl, string name);
public string   look_tree();
// public void     leave_env(object ob, object dest);
public void     reset_room();

/* definitions */
#define  XHERB_DIR             ("/d/Gondor/common/herbs/")
#define DEL_RIMMON_HERBS ({ \
                                 (XHERB_DIR + "blueberry"),\
                                 (XHERB_DIR + "clove"),\
                                 (XHERB_DIR + "dill"),\
                                 (XHERB_DIR + "fennel"),\
                                 (XHERB_DIR + "foxglove"),\
                                 (XHERB_DIR + "garlic"),\
                                 (XHERB_DIR + "ginger"),\
                                 (XHERB_DIR + "hemlock"),\
                                 (XHERB_DIR + "holly"),\
                                 (XHERB_DIR + "mint"),\
                                 (XHERB_DIR + "oregano"),\
                                 (XHERB_DIR + "rosemary"),\
                                 (XHERB_DIR + "sage"),\
                                 (XHERB_DIR + "tarragon"),\
                                 (XHERB_DIR + "thyme"),\
                              })
#define IN_TREE             TP->query_prop("_live_s_sitting")
#define NPC_FILES         ({ (DELRIMMON_DIR + "npc/black_squirrel"),\
                             (DELRIMMON_DIR + "npc/forest_animal"),\
                             (DELRIMMON_DIR + "npc/outdoor_orc"),\
                             (DELRIMMON_DIR + "npc/forest_hen"),\
                          })

/* global variables */
public object  Npc;


/*
 * function name:        create_tree_room
 * description  :        our dummy routine for inheriting rooms
 */
public void
create_tree_room()
{
} /* create_tree_room */

/*
 * function name:        create_del_rimmon
 * description  :        here we provide presets for our forest
 *                       rooms in the Blackwall Mountains.
 */
public void
create_del_rimmon()
{
    set_short(del_rimmon_short);
    set_long(del_rimmon_long);

    set_loc(2);   /* this defines this as a forest room */

    add_chair("tall pine tree", "[in] / [into] / [up] [the] [tall]"
            + " [pine] 'tree'", 3, "in");
    try_item( ({ "tree", "pine tree", "tall tree", "tall pine tree" }),
             look_tree);
    /* so players in tree will not be added to room desc */
    set_no_sitting_in_desc(1);

    add_cmd_item( ({ "tree", "pine tree", "tall tree",
                     "tall pine tree" }),
        ({ "push", "move", "roll", "shove", "get", "take" }),
        "You cannot budge the tree.\n" );


    add_forest_herbs();
    create_tree_room();

    reset_room();

    add_view();
    set_rope_tie( ({ "tree", "branch", "trunk" }) );
} /* create_del_rimmon */

/*
 * Function name:        add_forest_herbs
 * Description  :        redefine this if you want to add your
 *                       own herbs to this room
 */
public void
add_forest_herbs()
{
    set_up_herbs( ({ ONE_OF_LIST(DEL_RIMMON_HERBS),
                     ONE_OF_LIST(DEL_RIMMON_HERBS),
                     ONE_OF_LIST(DEL_RIMMON_HERBS) }),
                          ({ "ground", "bush", "tree",
                             "undergrowth", "trees", "forest",
                             "shrub", "shrubs", "bushes", }),
                  3 );
} /* add_forest_herbs */


public void
init()
{
    ::init();
    init_room_chairs();
    add_action(do_climb, "climb");
    add_action(do_hop, "hop");
    add_action(do_hop, "jump");
    add_action(do_hop, "down");
} /* init */


/*
 * Function name:       do_climb
 * Description  :       transform "climb tree" to "sit on boulder"
 *                      and "climb down" to "hop down".
 * Arguments    :       string arg -- whatever the player typed
 * Returns      :       1 on success, 0 on failure
 */
public int
do_climb(string arg)
{
    int seated = (TP->query_prop(LIVE_S_SITTING) == "tall pine tree");

    if ( !arg )
        NF0("Climb "+( seated ? "where?\n" : "what?\n" ));

    if ( parse_command(arg, ({}),
    "[up] [into] [the] [tall] [pine] 'tree'") )
        return do_sit("in tree");
    if ( seated )
        return do_hop(arg);

    NF0("Climb what?\n");
} /* do_climb */

/*
 * Function name:       do_sit
 * Description  :       mask parent to block "sit" and "sit down"
 * Arguments    :       string arg -- whatever the player typed
 * Returns      :       1 on success, 0 on failure
 */
public int
do_sit(string arg)
{
    if ( !arg || arg == "down" )
        NF0("Sit on what?\n");
    return ::do_sit(arg);
} /* do_sit */


/*
 * Function name:       do_hop
 * Description  :       transform "hop down from tree" to "stand up"
 * Arguments    :       string arg -- whatever the player typed
 * Returns      :       1 on success, 0 on failure
 */
public int
do_hop(string arg)
{
    string      vb = QVB;

    if ( vb == "down" )
    {
        if ( strlen(arg) )
            return 0; /* ?? good NF0 msg ?? */
    }
    else if ( !arg || ( arg != "down" && 
    !parse_command(arg, ({}), "[down] [from] [the] [tall] [pine]"
                 + " 'tree'") ) )
        NF0(CAP(vb)+" where?\n");

    return do_stand("up");
} /* do_hop */

/*
 * Function name:       do_sit_msgs
 * Description  :       mask parent so the tree msgs look right
 * Arguments    :       object pl -- the person who's sitting
 *                      string prep -- the preposition
 *                      string name -- the name of the chair
 */
public void
do_sit_msgs(object pl, string prep, string name)
{
    WRITE("You climb up and crouch in the branches of a tall pine tree.");
    SAY(" climbs up and crouches in the branches of a tall pine tree.");
} /* do_sit_msgs */

/*
 * Function name:       do_stand_msgs
 * Description  :       mask parent so the tree msgs look right
 * Arguments    :       object pl -- the person who's standing
 *                      string name -- the name of the chair
 */
public void
do_stand_msgs(object pl, string name)
{
    write("You jump down from the branches of the tree.\n");
    SAY(" jumps down from the branches of a nearby tree.");
} /* do_stand_msgs */


/*
 * Function name:       look_tree
 * Description  :       VBFC for tree; include occupants.
 * Returns      :       string -- the desc
 */
public string
look_tree()
{
    return "This tall pine tree has many low-hanging branches growing"
         + " from its trunk.\n" +
        sitting_on_chair("tall pine tree", TP, 0, 1);
} /* look_tree */

/*
 * Function name:       leave_inv
 * Description  :       mask parent to be sure that departing players
 *                      are removed from tree occupants
 * Arguments    :       object ob -- the departing object
 *                      object dest -- its destination
 *
 * If they leave via a normal exit, they've already been made to stand.
 * However, if they leave by quitting, going netdead, teleporting, etc
 * and we don't call leave_inv_room_chairs(), then they'll still look
 * as if they're here.
 */
public void
leave_inv(object ob, object dest)
{
    ::leave_inv(ob, dest);
    leave_inv_room_chairs(ob, dest);
} /* leave_inv */

/*
 * Function name:        reset_room
 * Description  :        put a birds nest in appx 1 out of 20 rooms
 *                       which inherit this file, and clones up a
 *                       squirrel 1 out of 6 times
 */
void
reset_room()
{
    object  nest;

    if (nest = present("nest", this_object()))
    {
        nest->fill_nest();
    }

    if (!random(40))
    {
        if (!present("nest", TO))
        {
            nest = clone_object(DELRIMMON_DIR + "obj/bird_nest");
            nest->move(TO);
        }
    }

    if (!random(3))
    {
        if (!present("squirrel", TO))
        {
            Npc = clone_npc(Npc, ONE_OF_LIST(NPC_FILES));
        }
    }

    set_searched(- random(3));
} /* reset_room */
