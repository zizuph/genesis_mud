/*
 * Library of the Elemental Temple of Calia
 * 
 * Created by Petros, April 2010
 */

#pragma strict_types

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

inherit TEMPLE_ROOM_BASE;
inherit "/d/Sparkle/area/city/library/room/library_lib";
inherit "/d/Genesis/specials/guilds/lib/utility_functions";

// Defines
#define LIVE_I_SITTING "_live_i_sitting"

// Prototypes

// Global Variables
public object   sphere = 0;
public object tahla;

public void
create_temple_room()
{
    set_short("Elemental Temple Library");
    set_long("@@desc_long_description");    
                   
    add_exit(ELEMENTALIST_TEMPLE + "outer14a", "north");     
    
    try_item( ({ "hall", "library" }),
        "This is the Library of the Elemental Temple of Calia.\n");
    
    try_item( ({ "ceiling", "petrified wood", "beams", "wooden beams" }),
        "The ceiling here is made from the same petrified wood as the rest "
      + "of the temple. However, here it does not form "
      + "an arch, but has a flattened roofing made from beams of petrified "
      + "wood. The petrified wood seems to have grown thin stalactites, and "
      + "on the tip of each stalactite a large globe of white fluorescent "
      + "stone shines a pleasant light throughout the library.\n");
      
   try_item( ({ "door", "sign", "slender door", "north" }),
        "A tall door, crafted by an intrinsic mix of dark oak and petrified "
      + "wood is rather slender. The door itself is also remarkably hefty, "
      + "likely to prevent sounds from the outside travelling into the library.\n");
    
    try_item( ({ "globes", "globe", "glowing globes", "glowing globe",
            "massive glowing globes", "massive glowing globe", "massive globe",
            "massive globes", "stalactites", "stones", "massive stones" }),
        "Suspended from stalactites, these globes are massive stones of an "
      + "unknown origin, radiating a strong yet pleasant glow that illuminates "
      + "the library.\n");
   
    try_item( ({ "bookcases", "bookcase", "bookshelf", "bookshelves", "shelf",
        "shelves" }),
        "These tall bookcases are rather simple and devoid of any "
      + "ornamentation. They are very sturdy and made from a heavy dark oak. "
      + "Books, scrolls, and tablets of many kinds are organized neatly, "
      + "filling the shelves. You could try and <browse> the shelves to "
      + "see if anything strikes your fancy.\n");
    
    try_item( ({ "books", "scrolls", "tablets", "writings", "tomes", "tome",
        "archaic tablets", "fresh scrolls", "ancient leather-bound tomes" }),
        "Writings of every kind can be found here, ranging from ancient "
      + "leather-bound tomes to fresh scrolls and archaic tablets with "
      + "obscure symbols in languages lost in the dim of time. You could "
      + "<browse> the shelves to gain more knowledge, or perhaps <pen> works "
      + "of your own to add to the magnificence of this library.\n");
    
    try_item( ({ "symbols", "languages", "obscure symbols", "lost languages" }),
        "The obscure symbols range from Tengwar to Argosian scriptures. Some "
      + "are too ancient or obscure to possibly decipher. If you were to "
      + "<browse> the shelves here, you would know which works were "
      + "available for you to read.\n");
    
    try_item( ({ "desk", "desks", "wooden desk" }),
        "Which desk, the massive wooden desk or the reading desks?\n");
    
    try_item( ({ "massive desk", "massive wooden desk", "thick filing cabinets",
        "cabinets", "filing cabinets", "cabinet", "thick filing cabinet",
        "filing cabinet", "working space" }),
        "A delicate mix of petrified wood and light ash wood have been paired "
      + "and elegantly carved into a grand L-shaped desk. A pair of "
      + "thick filing cabinets occupy the space underneath it.\n");
    
    try_item( ({ "assistants", "assistant", "elderly half-elven lady",
        "old dwarven scholar", "lady", "scholar", "dwarven scholar",
        "half-elven lady" }),
        "An elderly half-elven lady wearing a simple woolen robe with her "
      + "silvery hair in a tight bun along with an old dwarven scholar "
      + "with a massive set of spectacles and a slightly rumpled brown robe "
      + "are busy maintaining the temple library.\n");
    
    try_item( ({ "reading desks", "reading desk" }),
        "These are simple reading desks, some of which are tall allowing "
      + "one to stand while working. There are also some lower tables, each "
      + "with a comfortable wooden chair. You could try to <sit> at one "
      + "of the reading desks.\n");
      
    // Set up the library shelves and books
    set_library_dir(ELEMENTALIST_DIR + "books/");
    set_approval_dir(ELEMENTALIST_DIR + "books/approval/");
    set_removed_dir(ELEMENTALIST_DIR + "books/removed/"); 
    create_genesis_library( ({ "information" }), // shelves
                "" ); // subdirectory
    
    reset_room();
}

/*
 * Function name: reset_room
 * Description  : This function should be redefined to make the room reset
 *                every half hour or so. If you redefine it, you do not have
 *                to call enable_reset() since we call it as part of our
 *                service ;-) Note that this service is only valid for rooms.
 */
