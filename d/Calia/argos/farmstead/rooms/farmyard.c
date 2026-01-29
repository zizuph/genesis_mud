/* /d/Calia/argos/farmstead/rooms/farmyard.c
**   Central yard of the farmstead outside of Argos. It contains a well
**   where the player can fetch water for the farmstead quest, and a few
**   bandits.
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   2/21/20    Brine      Created
**   6/19/20    Brine      Brigands will only chatter amongst themselves if
**                         there is a player present and no combat going on
*/

#pragma strict_types

inherit  "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include "defs.h"

int NUM_BRIGANDS = 3;
object *brigands = allocate(NUM_BRIGANDS);
string *dialogue = ({
    ({
        "Why are you always so mean?",
        "Because I can.",
        "rolleyes"
    }),
    ({
        "Those poor folks we robbed last. They lost all they had!",
        "Their screams were so delightful, though.",
        "say Quiet, you two!"
    }),
    ({
        "Do you ever wonder if birds think?",
        "No, but I sometimes wonder if you do.",
        "chuckle"
    }),
    ({
        "I could really go for some grog right now.",
        "Or a swig of rum!",
        "say If you two didn't drink so much, we'd still have plenty left."
    }),
    ({
        "I wonder what goodies we will find on our next raid!",
        "Maybe we will find you a brain?",
        "smirk"
    })
});
int NUM_DIALOGUES = sizeof(dialogue);

void reset_room();
void brigand_chatter();
int room_has_player();
int room_has_combat();

