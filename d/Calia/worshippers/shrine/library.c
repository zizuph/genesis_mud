/******************************************************
 * The Elemental Worshipper's of Calia Private Library
 *
 * Located: /d/Calia/worshippers/shrine/library.c
 *
 * Coded by: Quintas  
 * Date :    06/29/03
 *
 * Modifications :  Updated chair description to show
 *                  persons sitting in it. 
 *                  Quintas 01/26/04
 *
 * Acknowledgements : Thank you to Shiva, Raven, Deagol
 *                    and many other wizards for all the 
 *                    help and hints that led to this
 *                    work being completed.
 *
 ******************************************************/



inherit "/std/room";
inherit "/lib/library";

#include "defs.h"
#include <files.h>
#include <stdproperties.h>
#include <macros.h>
#include <std.h>
#include <composite.h>

#define SITTING_IN_CHAIR  "_sitting_in_chair"
#define IS_WRITING "_is_writing"
#define SHELF_TYPE shelf_types[0]
#define PLURAL_SHELF_TYPE \
    (sizeof(plural_shelf_types) ? \
    plural_shelf_types[0] : LANG_PWORD(shelf_types[0]))


int chair_occupied = 0;

/*
 * Function name: library_exit_block
 * Description:   Check to see if the player is carrying a library
 *                book.  This is meant to be used as a block function
 *                for exits from the library so that books cannot be
 *                removed.
 * Returns:       1/0 - book carried/not carried
 */
public int
library_exit_block()
{
    /* See if the player is carrying a book */
    if (::library_exit_block())
    {
        /* A book was found.  Give a warning and return 1 to block the exit */
        write("You cannot leave with a library scroll!\n");
        return 1;
    }
    /* See if the player is sitting at the desk. */
    if (this_player()->query_prop(SITTING_IN_CHAIR))
    {
        write("You are still sitting!\n");
        return 1;
    }

    
     /* No book present and not sitting in the chair.
        Return 0 to allow the player to exit */
    return 0;
}


