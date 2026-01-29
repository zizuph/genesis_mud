/*
 * Entrance to the Sewers from the Library
 *
 * Secret room behind bookshelf that allows entry into
 * the sewers.
 *
 * Created by Petros, March 2008
 */

#pragma strict_types

// Includes
#include <macros.h>
#include <stdproperties.h>
#include "defs.h"
#include "../../library/defs.h"

// Defines

// Inheritance
inherit SEWER_ROOM_BASE;

// Global Variables

// Prototypes
public void             init();
public void             create_sewer_room();
public void             remove_north_exit();
public void             add_north_exit();
public int              push_cmd(string args);
public int              climb_cmd(string args);

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

    add_action(push_cmd, "push");
    add_action(climb_cmd, "climb");
} // init

/* 
 * Function name:       create_library_room
 * Description  :       This function overrides the one in the base class
 * Arguments    :       none
 * Returns      :       void/nothing
 */
public void
create_sewer_room()
{
    // Descriptions Section
    set_short("Sewer Entrance");
    set_long("Strangely enough, this room is actually lit by torches, "
           + "though you can't really imagine who would ever come in "
           + "here. The room looks like an unfinished construction "
           + "area. There is a hole in the middle of the room with a "
           + "ladder leading down. The stench here is almost unbearable. "
           + "You can hear the soft footsteps of the Library patrons "
           + "through the north wall."
           + "\n\n");
 
    // Room Item Section                              
    add_item( ({ "torches", "light" }),
                 "Torches are hanging from the walls giving sufficient "
               + "light in this room."
               + "\n");

    add_item( ({ "hole", "ladder", "entrance" }),
                 "The hole seems to be an entrance to the sewer system "
               + "below. A ladder leads down from here."
               + "\n");
                              
    add_item( ({ "north wall", "crack" }),
                 "@@describe_north_wall@@");

    add_item( ({ "sewers", "sewer system", "sewer" }),
                 "From the foul stench coming from the hole, you're "
               + "fairly certain that the sewer system is beneath you. "
               + "\n");

    add_item( ({ "floor", "marble floor", "floors", "marble floors",
                 "ground" }),
                 "The only thing of interest in the floor here is the "
               + "hole and the foul stench coming from it."
               + "\n");
    
    add_item( ({ "wall", "walls", "stone" }),
                 "The walls here are made of unfinished stone. The "
               + "artisans clearly ignored this area, as well they "
               + "should. You see a slight crack in the north wall "
               + "that looks like it doesn't really belong."
               + "\n");
               
    add_item( ({ "ceiling" }),
                 "It's too dark to really get a good look at the ceiling."
               + "\n");
                   
    add_item( ({ "room" }),
                 "You are standing at one of the entrances to the sewer "
               + "system that runs underneath the City of Sparkle."
               + "\n");

    add_item( ({ "bookshelf" }),
                 "The back of the bookshelf forms a wall to the north."
               + "\n");

    try_item( ({ "water", "waters", "murky waters", "murky water" }),
                 "You hear the sounds of water, but you don't see "
               + "anything from here."
               + "\n");
                              
    // Properties Section
    add_prop(OBJ_S_SEARCH_FUN, "search_cmd");
    
    /* Add the map file - part of the library one, not the sewer */
    add_prop(ROOM_S_MAP_FILE, "library_map.txt");

    // Exits Section
    add_exit(SEWER_ROOM_DIR + "sewer1", "down", 0);
    
} // create_library_room

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
 * Function name:        push_cmd
 * Description  :        Reveals the exit back to the Library stacks
 * Arguments    :        none
 * Returns      :        nothing
 */
public int
push_cmd(string args)
{
    if (!args)
    {
        notify_fail("Push what?\n");
        return 0;
    }
    
    if (parse_command(args, ({ }), "[north] 'wall'"))
    {        
        if (IN_ARRAY("north", query_exit()))
        {
            write("The wall has already been pushed!\n");
            return 1;
        }
        say(QCTNAME(this_player()) + " pushes the north wall and reveals "
          + "an exit to the north as it rotates.\n");
        write("You push your hands against the wall and it rotates, "
            + "revealing an exit to the north.\n");
        add_exit(LIBRARY_ROOM_DIR + "poetry", "north", 0);
        (LIBRARY_ROOM_DIR + "poetry")->add_south_exit();
        set_alarm(7.0, 0.0, &remove_north_exit());
        return 1;
    }
    
    notify_fail("Push what?\n");
    return 0;
}

/*
 * Function name:        climb_cmd
 * Description  :        Allow the user to climb down
 * Arguments    :        none
 * Returns      :        nothing
 */
public int
climb_cmd(string args)
{
    if (!args)
    {
        notify_fail("Climb what?\n");
        return 0;
    }

    if (parse_command(args, ({ }), 
         "[down] [ladder]"))
    {
        this_player()->move_living("down", 
                                   SEWER_ROOM_DIR + "sewer1");
        return 1;        
    }
    
    notify_fail("Climb what?\n");
    return 0;
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
    case "wall":
    case "north wall":
        return "You search the wall carefully, and it looks like the wall "
             + "is hinged in such a way that you can <push> to rotate it "
             + "and possibly return back north.\n";

    }
    
    return "";
}

/*
 * Function name:        add_north_exit
 * Description  :        Reveals the exit to the north, called externally
 * Arguments    :        none
 * Returns      :        nothing
 */
public void
add_north_exit()
{
    tell_room(this_object(), "The north wall suddenly rumbles and reveals "
                           + "an exit to the north as it rotates.\n");
    add_exit(LIBRARY_ROOM_DIR + "poetry", "north", 0);
    set_alarm(7.0, 0.0, &remove_north_exit());
}

/*
 * Function name:        remove_south_exit
 * Description  :        Timed function that removes the south exit.
 * Arguments    :        none
 * Returns      :        nothing
 */
public void
remove_north_exit()
{
    tell_room(this_object(), "The wall to your north suddenly "
            + "rotates, closing off the exit to the north.\n");
    remove_exit("north");
}

/*
 * Function:    describe_north_wall
 * Description: Describes the north wall depending on whether it
 *              is open or not.
 */
public string
describe_north_wall()
{
    if (IN_ARRAY("north", query_exit()))
    {
        return "The north wall is completely rotated and there "
             + "is an exit to the north that leads directly into "
             + "the Library stacks.\n";
    }
    
    return "You're fairly certain that the Library stacks are beyond "
         + "the north wall. The crack that you see almost looks like "
         + "a door. You just have to figure out how to get into "
         + "the Library."
         + "\n";
}
