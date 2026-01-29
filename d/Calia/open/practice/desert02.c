// ROOM:  Calian desert - /d/Calia/open/practice/desert02

    /*  Calia Domain

        HISTORY
        1998-08-15 Created by Uhclem.

        PURPOSE
        This is a coding example for new Calian wizards.  There is no desert in
        Calia - this code is strictly for practice!

    */

// INCLUSIONS AND DEFINITIONS

inherit "/std/room";

// ROOM DEFINITION

void
create_room()
{

    /* DESCRIPTION */

    set_short("Calian desert");

    set_long("You find yourself in the middle of the great" +
        " Calian desert. All you see around you is sand.\n");

    /* ITEMS */

    add_item(({"sand", "desert"}), "The sand stretches on" +
        " endlessly in all directions.\n");

    /* EXITS */

    add_exit("/d/Calia/uhclem/workroom", "east", 0, 5);

    }
