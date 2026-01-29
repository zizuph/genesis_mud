/* /d/Calia/argos/farmstead/rooms/farmhouse.c
**   A farmhouse in the farmyard outside of Argos
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   2/21/20    Brine      Created
**
*/

#pragma strict_types

inherit  "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include "defs.h"

// Variables for keeping track of quest state
int fire_lit = 0;
int water_in_cauldron = 0;
int turnip_in_cauldron = 0;
int soup_cooked = 0;
object quest_solver = 0;
object container;
object skull_pointer = 0;
object spirit;

void
create_room()
{
    seteuid(getuid());

    set_short("Inside an abandoned farmhouse");

    set_long(
        "You are inside a badly run-down farmhouse that has has clearly been "
        + "abandoned some time ago. It consists of a single, sparsely "
        + "furnitured room, and is of simple, yet sturdy, construction. A "
        + "cauldron is suspended over a hearth at the centre of the stone "
        + "floor, and a table stands next to it.\n"
    );

    add_item(
        ({
            "room", "here", "farmhouse", "house", "farm house", "run-down "
            + "farmhouse", "badly run-down farmhouse"
        }),
        long()
    );

    add_item(
        "furniture",
        "An old, wooden table stands next to the hearth. A cupboard lies in "
        + "pieces on the floor.\n"
    );

    add_item(
        ({ "cupboard", "pieces", "rubble" }),
        "This was once a cupboard, no doubt used for holding various "
        + "household items. Now it is little more than rubble, lying "
        + "smashed on the floor.\n"
    );

    add_item(
        ({ "table", "old table", "wooden table", "old wooden table" }),
        "It is an old but sturdy wooden table, just about big enough "
        + "for two people to dine and do daily household chores on. A "
        + "couple of cracked bowls and some cutlery are stacked on "
        + "the middle of the table, otherwise it is mostly covered with "
        + "dust and leaves. @@table_desc"
    );

    add_item(
        ({ "bowl", "cracked bowl", "bowls", "cracked bowls" }),
        "They are a pair of cracked and dusty ceramic plates, stacked on "
        + "top of the table along with some cutlery.\n"
    );

    add_item(
        ({ "cutlery", "spoon", "spoons", "ladle" }),
        "A few spoons and a ladle, all made from wood, lie on the table, "
        + "alongside a couple of cracked bowls.\n"
    );

    add_item(
        ({ "floor", "stone floor", "flagstones", "ground" }),
        "Large, roughly cut flagstones are carefully laid out to create a "
        + "solid stone floor, with tightly packed dirt filling the gaps "
        + "in between.\n"
    );

    add_item(
        ({ "gap", "gaps" }),
        "They are tightly packed with dry dirt, and do not seem to hold "
        + "anything of interest.\n"
    );

    add_item(
        ({ "dirt", "tightly packed dirt", "surface" }),
        "Dirt has been tightly packed into every gap of the stone floor, "
        + "giving it a mostly coherent surface.\n"
    );

    add_item(
        ({
            "wall", "walls", "wooden walls", "post", "posts", "corner posts",
            "log", "logs", "plank", "planks", "planks of wood"
        }),
        "The walls are roughly hewn planks of wood, with solid logs serving "
        + "as corner posts. The wood is chipped and grey, but still appears "
        + "to be sturdy.\n"
    );

    add_item(
        ({ "roof", "rafter", "rafters", "joist", "joists", "beam", "beams" }),
        "The roof is propped by a series of rafters resting atop joist beams "
        + "that protrude from the top of the walls and run across the space "
        + "above the room. A smoke hood hangs from a joist above the hearth.\n"
    );

    add_item(
        ({ "hood", "smoke hood" }),
        "It is suspended above the hearth and connected to a pipe, obviously "
        + "designed to capture smoke from the hearth and lead it outside.\n"
    );

    add_item(
        ({ "pipe", "flue" }),
        "A pipe made from thin sheat metal runs from the top of the smoke "
        + "hood and up through the roof, serving as a makeshift chimney.\n"
    );

    add_item(
        ({
            "hearth", "fire place", "fireplace", "fire-place", "centre",
            "middle"
        }),
        "A brick-lined stone hearth sits in the middle of the floor. A "
        + "cauldron is suspended above it. @@fire_state"
    );

    add_item(
        ({
            "brick", "bricks", "brick lining", "circle", "fire cracked bricks",
            "circle of bricks", "brick circle", "border"
        }),
        "Fire cracked bricks laid in a circle form the border of the hearth.\n"
    );

    add_item(
        ({ "debris", "leaves", "dust" }),
        "Debris, leaves and dust cover just about everything in here.\n"
    );

    add_item(
        ({ "window", "windows", "shutter", "shutters" }),
        "The windows have long since lost their shutters, allowing dust and "
        + "leaves to enter freely into the room.\n"
    );

    add_item(
        ({ "cauldron", "cauldron chains", "chain", "chains" }),
        "A cauldron is suspended on chains above the hearth. @@cauldron_desc"
    );

    add_prop("ROOM_I_INSIDE", 1);

    add_exit(ROOM_DIR + "farmyard", "out");

    reset_room();
    container = clone_object(OBJ_DIR + "invis_container");
    container->move(TO);
}