void
create_room()
{
    seteuid(getuid());

    set_short("A farmyard in an abandoned farmstead");

    set_long(
        "This is the farmyard of an old, long abandoned farmstead. A "
        + "run-down farmhouse and a toolshed stand on the western part, "
        + "a partially collapsed barn occupy the eastern part and an "
        + "overgrown wheat field lies along the northern edge. At the center "
        + "stands a moss-grown well.\n"
    );

    add_item("farmyard", long());

    add_item(
        ({
            "farmstead", "old farmstead", "abandoned farmstead", "long "
            + "abandoned farmstead", "old, long abandoned farmstead"
        }),
        "This farmstead has obviously been abandoned for a long time.\n"
    );

    add_item(
        "western part",
        "A toolshed and a farmhouse stand on the western part of the "
        + "farmstead.\n"
    );

    add_item(
        "eastern part",
        "A partially collapsed barn stands on the eastern part of the "
        + "farmstead.\n"
    );

    add_item(
        ({ "edge", "northern edge" }),
        "A wheat field lies along the northern edge of the farmstead.\n"
    );

    add_item(
        "center",
        "A moss-grown well stands at the center of the farmyard.\n"
    );

    add_item(
        ({
            "farmhouse", "farm house", "house", "run-down farmhouse",
            "run-down house", "run-down farm house"
        }),
        "It appears to be a simple one-story wooden farmhouse, in a bad "
        + "state of disrepair. The windows are all missing their shutters, "
        + "the walls are the distinct grey of rotting wood and the front door "
        + "has fallen off its hinges.\nYou may enter it, if you dare...\n"
    );

    add_item(
        ({ "farmhouse wall", "farmhouse walls", "wood", "rotting wood" }),
        "The farmhouse walls have obviously not been maintained for some "
        + "time, and the elements have taken their toll on them.\n"
    );

    add_item("roof", "Which roof in particular?\n");

    add_item(
        ({
            "farmhouse roof", "house roof", "tiles", "clay tiles",
            "tile", "clay tile", "missing tile", "missing tiles"
        }),
        "The farmhouse roof is made up of clay tiles, a lot of which are "
        + "missing.\n"
    );

    add_item(
        ({ "window", "windows", "shutters", "window shutters" }),
        "All the windows that you can see of the farmhouse are missing their "
        + "shutters completely. It doesn't appear that anyone has "
        + "been living there for quite some time.\n"
    );

    add_item(
        ({ "door", "front door", "farmhouse door" }),
        "The farmhouse door has fallen off its hinges and lies flat on its "
        + "face.\n"
    );

    add_item(
        ({ "hinge", "hinges" }),
        "The hinges holding the farmhouse door are rusted and deteriorated "
        + "so badly that they could no longer support the weight of the "
        + "door.\n"
    );

    add_item(
        ({ "barn", "collapsed barn", "partially collapsed barn" }),
        "It is a moderately sized barn that appears to have seen better days. "
        + "The southernmost wall has tipped over and half the roof is "
        + "gone. The barn doors have fallen down, revealing that there "
        + "is still enough room inside that you could enter it.\n"
    );

    add_item(
        ({ "barn roof", "collapsed roof", "thatched straw roof" }),
        "The barn has a thatched straw roof, half of which seems to have "
        + "collapsed or disappeared with the wind.\n"
    );

    add_item("wall", "Which wall in particular?\n");

    add_item("walls", "Which walls in particular?\n");

    add_item(
        ({
            "southern wall", "southernmost wall", "barn wall", "barn walls"
        }),
        "The southernmost wall of the barn has tipped over. The other walls "
        + "seem to be still standing, if barely.\n"
    );

    add_item(
        ({ "barn door", "barn doors", "rubble", "wooden rubble" }),
        "They were once big and sturdy barn doors, now reduced to wooden "
        + "rubble.\n"
    );

    add_item(
        ({
            "field", "wheat field", "wheatfield", "wheat-field", "overgrown "
            + "field", "overgrown wheat field", "overgrown wheat-field"
        }),
        "It appears to be an overgrown wheat field. You could enter it, "
        + "if you wanted to.\n"
    );

    add_item(
        ({ "toolshed", "tool shed", "shed" }),
        "It is run-down and leaning, but still standing. You could enter "
        + "it if you wanted to.\n"
    );

    add_item(
        ({ "well", "moss-grown well", "brick well" }),
        "It is a brick well covered in moss. A pulley system is supported "
        + "by wooden beams, allowing buckets to be lowered down to fetch "
        + "water from the reservoir of the well.\n"
    );

    add_item(
        ({ "moss", "green moss", "brick", "bricks" }),
        "The bricks of the well are covered in green moss.\n"
    );

    add_item(
        ({ "pulley", "pulley-system", "pulley system", "system" }),
        "The wood is rotten and cracked and the rope is dirty and fleeced, "
        + "but it appears to still be usable. If you had a bucket, you "
        + "could try to fetch water.\n"
    );

    add_item(
        "rope",
        "A dirty old rope, secured to one of the beams, threaded through the "
        + "pulley system and coiled up at the edge of the well. It is "
        + "fleeced and brittle, but still looks quite strong.\n"
    );

    add_item(
        ({ "beam", "beams", "wooden beam", "wooden beams" }),
        "The beams prop up the pulley-system that allows items to be lowered "
        + "into the well and pulled back up again.\n"
    );

    add_exit(ROOM_DIR + "trail", "south");

    set_alarm(1.0, 0.0, reset_room);
    set_alarm(60.0, 60.0, brigand_chatter);
}

void
reset_room()
{
    for (int i = 0; i < NUM_BRIGANDS; i++)
    {
        if (!brigands[i])
        {
            if (i)
            {
                brigands[i] = clone_object(NPC_DIR + "brigand");
                brigands[i]->set_personality(i);
                brigands[i]->move(TO);
                brigands[0]->team_join(brigands[i]);
            } else {
                brigands[i] = clone_object(NPC_DIR + "brigand_leader");
                brigands[i]->move(TO);
            }
            tell_room(
                TO,
                capitalize(LANG_ADDART(brigands[i]->query_short()))
                 + " steps out of the forest.\n",
                brigands,
                brigands[i]
            );
        }
    }
}

void
do_brigand_talk(int which_dialogue, int which_line)
{
    if (
        objectp(brigands[0]) &&
        objectp(brigands[1]) &&
        objectp(brigands[2])
    )
    {
        if (which_line == 0)
        {
            if (CAN_SEE_IN_ROOM(brigands[1]))
            {
                brigands[1]->command(
                    "say to " + OB_NAME(brigands[2]) + " " +
                    dialogue[which_dialogue][which_line]
                );
                set_alarm(
                    2.0,
                    0.0,
                    &do_brigand_talk(which_dialogue, which_line +1)
                );
            }
        } else if (which_line == 1)
        {
            if (CAN_SEE_IN_ROOM(brigands[2]))
            {
                brigands[2]->command(
                    "say to " + OB_NAME(brigands[1]) + " " +
                    dialogue[which_dialogue][which_line]
                );
                set_alarm(
                    2.0,
                    0.0,
                    &do_brigand_talk(which_dialogue, which_line +1)
                );
            }
        } else {
            brigands[0]->command(dialogue[which_dialogue][which_line]);
        }
    }
}

