/*
*  /d/Sparkle/area/jade/rooms/yard.c
*  Created 2017-01-23 by Martin Berka on Genesis MUD
*
*/

#pragma strict_types

#include "../defs.h"
inherit ROOM_DIR + "jade_room";

#include <stdproperties.h>
#include <cmdparse.h> //For commands related to the sticky tree.
#include <composite.h> //For listing sticky tree contents
#include <ss_types.h> //For strength factor when sticking item on tree

/* Global variables */
static object pine;

/* Prototypes */
int stick_item(string str);
int unstick_item(string str);

/*
 * Function name: create_room
 * Description  : Constructor for the room
 */
void
create_room()
{
    set_short("A path in the Jade Forest");
    set_long("The ground here, to the south of a sturdy fence, is "
        + "scorched earth, bare of any life. The trees of the forest have been "
        + "cleared well away, and the nearest ones still standing are bereft "
        + "of limbs below the crowns. One pine appears to have taken the "
        + "hacking particularly hard@@note_stuck_items@@. "
        + "The trees on the northern side of the "
        + "fence also appear damaged, though in a less organized fashion. "
        + "Beyond them stand a two-storey house and a large orchard. The "
        + "cleared land continues west along the fence.\n");

    add_item( ({"pine", "tree", "pine tree", "sticky tree", "wounded tree",
        "wounds"}),
        "The pine tree's branches have been lopped off, leaving open wounds "
        + "from which a great deal of sap is oozing. The trunk of the pine "
        + "looks very sticky.@@list_stuck_items@@\n");
    add_item( ({"pine bark", "bark", "pine sap", "sap", "pine trunk", "trunk"}),
        "The trunk of the wounded pine is covered with sap. You could probably"
        + " <stick> something on the trunk.@@list_stuck_items@@\n");
    //TODO: STICKY SAP HERE.

    pine = clone_object("/std/container");
    pine->set_name("sticky pine");
    pine->add_prop(CONT_I_MAX_VOLUME, 100000); //Much can hang around the trunk
    pine->add_prop(CONT_I_MAX_WEIGHT, 20000); //but sap supports less weight
    //pine->move(TO);

    //pine->set_no_show_composite(1);

    add_deadzone( ({"east"}) );
    add_house();
    add_fence( ({"northwest", "north", "northeast"}) );
    add_forest( ({"southeast", "south", "southwest"}) );

    add_exit(ROOM_DIR + "jade_forest_w", "west");

    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(PATH_HOME_PROP, "west");

    reset_room();
}

/*
 * Function name: reset_room
 * Description  : Ensure that there is an ogre corpse by the fence
 */
void
reset_room()
{
    if (present("corpse") || present("ogre thing")) //Some remnant of an ogre
    {
        return;  //All is well
    }

    //Check for live ogre (archer is not perfect):
    object corpse = present("ogre");

    if (!corpse->query_npc()) //No NPC ogre - make one.
    {
        corpse = clone_object("/std/monster");
        corpse->set_race_name("ogre");
        corpse->set_name("ogre");
        corpse->set_living_name("jade_ogre_south");
        corpse->set_gender(random(2));
        corpse->set_adj( ({
            one_of_list( ({ "large", "small", "middling", "fat",
                "skinny", "muscular" }) ),
            one_of_list( ({ "thick-tusked", "sharp-clawed", "lumbering",
                "big-eared", "long-legged", "hairy", "hairless" }) )
        }) );
        corpse->move(this_object());
        tell_room(this_object(), "An ogre emerges from the among the trees "
            + "and stomps towards the fence.\n");
    }

    find_object(ARCHER_ROOM)->request_arrow(corpse);
}

/*
 * Function name: init
 * Description  : Set up actions - put.
 */
void
init()
{
    ::init();
    add_action(stick_item, "stick");
    add_action(unstick_item, "get");

    reset_room(); //Problems getting the ogre shot on arrival.
}

/*
 * Function name: unstick_item
 * Description	: Handles player attempt to get something from the
 *      sticky tree
 * Arguments	: (string) Text following the verb
 * Returns      : (int) 1 if recognized as an attempt to get a tree item;
 *      otherwise 0 to allow the reguar get action.
 */
int
unstick_item(string str)
{
    if (!str) //Not sticking anything, so assume it's the emote.
    {
        return 0; //Try regular "get"
    }

    //What are we sticking?
    //PARSE_COMMAND filters due to access problems.
    mixed matching;
    parse_command(lower_case(str), all_inventory(pine),
        "[the] %i [from] / [off] [the] [pine] [sap] / [tree] / [trunk]",
        matching);
    if (!matching) //Check number of items found
    {
        return 0; //Regular get
    }
    object to_unstick = matching[1]; //Take first
    if (!to_unstick)
    {
        return 0; //Regular get
    }

    if (TP->query_prop(LIVE_O_SPELL_ATTACK)) //Pulling from the tree takes focus
    {
        notify_fail("You are busy attacking!\n");
        return 1;
    }

    if (to_unstick->query_prop("_obj_m_stuck"))
    {
        write("The " + to_unstick->query_short() + " is stuck firmly to the "
            + "sap and you are unable to remove it intact.\n");
        return 1;
    }

    if (to_unstick->move(TP)) //Hit an error
    {
        return 1;
    }

    write("You manage to pull the " + to_unstick->query_short()
        + " off the pine tree.\n");
    tell_room(TO, QCTNAME(TP) + " pulls a " + to_unstick->query_short()
        + " off a tree.", ({TP}));

    return 1;
}

