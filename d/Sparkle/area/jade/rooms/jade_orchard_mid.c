/*
*  /d/Sparkle/area/jade/rooms/jade_orchard_mid.c
*  Created 2017-02-20 by Martin Berka on Genesis MUD
*  The middle of the orchard hosts a very relaxing rope swing.
*/

#pragma strict_types

#include "../defs.h"
inherit ROOM_DIR + "jade_room";

#include <stdproperties.h>

/* Global variables */
mapping swing_users; //Store players who have used the swing to prevent abuse


/*
 * Function name: create_room
 * Description  : Room constructor
 */
void
create_room()
{
    set_short("In the middle of an orchard");
    set_long("This is the heart of the orchard. Fruit trees grow thickly "
        + "on all sides. You cannot see anything beyond them except the sky and "
        + "a house far to the southwest. A path leads to the northeast. "
        + "Someone has tied two ropes to a large bough and made a swing. Grass "
        + "and herbs grow underfoot, and the air smells distinctly sweet.\n");

    add_item( ({"swing", "rope swing", "ropes", "board"}), "Two ropes hang "
        + "from the bough of a large tree, a board between them. You could "
        + "probably swing on this.\n" );

    add_cmd_item( ({"on swing", "on rope swing"}), ({"play", "sit", "relax",
        "rest"}), "@@do_swing");


    add_house();
    add_orchard( ({"south", "northwest"}) );

    add_exit(ROOM_DIR + "jade_orchard_n", "northeast");
    add_exit(ROOM_DIR + "jade_orchard_n", "north", 0, 5, 1);
    add_exit(ROOM_DIR + "jade_orchard_e", "east", 0, 3, 1);
    add_exit(ROOM_DIR + "jade_orchard_se", "southeast", 0, 5, 1);
    add_exit(ROOM_DIR + "jade_orchard_sw", "southwest", 0, 5, 1);
    add_exit(ROOM_DIR + "jade_orchard_w", "west", 0, 5, 1);

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
    swing_users = ([]);
}

/*
 * Function name: init
 * Description:   set up commands
 */


/*
 * Function name: do_swing
 * Description:   Let the player relax on the rope swing; restores up to 10%
 *      of mana range and reduces panic by 25% the first two times per reset.
 *      Overuse hurts.
 * Returns      : 1 (command recognized)
 */
int
do_swing()
{
    object tp = this_player();
    int previous_swing_count = swing_users[tp->query_name()];

    if (previous_swing_count > 4) //Sixth time, seriously enough.
    {

        if (tp->query_hp() > 50)
                {
            write("You're so bored that you fall off the swing. That was not "
                + "relaxing at all.\n");
            tell_room( this_object(), QCTNAME(tp) + " tries to "
                + "swing, but falls off.\n", ({tp}) );
            //Minor, objective injury, not like the myth-proof fence.
            tp->heal_hp(-25);
            tp->add_panic(25);  //And small mind penalties
            tp->add_mana(-50);
            swing_users[tp->query_name()] = previous_swing_count + 1;
        }
        else
        {
            write("That swing looks unsafe, maybe you should wait until you "
                + "can take a fall.\n");
        }

        return 1;
    }
    if (previous_swing_count > 1) //Already did this at least twice
    {
        write("You start to swing, but it just isn't the same as the first few "
            + "times. Maybe you'll enjoy it again later.\n");
        tell_room( this_object(), QCTNAME(tp) + " swings on "
            + "the rope swing.\n", ({tp}) );
        swing_users[tp->query_name()] = previous_swing_count + 1;

        return 1;
    }

    write("You sit down on the swing, gripping the rope on each side. The"
        + "device creaks, but holds your weight, and "
        + "proves easy to balance on. You sway back and forth, and start to "
        + "swing. Up above, someone is laughing, but you don't mind. For a few "
        + "relaxing moments, there is only you and the orchard.\n"
        + "As you finish and stand up, you feel more relaxed and "
        + "clear-headed.\n");
    tell_room( this_object(), QCTNAME(this_player()) + " swings peacefully on "
        + "the rope swing.\n", ({this_player()}) );

    swing_users[tp->query_name()] = previous_swing_count + 1;

    //Restore mana and calm
    int missing_mana = tp->query_max_mana() - tp->query_mana();
    tp->add_mana(min(tp->query_max_mana() / 10, missing_mana, ));
    tp->add_panic(tp->query_panic() / -4); //Easier since optimum is 0.

    return 1;
} /* do_swing */



void
init()
{
    ::init();
    add_action(do_swing, "swing"); //add_cmd_item requires extra words.
} /* init */
