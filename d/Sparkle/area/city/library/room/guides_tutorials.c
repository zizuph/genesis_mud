/*
 * /w/petros/sparkle/library/room/guides_tutorials.c
 *
 * East Hallway of the Genesis Library with books containing various
 * guides and references that may be useful to adventurers
 *
 * Created by Petros, March 2008
 */

#pragma strict_types

// Includes
#include <macros.h>
#include <stdproperties.h>
#include "defs.h"

// Defines
#define BIN_NOTE_CONTENT "The note reads, \"Greetings Traveller! We " \
                + "hope that you will find adventure and excitement " \
                + "in this fair Donut we call Genesis. In order to aid " \
                + "you, you may want to <grab> a tutorial journal to " \
                + "familiarize yourself with some basic concepts. May " \
                + "Lars be with you.\"" \
                + "\n"
#define JOURNAL_OBJ "/d/Sparkle/area/tutorial/obj/journal"

// Inheritance
inherit (LIBRARY_ROOM_DIR + "library_base");

// Global Variables

// Prototypes
public void             init();
public void             create_library_stack();
public int              read_cmd(string arg);
public int              grab_cmd(string arg);

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
    
    add_action(read_cmd, "read");
    add_action(grab_cmd, "grab");
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
    create_genesis_library( ({ "guides", "tutorials" }), 
                            "" );

    // Descriptions Section
    set_short("Stacks - guides and tutorials");
    set_long("Old books line the shelves on the northern wall of this "
           + "wing. A label on the shelves indicates that this section "
           + "is filled with tutorials and guides to help the everyday "
           + "adventurer. Torches light the hallway with a soft glow "
           + "providing ample light for reading. To the south you notice "
           + "a corridor leading south with more bookshelves on either "
           + "side. A curiously large bin has been placed in the center "
           + "of the room. To the east you see a stairwell and the way "
           + "west leads back to the circulation desk."
           + "\n\n");
 
    // Room Item Section                              
    add_item( ({ "old books", "spines", "spine", "old book", "tomes",
                 "tome" }),
                  "The spines of the books here are really faded. But "
                + "for the most part, you can still make out the titles. "
                + "\n");

    add_item( ({ "label" }),
                  "The label clearly indicates that guides and tutorials "
                + "can be found here."
                + "\n");

    add_item( ({ "bin", "large bin", "curiously large bin" }),
                  "The bin is filled with journals! On the outside of the "
                + "bin a note has been written indicating that Tutorial "
                + "Journals can be obtained here. You can probably "
                + "<grab> one if you don't have one already."
                + "\n");

    add_item( ({ "journal", "journals", "tutorial journal", 
                 "tutorial journals" }),
                  "You see lots of tutorial journals in the bin. You "
                + "should be able to <grab> one."
                + "\n");

    add_item( ({ "note" }),
                  BIN_NOTE_CONTENT);

    add_item( ({ "torches", "torch light", "light", "torch", 
                 "soft light", "hallway", "corridor" }),
                  "The east wing intersects the north wing here allowing "
                + "for light to stream in from torches in both wings. The "
                + "soft light is enough for reading."
                + "\n");

    add_item( ({ "east", "stairwell" }),
                  "The north wing where you are leads to the "
                + "stairwell to your east. The stairwell itself looks "
                + "like it is fairly well-lit."
                + "\n");

    add_item( ({ "west", "circulation desk" }),
                  "To your west, you can head back to the circulation "
                + "desk, as well as the exit. It is also the way back "
                + "to the entrance of the Library back onto the streets. "
                + "\n");
                
    add_item( ({ "north wing", "north corridor" }),
                  "The north wing stretches east and west from where "
                + "you stand. You are near the eastern end of it."
                + "\n");
                
    add_item( ({ "east wing", "east corridor" }),
                  "The east wing continues to the south. You "
                + "can see many patrons browsing the Library books."
                + "\n");

    // Properties Section
    
    // Exits Section
    add_exit(LIBRARY_ROOM_DIR + "circulation", "west", 0);
    add_exit(LIBRARY_ROOM_DIR + "ne_stairwell", "east", 0);
    add_exit(LIBRARY_ROOM_DIR + "domains", "south", 0);
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
 * Function name:        read_cmd
 * Description  :        This implements the read action in this room
 * Arguments    :        arg - argument to the read command
 * Returns      :        0/1 - command was successful or not
 */
public int
read_cmd(string arg)
{
    if (!arg)
    {
        return 0;
    }
    
    if (arg == "note")
    {
        write(BIN_NOTE_CONTENT);
        return 1;
    }
    
    return 0;    
}

/*
 * function name:        grab_cmd
 * description  :        Processes the grab command so that the user
 *                       can grab a tutorial journal
 * arguments    :        arg - arguments to the command
 * returns      :        0/1 whether the command succeeded
 */
public int
grab_cmd(string arg)
{
    if (!arg || arg == "")
    {
        notify_fail("Grab what?\n");
        return 0;
    }
    
    if (parse_command(arg, ({ }), 
         "[the] / [a] [tutorial] 'journals' [from] [the] [bin]")
        || present("_tutorial_journal", this_player()))
    {
        write("You don't really need more than one tutorial journal!\n");
        return 1;
    }

    if (!parse_command(arg, ({ }), 
            "[the] / [a] [tutorial] 'journal' [from] [the] [bin]"))
    {
        notify_fail("Grab what?\n");
        return 0;        
    }

    clone_object(JOURNAL_OBJ)->move(this_player(), 1);
    say(QCTNAME(this_player()) + " grabs a tutorial journal from "
      + "the bin.\n");
    write("You grab a tutorial journal from the bin.\n");
    return 1;
}