void
brigand_chatter()
{
    if (room_has_player() && !room_has_combat())
    {
        int rand_number = random(NUM_DIALOGUES);

        do_brigand_talk(rand_number, 0);
    }
}

int
room_has_player()
{
    object *things_in_room = all_inventory(TO);

    foreach(object thing: things_in_room)
    {
        if (interactive(thing))
        {
            return 1;
        }
    }

    return 0;
}

int
room_has_combat()
{
    object *things_in_room = all_inventory(TO);

    foreach(object thing: things_in_room)
    {
        if (thing->query_attack())
        {
            return 1;
        }
    }

    return 0;
}

/*
 * Function name: enter_func
 * Description  : Allows the player to enter locations without obvious exits,
 *                and gives a helpful hint if it fails.
 * Arguments    : string where - The name of the room to move to.
 * Returns      : int 1/0 - success/failure.
 */
int
enter_func(string where)
{
    string location = ROOM_DIR;
    string follow_dir = "";

    switch (where)
    {
        case "farmhouse":
        case "farm house":
            follow_dir = "farmhouse";
            location += follow_dir;
            break;
        case "shed":
        case "toolshed":
        case "tool shed":
            follow_dir = "toolshed";
            location += follow_dir;
            break;
        case "barn":
        case "partially collapsed barn":
            follow_dir = "barn";
            location += follow_dir;
            break;
        case "field":
        case "wheat field":
        case "overgrown field":
        case "overgrown wheat field":
        case "wheat-field":
        case "wheatfield":
        case "overgrown wheat-field":
        case "overgrown wheatfield":
            follow_dir = "field";
            location += follow_dir;
            break;
        default:
            notify_fail("Enter what? The farmhouse, the tool shed, the field, "
                + "or the barn?\n");
            return 0;
    }

    if (objectp(brigands[0]))
    {
        brigands[0]->command("say This is our farmstead now, shoo!");
        write(brigands[0]->query_The_name(TP) + " stands in your way.\n");
        if (!TP->query_wiz_level())
        {
            return 1;
        }
    }

    set_dircmd(follow_dir);
    write("You enter the " + where + ".\n");
    tell_room(
        TO,
        QCTNAME(TP) + " enters the " + where + ".\n",
        TP
    );
    TP->move_living("M", location);
    tell_room(
        location,
        QCTNAME(TP) + " arrives.\n",
        TP
    );
    return 1;
}

/*
 * Function name: fetch_water
 * Description  : Check player's inventory for bucket, and fill it with
 *                water if present. Necessary for the farmstead quest
 */
int
fetch_water(string arg)
{
    if (arg != "water")
    {
        notify_fail("Fetch what? Water?\n");
        return 0;
    }

    mixed bucket = present("battered bucket", this_player());
    if (intp(bucket) && bucket == 0)
    {
        notify_fail("You'll need a bucket for that.\n");
        return 0;
    } else if (objectp(bucket))
    {
        if (bucket->volume_left() < 5000)
        {
            notify_fail("There's not enough free volume in your bucket.\n");
            return 0;
        }

        object water = clone_object(OBJ_DIR + "water");
        water->move(bucket);
        bucket->set_has_water();
        write(
            "Using the rope and pulley, you lower the " + bucket->short()
            + " into the well until you hear a splash. When you pull it back "
            + "up, it is considerably heavier.\n"
        );
        tell_room(
            TO,
            QCTNAME(TP) + " lowers " + TP->query_possessive() + " "
            + bucket->short() + " into the well and fetches some water.\n",
            TP
        );
        return 1;
    }

    // Shouldn't happen, but safety first
    write("You'll need a bucket for that.\n");
    return 0;
}

void
init()
{
    ::init();
    add_action(enter_func, "enter");
    add_action(fetch_water, "fetch");
}
