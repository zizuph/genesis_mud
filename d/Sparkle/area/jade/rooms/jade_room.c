/*
*  /d/Sparkle/area/jade/rooms/jade_room.c
*  Created 2017-02-20 by Martin Berka on Genesis MUD
*
*/

#pragma strict_types

#include "../defs.h"
inherit "/std/room";

inherit "/d/Sparkle/area/city/rooms/delay_room";
inherit "/d/Sparkle/lib/room_tell";
inherit "/d/Gondor/common/lib/herbsearch";

#include <stdproperties.h>

/* Definitions */
#define HAS_FENCE           "_has_jade_fence"
#define HAS_FOREST_TREE     "_has_jade_forest_tree"
#define HAS_ORCHARD_TREE    "_has_jade_orchard_tree"

/* Global variables */

/* Prototypes */
void block_deadzone();
string *query_orchard_herbs();

/*
 * Function name: add_deadzone
 * Description  : Add the description of the area outside the fence to a room.
 * Arguments    : (object) Array of directions blocked by the threat of arrwos.
 */
varargs void
add_deadzone( string *blocked_directions = ({}) )
{
    add_item( ({"stumps", "tree stumps", "blackened tree stumps",
        "blackened stumps" }), "The blackened stumps of large trees litter the "
        + "scorched earth between the fence and the forest.\n");
    if (sizeof(blocked_directions))
    {
        set_no_exit_msg(blocked_directions, "@@block_deadzone");

        add_item( ({ "ground", "earth", "scorched earth", "land", "tree stumps",
            "blackened tree stumps", "blackened stumps", "trunks"}),
            "The ground around you and among the nearby trees is the coal "
            + "black of "
            + "a doused campfire. The only traces of life in the scorched earth "
            + "are blackened tree stumps and trunks.\n" );
    }
    else
    {
        add_item( ({ "earth", "scorched earth", }),
            "The earth between the fence and the forest appears scorched as "
            + "if by fire. It is littered with blackened tree stumps.\n" );
    }
}

/*
 * Function name: add_fence_view
 * Description  : Add the description of the fence to a room. Be sure to call
 *          init_fence from the init function to enable climbing attempt.
 * Arguments    : (object) Array of directions blocked by the fence
 */
varargs void
add_fence( string *blocked_directions = ({}) )
{
    add_item( ({"fence", "strong fence", "strong wooden fence",
        "sturdy fence", "sturdy wooden fence", "wooden fence",
        "wooden splitrail fence", "splitrail fence", "barricade", "tall fence",
        "large fence", "wood", "inner side"}) + blocked_directions,
        "The wooden splitrail fence is taller than you are, and straddles the "
        + "boundary between fence and barricade. Each post is "
        + "reinforced with a diagonal beam on the inner side. "
        + "The wood is crooked, but appears very firm. The tips of rusty "
        + "nails stick out from the posts and rails at every angle, along with "
        + "shards of glass and broken pottery.\n");
    add_item( ({"fence post", "fence posts", "post", "posts", "beam", "beams",
        "diagonal beam", "diagonal beams"}),
        "The fence posts support the rails and are covered with sharp "
        + "objects. Each post is reinforced with a diagonal beam on the inner "
        + "side.\n");
    add_item( ({"fence rail", "fence rails", "rail", "rails", "splitrail",
        "splitrails"}),
        "Three horizontal wooden rails connect each fence post. Someone "
        + "could probably climb them, but no one could do so safely: the rails "
        + "bristle with rusty nails and ceramic shards.\n");
    add_item( ({"nails", "rusty nails", "shards", "glass shards",
        "ceramic shards",
        "pottery", "broken pottery", "shards of glass", "sharp objects"}),
        "Rusty nails and shards of broken pottery and glass cover the fence, "
        + "leaving no safe handholds.\n");

    if (sizeof(blocked_directions))
    {
        set_no_exit_msg( blocked_directions, "The fence is in the way.\n");

        add_cmd_item( ({"fence", "strong fence", "strong wooden fence", "beam",
            "wooden fence", "wooden splitrail fence", "splitrail fence", "post",
            "barricade", "fence post", "fence rail", "rail", "splitrail"})
            + blocked_directions ,
            ({"climb", "climb over", "scale", "crawl under"}),
            ({"@@do_climb_fence|climb", "@@do_climb_fence|squeeze through"}));
    }
}


/*
 * Function name: add_forest
 * Description  : Add the description of the Jade Forest to a room, and
 *          optionally use it to block exits.
 * Arguments    : (object) Array of directions blocked by the forest (where you
 *          cannot go through it)
 */
