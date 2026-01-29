/*
 *  /d/Sparkle/guilds/new_merc/library.c
 *
 *  This is the guild library for the Mercenaries.
 *
 *  Created July 2009, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../merc_defs.h"

inherit MERC_ROOM_BASE;
inherit "/lib/guild_library";
inherit "/d/Emerald/blackwall/delrimmon/legacy/fireplace";
inherit "/d/Emerald/blackwall/delrimmon/legacy/room_chairs";
  
#include <macros.h>
#include <mail.h>
#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/legacy/room_chairs.h"
#include "/d/Emerald/blackwall/delrimmon/legacy/fireplace.h"

/* Definitions */
#define        BUNK_PROP    "_bunk_prop"
#define        CHAIR_NAME   "comfortable chair"

/* Prototypes */
public void        create_merc_room();
public void        init();
public mixed *     library_hook_get_approval_names();
varargs mixed      add_new_book(string title, string contents, 
                                string author, string shelf = "",
                                string filename = "", 
                                string book_id = "");
public int         do_sit(string arg);
public void        do_sit_msgs(object pl, string prep, string name);
public void        do_stand_msgs(object pl, string name);
public string      look_chairs();
public void        leave_inv(object ob, object to);
public string      show_subloc(string subloc, object pl, object for_obj);


/*
 * Function name:        create_merc_room
 * Description  :        set up the room with area presets
 */
