/*
 *  /d/Sparkle/area/city/rooms/inside/enchanter.c
 *
 *  This room is where Karkadelt the Enchanter plies his trade.
 *
 *  Created December 2010, by Cooper Sherry (Gorboth)
 *  Updated March 2017, by Tim Breen (Mirandus) to add a no steal
 *  property.
 */
#pragma strict_types

inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>
#include "../../defs.h"
#include "/d/Sparkle/sys/quests.h"


/* Prototypes */
public void        create_room();
public int         check_exit();
public int         climb_stairs(string arg);
public void        init();


/*
 * Function name:        create_room
 * Description  :        the room constructor
 */
public void
create_room()
{
    set_short("in the enchanter's shop");
    set_long("You have entered what appears to be a place of business,"
      + " yet the feeling in here is unlike anything else you have"
      + " experienced. A strange, palpable energy seems to hang in the"
      + " air, augmented by the many arcane items and images that adorn"
      + " the walls. A large stone table is set before many shelves. A"
      + " counter protrudes from one wall, beneath a prominently placed"
      + " poster which you could probably <read>. In the northeast corner,"
      + " a spiral staircase descends through a hole in the floor. A"
      + " doorway to the south leads back out onto the street.\n\n");

    add_item( ({ "place", "here", "area", "store",
                 "place of business", "room", "shop",
                 "enchanters shop", "enchanter's shop" }),
        "This is the Enchanter's Shop. You'll have to look around a bit"
      + " to get a sense of the place.\n");
    add_item( ({ "business" }),
        "Perhaps you'd like to engage in some yourself?\n");
    add_item( ({ "energy", "palpable energy", "strange energy",
                 "feeling", "strange palpable energy",
                 "strange, palpable energy" }),
        "It is hard to pinpoint exactly what this feeling is all about."
      + " There is a sense of the arcane here, as if the mere presence"
      + " of certain practices and knowledge have changed the aura of"
      + " the surroundings.\n");
    add_item( ({ "arcane", "sense", "sense of the arcane", "aura",
                 "surroundings", "aura of the surroundings" }),
        "It feels ... tingly.\n");
    add_item( ({ "tingle", "tingly feeling" }),
        "Tingle, tingle, tingle!\n");
    add_item( ({ "air" }),
        "The air in here is heavy with strange energy.\n");
    add_item( ({ "arcane item", "arcane items" }),
        "Much in here seems foreign to your experience and knowledge."
      + " A poster on the wall attacts your attention, however.\n");
    add_item( ({ "acrane image", "image", "images", "arcane images" }),
        "The images on the walls are most beguiling.\n");
    add_item( ({ "table", "stone table", "large table",
                 "large stone table" }),
        "The table is perfectly clean and there is nothing upon it.\n");
    add_item( ({ "stone" }),
        "The stone of the table appears to be white marble.\n");
    add_item( ({ "marble", "white marble" }),
        "The marble that makes up the stone table is polished and"
      + " spotlessly clean.\n");
    add_item( ({ "wall", "walls" }),
        "You notice a poster which hangs prominently on the wall.\n");
    add_item( ({ "shelf", "shelves", "many shelves" }),
        "The shelves are stuffed with very old looking scrolls, books,"
      + " and papers.\n");
    add_item( ({ "scroll", "scrolls", "book", "books", "paper",
                 "papers" }),
        "The contents of the shelves are beyond your reach behind the"
      + " counter.\n");
    add_item( ({ "counter" }),
        "The counter separates the front of the shop from the work area"
      + " toward the back, where the enchanter usually stands.\n");
    add_item( ({ "work area" }),
        "It is off limits.\n");
    add_item( ({ "stair", "staircase", "stairs", "spiral stair",
                 "steps", "spiral staircase", "northeast",
                 "northeast corner", "corner" }),
        "Spiral stairs in the northeast corner lead down through a hole"
      + " in the floor.\n");
    add_item( ({ "hole", "hole in the floor" }),
        "The hole in the floor allows access via the spiral staircase to"
      + " some lower level of the shop.\n");
    add_item( ({ "lower level", "lower level of the shop" }),
        "You'd probably need to climb down the stairs to know more.\n");
    add_item( ({ "door", "doorway", "south",
                 "doorway to the south" }),
        "The door opens back up onto the street.\n");
    add_item( ({ "street" }),
        "You could head south out of the shop to see it again if you"
      + " wished.\n");
    add_item( ({ "floor", "down", "ground" }),
        "The floor is neatly swept.\n");
    add_item( ({ "ceiling", "up", "roof" }),
        "The ceiling slopes upward high above your head.\n");
    add_item( ({ "sky" }),
        "The sky is not visible here, indoors.\n");

    add_item( ({ "poster", "prominent poster",
                 "prominently placed poster" }),
        &read_file("/d/Sparkle/area/orc_temple/text/enchanter_poster.txt"));

    add_cmd_item( ({ "poster", "the poster" }),
                  ({ "read", }), 
        &read_file("/d/Sparkle/area/orc_temple/text/enchanter_poster.txt"));

    add_prop(ROOM_I_LIGHT, ALWAYS_LIGHT);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_S_MAP_FILE, "sparkle_city_current.txt");
    add_prop(ROOM_M_NO_STEAL,
        "Just as you are reaching out to make your attempt at thievery,"
      + " you feel as though your hand is slapped by some invisible force."
      + " There must be some powerful enchantments in this room to prevent"
      + " such an action.\n");

    add_exit(STREET_DIR + "center_b", "south");
    add_exit("/d/Genesis/imbuement/enchanter_forge", "down", 
        check_exit, 1, 1);

    add_npc("/d/Sparkle/area/orc_temple/npc/enchanter", 1, &->arm_me());
} /* create_room */


/*
 * Function name:        check_exit
 * Description  :        see if players can use this exit
 * Returns      :        0 - let the player move this way
 *                       1 - block the player
 */
public int
check_exit()
{
    if (this_player()->test_bit("Sparkle",
            ORCTEMPLE_GHOST_GROUP,
            ORCTEMPLE_GHOST_BIT))
    {
        write("\nYou descend the spiral staircase ... \n\n");
        return 0;
    }

    write("A strange force prevents you from approaching the staircase."
      + " You glance up, and notice the enchanter peering at you. Perhaps"
      + " you could <ask> him about the staircase?\n");

    if (this_player()->query_wiz_level())
    {
        write("\nSince you're a wizard, you can go anyway ...\n\n");
        return 0;
    }

    return 1;
} /* check_exit */


/*
 * Function name:        climb_stairs
 * Description  :        Let players climb the stairs
 * Arguments    :        What the player typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
climb_stairs(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("Climb where?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[down] [the] [spiral] 'stair' / 'stairs' / 'stairway'"
      + " / 'staircase' [case]"))
    {
        notify_fail("Do you want to climb down the stairs perhaps?\n");
        return 0;
    }

    if (this_player()->query_wiz_level())
    {
        notify_fail("Normally, we would move the player 'down' here using"
          + " command(). Since you're a wizard, that won't work. You can"
          + " simply type <down> manually to use the stairs.\n");
        return 0;
    }

    this_player()->command("$d");
    return 1;
} /* climb_stairs */


/*
 * Function name:        init
 * Description  :        add some actions to the player 
 */
public void
init()
{
    ::init();

    add_action(climb_stairs, "climb");
    add_action(climb_stairs, "descend");
} /* init */
