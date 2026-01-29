/*
 * This is a very basic workroom
 * Finwe, November 2016
 */

// this is the standard workroom file
inherit "/std/workroom";
// this lets the room do random noises or actions
inherit "/d/Faerun/std/room_tell";

// always include /d/Faerun/defs.h in all files. Has basic defs
#include "/d/Faerun/defs.h"
#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>

void create_workroom()
{
    set_short("A large workroom");  // no period needed in short descriptions
    set_long("This is a simple workroom. It is made of stone blocks " +
        "and square shaped. Against one wall sits a table with a chair. " +
        "The ceiling is open allowing light to fill the room.\n");

// describes parts of the room
    add_item(({"walls"}),
        "The walls are smooth and made of stone blocks. They are set " +
        "together so tightly that no seams are visible.\n");
    add_item(({"floor", "ground", "down"}),
        "The floor is swept clean. It is smooth and constructed of stone " +
        "blocks. A large carpet covers the floor.\n");
    add_item(({"carpet", "rug"}),
        "The carpet is plush and green, and looks like a lawn. Spots of " +
        "yellow, red, purple, orange dot the carpet, and look like " +
        "wildflowers.\n");
    add_item(({"ceiling", "up"}),
        "The ceiling is high above your head. It is open and allows light " +
        "to filter into the workroom.\n");
    add_item(({"blocks", "stone blocks"}),
        "The stone blocks are smooth and square shaped. They make up the " +
        "workroom.\n");
    add_item(({"table"}),
        "It is made of wood and looks heavy. It sits agains a wall and is " +
        "littered with papers.\n");
    add_item(({"chair"}),
        "The chair looks comforable and well used. it is pushed in under " +
        "the table.\n");
    add_item(({"papers"}),
        "the papers look well read and are scattered in loose piles on " +
        "the table. They are written in some foreign language. Charts and " +
        "diagrams are written on some on the papers.\n");

// Every 2 minutes, the room will do one of these actions.
// This number can be changed
    set_room_tell_time(120);

// These are the actions that will fired off every 60 seconds.
// They will be randomly selected.
    add_room_tell("A bird flies overhead.");
    add_room_tell("Rumbling sounds echo from overhead.");
    add_room_tell("A cool breeze blows in from outside.");
    add_room_tell("Clouds slowly drift by, casting shadows in their wake.");
    add_room_tell("Some raindrops fall on your head.");


// sets the room to have 1 level of light
    add_prop(ROOM_I_LIGHT, 1);
// have the room reset itself periodically
    reset_workroom();

    add_exit("@@goto_start", "startloc");
    add_exit("/d/Genesis/start/human/town/tower", "sparkle");
// These exits will be hidden and only wizards can enter it
    add_exit("/d/Genesis/wiz/green","island",0,0,1);
}


void
init()
{
    ::init();
}

public void
reset_workroom()
{
    ::reset_workroom();
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob,from);
    if (sizeof(query_room_tells()))
    {
    	start_room_tells();
    }
}
