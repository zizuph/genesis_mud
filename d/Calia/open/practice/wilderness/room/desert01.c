// ROOM:  Calian desert - /d/Calia/open/practice/wilderness/desert01

    /*  Calia Domain

        HISTORY
        1998-08-26 Created by Uhclem.

        PURPOSE
        This is a coding example for new Calian wizards.  There is no desert in
        Calia - this code is strictly for practice!

    */

// INCLUSIONS AND DEFINITIONS

inherit "/std/room";

#define WILDERNESS_ROOM    "/d/Calia/open/practice/wilderness/room"

// ROOM DEFINITION

void
create_room()
{

    /* DESCRIPTION */

    set_short("Calian desert");

    set_long("You stand in the midst of a great desert." +
        " Blazing sand stretches before you in all" +
        " directions, reflecting the heat of the relentless" +
        " sun and scorching your feet. The air is motionless, and" +
        " not a single cloud offers hope of relief. Only an" +
        " old trail, barely visible in the sand, gives evidence" +
        " that some other travelers have passed this way before you.\n");

    /* ITEMS */

    add_item(({"sand", "desert"}), "The sand stretches on" +
        " endlessly in all directions.\n");

    add_item(({"trail", "old trail"}), "The trail leads east and" +
        " west to the horizon.\n");

    add_item(({"sun", "horizon", "sky"}), "The sun is" +
        " directly overhead, and the horizon is merely a" +
        " flat line dividing sand from sky.\n");

    /* EXITS */

    add_exit(WILDERNESS_ROOM + "desert02", "east", 0, 5);
    add_exit(WILDERNESS_ROOM + "desert03", "north", 0, 5);

    /* PROPERTIES */

    add_prop(ROOM_I_LIGHT, 2);
    add_prop(ROOM_I_HIDE, 98);

    }