/*
 * Function name: list_stuck_item
 * Description  : Returns sentence with list of the items on the sticky tree
 * Returns      : (string) sentence with composite list, if anything there.
 */
string
list_stuck_items()
{
    object *pine_contents = all_inventory(pine);
    if (sizeof(pine_contents))
    {
        return " You see " + COMPOSITE_DEAD(pine_contents) + " stuck in the"
            + " sap on the trunk.";
    }
    else
    {
        return "";
    }
}

/*
 * Function name: sap_drops
 * Description  : Drop an item from the trunk of the sticky tree once the sap
 *      can no longer support its weight.
 * Arguments    : (object) The object to drop
 */
void
sap_drops(object to_drop)
{
    if (!to_drop || environment(to_drop) != pine)
    {
        return;
    }
    to_drop->move(TO);
    tell_room(TO, "A " + to_drop->query_short() + " drops from the trunk of "
        + "a pine tree.\n", 0);
}

/*
 * Function name: sap_loosens
 * Description  : Makes it possible to pull an object from the tree and
 *      schedules the point at which the object falls off
 * Arguments    : (object) The object to loosen
 */
void
sap_loosens(object to_loosen)
{
    to_loosen->remove_prop("_obj_m_stuck");
    //Any object at this point has the same area of contact with the sap.
    //Only weight remains.
    set_alarm(1200.0 - to_loosen->query_prop(OBJ_I_WEIGHT),
        0.0, &sap_drops(to_loosen));
}

/*
 * Function name: note_stuck_items
 * Description  : Mention (for the room description) that there are items on
 *      the tree,
 * Returns:     (string) snippet to insert into description
 */
string
note_stuck_items()
{
    if (sizeof( all_inventory(pine) ))
    {
        return ", and has "
            + (sizeof(all_inventory(pine)) == 1 ? "something" : "some things")
            + " stuck to its trunk";
    }
    return "";
}

/*
 * Function name: stick_item
 * Description  : Put an item in the sticky sap
 * Returns:     (int) 1 if a stickable item is recognized, else 0 which results
 *      in the "stick tongue out" emote.
 */
int
stick_item(string str)
{
    if (!str) //Not sticking anything, so assume it's the emote.
    {
        return 0; //Give the emote a chance.
    }


    //What are we sticking?
    mixed oblist = PARSE_COMMAND(lower_case(str), all_inventory(TP),
       "[on] [the] %i [in] / [on] [the] [pine] [sap] / [tree] / [trunk]");

    if (!sizeof(oblist))
    {
        return 0; //Emote
    }

    object to_stick = oblist[0];

    if (TP->query_prop(LIVE_O_SPELL_ATTACK) || TP->query_prop(LIVE_I_STUNNED))
    {
        notify_fail("You are busy with other things!\n");
        return 1;
    }

    int stick_error = to_stick->move(pine); //Hit an error
    switch (stick_error)
    {
    case 1:
        write("The " + to_stick->query_short() + " peels away from the sap and "
            + "drops to the ground.\n");
        to_stick->move(TO);
        return 1;
    case 2:
        write("You start to stick the "  + to_stick->query_short() + " in the "
            + "sap, but cannot seem to release it. The sap does not adhere "
            + "strongly, and you are able to pull both arm and item free.\n");
        return 1;
    case 8:
        write("You cannot find enough space on the trunk!\n");
        return 1;
    }

    to_stick->add_prop("_obj_m_stuck", 1);

    //Assume that the max contact area is a 20x20cm square (20^3 cube):
    int physics_factor = 2 * min(8000, to_stick->query_prop(OBJ_I_VOLUME))
        - 4 * to_stick->query_prop(OBJ_I_WEIGHT) //Heavier - falls faster
        + 6 * min(100, TP->query_stat(SS_STR)); //Forces greater contact area
    set_alarm(itof(600 + physics_factor), 0.0, &sap_loosens(to_stick));

    write("You stick the " + to_stick->query_short() + " on the pine tree, "
        + "where it remains, the sap gripping it tightly.\n");
    tell_room(TO, QCTNAME(TP) + " sticks a " + to_stick->query_short()
        + " on a tree.", ({TP}));

    /*stuck_items += ({to_stick});
    to_stick->set_no_show();
    to_stick->add_prop(OBJ_M_NO_GET, 1);*/

    return 1;
}