public void
create_merc_room()
{
    set_short("a quiet library in the Mercenary Guild");
    set_long("This central room is much quieter than most other places"
      + " in the lodge. There are no windows, and a thick carpet has been"
      + " spread over the floor. As such, it functions quite well as"
      + " the guild library. The northern half of the room is filled with"
      + " shelves of books. Comfortable chairs are placed around the"
      + " southern half of the room. A plaque is here to assist people"
      + " who wish to use the library.\n\n");

    add_item( ({ "window", "windows" }),
        "There are no windows in this room.\n");
    add_item( ({ "central room" }),
        "Indeed, this room is positioned right in the middle of the"
      + " second floor.\n");
    add_item( ({ "second floor", "second story" }),
        "Its hard to tell that you are up on the second story here in"
      + " the library due to the lack of windows.\n");
    add_item( ({ "here", "area", "room", "library", "guild library" }),
        "This library, though fairly small, is extremely comfortable.\n");
    add_item( ({ "floor", "ground", "down" }),
        "The floor of the library is covered with a nice thick carpet.\n");
    add_item( ({ "carpet", "rug", "thick carpet", "thick rug",
                 "nice carpet", "nice rug", "nice thick carpet",
                 "nice thick rug" }),
        "The carpet really helps absorb sound, keeping the library"
      + " quiet for reading.\n");
    add_item( ({ "north half", "northern half", "north half of the room",
                 "northern half of the room", "north", "north wall",
                 "northern wall", "wall to the north" }),
        "The northern half of the room is where the shelves of books"
      + " are located in this library.\n");
    add_item( ({ "south half", "southern half", "south half of the room",
                 "southern half of the room", "south", "south wall",
                 "southern wall", "wall to the south",
                 "sitting room" }),
        "The southern half of the room functions as a sitting room for"
      + " those who wish to read in comfort.\n");
    add_item( ({ "shelf", "shelves", "shelf of books", "bookshelf",
                 "shelves of books", "bookshelves" }),
        "There are quite a few of them. You can <list> to see the"
      + " available shelves. You can also <read plaque> for more"
      + " detailed instructions.\n");
    add_item( ({ "book", "books" }),
        "To see which books are available here you may <read plaque> to"
      + " see how to use the library.\n");
    add_item( ({ "chair", "chairs", "comfortable chair",
                 "comfortable chairs", "very comfortable chair",
                 "very comfortable chairs" }), look_chairs);
    add_item( ({ "people", "person", "persons", "mercenary",
                 "mercenaries" }),
        "There are a number of people in here reading books. Perhaps"
      + " you'd like to join them?\n");
    add_item( ({ "corner", "corners" }),
        "There is a Mercenary in the corner very engrossed in a book.\n");
    add_item( ({ "mercenary in the corner" }),
        "Totally absorbed in a book, that one.\n");
    add_item( ({ "west", "west wall", "western wall",
                 "wall to the west" }),
        "The western wall houses a few shelves and a few chairs.\n");
    add_item( ({ "east", "east wall", "eastern wall",
                 "wall to the east" }),
        "The eastern wall houses a few shelves and a few chairs.\n");
    add_item( ({ "light", "sunlight", "illumination" }),
        "The light in this room is supplied by lanterns which have"
      + " been fixed to the wall.\n");
    add_item( ({ "lantern", "lanterns" }),
        "There are quite a few of them, so as to provide enought"
      + " light to read by.\n");
    add_item( ({ "librarian" }),
        "The librarian moves around the library quietly and almost"
      + " unnoticed.\n");

    add_cmd_item( ({ "lantern", "lamp", "lanterns", "lamps" }),
                  ({ "get", "take", "pick" }),
        "The lanterns are fixed in place, and cannot be removed.\n");
    add_cmd_item( ({ "lantern", "lamp", "lanterns", "lamps" }),
                  ({ "extinguish" }),
        "The librarian will not allow that!\n");

    add_tell("A Mercenary sitting in the corner quietly turns the"
      + " page on a book he is reading.\n");
    add_tell("You hear a quiet cough from somewhere in the library.\n");
    add_tell("Muffled footfalls echo from beyond the walls.\n");
    add_tell("One of the people sitting nearby stands up, returns the"
      + " book they were reading, and quietly leaves the room.\n");

    add_indoor_view();
    add_indoor_lodge_view();

    add_prop(ROOM_I_INSIDE, 1);

    set_no_exit_msg( ({ "northwest", "northeast", "southeast",
                        "southwest" }),
        "You poke around the corner of the library, but don't find"
      + " anything interesting.\n");
    set_no_exit_msg( ({ "west", "east" }),
        "There is a wall there.\n");

    set_library_book_object(OBJ_DIR + "merc_book");

    setuid();
    seteuid(getuid());

    // Guild Library Specific Items
    set_library_save_path(BOOKS_DIR);
    set_library_allow_new_books(1);

    create_library();

    add_item(({"plaque", "instructions", }), library_help);
    add_cmd_item(({"plaque", "instructions", }), "read", library_help);
    // End Guild Library Specific Items

    add_chair(CHAIR_NAME, "[down] [at] [in] [on] [one] [of] [the] [nearby]"
                        + " [very] [comfortable] "
                        + " 'chair' / 'chairs'",
                          20, "in", 0);
    
    room_add_object(DOORS_DIR + "n_library_s");
    room_add_object(DOORS_DIR + "s_library_n");
} /* create_room */


/* 
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();
    init_library();
    init_room_chairs();
} /* init */


/*
 * Function name: query_librarian
 * Description  : See if a person is a librarian
 * Arguments    : player - the player we want to check
 * Returns      : 0 on failure, 1 on success
 */
