/*
*  /d/Sparkle/area/jade/rooms/jade_forest_e.c
*
*  A hidden room outside the fence, reachable only by tunneling through the
*  manure pile in the orchard. One-way non-obvious exits lead to logical
*  locations: near the farm entrance, in the forest near the docks in Faerie,
*  to the merc camp. Five green gems may be found in the ruins of the tents
*  each Arma - decreasing in value, with at least four resets between
*  successive finds.
*
*  Created 2017-01-23 by Martin Berka on Genesis MUD
*/

#pragma strict_types

#include "../defs.h"
inherit ROOM_DIR + "jade_room";

#include <stdproperties.h>

/* Global variables */
static object   corpse;
int gem_found_recently, //Since last reset
    gems_found; //The number of times gems have been found since Arma - limited

/* Prototypes */
string search_wreckage(object player, string str);

/*
 * Function name: create_room
 * Description  : Constructor for the room
 */
void
create_room()
{
    set_short("Southeast of a fence in the Jade Forest");
    set_long("The trees of the Jade Forest tower over you, casting deep "
        + "shadows. The nearest ones are bereft of limbs below the crowns, and "
        + "the surrounding ground is scorched. The wrecked remains of "
        + "several tents lie around you. "
        + "A few paces to the northwest, the trees have been cleared entirely, "
        + "leaving only a strip of scorched earth running to the north and to "
        + "the west along a sturdy, wooden fence. Through the fence you see "
        + "an orchard, an outhouse and a large pile of manure.\n");

    add_item("tree", "You can't see the trees for the forest!\n");

    add_item( ({"wreckage", "wrecked remains", "tents", "remains", "fabric",
        "charred fabric"}), "The tents were once each large enough for "
        + "several people to sleep in. "
        + "Now they are nothing but charred fabric.\n");

    add_item( ({"outhouse", "simple outhouse", "latrine", "privy", "toilet"}),
        "The outhouse is a simple structure made of unpainted grey wood, with"
        + "a roof that slopes towards the back. It is just "
        + "large enough to contain a pit toilet.\n");
    add_item( ({"pile", "manure", "pile of manure", "huge pile of manure",
        "heap"}),
        "The huge pile of manure "
        + "is quite close to the fence, but quite far from the forest "
        + "trees.\n" );
    add_item( ({"smell", "smells", "odour", "odor", "stink"}),
        "Only a whiff of odour reaches you at this distance.\n");

    add_deadzone( ({"west", "north"}) );
    add_fence( ({"northwest"}) );
    add_forest( ({"east", "south"}) );
    add_orchard();

    add_exit("@@forest_exit|jade", "southwest", 0, 0, 1);
    add_exit("@@forest_exit|faerie", "southeast", 0, 0, 1);
    add_exit("@@forest_exit|merc", "northeast", 0, 0, 1);

    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(OBJ_S_SEARCH_FUN, "search_wreckage");

    reset_room();
}

/*
 * Function name: reset_room
 * Description  : Populate room with NPC's
 */
void
reset_room()
{
    if (!present("corpse"))
    {
        object corpse = clone_object("/std/monster");
        corpse->set_race_name("ogre");
        corpse->set_name("ogre");
        corpse->set_gender(random(2));
        string *phys_list = ({ "large", "small", "middling", "fat", "skinny",
            "muscular" });
        string *feature_list = ({ "large-tusked", "sharp-clawed", "lumbering",
            "large-eared", "long-legged", "hairy", "hairless" });
        corpse->set_adj( ({phys_list[random(6)], feature_list[random(7)] }) );

        corpse->move(this_object());
        tell_room(this_object(), "An ogre emerges from the among the trees "
            + "and stomps towards the fence.\n");
        find_object(ARCHER_ROOM)->request_arrow(corpse);
    }

    if (gem_found_recently)
    {
        gem_found_recently--;
    }
}

/*
 * Function name: forest_exit
 * Description  : Travel through forest to one of several formerly distant
 *      locations.
 * Arguments    : (string) Destination: merc / faerie / jade
 * Returns      : (string) Path to target room
 */
string
forest_exit(string dir)
{
    switch (dir)
    {
    case "merc":
        write("You find yourself lost in Jade Forest. You stumble around, "
            + "doing your best to continue in a straight line in spite of the "
            + "thick undergrowth. You eventually emerge from among the trees "
            + "and find yourself in a clearing.\n");
        return "/d/Sparkle/guilds/new_merc/rooms/path3";
    case "faerie":
        write("You find yourself lost in Jade Forest. You stumble around, "
            + "doing your best to continue in a straight line in spite of the "
            + "thick undergrowth. As you are wondering whether you should "
            + "turn around and look for a way back, you emerge from the "
            + "trees and onto a road.\n");
        return "/d/Sparkle/area/faerie/rooms/forest/ctroad21";

    case "jade":
    default:
        write("The undergrowth proves dense. You find your path curving to the "
            + "west, and eventually emerge from the trees near the fence.\n");
        return ROOM_DIR + "jade_forest_s";
    }
}


/*
 * Function name: search_wreckage
 * Description  : Search the wreckage of the bandit camp for loot - find a green
 *      gem
 * Arguments    : (object) Player who searched
 *                (string) What the player searched
 */
string
search_wreckage(object player, string str)
{
    if (member_array( str, ({"wreckage", "wrecked remains", "tents", "tent",
        "remains", "fabric", "charred fabric"}) ) > -1)
    {
        if (!gem_found_recently && gems_found < 5)
        {
            object gem;
            switch (gems_found)
            {
                case 0:
                    gem = clone_object("/d/Genesis/gems/obj/emerald.c");
                    break;
                case 1:
                    gem = clone_object("/d/Genesis/gems/obj/jade.c");
                    break;
                case 2:
                    gem = clone_object("/d/Genesis/gems/obj/bloodstone.c");
                    break;
                case 3:
                    gem = clone_object("/d/Genesis/gems/obj/peridot.c");
                    break;
                default:
                    gem = clone_object("/d/Genesis/gems/obj/chrysoprase.c");
            }
            gems_found++;
            gem_found_recently = 4; //Next, lesser gem available in four resets
            gem->move(player);
            return "You find a " + gem->query_short() + " under the "
                + "charred fabric!\n";
        }
    }
    return "Your search reveals nothing special.\n";
}