public void
reset_room()
{
    ::reset_room();
    setuid(); seteuid(getuid());
    // Clone the sphere for alpha testing
    if (!objectp(sphere))
    {
        sphere = clone_object(ELEMENTALIST_OBJS + "sphere");
        sphere->move(this_object(), 1);        
    }
    if (!objectp(tahla)) { 
         tahla = clone_object(ELEMENTALIST_NPCS +"tahla");
         tahla->set_width_desc("lean");
         tahla->set_height_desc("tall"); 
         tahla->move_living("steps out from behind a shelf", TO); 
     }     
}

public string
desc_long_description()
{
    string long_desc = 
          "You have entered a vast library hall within the Elemental "
        + "Temple of Calia. A sense of order and reverence emanates from the "
        + "very foundations of this room. The grey stone walls are covered "
        + "from floor to vaulted ceiling with massive oaken bookcases. "
        + "A massive wooden desk occupies the northeastern area of this room "
        + "along with filing cabinets used by the library staff. To the north "
        + "and southwest, wooden bookcases line the area, and the "
        + "southeastern region holds several reading desks. Suspended from "
        + "the wooden ceiling are massive glowing globes, providing the "
        + "illumination needed for both studying and writing. A slender door "
        + "leads north. "; 
    
    int bInnerCircle = cannot_see_inner_circle();
    if (!bInnerCircle)
    {
        return long_desc + "\n\n";
    }

    return long_desc += "\n\n";
}

public void
init()
{
    ::init();
    init_genesis_library();

    add_action("do_sit", "sit");
    add_action("do_stand", "stand");
}

/*
 * Function:    do_read
 * Description: Allows someone to read the sign going into the library
 */
public int
library_read(string arg)
{
    // We first call the parent library_read function to see if it matches
    int return_value = ::library_read(arg);
    if (return_value) 
    {
        return return_value;
    }

    if (!strlen(arg))
    {
        return 0;
    }
    
    arg = lower_case(arg);
    if (!parse_command(arg, ({ }), "[small] 'sign'")
        && !parse_command(arg, ({ }), "[fine] 'print'"))
    {
        return 0;
    }

    string sign_text = read_file(ELEMENTALIST_TEMPLE + "chapel_sign.txt");
    if (!strlen(sign_text))
    {
        return 0;
    }
    
    write("You read the small sign on the door:\n\n");
    write(sign_text);
    
    return 1;
}

/*
 * Function name: prevent_leave
 * Description:   Called when an object is trying to leave this container
 *                to see if we allow it to leave.
 * Arguments:     object ob - the object trying to leave
 * Returns:       1 - The object is not allowed to leave
 *                0 - The object is allowed to leave
 */
public int
prevent_leave(object ob)
{
    int base_value = ::prevent_leave(ob);
    if (base_value)
    {
        return base_value;
    }
    
    if (ob->query_prop(LIVE_I_SITTING))
    {
        ob->catch_tell("You can't leave while sitting down! Try to <stand> "
            + "first.\n");
        return 1;
    }
    
    return base_value;
}

 
/*
 * Function name: do_sit
 * Description  : Allows the player to sit at a reading desk
 * Arguments    : arg - should be empty
 * Returns      : int 1/0 - success/failure.
 */
public int
do_sit(string arg)
{
    if (this_player()->query_prop(LIVE_I_SITTING))
    {
        notify_fail("You are already sitting at one of the reading desks!\n");
        return 0;
    }

    write("You find yourself an empty reading desk and sit down.\n");
    say(QCTNAME(this_player()) + " finds an empty reading desk and "
        + "sits down.\n");
    this_player()->add_prop(LIVE_S_EXTRA_SHORT, " is sitting");
    this_player()->add_prop(LIVE_I_SITTING, 1);
    return 1;
}

/*
 * Function:    do_stand
 * Description: Function to allow someone to stand up from a reading desk.
 */
public int
do_stand(string arg)
{
    if (!this_player()->query_prop(LIVE_I_SITTING))
    {
        notify_fail("You are not sitting!\n");
        return 0;
    }
    
    write("You get out of the comfortable wooden chair and stand up.\n");
    say(QCTNAME(this_player()) + " gets out of the comfortable wooden "
        + "chair and stands up.\n");
    this_player()->remove_prop(LIVE_S_EXTRA_SHORT);
    this_player()->remove_prop(LIVE_I_SITTING);
    return 1;
}

/*
 * Function name: library_read_book
 * Description:   Display the text of a book to the reader
 * Arguments:     string text_filename - The filename of the book file to use
 *                string book_name     - The title of the book
 *                int mread            - true if more should be used
 * Returns:       nothing
 */
public void
library_read_book(string text_filename, string book_name, int mread)
{
    setuid();
    seteuid(getuid());

    write("You pick up the book titled \"" 
        + implode(map(explode(book_name, " "), capitalize), " ")
        + "\" from the bookshelf and begin to read it:\n\n");        
    display_library_action(" picks up a book from the bookshelf and "
                        + "begins to read it.\n");
        
    if (mread || (file_size(text_filename) > 4000))
    {
        this_player()->more(generate_scroll_text(read_file(text_filename, 4), "Property of the Elemental Guilds of Calia"));
    }
    else
    {
        write(generate_scroll_text(read_file(text_filename, 4), "Property of the Elemental Guilds of Calia"));
    }
}
