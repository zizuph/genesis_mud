/*
 * Genesis Library Writing Room
 *
 * Writing Room of the Library where players can
 * construct books for submission to the Library
 *
 * Created by Petros, May 2009
 */

#pragma strict_types

// Includes
#include <macros.h>
#include <stdproperties.h>
#include "defs.h"

// Inheritance
inherit (LIBRARY_ROOM_DIR + "library_base");

// Defines
#define IS_SITTING_PROP     "_library_is_sitting"
#define OLD_EXTRA_SHORT     "live_s_old_extra_short"

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
    create_genesis_library(({ "unclassified", "approval" }), "");
    
    // Descriptions Section
    set_short("Writing room");
    set_long("Various writing stations line the walls of this dimly lit "
           + "room. The air in here is a bit musky and the distinct smell "
           + "of writing ink wafts from each station. You see a few "
           + "individuals sitting and writing, with the only sound they "
           + "make being the scraping of the quill against the paper. "
           + "There are some empty stations for you to <sit> in, however. "
           + "\n\n");
 
    // Room Item Section                              
    add_item( ({ "station", "stations", "writing station",
                 "writing stations", "various writing stations" }),
        "Each station has a desk, a comfortable chair, an inkwell, and"
      + " a pile of blank parchment.\n");
    add_item( ({ "desk", "desks" }),
        "The desks are fairly small, but provide ample room for the"
      + " art of composition, which is strongly encouraged here.\n");
    add_item( ({ "chair", "chairs", "comfortable chair",
                 "comfortable chairs" }),
        "They look comfortable. You think you could <sit> in one for"
      + " hours while working up your next masterpiece.\n");
    add_item( ({ "ink", "writing ink" }),
        "Each inkwell looks like it has plenty of ink. I suppose they"
      + " have someone come around and fill them regularly.\n");
    add_item( ({ "inkwell", "inkwells" }),
        "A feathery quill extends from the inkwells. Inviting, eh?\n");
    add_cmd_item( ({ "quill", "feathery quill", "quills",
                     "feathery quills" }),
                  ({ "get", "take", "steal", "pick" }),
        "If you want to write something, you'll need to <sit> at one of"
      + " the stations and <write> a book.\n");
    add_item( ({ "quill", "quills", "feathery quill", "feathery quills" }),
        "Soft, supple in the hand, perfect for writing a book!\n");
    add_item( ({ "wall", "walls", "walls of this dimly lit room" }),
        "The walls are lined with writing stations, a few of which are"
      + " occupied by individuals hunched over their work.\n");
    add_item( ({ "individual", "individuals", "writer", "writers" }),
        "There are a number of writers present here, which stands to"
       + " reason since this is, in fact, a writing room.\n");
    add_item( ({ "room", "here", "area", "writing room", "dimly lit room" }), 
        "This appears to be a room dedicated to writing. There are many"
      + " stations lining the walls which look like they would welcome"
      + " your efforts.\n");
    add_item( ({ "air" }),
        "Pretty musty in here, isn't it?\n");
    add_item( ({ "smell", "smell of ink", "smell of writing ink" }),
        "Its not exactly an unpleasant smell ... just distinctive.\n");
    add_item( ({ "scraping", "scraping of the quill",
                 "scraping of the quill against the paper" }),
        "Scrape ... scrape ... scrape ...\n");
    add_item( ({ "empty station", "empty stations" }),
        "This is your chance for immortal glory. You too could be"
      + " published and your work added to the Library of Sparkle! Sit,"
      + " my friend ... <sit> and write what is within you.\n");
    add_item( ({ "floor", "ground", "down" }),
        "The floor is polished hardwood, which shows a few signs of use.\n");
    add_item( ({ "hardwood", "polished hardwood" }),
        "It is extremely fine material. A pity about the stains.\n");
    add_item( ({ "signs", "signs of use", "sign of use", "stain",
                 "ink stains" }),
        "A number of places on the floor have ink stains that it seems"
      + " even the best efforts were unable to remove.\n");
    add_item( ({ "ceiling", "up", "roof" }),
        "The ceiling of this room is a bit lower than in the rest of the"
      + " library.\n");
    add_item( ({ "pile", "pile of parchment", "piles of parchment",
                 "paper", "papers", "pile of paper", "piles of paper",
                 "paper pile", "parchment pile", "paper piles",
                 "parchment piles" }),
        "They are neat and orderly. There's nothing like a fresh sheet"
      + " to encourage the creative mind, eh?\n");
    add_item( ({ "fresh sheet", "sheet", "fresh sheet" }),
        "C'mon ... you know you want to. Write something!\n");

    // Exits Section
    add_exit(LIBRARY_ROOM_DIR + "poetry", "south", "@@is_sitting@@");    
}

/* 
 * Function name: can_write_book
 * Description:   Will be used to determine whether one can write books
 *                in this particular library room.
 * Arguments:     none
 * Returns:       nothing
 */
public int
can_write_book()
{
    return 1;
}

/*
 * Function name: library_write_access
 * Description:   Redefine this function to limit permission to write books
 * Returns:       1 - this_player() is permitted to write a book
 *                0 - this_player() is not permitted to write a book
 */
public int
library_write_access()
{
    // Everyone can write in this library as long as they're sitting
    if (this_player()->query_prop(IS_SITTING_PROP))
    {
        return 1;
    }
    
    write("You're not sitting at a nice writing station "
        + "and you just can't figure out how else you'd be able "
        + "to write a book!\n");
    return 0;
}

/*
 * Function name: library_write
 * Description:   The "write" command
 * Arguments:     string str - arguments to the "write" command
 * Returns:       1/0 - syntax success/failure
 */