public int 
query_librarian(object player)
{

    // By default only wizards are librarians. However, if you want,
    // return 1 here for mercs that have a certain level, or just all
    // mercs.
    //
    // Librarians have the ability to create/remove/delete, etc.

    string *names = library_hook_get_approval_names();

    foreach(string name: names)
    {
        if(player->query_real_name() == name)
            return 1;
    }

    return player->query_wiz_level();
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
public mixed *
library_hook_get_approval_names()
{
    return ({ "gorboth", "allara", "zillian" });
} /* library_hook_get_approval_names */


/*
 * Function name: add_new_book
 * Description  : Add a new book to the shelves
 * Arguments    : title - the title of the book
 *              : contents - the contents of the book
 *              : author - the author of the book
 *              : shelf (optional) - the shelf on which to place the book
 *              : filename (optional) - which filename to use for storing the
 *              :       content
 *              : book_id (optional) - the id by which the book is known
 * Returns      : a filename which contains the contents or 0 on failure
 *
 * I mask this from the parent so that I can have it generate a mail
 * and send it to whoever I have deemed to be the current guild
 * librarian.
 */
varargs mixed
add_new_book(string title, string contents, 
             string author, string shelf = "", string filename = "", 
             string book_id = "")
{
    mixed  submitted = ::add_new_book(title, contents, author, shelf,
                         filename, book_id);
    string *names = library_hook_get_approval_names();

    if (!submitted)
    {
        return 0;
    }

    CREATE_MAIL("New book " + author, "MercLibrary",
                implode(names, ","), "",
                "========================================================="
              + "======================\n"
              + "Title: " + title + "\n"
              + "========================================================="
              + "======================\n\n"
              + contents + "\n"
              + "---------------------------------------------------------"
              + "----------------------\n");

    return submitted;
} /* add_new_book */


/*
 * Function name:        look_chairs
 * Description  :        VBFC for block; include occupants
 * Returns      :        string -- the desc
 */
public string
look_chairs()
{
    return "Comfortable chairs are placed around the room,"
      + " offering a place to <sit> while reading.\n"
         + sitting_on_chair(CHAIR_NAME, this_player(), 0, 0);
} /* look_chairs */


/* 
 * Function name: leave_inv
 * Description:   Called when objects leave this container or when an
 *                object is about to change its weight/volume/light status.
 * Arguments:     ob: The object that just left this inventory.
 *                to: Where it went.
 *
 * This function is redefined to force players to stand up before
 * leaving if they are currently sitting in a chair. Also, we set up
 * some special library leave functions.
 */
public void
leave_inv(object ob, object to)
{
    object   oldtp;

    leave_inv_room_chairs(ob, to);
    library_leave_inv(ob, to);
    ::leave_inv(ob, to);
} /* leave_inv */


/*
 * Function name:       do_sit
 * Description  :       mask parent to block "sit" and "sit down"
 * Arguments    :       string arg -- whatever the player typed
 * Returns      :       1 on success, 0 on failure
 */
public int
do_sit(string arg)
{
    if (!arg ||
        arg == "down")
    {
        notify_fail("Sit where?\n");
        return 0;
    }
    return ::do_sit(arg);
} /* do_sit */


/*
 * Function name:       do_sit_msgs
 * Description  :       mask parent so the block msgs look right
 * Arguments    :       object pl -- the person who's sitting
 *                      string prep -- the preposition
 *                      string name -- the name of the chair
 */
public void
do_sit_msgs(object pl, string prep, string name)
{
    write("You make yourself comfortable in one of the chairs.\n");
    say(QCTNAME(pl) + " sits down and gets comfortable in one of the"
      + " chairs.\n");
} /* do_sit_msgs */


/*
 * Function name:       do_stand_msgs
 * Description  :       mask parent so the block msgs look right
 * Arguments    :       object pl -- the person who's standing
 *                      string name -- the name of the chair
 */
public void
do_stand_msgs(object pl, string name)
{
    write("You stand up from the chair, feeling a bit less cozy.\n");
    say(QCTNAME(pl) + " stands up from one of the chairs.\n");
} /* do_stand_msgs */


/*
 * Function name:       show_subloc
 * Description  :       generate "foo is sitting ..." msg
 *                      for living's desc.
 * Arguments    :       string subloc -- the subloc
 *                      object pl -- the player
 *                      object for_obj -- who's doing the looking
 * Returns      :       string -- the "is sitting" msg
 *
 * This is a mask from the room_chairs.c code to create my own
 * look for it.
 */
public string
show_subloc(string subloc, object pl, object for_obj)
{
    string      name;
    mixed       *chairptr;

    if (this_player()->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
    {
        return "";
    }

    if (subloc != SITTING_S_SUBLOC)
    {
        return pl->show_subloc(subloc, pl, for_obj);
    }

    if (strlen(name = pl->query_prop(LIVE_S_SITTING)) &&
        pointerp(chairptr = query_room_chairs()[name]))
    {
        if (for_obj != pl)
        {
            return capitalize(pl->query_pronoun()) + " is sitting"
              + " in one of the comfortable chairs.\n";
        }
        return "You are sitting in a very comfortable chair.\n";
    }
    return "";
} /* show_subloc */
