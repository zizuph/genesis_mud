/*
 * /d/Sparkle/area/city/library/room/circulation.c
 *
 * Circulation Desk for the Genesis Library
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
inherit LIBRARY_ROOM_BASE;

// Global Variables
object nikolon_obj;

// Prototypes
public void             create_library_room();
public void             init();
public void             reset_room();
public string           sparkle_short();
public varargs string   sparkle_long();
public int              grab_cmd(string arg);
public int              browse_cmd(string arg);
public int              read_cmd(string arg);
public string           read_sign();

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
    add_action(browse_cmd, "browse");
    add_action(read_cmd, "read");
} // init

/* 
 * Function name:       create_room
 * Description  :       This function overrides the one in the base class
 * Arguments    :       none
 * Returns      :       void/nothing
 */
public void
create_library_room()
{
    // Room Item Section                               
    add_item( ({ "desk", "wooden desk", "finely crafted desk", 
                 "finely crafted wooden desk", "circulation desk",
                 "cedar desk" }),
                  "The desk is constructed out of the finest cedar wood. "
                + "On each side of the desk you spot patterns carved "
                + "into the wood. Hanging off to one side of the desk "
                + "is a small dispenser.\n");

    add_item( ({ "side", "sides", "desk side", "desk sides", "patterns",
                 "carvings", "carved patterns", "carved pattern" }),
                  "The carvings along the sides of the desk tell the "
                + "story of the Genesis donut. You see carvings of "
                + "shapes that you recognize as the shapes of the "
                + "domain continents.\n");

    add_item( ({ "continents", "shapes", "domain continents",
                 "progression" }),
                  "You marvel at the progression of shapes carved into "
                + "the desk. They show the slowly changing continents "
                + "as they developed over the years.\n");

    add_item( ({ "dispenser", "small dispenser" }),
                  "The small dispenser contains little informational "
                + "packets that you can <grab>.\n");

    add_item( ({ "sign", "large sign", "letters", "font", "bright font",
                 "red font", "bright red font" }),
                  &read_sign());

    add_item( ({ "papers", "stacks of paper", "paper stacks" }),
                  "Whoever works at this desk is clearly not very "
                + "organized or is otherwise occupied. The papers look "
                + "like work orders that need to be reviewed by the "
                + "person in charge here.\n");

    add_item( ({ "white wall", "formidable white wall" }),
                  "The work orders on the desk form a formidable white "
                + "wall. You wonder how anyone can let this much go "
                + "unfinished."
                + "\n");
                
    add_item( ({ "work orders", "orders" }),
                  "These look like completed work orders that still "
                + "need to be signed off by someone. The orders were "
                + "for the construction of the Genesis Library. You "
                + "wonder who is not completing these orders.\n");

    add_item( ({ "stacks", "hallways", "hallway" }),
                  "You see the Genesis Library stacks to the east and "
                + "to the west. It looks like the circulation "
                + "desk sits along the north wing of the library.\n");

    add_item( ({ "foyer", "fountain" }),
                  "You can see a fountain in the foyer to your north. "
                + "The foyer is a radiant room that acts as the "
                + "welcoming room to the Genesis Library.\n");

    add_item( ({ "light", "light sources" }),
                  "You don't see any obvious light sources, but the "
                + "room is quite adequately lit.\n");

    add_item( ({ "ceiling", "wires", "large wires" }),
                  "You look up and see large wires that are barely "
                + "visible suspending the large sign.\n");
                
    // Exits Section
    add_exit(LIBRARY_ROOM_DIR + "entrance", "north", 0);
    add_exit(LIBRARY_ROOM_DIR + "racial_guilds", "west", 0);
    add_exit(LIBRARY_ROOM_DIR + "guides_tutorials", "east", 0);
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
    nikolon_obj = find_living ("nikolon");
    if (!nikolon_obj)
    {
        nikolon_obj = clone_object(LIBRARY_NPC_DIR + "nikolon");

        nikolon_obj->move(this_object(), 1);
        tell_room(this_object(),
            "A lanky light-haired human slowly walks into the room "
          + "and stands behind the circulation desk.\n");
    }
} // reset_room

/*
 * Function name:        sparkle_short
 * Description  :        provide a short description for locations
 *                       in the City of Sparkle
 * Deturns      :        string -- the short description
 */
public string
sparkle_short()
{
    return "Circulation desk";
} // sparkle_short


/*
 * function name:        sparkle_long
 * description  :        provides a long descriptions for locations
 *                       in the city of Sparkle
 * returns      :        the room description
 */
public varargs string
sparkle_long()
{
    return "A finely crafted wooden desk sits prominently in the center "
           + "of the room. The desk itself is quite wide and there are "
           + "stacks of paper that seem to form a formidable white wall "
           + "between you and the area behind the desk. A large sign "
           + "hangs from the ceiling over the desk. Though the room is "
           + "well-lit, you do not see any obvious light sources. To the "
           + "north, you hear the sounds of the fountain in the foyer. "
           + "Hallways lead to the east and the west."
           + "\n\n";
} // sparkle_long

/*
 * function name:        browse_cmd
 * description  :        Notifies the player that they can't actually
 *                       browse anything here.
 * returns      :        0/1 - whether the command succeeded
 */
public int
browse_cmd(string arg)
{
    notify_fail("There are no bookshelves to browse here, but you see "
              + "some bookshelves to the west and to the east of here.\n");
    return 0;
}

/*
 * function name:        grab_cmd
 * description  :        Processes the grab command so that the user
 *                       can grab a library informational packet
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
         "[the] / [a] [little] [informational] 'packets' "
       + "[from] [the] [dispenser]"))
    {
        write("The dispenser only allows you to grab one packet at "
            + "a time.\n");
        return 1;
    }

    if (!parse_command(arg, ({ }), 
            "[the] / [a] [little] [informational] 'packet' "
          + "[from] [the] [dispenser]"))
    {
        notify_fail("Grab what?\n");
        return 0;        
    }
    
    clone_object(LIBRARY_OBJ_DIR 
                + "info_packet")->move(this_player(), 1);
    say(QCTNAME(this_player()) + " grabs an informational packet from "
      + "the dispenser.\n");
    write("You grab an informational packet from the dispenser.\n");
    return 1;
}

/*
 * function name:        read_cmd
 * description  :        sets up the read command for the sign.
 * returns      :        the room description
 */
public int
read_cmd(string arg)
{
   if (!arg || arg == "")
    {
        notify_fail("Grab what?\n");
        return 0;
    }

    if (parse_command(arg, ({ }), 
            "[the] / [a] [large] 'sign'"))
    {
        write(read_sign());
        return 1;
    }
        
    notify_fail("Read what?");
    return 0;
}

/*
 * function name:        read_sign
 * description  :        returns the description for the sign
 * returns      :        the sign text
 */
public string
read_sign()
{
    string sign_text;
    
    sign_text = 
           "A large sign hangs from the ceiling displaying its "
         + "letters in a bright red font:\n\n"
         + "C I R C U L A T I O N   D E S K\n\n";
         
    if (nikolon_obj && environment(nikolon_obj) != this_object())
    {
        sign_text += "Librarian is in his office. Will be back in "
                   + "a few hours.\n\n";
    }
    
    return sign_text;  
}
