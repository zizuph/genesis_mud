/*
 * Poetry Stacks in the Genesis Library
 *
 * South wing in the Genesis Library. Contains
 * books on Poetry and Literature
 *
 * Created by Petros, March 2008
 */

#pragma strict_types

// Includes
#include <macros.h>
#include <stdproperties.h>
#include "defs.h"

// Defines

// Inheritance
inherit (LIBRARY_ROOM_DIR + "library_base");

// Global Variables
public string * book_identifiers = 
    ({ "leather-bound book", "leather bound book", "leather book",
       "bound book" });
       
// Prototypes
public void             init();
public void             create_library_stack();
public int              pull_cmd(string args);
public void             remove_south_exit();
public string           search_cmd(object player, string args);
public string           center_bookshelf_description();

/* 
 * Function name:       init
 * Description  :       Standard init function to add actions
 * Arguments    :       none
 * Returns      :       void/nothing
 */
public void 
init() 
{
    ::init();  
    
    add_action(pull_cmd, "pull");
} // init

/* 
 * Function name:       create_library_stack
 * Description  :       This function overrides the one in the base class
 * Arguments    :       none
 * Returns      :       void/nothing
 */
public void
create_library_stack()
{
   // Library Initialization Section
    create_genesis_library( ({ "poetry", "literature" }), 
                            "" );

    // Descriptions Section
    set_short("Stacks - poetry and literature");
    set_long("Shelves of books line the walls to the south of the "
           + "hallway. A quick glance at the titles reveals that some of "
           + "the greatest works of poetry and literature are contained "
           + "here for anyone to peruse. The marble floor here looks a "
           + "bit more faded, especially close to the center bookshelf "
           + "in the room. The stacks continue to both the east and the "
           + "west. There is a small room to your north."
           + "\n\n");
 
    // Room Item Section  
    add_item( ({ "walls", "south wall", "wall", "poem" }),
                  "On the wall to the south of you, someone has taken "
                + "the time to write a heartfelt poem: \n\n"
                + "  Lonely, lonely was I upon entering the world,\n"
                + "  Thrust into existence to survive or fail,\n"
                + "  Seeking purpose or meaning to this lonely existence.\n"
                + "  To love. To hate. To live. To die.\n"
                + "  Genesis, oh Genesis, this Donut I yearn to know,\n"
                + "  Feeling of success in friendship and purpose.\n"
                + "  Grant me the time to seek such beauty;\n"
                + "  Grant me the patience to balance such pain.\n\n"
                + "A poem by a gnome and an elf.\n");

    add_item( ({ "hallway" }),
                  "The hallway is in the middle of the very short south "
                + "corridor.\n");

    add_item( ({ "poetry", "literature" }),
                  "You see plenty of titles of poetry and literature on "
                + "the shelves. You even see a wonderful poem written "
                + "on the south wall.\n");

    add_item( ({ "marble floor", "floor", "marble", "ground" }),
                  "The Genesis Library is fairly new, but they must have "
                + "used some very poor material for the marble here. Near "
                + "the center bookshelf, the ground looks downright dull. "
                + "It is very unlike the rest of the floor that you have "
                + "seen which is usually quite pristine and shiny.\n");

    add_item( ({ "center bookshelf", "center shelf", "middle shelf",
                 "middle bookshelf" }),
                  &center_bookshelf_description());
                                

    add_item( ({ "small room", "room to the north", "north room",
                 "northern room" }),
        "A small and dimly lit room is visible through an archway to"
      + " the north.\n");
    add_item( ({ "arch", "archway" }),
        "The archway is both elegant and functional, providing passage"
      + " into the writing room to the north.\n");
    add_item( ({ "dimly lit room", "dimly-lit room", "writing room" }),
        "You can't see much from here, but there appear to be people"
      + " in there at various writing stations.\n");
    add_item( ({ "people", "stations", "station", "writing station",
                 "writing stations" }),
        "You just can't make out much from here. Perhaps go north and"
      + " take a closer look?\n");
    add_item( book_identifiers,
                  "Upon closer inspection, you notice that the leather-bound "
                + "book doesn't look like it has any pages in it! You see "
                + "some grease on the upper side of the book. Could it "
                + "be that you could pull on it?\n");

    // Properties Section
    add_prop(OBJ_S_SEARCH_FUN, "search_cmd");
    
    // Exits Section
    add_exit(LIBRARY_ROOM_DIR + "theology", "east", 0);
    add_exit(LIBRARY_ROOM_DIR + "clubs_craft_guilds", "west", 0);
    add_exit(LIBRARY_ROOM_DIR + "writing_room", "north", 0);
} // create_library_stack