void
reset_quest()
{
    quest_solver = 0;

    if (water_in_cauldron)
    {
        tell_room(
            TO,
            "The contents of the cauldron evaporate.\n",
            0,
            TO
        );
        water_in_cauldron = 0;
        turnip_in_cauldron = 0;
        soup_cooked = 0;
    }

    if (skull_pointer)
    {
        tell_room(
            TO,
            "The " + skull_pointer->short() + " on the table turns to "
            + "dust.\n",
            0,
            TO
        );
        skull_pointer->remove_object();
    }
}

void
reset_room()
{
    if (present(quest_solver))
    {
        // delay reset by one reset cycle if quest doer is still in the room,
        // it would be annoying if the room reset in the middle of doing the
        // quest
        quest_solver = 0;
    } else {
        reset_quest();
    }

    if (fire_lit)
    {
        tell_room(
            TO,
            "The fire in the hearth flickers and dies out.\n",
            0,
            TO
        );
        fire_lit = 0;
    }

    if (!spirit)
    {
        spirit = clone_object(NPC_DIR + "spirit");
        spirit->move(TO);
        tell_room(
            TO,
            "A shrill cry alerts you to the presence of " + QNAME(spirit)
            + ".\n",
            0,
            spirit
        );
    }
}

int
query_soup_cooked()
{
    return soup_cooked;
}

void
set_soup_cooked()
{
    soup_cooked = 1;
}

void
set_has_water()
{
    water_in_cauldron = 1;
}

void
set_has_turnip()
{
    turnip_in_cauldron = 1;
}

void
toggle_fire_lit()
{
    fire_lit = fire_lit ? 0 : 1;
}

string
fire_state()
{
    return fire_lit ? "A fire burns in the hearth.\n"
        : "You could probably light a fire here.\n";
}

object
get_skull_ref()
{
    return skull_pointer;
}

void
reset_skull_pointer()
{
    skull_pointer = 0;
}

string
cauldron_desc()
{
    if (soup_cooked)
    {
        return "It contains some turnip soup.\n";
    }

    if (turnip_in_cauldron)
    {
        return "It contains some water and a turnip. Maybe you could cook "
            + "some soup?\n";
    }

    if (water_in_cauldron)
    {
        return "It contains some water. You could probably toss something "
            + "into it... Like a turnip, maybe?\n";
    }

    return "It contains nothing but dust. You could probably fill water "
        + "into it from a suitable container.\n";
}

string
table_desc()
{
    if (skull_pointer)
    {
        return "A " + skull_pointer->short() + " is placed at the end of "
            + "the table.\n";
    }
    return "There seems to be enough space that you could place something "
        + "at the end of the table. But what would you want to place there, "
        + "and why? Hmm.\n";
}