void
add_forest( string *blocked_directions = ({}) )
{
    if (sizeof(blocked_directions))
    {
        set_no_exit_msg( blocked_directions,
            "The undergrowth is too dense in that direction.\n");

        add_item("trees", "The trees of the Jade Forest tend to grow densely, "
            + "in varying "
            + "shades of green. The nearby ones have no lower branches.\n" );

        add_item( ({"forest", "Jade Forest"}) + blocked_directions,
                "The trees of the Jade Forest tend to grow densely, in varying "
                + "shades of green, casting dark shadows over everything beneath them."
                + " The nearest trees have no lower branches.\n" );
        add_item( ({"nearby trees", "nearest trees", "branches", "trunks",
                "tree trunks", "stumps"}),
                "The branches on the nearest trees tower high above, but the parts of "
                + "the trunks within reach have only chopped-off stumps and some sort "
                + "of oily coating.\n" );
        add_item( ({ "oil", "coating", "oily coating", "green coating" }),
            "It is an iridescent green, and very slippery.\n" );
        add_item( ({"shadows", "shadow", "shade", "darkness"}),
            "The shadows are interruped by the occasional patch of filtered "
            + "sunlight, but they are deep enough that anything could be hiding "
            + "among them.");
        add_item( ({"patch", "patch of sunlight", "patches",
            "patches of sunlight"}), "There are a few patches of sunlight, "
            + "illuminating a small fraction of the undergrowth.\n" );

        add_item( ({ "undergrowth", "bushes", "plants", "vines", "vine",
            "bush" }), "Beginning a few steps away, a tangle of undergrowth "
            + "surrounds the bases of the trees, the taller vines and bushes "
            + "reaching past your waist.\n");
        add_item( ({"sky", "up", "treetops", "foliage", "sunlight"}),
            "You can see patches of sky through the "
            + "treetops. It is sunny out there, but the forest is shadowy "
            + "thanks to the dense green foliage.\n");
        add_item( ({"sun"}), "It hurts your eyes!" );

        add_cmd_item(({"tree", "trees"}) + blocked_directions, "climb",
            "All the nearby trees have had their lower "
            + "branches removed, and their bark coated with some "
            + "sort of oil. You slide right down.\n");

        set_tell_time(180);
        add_tell("@@barkhound_bites");
        add_tell("Something rustles in the undergrowth.\n");
        add_tell("The forest briefly becomes even darker as a cloud blocks "
            + "the sun.\n");
        add_tell("A bird takes off from a nearby tree with a flutter of "
            + "wings.\n");

        set_up_herbs(({ "/d/Earthsea/herbs/herb_files/bergamot",
                        "/d/Gondor/common/herbs/basil",
                        "/d/Gondor/common/herbs/clove",
                        "/d/Krynn/common/herbs/fdlhead",
                        "/d/Shire/common/herbs/khuz",
                        "/d/Gondor/common/herbs/laurel",
                        "/d/Gondor/common/herbs/mint",
                        "/d/Krynn/common/herbs/poison_ivy",
                        "/d/Gondor/common/herbs/savory",
                         }),
                    ({"ground", "orchard"}), 5);
        return;
    }

    //Less to see from the outside
    add_item( ({"trees", "forest", "jade forest", "green wall"}),
        "From the outside, the trees of the Jade Forest form a wall of mottled "
        + "green.\n" );
}


/*
 * Function name: add_house
 * Description  : Add the description of the house to a room, and optionally
 *          use it to block exits.
 * Arguments    : (object) Array of directions blocked by the house (exclude
 *          directions that enter it)
 */
void
add_house( string *blocked_directions = ({}) )
{
    add_item( ({"house", "two-storey house", "two-story house", "wooden house",
        "farmhouse"}) + blocked_directions ,
        "The house is two storeys tall and grey, green and brown in colour. "
        + "Its sturdy walls and roof remind you of the trees of the nearby "
        + "forest. It looks large enough for a substantial family to "
        + "live in comfortably, but you cannot see "
        + "any windows. The roof slopes down steeply to the north and south.\n");
    add_item( ({"roof", "steep roof"}),
        "The roof is painted the same shade of green as the nearby trees and "
        + "probably poorly visible to anyone further away. It is quite steep, "
        + "sloping down to the north and south.\n");
    add_item( ({"wall", "walls", "palisade", "logs", "grey logs",
        "green logs"}),
        "The walls of the house are a mixture of grey and green logs, "
        + "planted in the ground like a palisade. They are sanded smooth and "
        + "bare of windows or protrusions.\n");

    if (sizeof(blocked_directions))
    {
        add_cmd_item( ({"house", "two-storey house", "two-story house",
            "wooden house", "farmhouse"}) + blocked_directions, "climb",
            "You find no handholds!\n");
        set_no_exit_msg( blocked_directions, "A wall of the house is in the "
            + "way.\n");
    }
}


/*
 * Function name: add_orchard
 * Description  : Add the description of the orchard, and optionally the
 *          use it to block exits - also indicates that player is in the orchard
 *          and sets appropriate herbs.
 * Arguments    : (object) Array of directions blocked by the orchard trees
 *          (not directions where you could reach another orchard location by
 *          going around)
 */
