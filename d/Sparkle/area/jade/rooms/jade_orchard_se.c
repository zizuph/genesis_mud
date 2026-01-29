/*
*  /d/Sparkle/area/jade/rooms/jade_orchard_se.c
*  Created 2017-02-20 by Martin Berka on Genesis MUD
*
*/

#pragma strict_types

#include "../defs.h"
#include "../bandit_quest_constants.h"
inherit ROOM_DIR + "jade_room";

#include <stdproperties.h>

/* Global variables */
object family; //NPC


/*
 * Function name: create_room
 * Description  : Room constructor
 */
void
create_room()
{
    set_short("By an outhouse in an orchard");
    set_long("Mature fruit trees grow on all sides, except to the east, "
        + "where an outhouse "
        + "stands (and smells), and to the southeast, occupied by "
        + "a large pile of dried manure. "
        + "Beyond them, the tall fence makes a gradual turn, its "
        + "eastern "
        + "leg continuing north and the southern part stretching west. Paths "
        + "lead west towards a two-storey house and north.\n");

    add_item( ({"outhouse", "simple outhouse", "latrine", "privy", "toilet"}),
        "The outhouse is a simple structure made of unpainted grey wood, with"
        + "a roof that slopes towards the back. It is just "
        + "large enough to contain a pit toilet. "
        + "Marks on the ground indicate that it was recently "
        + "repositioned. While the arrangement appears relatively hygienic, "
        + "that's more than can be said for the nearby pile of manure.\n");
    add_item( ({"door", "outhouse door", "privy door", "words", "opening"}),
        "The door is made of the same grey "
        + "wood as the rest of the privy. There is a curved opening in "
        + "the upper part, serving to vent gases. Below it are carved the "
        + "words 'Knock first!'.\n");
    add_item( ({"opening", "curved opening", "opening on door"}),
        "This must greatly reduce the smell in there.\n");
    add_item( ({"pile", "manure", "pile of manure", "huge pile of manure",
        "heap"}),
        "The huge pile of manure "
        + "is fairly dry and only make a mild contribution to the smell here. "
        + "Its height and clumpy nature make it look rather unstable. It is "
        + "not clear why someone would pile it up and leave it so "
        + "long untouched.\n" );
    add_item( ({"smell", "smells", "odour", "odor", "stink"}),
        "You would rather not. You continue breathing shallowly through your "
        + "mouth.\n");

    add_item( ({"leg", "eastern leg", "eastern fence"}),
        "The fence to the east passes beyond the outhouse and the trees north "
        + "of it, extending out of sight to the northeast.\n" );
    add_item( ({"part", "southern leg", "southern fence"}),
        "The fence to the east passes beyond the outhouse and the trees north "
        + "of it, extending out of sight to the northeast.\n" );

    add_item( ({"mature trees", "mature fruit trees"}),
        "The trees here are fully grown, their lowest branches well out of "
        + "reach. They were clearly planted generations ago.\n");

    add_cmd_item( ({"outhouse", "simple outhouse", "latrine", "privy",
        "toilet"}), "enter",
        "As you approach the outhouse, a voice shouts: Occupied!\n");

    add_house();
    add_fence( ({"south"}) );
    add_orchard( ({"southwest", "northeast"}) );

    add_exit(ROOM_DIR + "jade_orchard_sw", "west");
    add_exit(ROOM_DIR + "jade_orchard_e", "north");
    add_exit(ROOM_DIR + "jade_orchard_mid", "northwest", 0, 5, 1);
    set_no_exit_msg( ({"east"}),
        "As you approach the outhouse, a voice shouts: Occupied!\n");
    set_no_exit_msg( ({"southeast"}),
        "The pile of manure is in the way!\n");

    add_prop(OBJ_S_SEARCH_FUN, "search_pile");
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    reset_room();
}

/*
 * Function name: reset_room
 * Description  : Populate room with NPC's
 */
void
reset_room()
{
    if (!objectp(family)) //Generic family, has no quest role
    {
        family = clone_object(NPC_DIR + "family.c");
        family->move(this_object());
    }
}

/*
 * Function name: enter_tunnel
 * Description  : Move through tunnel to forest
 * Arguments    : (string) text after "enter"
 * Returns      : (int) 1 (command recognized) / 0
 */
int
enter_tunnel(string str)
{
    if (!member_array( str, ({"pile", "heap", "tunnel", "the tunnel",
        "through tunnel", "into tunnel"}) ))
    {
        return 0;
    }

    if (present(QUEST_BURDEN, this_player()))
    {
        write("You cannot enter the tunnel while burdened - clearing away all "
            + "that manure takes two hands!\n");
        return 1;
    }

    /* This is disgusting.
     *  Degrade appearance ~enough to go to from "image of perfection" to
     *  "hideous" in the most favorable eyes. Produces a variable
     *  amount of dirtiness. */
    object player = this_player();
    int prior_offset = player->query_appearance_offset();
    if (prior_offset < 40)
    {
        player->set_appearance_offset(max(40 + random(10), prior_offset + 15));
    }

    write("You clear enough manure away to enter the tunnel, and are nearly "
        + "buried as the clumps roll down and fill the hole behind you. All "
        + "you can do is crawl forwards, towards the only remaining souce of "
        + "light. After several minutes, you emerge among trees.\n");
    player->move_living("into the pile of manure", ROOM_DIR + "jade_forest_e");
    return 1;
}

/*
 * Function name: search_pile
 * Description  : Search the pile of manure to reveal secret passage!
 * Arguments    : (object) Player who searched
 *                (string) What the player searched
 */
string
search_pile(object player, string str)
{
    if (member_array(str, ({"manure", "pile of manure", "pile", "heap"})) > -1 )
    {
        /* This is somewhat dirty, though not as bad as the next step.
         *  Degrade appearance ~enough to go to from "image of perfection" to
         *  "plain" in the most favorable eyes. Searching can produce a variable
         *  amount of dirtiness. */
        int prior_offset = player->query_appearance_offset();
        if (prior_offset < 45)
        {
            player->set_appearance_offset(max(20 + random(15),
                prior_offset + 10));
        }

        add_action(enter_tunnel, "enter");
        add_action(enter_tunnel, "crawl");
        add_action(enter_tunnel, "climb");

        return "Your uncommon interest in the pile of manure is rewarded with "
            + "the discovery of a tunnel under it. As the manure is dry, you "
            + "should be able to enter the tunnel if you don't mind getting "
            + "dirty.\n";
    }
    return "Your search reveals nothing special.\n";
}