int
fill_cauldron(string arg)
{
    notify_fail(
        capitalize(query_verb()) + " what with what from where?\n"
    );

    if (!strlen(arg))
    {
        return 0;
    }

    object *buckets;
    int result = parse_command(
        arg,
        all_inventory(TP) + all_inventory(environment(TP)),
        "[the] 'cauldron' 'with' [the] 'water' 'from' / 'of' [the] %i %s",
        buckets
    );

    if (result)
    {
        int num_hits;
        object bucket;

        buckets = NORMAL_ACCESS(buckets, 0, 0);

        num_hits = sizeof(buckets);
        if (num_hits == 0)
        {
            // No bucket in player's inventory or environment
            return 0;
        }
        if (num_hits > 1)
        {
            write("You can only fill from one item at a time!\n");
            return 1;
        }

        bucket = buckets[0];
        if (MASTER_OB(bucket) != OBJ_DIR + "bucket")
        {
            write("Can't fill water into the cauldron from that.\n");
            return 1;
        }

        if (!bucket->query_has_water())
        {
            write("There is no water in the " + bucket->short() + "!\n");
            return 1;
        }

        if (environment(bucket) != TP)
        {
            write(
                "You must possess the " + bucket->short() + " to do that!\n"
            );
            return 1;
        }

        if (water_in_cauldron)
        {
            write(
                "The cauldron is already filled with water!\n"
            );
            return 1;
        }

        write(
            "You fill the cauldron with water from your " + bucket->short()
            + ".\n"
        );
        tell_room(
            TO,
            QCTNAME(TP) + " fills the cauldron with water from "
            + TP->query_possessive() + " " + bucket->short() + ".\n",
            TP
        );
        quest_solver = TP;
        set_has_water();
        write("Your " + bucket->short() + " crumbles apart.\n");
        bucket->remove_object();
        // TODO: questprop
        return 1;
    }

    return 0;
}

int
place_turnip(string arg)
{
    notify_fail(
        capitalize(query_verb()) + " what in where?\n"
    );

    if (!strlen(arg))
    {
        return 0;
    }

    object *turnips;
    int result = parse_command(
        arg,
        all_inventory(TP) + all_inventory(environment(TP)),
        "[the] %i 'in' / 'into' [the] 'cauldron'",
        turnips
    );

    if (result)
    {
        int num_hits;
        object turnip;

        turnips = NORMAL_ACCESS(turnips, 0, 0);

        num_hits = sizeof(turnips);
        if (num_hits == 0)
        {
            // No turnip in player's inventory or environment
            return 0;
        }

        if (!water_in_cauldron)
        {
            write(
                "You should probably fill the cauldron with water first.\n"
            );
            return 1;
        }

        if (turnip_in_cauldron)
        {
            write(
                "There is already a turnip in the cauldron!\n"
            );
            return 1;
        }

        turnip = turnips[0];
        if (MASTER_OB(turnip) != OBJ_DIR + "turnip")
        {
            write("That's not the right kind of turnip!\n");
            return 1;
        }

        if (num_hits > 1)
        {
            write("One turnip should be enough.\n");
            return 1;
        }

        if (environment(turnip) != TP)
        {
            write(
                "You must possess the " + turnip->short() + " to do that!\n"
            );
            return 1;
        }

        write(
            "You toss " + turnip->short() + " into the cauldron. It makes a "
            + "satisfying little splish as it hits the water.\n"
        );
        tell_room(
            TO,
            QCTNAME(TP) + " tosses " + turnip->short() + " into the "
            + "cauldron.\n",
            TP
        );
        quest_solver = TP;
        set_has_turnip();
        turnip->remove_object();
        // TODO: questprop
        return 1;
    }

    return 0;
}

