// OBJECT:  magic holly bough

    /* Calia Domain

    HISTORY

    [98-12-17] Created by Uhclem from [D:\CALIA\YULEWARE\BOUGH.DOC].

    PURPOSE

    Christmas decoration: it is "decked" on walls with a magic candy cane. */

// INCLUSIONS AND DEFINITIONS

inherit "/std/container";

#include <stdproperties.h>
#include <composite.h>

// GLOBAL VARIABLES

int Level = 1;

// OBJECT DEFINITION

void
create_container()

    {

    /*  DESCRIPTION  */

    set_name("magic_holly_bough");
    add_name("bough");
    add_name("boughs");
    add_name("holly");
    add_name("bough of holly");
    add_name("boughs of holly");

    set_short("decorative bough of holly hanging high on the wall");

    set_long("A long, graceful bough of holly arcs across the" +
        " wall, its glossy deep green leaves dotted" +
        " with bright red berries.\n");

    /*  PROPERTIES  */

    add_prop(CONT_I_WEIGHT, 150);
    add_prop(CONT_I_VOLUME, 300);
    add_prop(CONT_I_MAX_WEIGHT, 300);
    add_prop(CONT_I_MAX_VOLUME, 600);
    add_prop(OBJ_I_VALUE, 1000000);

    add_prop(OBJ_I_NO_GET,
        "The holly writhes strangely as you reach for it, and" +
        " you even think you hear it growling at you! You" +
        " decide that you'd better leave it right where it is.\n");

    setuid();  /*  "uid" settings required for cloning holly boughs. */
    seteuid(getuid());

    /*  ITEMS  */

    add_item(({"berry", "berries"}),
        "The berries are bright red and contrast vividly with the" +
        " dark green of the leaves.\n");

    add_item(({"leaf", "leaves"}),
        "The leaves are dark green and contrast vividly with the" +
        " bright red of the berries.\n");

    }

// FUNCTIONS

// Function:  bough_upgrade

/*

Purpose:  increase the amount of holly boughs if a player "decks" a room that
is already decked.

Arguments:  none

Returns:  1

*/

int
bough_upgrade()

    {

    object this_room = environment(this_player());
    object mistletoe;
    Level = Level + 1;

    if (Level < 8 &&
        !present("mistletoe", this_player()) &&
        !present("mistletoe", this_object()) &&
        random(2))

        {

        mistletoe = clone_object("/d/Calia/yuleware/mistletoe");
        mistletoe->move(this_object());

        }

    switch (Level)

        {

        case 2:

            set_short("pair of gracefully entwined boughs of" +
                " holly hanging high on the wall");

            set_long("The boughs are wrapped around each other so" +
                " that their glossy leaves and bright" +
                " berries spiral elegantly along the wall.\n");

            break;

        case 3:

            set_short("few boughs of holly covering the length" +
                " of one wall");

            set_long("The holly boughs cascade the length of" +
                " the wall, their deep green leaves and" +
                " bright red berries lending a festive air to" +
                " the room. They would make an excellent" +
                " backdrop for a holiday celebration!\n");

            break;

        case 4:

            set_short("number of boughs of holly" +
                " spreading across two walls and" +
                " onto the ceiling");

            set_long("The holly boughs cascade the length of" +
                " one wall and cross over to another by way" +
                " of the ceiling. They form a lovely arch" +
                " under which to celebrate the holidays.\n");

            break;

        case 5:

            set_short("grand display of boughs of holly ringing" +
                " the room and criss-crossing the ceiling");

            set_long("The holly boughs are stylishly arranged so" +
                " that they wrap around the room making" +
                " an impressive display of lush green leaves" +
                " and bright red berries. Someone has obviously put" +
                " a lot of effort into preparing this" +
                " room for the holidays!\n");

            break;

        case 6:

            set_short("abundance of holly covering nearly every inch" +
                " of the ceiling and walls");

            set_long("You find yourself surrounded by walls" +
                " of lush green leaves and bright red berries, not" +
                " at all what you expected when you walked in" +
                " here! You feel quite jovial in such" +
                " a lavishly decorated room and perhaps even" +
                " a bit intoxicated, as if you had just walked" +
                " into some sort of enchanted holiday forest.\n");

            break;

        case 7:

            set_short("huge heap of holly");

            set_long("The room is decorated with so much holly" +
                " that you can hardly move around in" +
                " it. Nonetheless, the glossy green leaves" +
                " and bright red berries are decorative, and they" +
                " inspire a bit of holiday cheer in you despite a" +
                " mild sense of claustrophobia.\n");

            break;

        default:

            tell_room(this_room,
                "The weight of the holly brings it crashing to" +
                " the ground! A great cloud of green" +
                " smoke suddenly billows from the fallen pile" +
                " of holly boughs, and when it clears" +
                " the holly has all disappeared.\n");

            mistletoe = present("mistletoe");
            if (mistletoe) mistletoe->remove_object();

            remove_object();

        }

    return 1;

    }

// Function:  describe_contents(object for_obj, object *obarr)

/*

Purpose:  override the standard describe_contents message to prevent the
unattractive "empty" message.

Arguments:  object receiving the description, objects to be described.

Returns:  nothing

*/

void
describe_contents(object for_obj, object *obarr)

    {

    if (sizeof(obarr) > 0) for_obj->catch_tell("Deep within the" +
    " holly leaves you see " + COMPOSITE_DEAD(obarr) + ".\n");

    }