/*
 * Function name:        reset_room
 * Description  :        Override the standard reset_room to bring in
 *                       objects that should be here.
 * Arguments    :        none
 * Returns      :        nothing
 */
public void
reset_room()
{
} // reset_room

/*
 * Function name:        pull_cmd
 * Description  :        Pull the book to reveal the exit to the south.
 * Arguments    :        none
 * Returns      :        nothing
 */
public int
pull_cmd(string args)
{
    string target;
    
    if (!args)
    {
        notify_fail("Pull what?\n");
        return 0;
    }
    
    args = lower_case(args);
    if (!sscanf(args, "on %s", target))
    {
        target = args;
    }
    
    notify_fail("Pull what?\n");
    if (IN_ARRAY(target, book_identifiers))
    {
        if (IN_ARRAY("south", query_exit()))
        {
            write("You pull the leather-bound book again, but nothing "
                + "happens.\n");
            return 1;
        }
        say(QCTNAME(this_player()) + " does something and you hear a "
          + "click along the bookshelf to your south. Suddenly, the "
          + "center bookshelf rotates and reveals an exit to the "
          + "south!\n");
        write("You pull the leather-bound book and you hear a small "
            + "click. Suddenly, the center bookshelf rotates and "
            + "reveals an exit to the south!\n");
        add_exit(SEWER_ROOM_DIR + "sewer_entrance", "south", 0);
        (SEWER_ROOM_DIR + "sewer_entrance")->add_north_exit();
        set_alarm(7.0, 0.0, &remove_south_exit());
        return 1;
    }
    else if (target == "book")
    {
        notify_fail("Pull which book?\n");
    }
                    
    return 0;
}

/*
 * Function name:        add_south_exit
 * Description  :        Reveals the exit to the south
 * Arguments    :        none
 * Returns      :        nothing
 */
public void
add_south_exit()
{
    tell_room(this_object(), "The bookshelf to your south suddenly "
                           + "rotates, revealing an exit to your "
                           + "south.\n");
    add_exit(SEWER_ROOM_DIR + "sewer_entrance", "south", 0);
    set_alarm(7.0, 0.0, &remove_south_exit());
}

/*
 * Function name:        remove_south_exit
 * Description  :        Timed function that removes the south exit.
 * Arguments    :        none
 * Returns      :        nothing
 */
public void
remove_south_exit()
{
    tell_room(this_object(), "The bookshelf to your south suddenly "
            + "rotates, closing off the exit to the south.\n");
    remove_exit("south");
}

/*
 * Function name:        search_cmd
 * Description  :        Search function that allows players to search the
 *                       center bookshelf to find the trigger
 * Arguments    :        none
 * Returns      :        nothing
 */
public string
search_cmd(object player, string args)
{
    switch (args)
    {
    case "leather-bound book":
    case "center bookshelf":
    case "shelf":
    case "bookshelf":
        return "You search carefully and discover that you might be able "
             + "<pull> on the leather-bound book.\n";

    case "marble floor":
    case "floor":
    case "marble":
    case "ground":
    case "ground":
        return "You carefully follow the markings on the ground, and they "
             + "seem to be footprints which lead right into the center "
             + "bookshelf.\n";
    }
    
    return "";
}

public string
center_bookshelf_description()
{
    if (IN_ARRAY("south", query_exit()))
    {    
        return "The center bookshelf has rotated, revealing an entrance "
             + "to the south.\n";
    }
    
    return "There is nothing remarkable about this bookshelf "
         + "except for the fact there is one leather-bound book "
         + "that seems a bit out of place from the rest of the "
         + "books. A slightly foul odor comes from the bookshelf.\n";
}
