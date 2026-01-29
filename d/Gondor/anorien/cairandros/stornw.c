/*
 * Cair Andros - /d/Gondor/anorien/cairandros/stornw.c
 *
 * Varian 2016
 * 
 * Changes:
 * Cotillion - 2020-09-07
 * - Fixed cloning of keys
 */

#pragma strict_types
#include "../defs.h"

inherit ANORIEN_STD_DIR + "room";
#include <stdproperties.h>
#include <macros.h>

object wbox, door;
int open;

/*
 * Function name:        create_anorien_room()
 * Description  :        Creates a room in Anorien
 */
nomask void 
create_anorien_room() 
{    
    set_short("Inside the fort at Cair Andros");
    set_long("You are inside what appears to be a small office inside " +
        "the fortress of Cair Andros. The room is illuminated by torches " +
        "that have been mounted on the brackets hanging from the east and " +
        "west walls. A small wooden desk and chair sit near the " +
        "southern wall, providing a place for some officer to " +
        "maintain the paperwork for the garrison. The room looks " +
        "rather tidy, and is otherwise empty, with only a large " +
        "wooden door in the north wall to provide access into the " +
        "rest of the fort.\n"); 

    add_item(({"stair","stairs","step","steps","stone stair","stone stairs",
            "staircase","stone staircase"}),
        "You do not see any stairs here, but you do recall seeing some " +
        "in the corner of the fortress.\n");
    add_item(({"hall","hallway","corridor"}),
        "You are in the middle of a storage room! But there is a " +
        "hallway on the other side of the door.\n");
    add_item(({"wall", "walls"}),
        "There are indeed four walls in this room, did you want to " +
        "examine one in particular?\n");
    add_item(({"east","eastern wall"}),
        "The eastern wall is rather plain, but a burning torch has been " +
        "mounted in the middle of the wall to help provide some light.\n");
    add_item(({"north", "northern wall"}),
        "The north wall has a rather large wooden door that leads out " +
        "to the rest of the fortress.\n");
    add_item(({"west", "western wall"}),
        "The western wall is rather plain, but a burning torch has been " +
        "mounted in the middle of the wall to help provide some light.\n");
    add_item(({"south", "southern wall"}),
        "There is a small desk and chair set up near the southern wall, " +
        "presumably the property of the officer who commands the " +
        "garrison here.\n");
    add_item(({"northeast","northeastern corner"}),
        "There is nothing interesting to see in the northeastern corner of " +
        "this storage room.\n");
    add_item(({"northwest", "northwestern corner"}),
        "There is nothing interesting to see in the northwestern corner of " +
        "this storage room.\n");
    add_item(({"southwest", "southwestern corner"}),
        "There is nothing interesting to see in the southwestern corner of " +
        "this storage room.\n");
    add_item(({"southeast", "southeastern corner"}),
        "There is nothing interesting to see in the southeastern corner of " +
        "this storage room.\n");
    add_item(({"up", "ceiling"}),
        "The ceiling up above is made of cold grey stone, much like almost " +
        "everything else in here.\n");
    add_item(({"down", "ground", "floor"}),
        "The floor here is made from large blocks of grey stone, just like " +
        "pretty much everything else you can see in here.\n");
    add_item(({"fort","fortress","fortifications","stone fort","stone",
            "stone fortress","stone fortifications","tall fortifications",
            "tall stone fort","tall stone fortifications","tall fort",
            "tall fortress","tall stone fortress"}),
        "You are standing inside the tall stone fortress that guards the " +
        "fords which cross the Anduin at Cair Andros. The fort is in " +
        "very good condition, and appears to be well tended by the " +
        "soldiers of Gondor. \n");
    add_item(({"stone","stones","stone block","stone blocks"}),
        "The entire fortress appears to have been made from massive stone " +
        "blocks, precisely cut and fit in a very sturdy formation.\n");
    add_item(({"gondor"}),
        "Gondor is the southern kingdom of the Numenoreans who settled " +
        "in Middle Earth. While still strong, it is but a shadow of " +
        "the power and glory it once enjoyed.\n");
    add_item(({"numenor","numenorians","dunedain","westernesse"}),
        "Numenor was a great island kingdom that existed a long time " +
        "ago, but sank into the sea. The survivors, known today as the " +
        "Dunedain, sailed to Middle-Earth where they established " +
        "great kingdoms such as Gondor.\n");
    add_item(({"torch","torches"}),
        "There are two torches here, set into iron brackets on the east " +
        "and west walls in order to provide plenty of light.\n");
    add_item(({"bracket","brackets","iron bracket","iron brackets"}),
        "These brackets have been firmly mounted to the walls, providing " +
        "the perfect perch for torches to illuminate the office.\n");
    add_item(({"ithilien"}),
        "The land of Ithilien lies to the east, on the other side of the " +
        "Anduin.\n");
    add_item(({"anorien"}),
        "The rolling plains of Anorien are west of the fortress, on the " +
        "other side of the river.\n");
    add_item(({"island","isle","caer andros"}),
        "You are currently on the island of Cair Andros, inside the " +
        "fortress which guards the fords which cross the Anduin here. " +
        "On the east side of the river are the lands of Ithilien, while " +
        "to the west, the rolling plains of Anorien can be found.\n");
    add_item(({"box","wooden box","small box","small wooden box"}),
        "@@box");
    add_item(({"desk","small desk"}),
        "@@desk");

    set_no_exit_msg(({"northwest","northeast","southwest","southeast",
            "south","east","west"}),
        "Those walls sure are solid! It does not look like there is any " +
        "way out except by using the door in the northern wall.\n");

    add_prop(ROOM_I_INSIDE,1);

    door = clone_object(AN_OBJ_DIR + "storage_door_out_nw");
    door->move(TO);

    add_cmd_item( ({ "wooden box", "box" }),
        "open", "@@open_box" );
    add_cmd_item( ({ "wooden box", "box" }),
        "close", "@@close_box" );

    wbox = clone_object(AN_OBJ_DIR + "wbox.c");
    wbox->set_no_show();

    wbox->add_object(AN_OBJ_DIR + "fort_key");
    wbox->add_object(AN_OBJ_DIR + "storsw_key");
    wbox->add_object(AN_OBJ_DIR + "storse_key");
    wbox->add_object(AN_OBJ_DIR + "storne_key");
    wbox->reset();
    wbox->move(TO, 1);
}

