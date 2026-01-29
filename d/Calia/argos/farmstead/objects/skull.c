/* /d/Calia/argos/farmstead/objects/skull.c
**   A toothless skull, a quest object for the farmstead quest
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   2/27/20    Brine      Created
**
*/

#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include "defs.h"

// Variables for keeping track of skull state
int has_teeth = 0;
int has_hair = 0;

void
create_object()
{
    seteuid(getuid());

    set_name("skull");

    set_adj("toothless");

    set_short("@@short_desc");

    set_long("@@long_desc");

    add_prop(OBJ_I_VOLUME, 300);
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_M_NO_SELL, "The " + short() + " isn't worth anything.\n");

    add_item(
        ({
            "socket", "sockets", "tooth socket", "tooth sockets",
            "deep sockets", "jaws"
        }),
        "Deep tooth sockets line the jaws of the skull. Once they held teeth, "
        + "now they are empty. Maybe you could insert something into them?\n"
    );

    add_item(
        ({
            "crack", "jagged crack", "deep crack", "deep jagged crack", "dome"
        }),
        "A deep, jagged crack runs across the dome of the skull. It looks "
        + "deep enough that you could probably stuff something into it.\n"
    );
}

/*
 * Function name: short_desc
 * Description  : Calculates the short description of the object based
 *                on which quest steps have been completed
 */
string
short_desc()
{
    if (has_teeth && !has_hair)
    {
        return "grinning skull";
    }
    if (!has_teeth && has_hair)
    {
        return "golden-haired toothless skull";
    }
    if (has_teeth && has_hair)
    {
        return "golden-haired grinning skull";
    }
    return "toothless skull";
}

/*
 * Function name: long_desc
 * Description  : Calculates the short description of the object based
 *                on which quest steps have been completed
 */
string
long_desc()
{
    string desc = "This is the skull of a long-dead human. It has a rather "
        + "prominent jaw.\n";
    if (has_hair)
    {
        desc += "A lump of straw has been attached to its top, giving it "
            + "the appearance of having long, golden blonde hair.\n";
    }
    else
    {
        desc += "A jagged crack runs across its dome. It is quite deep.\n";
    }
    if (has_teeth)
    {
        desc += "A set of smooth pebbles serve as dentures, giving the skull "
            + "a broad and toothy grin.\n";
    }
    else
    {
        desc += "All the teeth have fallen out, leaving only deep sockets.\n";
    }
    return desc;
}

int
query_teeth()
{
    return has_teeth;
}

int
query_hair()
{
    return has_hair;
}

/*
 * Function name: add_feature
 * Description  : Called to update internal state as quest steps are completed,
 *                so that the successful completion of steps can be tracked
 *                as well as verified visually by the player
 * Arguments    : string what: "teeth" | "hair" - What feature to add
 */
void
add_feature(string what)
{
    switch (what)
    {
        case "teeth":
            has_teeth = 1;
            remove_adj("toothless");
            add_adj("grinning");
            remove_item("socket");
            break;
        case "hair":
            has_hair = 1;
            add_adj("golden-haired");
            remove_item("crack");
            break;
        default:
            return;
    }
}

/*
 * Function name: stuff_hair
 * Description  : Parses player commands to allow completing a step in
 *                the farmhouse quest, if the player has found the
 *                correct items.
 * Arguments    : string arg - The arguments entered by the player
 * Returns      : int 1/0 - success/ failure
 */
int
stuff_hair(string arg)
{
    notify_fail(
        capitalize(query_verb()) + " what into what?\n"
    );

    if (!stringp(arg))
    {
        return 0;
    }

    object *straws;
    int result = parse_command(
        arg,
        all_inventory(TP) + all_inventory(environment(TP)),
        "[the] %i 'in' / 'into' [the] 'crack' / 'skull' %s",
        straws
    );

    if (result)
    {
        int num_hits;
        object straw;

        straws = NORMAL_ACCESS(straws, 0, 0);

        num_hits = sizeof(straws);
        if (num_hits == 0)
        {
            // Player doesn't have available straw
            return 0;
        }
        if (num_hits > 1)
        {
            // Trying to stuff too many items
            write("You can only stuff one item at a time!\n");
            return 1;
        }

        straw = straws[0];
        if (MASTER_OB(straw) != OBJ_DIR + "straw")
        {
            write("That doesn't go there.\n");
            return 1;
        }

        if (environment() != TP)
        {
            write("You must possess the " + short() + " to do that!\n");
            return 1;
        }

        if (query_hair())
        {
            write(
                "Something has already been stuffed into the " + short()
                + "!\n"
            );
            return 1;
        }

        write(
            "You stuff the " + straw->short() + " neatly into the crack on "
            + "the dome of the " + short() + ". It now looks very dashing, "
            + "indeed!\n"
        );
        straw->remove_object();
        TP->add_prop(FARMSTEAD_I_HAIR, 1);
        add_feature("hair");
        return 1;
    }

    return 0;
}

/*
 * Function name: insert_teeth
 * Description  : Parses player commands to allow completing a step in
 *                the farmhouse quest, if the player has found the
 *                correct items.
 * Arguments    : string arg - The arguments entered by the player
 * Returns      : int 1/0 - success/ failure
 */
int
insert_teeth(string arg)
{
    notify_fail(
        capitalize(query_verb()) + " what into where?\n"
    );

    if (!stringp(arg))
    {
        return 0;
    }

    object *pebbles;
    int result = parse_command(
        arg,
        all_inventory(TP) + all_inventory(environment(TP)),
        "[the] [handful] [of] %i 'in' / 'into' [the] [deep] [tooth] "
        + "'socket' / 'sockets' / 'skull' %s",
        pebbles
    );

    if (result)
    {
        int num_hits;
        object pebble;

        pebbles = NORMAL_ACCESS(pebbles, 0, 0);

        num_hits = sizeof(pebbles);
        if (num_hits == 0)
        {
            // Player doesn't have available pebbles
            return 0;
        }
        if (num_hits > 1)
        {
            // Trying to insert too many items
            write("You can only insert one handful of items at a time!\n");
            return 1;
        }

        pebble = pebbles[0];
        if (MASTER_OB(pebble) != OBJ_DIR + "pebbles")
        {
            write("That doesn't go there.\n");
            return 1;
        }

        if (environment() != TP)
        {
            write("You must possess the " + short() + " to do that!\n");
            return 1;
        }

        if (query_teeth())
        {
            write(
                "Something has already been inserted into the " + short()
                + "'s tooth sockets!\n"
            );
            return 1;
        }

        write(
            "You carefully insert the " + pebble->short() + " into the "
            + "tooth sockets of the " + short() + ". It now has quite a "
            + "grin!\n"
        );
        pebble->remove_object();
        TP->add_prop(FARMSTEAD_I_TEETH, 1);
        add_feature("teeth");
        return 1;
    }

    return 0;
}

void
init()
{
    ::init();
    add_action(stuff_hair, "stuff");
    add_action(insert_teeth, "insert");
}
