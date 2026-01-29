/*
 * /w/petros/sparkle/library/room/map_reference.c
 *
 * South Hallway of the Genesis library with books containing
 * various maps and references.
 *
 * Created by Petros, March 2008
 */

#pragma strict_types

// Includes
#include <macros.h>
#include <stdproperties.h>
#include "defs.h"

// Defines
#define MAGIC_MAP_OBJ "/d/Sparkle/std/obj/magic_map"

// Inheritance
inherit (LIBRARY_ROOM_DIR + "library_base");

// Global Variables

// Prototypes
public void             init();
public void             create_library_stack();
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
    create_genesis_library( ({ "maps", "references" }), 
                            "" );

    // Descriptions Section
    set_short("Stacks - maps and references");
    set_long("Numerous land and ocean charts and graphs can be seen in "
           + "the displays next to the bookshelves. Maps and other "
           + "references can be found here. A soft light illuminates "
           + "the room, allowing one to read comfortably. You see that "
           + "the light comes from a few torches. Their light strikes "
           + "the shiny marble flooring, creating a picturesque scene. "
           + "You see the stacks continue to the north and to the south. "
           + "In the middle of the room is a magic map dispenser." 
           + "\n\n");
 
    // Room Item Section                              
    add_item( ({ "charts", "ocean charts", "graphs", "land charts"}),
                  "Everything you see in the room is a cartographer's "
                + "dream. Anything that an adventurer would need in "
                + "order to find their way around is here. The ocean "
                + "charts detail the shipping lines, the land charts "
                + "detail the roads that one can travel on. There are "
                + "graphs of travel times among other things.\n");

    add_item( ({ "maps", "references", "map", "reference" }),
                  "Over the years, travellers from all over the donut "
                + "have contributed by mapping their way and writing "
                + "references for others to read. These are all stored "
                + "within these stacks. You also see magic maps in the "
                + "dispenser which you can <grab>.\n");

    add_item( ({ "light", "torches", "torch", "lights" }),
                  "The torches are attached to the wall high above the "
                + "bookshelves. The light that comes from them gives "
                + "sufficient and comfortable reading light for the "
                + "patrons.\n");

    add_item( ({ "wall", "walls" }),
                  "Bookshelves are lined against the walls here. You "
                + "don't see any displays here other than the charts "
                + "and graphs.\n");
                
    add_item( ({ "dispenser", "map dispenser", "magic map dispenser" }),
                  "This dispenser has carefully stacked magic maps inside "
                + "of it. You can <grab> one if you do not already have "
                + "one.\n");

    add_item( ({ "marble flooring", "flooring", "floors",
                 "marble floors", "shiny marble flooring",
                 "shiny floors", "shiny flooring", "scene",
                 "picturesque scene" }),
                  "Your eyes feast upon the marvelous play of lights "
                + "on the marble flooring. Somehow the soft light makes "
                + "everything in this room seem almost dream-like.\n");                

    // Properties Section
    
    // Exits Section
    add_exit(LIBRARY_ROOM_DIR + "domains", "north", 0);
    add_exit(LIBRARY_ROOM_DIR + "theology", "south", 0);
} // create_room

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
 * function name:        grab_cmd
 * description  :        Processes the grab command so that the user
 *                       can grab a magic map from the dispenser
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
         "[the] / [a] [magic] 'maps' "
       + "[from] [the] [dispenser]"))
    {
        write("The dispenser only allows you to grab one map at "
            + "a time.\n");
        return 1;
    }

    if (!parse_command(arg, ({ }), 
            "[the] / [a] [magic] 'map' "
          + "[from] [the] [dispenser]"))
    {
        notify_fail("Grab what?\n");
        return 0;        
    }
    
    if (present("_sparkle_magic_map", this_player()))
    {
        write("You already have a magic map!\n");
        return 1;
    }
    
    clone_object(MAGIC_MAP_OBJ)->move(this_player(), 1);
    say(QCTNAME(this_player()) + " grabs a magic map from "
      + "the dispenser.\n");
    write("You grab a magic map from the dispenser.\n");
    return 1;
}