void
add_orchard( string *blocked_directions = ({}) )
{
    add_item( ({"orchard", "orchard trees", "species"}),
        "The trees in the orchard are of various ages, and various species, "
        + "judging by the types of fruit growing on some of them.\n");
    add_item( ({"fruit", "fruits"}), "A variety of fruits hang from the trees, "
        + "most not yet ripe.\n");

    if (sizeof(blocked_directions))
    {
        set_no_exit_msg( blocked_directions, "Trees completely block the "
            + "way in that direction.\n");

        add_item( ({"tree", "trees"}), "The trees in the orchard are of "
            + "various ages, and various species, "
            + "judging by the types of fruit growing on some of them.\n");

        add_item( ({"sky", "up", "sunlight"}),
            "What sky you can see through the treetops is clear and sunny.\n");
        add_item( ({"sun"}), "It hurts your eyes!" );
        add_item( ({"ground", "down", "grass", "lush grass", "plants",
            "small plants", "path", "trail"}),
            "Apart from the faint spath, the ground here is covered with lush "
            + "grass and small plants.\n");

        add_cmd_item( ({"tree", "fruittree", "fruit tree"}), "climb",
            "You start to climb a fruit tree. You feel the "
            + "whoosh of an arrow passing by your face.\n"
            + "Someone yells: Hey! We decide when the fruits are "
            + "ready!\nYou climb back down.\n");

        //Include common green/hardy/forest-based, plus the local specialties
        set_up_herbs( query_orchard_herbs(),
                    ({"ground", "orchard"}), 5);
    }
}


/*
 * Function name: barkhound_bites
 * Description  : Sneaky wolves gnaw on legs of idle players in the forest.
 * Return       : (string) ""
 */
string
barkhound_bites()
{
    //Just a warning, since not trying to cross
    object *livings = filter(all_inventory(this_object()), living);
    foreach (object player: livings)
    {
        if (player->query_npc())
        {
            continue; //Not really a player
        }

        if (query_idle(player) > 120)
        {
            player->catch_msg("You suddenly feel a gnawing pain in your leg. A "
                + "downward glance reveals a large, mossy wolf peacefully "
                + "chewing on it! "
                + "You startle, and so does the wolf, vanishing into "
                + "the bushes in one fluid slink.\n");

            object dye = clone_object(OBJ_DIR + "dyed_skin");
            dye->set_skin_adj("grey-green");
            dye->set_skin_noun("leg");
            dye->move(this_player());
        }
    }

    return "";
}


/*
 * Function name: block_deadzone
 * Description  : Send a warning arrow at the player when they attempt to travel
 *          in the cleared area parallel to the fence.
 * Return       : (string) ""
 */
string
block_deadzone()
{
    //Just a warning, since not trying to cross
    find_object(ARCHER_ROOM)->send_arrow(this_player(), 0, 1);
    this_player()->catch_msg("You decide that continuing in that direction "
        + "would be hazardous to your health.\n");
    return "";
}

/*
 * Function name: do_climb_fence
 * Description  : Allow the player to try get over the fence. As can be expected
 *          from the fence descriptions, this damages the player - and also
 *          attracts the attention of the archer in the attic.
 * Arguments    : (string) verb used to cross fence (climb / squeeze through)
 * Return       : (int) Command recognized
 */
int
do_climb_fence(string verb)
{
    object tp = this_player();
    if (tp->query_hp() < 50)
    {
        tp->catch_msg("You do not feel safe even touching the "
            + "fence, let alone trying to " + verb + " it.\n");
        return 1;
    }
    tp->catch_msg("You regret your decision to " + verb + " the fence the "
        + "moment you touch the rail. Nails and shards bite into you.\n");
    tp->heal_hp(-max(25, tp->query_hp() / 15));
    find_object(ARCHER_ROOM)->send_arrow(tp); //UPDATE - DO_HIT?
    tp->catch_msg("You abandon your attempt to cross the fence.\n");
    return 1;
}


/*
 * Function name: init
 * Description  : Actions when player enters - make sure room tells active.
 */
void
init()
{
    ::init();
    start_room_tells();
}


/*
 * Function name: looks_green
 * Description	: Check whether a player looks green enough to pass for a local
 * Arguments	: (object) player
 * Returns		: (int) 1/0 yes/no
 */
int
looks_green(object player_to_check)
{
    object dye = present("_dyed_skin_", player_to_check);
    return (dye && dye->query_skin_adj() == "green"
        && dye->query_skin_noun() == "skin"
        && dye->query_time_remaining() > 600.0); /*Skin looks very green*/
}


/*
 * Function name: query_orchard_herbs
 * Description  : Returns the herbs usually found in the orchard - good greens
 * Returns      : (string *) Herb file array
 */
string
*query_orchard_herbs()
{
    return ({   "/d/Earthsea/herbs/herb_files/bergamot",
                "/d/Gondor/common/herbs/basil",
                "/d/Gondor/common/herbs/clove",
                "/d/Krynn/common/herbs/fdlhead",
                "/d/Gondor/common/herbs/laurel",
                "/d/Gondor/common/herbs/mint",
                "/d/Gondor/common/herbs/savory",
                "/d/Sparkle/area/jade/obj/jade_pear",
                "/d/Sparkle/area/jade/obj/neh_fruit"
             });
}