string
desk()
{
    TP->add_prop("_obj_i_wbox_found", 1);
    if (open)
    return "This is a small desk that has been set up at the southern " +
        "end of the office, presumably for the use of the officer who " +
        "commands the garrison here.\nHidden beneath the desk is an " +
        "open wooden box.\n";
    return "This is a small desk that has been set up at the southern " +
        "end of the office, presumably for the use of the officer who " +
        "commands the garrison here.\nHidden beneath the desk is a " +
        "closed wooden box.\n";
}

string
box()
{
    TP->add_prop("_obj_i_wbox_found", 1);
    if (open)
    return "This small wooden box has been hidden beneath the desk and " +
        "has been left open.\n";
    return "This small wooden box has been hidden beneath the desk and " +
        "has been left closed.\n";
}


/*
 * Function name:        open_box
 * Description  :        Allows players to open the box where they key is
 */
int
open_box(string str)
{
    if (TP->query_prop("_obj_i_wbox_found") != 1)
    {
       NF("What box?\n");
       return 0;
    }

    if (open)
    {
       write("The wooden box is already open.\n");
       return 1;
    }

    write("You open the wooden box.\n");
    say(QCTNAME(TP) + " rummages around beneath the desk opening " +
        "something you can't quite see from here.\n");
    open = 1;
    wbox->unset_no_show();
    return 1;
}
/* open_box */

/*
 * Function name:        close_box
 * Description  :        Allows players to close the box again
 */
int
close_box(string str)
{    
    if (TP->query_prop("_obj_i_wbox_found") != 1)
    {
       NF("What box?\n");
       return 0;
    }

    if (!open)
    {
        write("The wooden box is already closed.\n");
        return 1;
    }
    
    write("You close the wooden box.\n");
    say(QCTNAME(TP) + " rummages around beneath the desk closing " +
        "something you can't quite see from here.\n");
    open = 0;
    wbox->set_no_show();
    return 1;
}
/* close_box */

