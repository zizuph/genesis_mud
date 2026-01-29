/*
*  /d/Sparkle/area/jade/rooms/jade_orchard_w.c
*  Created 2017-02-20 by Martin Berka on Genesis MUD
*
*/

#pragma strict_types

#include "../defs.h"
inherit ROOM_DIR + "jade_room";

#include <stdproperties.h>

/* Global variables */
mapping fruit_users;

/* Prototypes */
int grab_fruit(string str);
int leave_to_stand();

/*
 * Function name: create_room
 * Description  : Room constructor
 */
void
create_room()
{
    object gate;
    set_short("The western part of an orchard");
    set_long("Fruit trees grow to the north and to the east of this unplanted "
        + "space, which hosts a pile of ripe fruits. "
        + "There is a "
        + "fence beyond the northern trees, which turns south here. A large gate "
        + "allows passage to the west side; a path runs through it and to "
        + "the northeast. To the south stands "
        + "a two-storey house, bare walls unmarked by doors or windows.\n");

    add_item( ({"space", "empty space", "unplanted space"}),
        "The space immediately around the path could fit several trees, but "
        + "is empty apart from the lush grass and the pile of fruit\n" );

    add_house( ({"south"}) );
    add_fence( ({"southwest", "north"}) );
    add_orchard( ({"northwest"}) );
    remove_item("fruit");
    add_item( ({"fruit", "ripe fruit", "fruits", "ripe fruits", "pile",
        "pile of fruit", "pile of fruits", "stack", "heap"}),
        "Ripe fruits are piled by the path. It might be "
        + "possible to grab one.\n");

    add_exit(ROOM_DIR + "jade_stand", "west", "@@leave_to_stand");
    add_exit(ROOM_DIR + "jade_orchard_n", "northeast");
    add_exit(ROOM_DIR + "jade_orchard_sw", "southeast", 0, 5, 1);
    add_exit(ROOM_DIR + "jade_orchard_mid", "east", 0, 5, 1);

    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    reset_room();

    add_item( ({ "gate", "sturdy gate", "west gate", "gateway",
        "wooden gate", "sturdy wooden gate", "western gate",
        "fence gate", "gate to the west", "gateway to the west",
        "fencegate", "gate in the fence", "sharpened gate" }),
        "A gate leads through the fence. Its construction is "
        + "much like the fence's, but this side is smooth and looks like it "
        + "could be opened with just a push.\n");
    add_cmd_item( ({ "gate", "sturdy gate", "west gate", "gateway",
        "wooden gate", "sturdy wooden gate", "western gate",
        "fence gate", "gate to the west", "gateway to the west",
        "fencegate", "gate in the fence", "sharpened gate" }),
        ({"push", "open", "enter", "leave through", "go through"}),
        "@@leave_to_stand");

    fruit_users = ([]);
}

/*
 * Function name: get_fruit
 * Description	: Parsing check before calling grab_fruit with get/take command
 * Arguments	: (string) str - text after verb
 * Returns		: (int) Action recognized? 1
 */
int
get_fruit(string str)
{
    if (!parse_command(str, ({ }),
        " [a] 'fruit' / 'fruits' 'from' [the] 'pile' / 'heap' "))
    {
        return 0;
    }
    return grab_fruit(str);
}

/*
 * Function name: grab_fruit
 * Description  : Player may try to take a fruit from the pile. The archer will
 *      not allow an outsider to do this.
 * Returns      : (int) Action recognized? 1
 */
int
grab_fruit(string str)
{
    if (!wildmatch("*fruit*", str))
    {
        return 0;
    }

    if (!looks_green(TP)) //Archer stops anyone who looks like an outsider
    {
        //Send arrow and message
        write("You reach for a fruit. ");
        find_object(ARCHER_ROOM)->send_arrow(this_player());
        tell_room(this_object(), "Someone shouts: If you want fruit, buy it at "
            + "the stand!\n", 0);
        return 1;
    }

    // No local would help themselves to > 3 fruits per arma
    int previous_fruit_count = fruit_users[this_player()->query_name()];
    fruit_users[this_player()->query_name()] = previous_fruit_count + 1;

    if (previous_fruit_count > 3) //Player has already been warned
    {
        tell_room( this_object(), "You reach for a fruit. A voice shouts: Hey! "
            + "None of us chooses to eat that much fruit!\n", 0 );
        find_object(ARCHER_ROOM)->send_arrow(this_player());
        return 1;
    }
    if (previous_fruit_count > 2) //Already had three fruits
    {
        tell_room( this_object(), "You reach for a fruit. A voice shouts: "
            + "Isn't that a bit much?\n", 0);

        return 1;
    }

    object fruit = clone_object(one_of_list(
        ({  "/d/Earthsea/herbs/herb_files/bergamot",
            "/d/Sparkle/area/jade/obj/jade_pear",
            "/d/Sparkle/area/jade/obj/neh_fruit",
            "/d/Genesis/start/human/wild2/obj/apple",
            "/d/Genesis/start/human/wild2/obj/peach",
            "/d/Genesis/start/human/wild2/obj/pear"
        }) ));
    fruit->move(TP);

    write("You grab a " + fruit->query_short() + " from the pile of fruit.\n");
    tell_room( this_object(), QCTNAME(this_player()) + " grabs something "
        + "from the pile of fruit.\n", ({this_player()}) );

    return 1;
}


/*
 * Function name: leave_to_stand
 * Description	: One-way exit to fruit stand, with message.
 * Returns		: (1) block or (0) pass
 */
int
leave_to_stand()
{
    write("You push against the gate and it opens easily, slamming shut "
        + "behind you.\n");
    return 0;
} /* leave_to_stand */


/*
 * Function name: init
 * Description:   set up the commands
 */
void
init()
{
    ::init();
    add_action("get_fruit", "get");
    add_action("get_fruit", "take");
    add_action("grab_fruit", "grab"); //Unique verb, does not require "from pile"
} /* init */