void
create_room()
{
    set_short("A small chamber");
    set_long("This chamber has been carved out of the solid rock. "+
        "All the surfaces have been polished to a brilliance that " +
        "allows the reflection of light that is given off by the " +
        "phosphorescent moss that grows along the ceiling. On the " +
        "southern wall you notice rows " +
        "of small slots carved into the stone, which appear to be " +
        "shelves of some sort. Each of these slots contain a number " +
        "of parchment scrolls. On the western wall you notice a small " +
        "slate plaque that you can read. Against the eastern wall " +
        "you see a small desk. You can head out back into the bank " +
        "to the northwest.\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_IS, 1);    
    add_prop(ROOM_M_NO_TELEPORT, "You cannot do that here.");

    set_book_type("scroll");
    set_plural_book_type("scrolls");

    set_shelf_type(({"row", "shelf"}));
    set_plural_shelf_type(({"rows", "shelves"}));
 
    set_borrow_required(1);
    
    // Set the directory where book files will be store */
    set_book_directory("/d/Calia/worshippers/shrine/texts/");
    set_book_approval_directory("/d/Calia/worshippers/shrine/texts/approval/");
    set_book_removal_directory("/d/Calia/worshippers/shrine/texts/removal/");
   
    // Initialize the library
    create_library();
 
    // Add things to look at in this room.

    add_item("chamber", query_long());
    add_item(({"plaque", "small plaque", "slate plaque", "small slate plaque"}),&library_help());
    add_cmd_item("plaque", "read", &library_help());
    add_item(({"row", "rows"}), "These rows of slots are carved into the west " +
              "wall. There are a number of scrolls in them.\n");
    add_item(({"shelf", "shelves"}), "These aren't really shelves, but more " +
              "like rows of slots.\n");
    add_item(({"slot", "slots"}), "There are a number of little slots carved " +
              "into the wall.  Each contains mutltiple scrolls.\n");
    add_item(({"scroll", "scrolls", "parchment scrolls"}), "These scrolls fit " +
              "nicely in the slots that hold them.  Perhaps you should read " +
              "the plaque to find out how to read them?\n");
    add_cmd_item("scroll", "read", "Hmmm, are you actually holding a scroll?\n");
    add_item(({"west wall", "western wall"}), "This is the west wall of this " +
              "chamber. There is a slate plaque hanging on it.\n");
    add_item(({"wall", "walls", "eastern wall", "northern wall"}), "These walls " +
              "are made of carved stone. A small desk has been set along the " +
              "eastern wall.\n");
    add_item(({"south wall", "southern wall"}), "This wall has rows of small slots " +
              "carved into it\n");
    add_item("desk", "This is a sturdy wooden desk with a chair behind it. " +
             "You see a pile of parchment and an inkwell with a quill " +
             "sitting on it.\n");
    add_item(({"rock", "surface", "surfaces", "stone"}), "These surfaces have been " +
             "highly polished to reflect the light from the moss.\n");
    add_item(({"pile", "parchment", "pile of parchment"}), "These leaves of " +
             "parchment are of a good quality.  In fact, they are good " +
             "to write a tome of information with!\n");
    add_item(({"inkwell", "pot"}), "This is a small, black-laquered, ceramic " +
             "pot. It is full of ink and ready for use.\n");
    add_item("quill", "The quill is a large tailfeather from a pigeon. It has " +
             "been sharpened and fitted with a split metal tip, to make it " +
             "into a writing implement.\n");
    add_item(({"tailfeather", "feather"}), "This is a large tail feather from " +
             "a pigeon that has been harvested to make a quill like the one " +
             "you are holding.\n");
    add_item("ink", "This is a black, viscous, liquid that can be used for " +
             "writing a book.\n");
    add_item(({"tip", "metal tip"}), "This metal tip is split from it's point " +
             "up it's center to form a slot to hold ink.  Perhaps you could " +
             "use it to write a book?\n");
    add_item("chair", "This is a comfortable looking chair, suitable for sitting " +
              "in for long periods.\n");
    add_item("floor", "A marble tiled floor. It has been kept clean of natural " +
             "litter.\n");
    add_item("ceiling", "The ceiling is a result of this chamber being carved " +
             "out of the stone. Phosphorescent moss grows all along it to provide " +
             "the light for this room.\n");
    add_item(({"moss", "phosphorescent moss"}), "This moss, usually found in " +
             "dark, subterranean caves, gives off a faint yellow-green glow " +
             "that is magnified by the polished walls.\n");
             
    
    add_exit(WOR_SHRINE +"bank","northwest",library_exit_block,1);
}

int
do_sit(string str)
{
    if (chair_occupied)
    {
        notify_fail("There is already somebody sitting in the only chair!\n");
        return 0;
    }

    if ((!str) && (str != "down") && (str != "in chair"))
    {
        notify_fail("Sit where? In the chair?\n");
        return 0;
    }

    if (this_player()->query_prop(SITTING_IN_CHAIR))
    {
        notify_fail("You are already sitting on the couch.\n");
        return 0;
    }

    this_player()->add_prop(SITTING_IN_CHAIR,1);
    chair_occupied = 1;
    write("You sit down in the chair.\n");
    say(QCTNAME(this_player())+" sits down in the only chair.\n");
    this_player()->add_prop(LIVE_S_EXTRA_SHORT," is sitting on the only chair");
    return 1;
}

int
do_stand(string str)
{
    if ((!str) && (str != "up"))
    {
        NF("Stand what...up?\n");
        return 0;
    }

    if (!TP->query_prop(SITTING_IN_CHAIR))
    {
        NF("You are already standing.\n");
        return 0;
    }

    TP->remove_prop(SITTING_IN_CHAIR);
    chair_occupied = 0;
    write("You stand up from the chair.\n");
    say(QCTNAME(this_player())+" stands up.\n");
    this_player()->remove_prop(LIVE_S_EXTRA_SHORT);
    return 1;
}

void
init()
{
    ::init();

    // Add the library commands
    init_library();
    // Add the chair commands
    add_action(do_sit,"sit");
    add_action(do_stand,"stand");
}


/*
 * Function name: library_admin_access
 * Description:   Redefine this function to limit permission to admin commands
 * Returns:       1 - this_player() is permitted to perform admin commands
 *                0 - this_player() is not permitted to perform admin commands
 */
public int
library_admin_access()
{
    if (SECURITY->query_wiz_rank(this_interactive()->query_real_name()) &&         SECURITY->query_wiz_dom(this_interactive()->query_real_name()) == "Calia")
    {
        return 1;
    }

    if (SECURITY->query_wiz_rank(this_interactive()->query_real_name()) >= WIZ_ARCH)
    {
        return 1;
    }

    if (this_interactive()->query_guild_member("Elemental Worshippers of Calia") && this_interactive()->query_guild_leader_lay())
    {
        return 1;
    }

    write("You don't have permission to do that.\n");
    return 0;
}


/*
 * Function name: library_write_access
 * Description:   Limit permission to write books to certain people
 * Returns:       1 - this_player() is allowed to write
 *                0 - this_player() is not allowed to write
 */

public int
library_write_access()
{
    /* We'll allow any member of the layman guild
     * to write books
     */
    if (this_interactive()->query_guild_member("Elemental Worshippers of Calia"))
    {
        return 1;
    }

    /* We'll allow Calian wizards to write books */
    if (SECURITY->query_wiz_dom(this_interactive()->query_real_name()) == "Calia")
    {
        return 1;
    }

    /* No-one else has permission to write books */
    write("The Elementals will not accept books from people " +
          "who do not worship them.\n");
    return 0;
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

/* Quintas : Redefined to add property management. */
public int
done_writing(string title, string summary, string input)
{
    if (!strlen(input))
    {
        library_write_abort_hook();
        this_player()->remove_prop(IS_WRITING);
        return 0;
    }

    if (!add_book(title, summary, "by " + this_player()->query_name(), 
        input, !!strlen(appr_dir)))
    {
        library_write_failed_hook();
        this_player()->remove_prop(IS_WRITING);
    }
    else
    {
        this_player()->remove_prop(IS_WRITING);
        write("Ok.\n");
    }

    return 1;

}

/*
 * Function name: library_write_get_summary
 * Description:   Catch input from the user to be used as the new
 *                book's summary
 * Arguments:     object who   - the user
 *                string title - the new book's title
 *                string input - the user's input
 * Returns:       1/0 - summary set/not set
 */
public int
library_write_get_summary(object who, string title, string input)
{
    if (input == "~q")
    {
        this_player()->remove_prop(IS_WRITING);
        return 0;
    }

    set_this_player(who);

    if (!library_validate_summary(input))
    {
        input_to(&library_write_get_summary(this_player(), title));
        return 0;
    }

    setuid();
    seteuid(getuid());

    write("\n");
    clone_object(EDITOR_OBJECT)->edit(&done_writing(title, input));
    return 1;
}

/*
 * Function name: library_write_get_title
 * Description:   Catch user input to be used as the new book's title
 * Arguments:     object who   - the user
 *                string input - the title
 * Returns:       1/0 - title set/not set
 */
public int
library_write_get_title(object who, string input)
{
    if (input == "~q")
    {
        this_player()->remove_prop(IS_WRITING);
        return 0;
    }

    set_this_player(who);

    if (!library_validate_title(input))
    {
        input_to(&library_write_get_title(this_player()));
        return 0;
    }

    library_write_prompt_summary_input_hook();
    input_to(&library_write_get_summary(this_player(), input));
    return 1;
}


/*
 * Function name: library_write
 * Description:   The "write" command
 * Arguments:     string str - arguments to the "write" command
 * Returns:       1/0 - syntax success/failure
 */
/* Quintas : Redefined to add property management. */
public int
library_write(string str)
{
    if (!this_player()->query_prop(SITTING_IN_CHAIR))
    {
        write("Don't you think it would be easier to write a book " +
              "if you were sitting down?\n");
        return 1;
    }

    if (!library_write_access())
    {
        return 1;
    }
 
    this_player()->add_prop(IS_WRITING, 1);
    library_write_prompt_title_input_hook();

    input_to(&library_write_get_title(this_player()));
    return 1;
}


/*
 * Function name: library_help
 * Returns:       A string containing library help information
 */
public string
library_help()
{
    function help_cmd = &sprintf("%-33s - %-=40s\n", , );

    string str =
        "\nLibrary commands available:\n" +
        help_cmd("List " + 
            (m_sizeof(book_shelves) ? "[<" + SHELF_TYPE + ">] " : "") +
            "[titles]", "List books in the library.");

    if (m_sizeof(book_shelves))
    {
        str += help_cmd("List " + PLURAL_SHELF_TYPE, 
                        "List " + PLURAL_SHELF_TYPE + " in the library.");
    }

    if (borrow_required)
    {
        str += 
            help_cmd("Borrow <title>",
                     "Borrow a book for reading.") +
            help_cmd("Return <book>",
                     "Return a book to the library.");
    }
    else
    {
        str += help_cmd("Read <title>", "Read a book in the library.") +
               help_cmd("Mread <title>", "Mread a book in the library.");
    }

    str += help_cmd("Write", "Write a book and submit it to the library.");

    if ((SECURITY->query_wiz_rank(this_player()->query_real_name()) &&                 SECURITY->query_wiz_dom(this_player()->query_real_name()) == "Calia") ||
        (SECURITY->query_wiz_rank(this_player()->query_real_name()) >= WIZ_ARCH) ||
        (this_player()->query_guild_member("Elemental Worshippers of Calia") &&         this_player()->query_guild_leader_lay()))
    {
        str += "\nAdministrator commands available:\n\n";

        if (strlen(appr_dir))
        {
            str += 
                help_cmd("Approve <title>",
                     "Approve a book for inclusion in the library.");

            if (borrow_required)
            {
                str += help_cmd("Borrow approval <title>",
                    "Administrators may borrow books which have not been " +
                     "approved by using the \"approval\" option.");
            }
            else
            {
                str += help_cmd("(m)read approval <title>",
                    "Administrators may read books which have not been " +
                    "approved by using the \"approval\" option.");
            }

            str +=
                help_cmd("Deny <title>",
                     "Deny a book from inclusion in the library.") +
                help_cmd("List approval [titles]",
                     "Administrators may list books that need approval with " +
                     "the \"approval\" option.");
        }

        str += help_cmd("Discard <title>", "Remove a book from the library.");

        if (m_sizeof(book_shelves))
        {
            str += help_cmd("Classify <title>",
                            "Assign a book to a " + SHELF_TYPE + ".");
        }
    }
    return str + "\n";
}