int
light_fire(string arg)
{
    if (arg == "fire")
    {
        if (!fire_lit)
        {
            toggle_fire_lit();
            write("You light a fire in the hearth.\n");
            tell_room(
                TO,
                QCTNAME(TP) + " lights a fire in the hearth.\n",
                TP
            );
            return 1;
        }
        write("There is already a fire going in the hearth.\n");
        return 1;
    }
    notify_fail("Light what? A fire?\n");
    return 0;
}

int
extinguish_fire(string arg)
{
    if (arg == "fire")
    {
        if (fire_lit)
        {
            toggle_fire_lit();
            write("You extinguish the fire in the hearth.\n");
            tell_room(
                TO,
                QCTNAME(TP) + " extinguishes the fire in the hearth.\n",
                TP
            );
            return 1;
        }
        write("There is no fire burning in the hearth.\n");
        return 1;
    }
    notify_fail("Extinguish what? The fire?\n");
    return 0;
}

int
cook_soup(string arg)
{
    notify_fail("Cook what?\n");

    if (strlen(arg) &&
        parse_command(arg, ({}), "[the] [some] [turnip] 'soup' %s"))
    {
        if (water_in_cauldron && turnip_in_cauldron)
        {
            if (fire_lit)
            {
                quest_solver = TP;
                soup_cooked = 1;
                write(
                    "You cook some turnip soup in the cauldron! It smells "
                    + "... quite bland, honestly.\n"
                );
                tell_room(
                    TO,
                    QCTNAME(TP) + " cooks some turnip soup in the cauldron! "
                    + "It smells ... quite bland, honestly.\n",
                    TP
                );
                TP->add_prop(FARMSTEAD_I_COOKED, 1);
                return 1;
            }
            write("There is no fire going in the hearth.\n");
            return 1;
        }
        write("There's nothing to cook soup from in the cauldron.\n");
        return 1;
    }
    return 0;
}

int
place_skull(string arg)
{
    string verb = query_verb();
    notify_fail(capitalize(verb) + " what on where?\n");
    string pattern = "[the] %i 'on' / 'at' [the] [end] [of] [the] 'table'";
    object* skulls;
    if (
        strlen(arg)
        && parse_command(
            arg,
            all_inventory(TP) + all_inventory(environment(TP)),
            pattern,
            skulls
        ))
    {
        skulls = NORMAL_ACCESS(skulls, 0, 0);

        int num_hits = sizeof(skulls);

        if (num_hits == 0)
        {
            return 0;
        }

        object skull = skulls[0];
        if (MASTER_OB(skull) != OBJ_DIR + "skull")
        {
            write("That doesn't go on the table.\n");
            return 1;
        }

        if (num_hits > 1)
        {
            write(
                "You can only " + verb + " one object on the table at "
                + "a time.\n"
            );
            return 1;
        }

        if (environment(skull) != TP)
        {
            write("You must possess the " + skull->short() + " to do that!\n");
            return 1;
        }

        if (skull_pointer)
        {
            write("There is already a skull awaiting supper at the table!\n");
            return 1;
        }

        write(
            "You " + verb + " the " + skull->short() + " at the end of the "
            + "table. It looks quite ready for supper.\n"
        );
        tell_room(
            TO,
            QCTNAME(TP) + " " + verb + "s a " + skull->short() + " at the end "
            + "of the table.\n",
            TP
        );
        TP->add_prop(FARMSTEAD_I_PLACED_SKULL, 1);
        skull_pointer = skull;
        skull->move(container, 1);
        quest_solver = TP;
        return 1;
    }
    return 0;
}

void
init()
{
    ::init();
    add_action(fill_cauldron, "fill");
    add_action(place_turnip, "put");
    add_action(place_turnip, "toss");
    add_action(light_fire, "light");
    add_action(extinguish_fire, "extinguish");
    add_action(cook_soup, "cook");
    add_action(place_skull, "place");
    add_action(place_skull, "put");
    add_action(place_skull, "set");
}