public int
library_write(string str)
{
    if (!library_write_access())
    {
        return 1;
    }

    tell_room(environment(this_player()), QCTNAME(this_player())
        + " begins to write a book.\n", ({ this_player() }) );
        
    library_write_prompt_title_input_hook();

    input_to(&library_write_get_title(this_player()));
    return 1;
}

/*
 * Function name: library_read
 * Description:   Try to read a book from the library.
 * Arguments:     string str - any arguments to the command
 * Returns:       1/0 - Command success/failure
 */
public int
library_read(string str)
{
    if (library_admin_access())
    {
        return ::library_read(str);
    }
    
    return 0;
}

/* 
 * Function name: library_list
 * Description:   The "list" command
 * Arguments:     string str - arguments given to the "list" command
 * Returns:       1/0 - syntax success/failure
 */
public int
library_list(string str)
{
    if (library_admin_access())
    {
        return ::library_list(str);
    }
    
    return 0;
}

/*
 * Function name: library_hook_get_approval_names
 * Description  : This routine can be redefined in the library code to provide
 *                the names of the players who are authorized to approve books
 *                before they are added to the library. If this is the case,
 *                those players will receive a mail informing them of the fact
 *                that a new book has been submitted.
 * Returns      : string * - the list of names (in lower case).
 */
public mixed
library_hook_get_approval_names()
{
    return ({ "petros" });
}

/*
 * Function name: library_write_abort_hook
 * Description:   Redefine this to alter the message given when the
 *                user aborts writing a book
 */
public void
library_write_abort_hook()
{
    write("You decide to stop writing the book you're working "
        + "on. A gnome comes by and collects the unfinished "
        + "work.\n");
}

/*
 * Function name: library_write_prompt_title_input_hook
 * Description:   Redefine this to alter the message given to prompt
 *                the user to input a book title
 */
public void
library_write_prompt_title_input_hook()
{
    write("Type the name of the book below. (fewer than 20 " 
        + "characters).  (~q to quit)\n> ");
}
       
/*
 * Function name: library_write_prompt_summary_input_hook
 * Description:   Redefine this to alter the message given to prompt
 *                the user to input a book summary
 */
public void
library_write_prompt_summary_input_hook()
{
    write("\nEnter a short summary of the book. (~q to quit)\n> ");
}

/*
 * Function name: library_write_failed_hook
 * Description:   Redefine this to alter the message given when a book
 *                cannot be saved for some reason.
 */
public void
library_write_failed_hook()
{
    write("Something prevents you from completing the book "
        + "that you were working on.\n");
}

/*
 * Function name: done_writing
 * Description:   Catch input from the user to be used as the new
 *                book's text and add the new book to the library
 * Arguments:     string title   - the book's title
 *                string summary - the book's summary
 *                string input   - the book's text
 * Returns:       1/0 - text set/not set
 */
public int
done_writing(string title, string summary, string input)
{
    if (!strlen(input))
    {
        library_write_abort_hook();
        return 0;
    }

    if (!add_book(title, summary, this_player()->query_name(), 
        input, !!strlen(appr_dir)))
    {
        library_write_failed_hook();
    }
    else
    {
        write("You complete your work and a gnome picks it up. You "
            + "sense that your work has been submitted to the "
            + "librarian for his consideration.\n");
    }

    return 1;
}

public int
do_sit(string arg)
{
    if (this_player()->query_prop(IS_SITTING_PROP))
    {
        notify_fail("You are already sitting down!\n");
        return 0;
    }
    
    this_player()->add_prop(IS_SITTING_PROP, 1);
    this_player()->add_prop(OLD_EXTRA_SHORT,
        this_player()->query_prop(LIVE_S_EXTRA_SHORT));
    this_player()->add_prop(LIVE_S_EXTRA_SHORT, 
        " is sitting at a writing station");
    write("You find an empty station and plop yourself into "
        + "the comfortable chair. A nearby gnome indicates "
        + "to you that you can begin to <write> a new book.\n");
    tell_room(this_object(), QCTNAME(this_player()) + " seats "
        + this_player()->query_objective() + "self at one of "
        + "the writing stations.\n", ({ this_player() }) );        
        
    return 1;
}

public int
do_stand(string arg)
{
    if (!this_player()->query_prop(IS_SITTING_PROP))
    {
        notify_fail("You are already standing!\n");
        return 0;
    }
    
    this_player()->remove_prop(IS_SITTING_PROP);
    this_player()->add_prop(LIVE_S_EXTRA_SHORT,
        this_player()->query_prop(OLD_EXTRA_SHORT));
    this_player()->remove_prop(OLD_EXTRA_SHORT);
    write("You get up from the comfortable chair at the "
        + "writing station.\n");
    tell_room(this_object(), QCTNAME(this_player()) + " stands "
        + "up.\n", ({ this_player() }) );
        
    return 1;    
}

/* 
 * Function name: leave_inv
 * Description:   Called when objects leave this container or when an
 *                object is about to change its weight/volume/light status.
 * Arguments:     ob: The object that just left this inventory.
 *                to: Where it went.
 */
public void
leave_inv(object ob, object to)
{
    if (living(ob)
        && ob->query_prop(IS_SITTING_PROP))
    {
        do_stand("");
    }
    ::leave_inv(ob, to);
}

public int
is_sitting()
{
    object player;
    
    player = this_player();
    if (living(player) 
        && player->query_prop(IS_SITTING_PROP))
    {
        player->catch_tell("You are comfortably sitting in the "
            + "writing station! Maybe you should try to <stand> "
            + "first.\n");
        return 1;
    }
    
    return 0;    
}

public void
init()
{
    ::init();
    add_action(do_sit, "sit");
    add_action(do_stand, "stand");
}
