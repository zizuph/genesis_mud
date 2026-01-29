/* 
 * /lib/library.c
 *
 * Support for libraries.
 * 
 * Notation - This is from /lib/library, this was changed to use 
 * scrolls instead of books.
 * So if you wish to use books, use mudlib. Damaris.
 * Example usage:
 * 
 * inherit "/std/room";
 * inherit "/lib/library";
 *
 * void
 * create_room()
 * {
 *     set_short("Library");
 *     set_long("This is a library.\n");
 *    
 *     // Set the directory where scroll files will be stored
 *     set_scroll_directory("/d/Domain/subdir/");
 *
 *     // Make two shelves, one for maps and one for other scrolls
 *     add_scroll_shelf(({ "general", "maps" }));
 *
 *     // Initialize the library
 *     create_library();
 * 
 *     // Add a sign with help information
 *     add_item("sign", library_help());
 *     add_cmd_item("sign", "read", library_help());
 * }
 *
 * void
 * init()
 * {
 *     ::init();
 *
 *     // Add the library commands
 *     init_library();
 * }
 *
 * N.B.  Directories given in configuration must exist for the library to
 *       function properly.  If a shelf is added, a directory with the
 *       same name as the shelf must exist under the the directory given
 *       to set_scroll_directory().
 */

#include <cmdparse.h>
#include <files.h>
#include <language.h>
#include <macros.h>
#include <mail.h>
#include <stdproperties.h>

#define SCROLL_TYPE  scroll_types[0]
#define PLURAL_SCROLL_TYPE \
    (sizeof(plural_scroll_types) ? \
    plural_scroll_types[0] : LANG_PWORD(scroll_types[0]))
  
#define SHELF_TYPE shelf_types[0]
#define PLURAL_SHELF_TYPE \
    (sizeof(plural_shelf_types) ? \
    plural_shelf_types[0] : LANG_PWORD(shelf_types[0]))

#define SCROLL_ID    (MASTER + "_library_scroll")
#define DEFAULT_TEXT_FILE_NAME "scroll"

#define TITLE_LINE   1
#define SUMMARY_LINE 2
#define AUTHOR_LINE  3
#define TEXT_LINE    4

#define MAX_TITLE_SIZE 20

static int borrow_required;

static string  scroll_dir  = "",
               appr_dir  = "",
               removal_dir = "",
               scroll_list = "",
               scroll_list_short = "",
               appr_list = "",
               appr_list_short = "",
               text_file_name = DEFAULT_TEXT_FILE_NAME,
              *scroll_types = ({ "scroll" }),
              *plural_scroll_types = ({ "scrolls" }),
              *shelf_types = ({ "shelf" }),
              *plural_shelf_types = ({ "shelves" }),
               default_shelf = "";

static mapping scroll_map;
static mapping appr_map;
static mapping scroll_shelves = ([]);

public void done_writing(string title, string summary, string input);
public int library_approve_access();
public string get_scroll_name(string dir);

/*
 * Configuration functions
 */

/*
 * Function name: set_scroll_directory
 * Description:   Set the directory where scrolls will be stored
 * Arguments:     string dir - the directory name with trailing slash
 */
public void
set_scroll_directory(string dir)
{
    scroll_dir = dir;
}

/*
 * Function name: set_scroll_approval_directory
 * Description:   Set the directory where unapproved scrolls will be stored.
 *                If this is not set, new scrolls will not need approval.
 * Arguments:     string dir - the directory name with trailing slash.
 */
public void
set_scroll_approval_directory(string dir)
{
    appr_dir = dir;
}

/*
 * Function name: set_scroll_removal_directory
 * Description:   Set the directory where removed (denied or discarded) scrolls
 *                are placed.  If this is not set, the files will simply be
 *                deleted.
 * Arguments:     string dir - the directory name with trailing slash.
 */
public void
set_scroll_removal_directory(string dir)
{
    removal_dir = dir;
}

/*
 * Function name: set_text_file_name
 * Description:   Set the prefix for the filenames of the scrolls.
 * Arguments:     string name - the filename prefix
 */
public void
set_text_file_name(string name)
{
    text_file_name = name;
}

/*
 * Function name: set_scroll_type
 * Description:   Set the names to be used to identify scrolls in the library.
 *                The argument to this function is passed directly to
 *                the set_name() function on each scroll instance.
 * Arguments:     mixed types - a string name or array of string names
 */
public void
set_scroll_type(mixed types)
{
    if (stringp(types))
    {
        scroll_types = ({ types });
    }
    else if (pointerp(types))
    {
        scroll_types = types;
    }
}

/*
 * Function name: set_plural_scroll_type
 * Description:   Set the names to be used to identify multiple scrolls.
 *                The argument to this function is passed directory to
 *                the set_pname function on each scroll instance.
 * Arguments:     mixed types - a string name or array of string names
 */
public void
set_plural_scroll_type(mixed types)
{
    if (stringp(types))
    {
        plural_scroll_types = ({ types });
    }
    else if (pointerp(types))
    {
        plural_scroll_types = types;
    }
}

/*
 * Function name: set_borrow_required
 * Description:   Indicate that that scrolls must be borrowed from
 *                the library in order to be read.
 * Arguments:     int i - if true, scrolls must be borrowed
 */
public void
set_borrow_required(int i)
{
        borrow_required = i;
}

/*
 * Function name: add_scroll_shelf
 * Description:   Add scroll shelves to the library.  This allows scrolls to
 *                be listed according to categories.
 * Arguments:     mixed shelf - a shelf name or array of shelf names.  These
 *                              are used both as names for the shelves when
 *                              players list shelves and also as subdirectories
 *                              (under the directory specified by
 *                              set_scroll_directory()) in which the scroll files
 *                              for each shelf will be stored.
 */
public void
add_scroll_shelf(mixed shelf)
{
    int i;

    if (!pointerp(shelf))
    {
        shelf = ({ shelf });
    }

    if (!strlen(default_shelf))
    {
        default_shelf = shelf[0];
    }

    for (i = 0; i < sizeof(shelf); i++)
    {
        scroll_shelves[shelf[i]] = 0;
    }
}

/*
 * Function name: set_default_shelf
 * Description:   Set the default shelf to be used when none is specified
 *                by the code or player.
 * Arguments:     string shelf - the name of the shelf to use (one of the
 *                               shelf names given in add_scroll_shelf())
 */
public void
set_default_shelf(string shelf)
{
    default_shelf = shelf;
}

/*
 * Function name: set_shelf_type
 * Description:   Set the names by which a shelf can be identified in case
 *                "shelf" is not appropriate.
 * Arguments:     mixed types - a string name or array of string names
 */
public void
set_shelf_type(mixed types)
{
    if (stringp(types))
    {
        shelf_types = ({ types });
    }
    else if (pointerp(types))
    {
        shelf_types = types;
    }
}

/*
 * Function name: set_plural_shelf_type
 * Description:   Set the names by which multiple shelves can be identified
 *                in case "shelves" is not appropriate.
 * Arguments:     mixed types - a string name or array of string names
 */
public void
set_plural_shelf_type(mixed types)
{
    if (stringp(types))
    {
        plural_shelf_types = ({ types });
    }
    else if (pointerp(types))
    {
        plural_shelf_types = types;
    }
}

/*
 * Hooks for altering default messages
 */

/*
 * Function name: library_no_scrolls_hook
 * Description:   Redefine this to alter the message given when commands
 *                fail because the library is empty.
 * Returns:       1/0
 */
public int
library_no_scrolls_hook()
{
    write("There are no scrolls available.\n");
    return 1;
}

/*
 * Function name: library_no_approval_scrolls_hook
 * Description:   Redefine this to alter the message given when commands
 *                fail because there are no scrolls needing approval
 * Returns:       1/0
 */
public int
library_no_approval_scrolls_hook()
{
    write("There are no scrolls needing approval.\n");
    return 1;
}

/*
 * Function name: library_list_short_hook
 * Description:   Redefine this to alter how the short listing of scrolls
 *                is presented
 */
public void
library_list_short_hook()
{
    write(scroll_list_short);
}

/*
 * Function name: library_list_long_hook
 * Description:   Redefine this to alter how the long listing of scrolls is
 *                presented
 */
public void
library_list_long_hook()
{
    write(scroll_list);
}

/*
 * Function name: library_list_approval_long_hook
 * Description:   Redefine this to alter how the long listing of scrolls
 *                needing approval is presented
 */
public void
library_list_approval_long_hook()
{
    write(appr_list);
}

/* 
 * Function name: library_list_approval_short_hook
 * Description:   Redefine this to alter how the short listing of scrolls
 *                needing approval is presented
 */
public void
library_list_approval_short_hook()
{
    write(appr_list_short);
}

/*
 * Function name: library_no_shelves_hook
 * Description:   Redefine this to alter the message given when a command
 *                fails because no shelves exist
 * Returns:       1/0
 */
public int
library_no_shelves_hook()
{
    notify_fail("There are no different " + SHELF_TYPE + ".\n");
    return 0;
}
   
/*
 * Function name: library_list_shelves_hook
 * Description:   Redefine this to alter how the listing of shelves is
 *                presented
 */
public void
library_list_shelves_hook()
{
    write(implode(map(m_indices(scroll_shelves), capitalize), "\n") + "\n");
}

/*
 * Function name: library_list_shelf_long_hook
 * Description:   Redefine this to alter how the long listing of scrolls
 *                on a given shelf is presented
 * Arguments:     string shelf - the name of the shelf
 */
public void
library_list_shelf_long_hook(string shelf)
{
    write(scroll_shelves[shelf][0]);
}

/*
 * Function name: library_list_shelf_short_hook
 * Description:   Redefine this to alter how the short listing of scrolls
 *                on a given shelf is presented
 * Arguments:     string shelf - the name of the shelf
 */
public void
library_list_shelf_short_hook(string shelf)
{
    write(scroll_shelves[shelf][1]);
}

/*
 * Function name: library_list_syntax_failure_hook
 * Description:   Redefine this to alter the message given when
 *                incorrect syntax is used for the "list" command
 * Arguments:     string str - the arguments to the "list" command
 * Returns:       1/0
 */
public int
library_list_syntax_failure_hook(string str)
{
    notify_fail("Usage: " + query_verb() + 
        (strlen(appr_dir) ? " [approval]" : "") + " [titles]\n");
    return 0;
}

/*
 * Function name: library_borrow_syntax_failure_hook
 * Description:   Redefine this to alter the message given when
 *                incorrect syntax is used for the "borrow" or
 *                "read" command
 * Arguments:     string str - the arguments to the "borrow" command
 * Returns:       1/0
 */
public int
library_borrow_syntax_failure_hook()
{
    notify_fail("Usage: " + query_verb() + " <title>\n");
    return 0;
}

/* 
 * Function name: library_borrow_unavailable_approval_scroll_hook
 * Description:   Redefine this to alter the message given when a
 *                user attempts to borrow or read a nonexistant scroll from
 *                scrolls needing approval
 * Arguments:     string title - the title of the scroll
 * Returns:       1/0
 */
public int
library_borrow_unavailable_approval_scroll_hook(string title)
{
    write("There is no such " + SCROLL_TYPE + " available for approval.\n");
    return 1;
}

/*
 * Function name: library_borrow_unavailable_scroll_hook
 * Description:   Redefine this to alter the message given when a
 *                user attempts to borrow or read a nonexistant scroll
 * Arguments:     string title - the title of the scroll
 * Returns:       1/0
 */
public int
library_borrow_unavailable_scroll_hook(string title)
{
    write("There is no such " + SCROLL_TYPE + " available.\n");
    return 1;
}

/*
 * Function name: library_borrow_hook
 * Description:   Redefine this to alter the message given when a
 *                user borrows or reads a scroll
 * Arguments:     object scroll  - the scroll borrowed
 *                string title - the title of the scroll
 */
public void
library_borrow_hook(object scroll, string title)
{
    write("You borrow " + LANG_ADDART(scroll->short()) + ".\n");
    say(QCTNAME(this_player()) + " borrows " + LANG_ADDART(scroll->short()) +
        ".\n");
}

/*
 * Function name: library_return_syntax_failure_hook
 * Description:   Redefine this to alter the message given when incorrect
 *                syntax is used for the "return" command
 * Arguments:     string str - the arguments to the "return" command
 * Returns:       1/0
 */
public int
library_return_syntax_failure_hook(string str)
{
    notify_fail(capitalize(query_verb()) + " what?\n");
    return 0;
}

/*
 * Function name: library_return_hook
 * Description:   Redefine this to alter the message given when a
 *                user returns a scroll
 * Arguments:     object scroll - the scroll being returned
 */
public void
library_return_hook(object scroll)
{
    write("You return the " + scroll->short() + ".\n");
    say(QCTNAME(this_player()) + " returns " + LANG_ADDART(scroll->short()) + 
        ".\n");
}

/*
 * Function name: library_write_abort_hook
 * Description:   Redefine this to alter the message given when the
 *                user aborts writing a scroll
 */
public void
library_write_abort_hook()
{
    write("You stop writing.\n");
}

/*
 * Function name: library_write_prompt_title_input_hook
 * Description:   Redefine this to alter the message given to prompt
 *                the user to input a scroll title
 */
public void
library_write_prompt_title_input_hook()
{
    write("What is the name of the scroll? (fewer than " + MAX_TITLE_SIZE +
        " characters).  (~q to quit)\n> ");
}
       
/*
 * Function name: library_write_prompt_summary_input_hook
 * Description:   Redefine this to alter the message given to prompt
 *                the user to input a scroll summary
 */
public void
library_write_prompt_summary_input_hook()
{
    write("\nEnter a short summary of the scroll. (~q to quit)\n> ");
}

/*
 * Function name: library_write_failed_hook
 * Description:   Redefine this to alter the message given when a scroll
 *                cannot be saved for some reason.
 */
public void
library_write_failed_hook()
{
    write("Failed to write scroll.\n");
}

/*
 * Function name: library_approve_syntax_failure_hook
 * Description:   Redefine this to alter the message given when incorrect
 *                syntax is used for the "approve" command
 * Arguments:     string str - the arguments to the "approve" command
 * Returns:       1/0
 */
public int
library_approve_syntax_failure_hook(string str)
{
    notify_fail("Usage: " + query_verb() + " <title>\n");
    return 0;
}

/*
 * Function name: library_approve_unavailable_scroll_hook
 * Description:   Redefine this to alter the message given when a
 *                user attempts to approve a nonexistant scroll
 * Arguments:     string title - the scroll's title
 * Returns:       1/0
 */
public int
library_approve_unavailable_scroll_hook(string title)
{
    write("There is no scroll by that title that needs approval.\n");
    return 1;
}

/*
 * Function name: library_approve_hook
 * Description:   Redefine this to alter the message given when a
 *                user approves a scroll
 * Arguments:     string title - the scroll's title
 */
public void
library_approve_hook(string title)
{
    write("Ok.\n");
}

/*
 * Function name: library_classify_syntax_failure_hook
 * Description:   Redefine this to alter the message given when incorrect
 *                syntax is used for the "classify" command
 * Arguments:     string str - the arguments to the "classify" command
 * Returns:       1/0
 */
public int
library_classify_syntax_failure_hook(string str)
{
    notify_fail("Usage: " + query_verb() + " <title>.\n");
    return 0;
}

/*
 * Function name: library_classify_unavailable_scroll_hook
 * Description:   Redefine this to alter the message given when a
 *                user attempts to classify a nonexistant scroll
 * Arguments:     string title - the scroll's title
 * Returns:       1/0
 */
public int
library_classify_unavailable_scroll_hook(string title)
{
    notify_fail("There is no such " + SCROLL_TYPE + " to classify.\n");
    return 0;
}

/*
 * Function name: library_classify_unavailable_shelf_hook
 * Description:   Redefine this to alter the message given when a
 *                user attempts to classify a scroll under a nonexistant
 *                shelf
 * Arguments:     string shelf - the shelf name
 */ 
public void
library_classify_unavailable_shelf_hook(string shelf)
{
    write("There is no such " + SHELF_TYPE + ".\n");
}

/* 
 * Function name: library_classify_hook
 * Description:   Redefine this to alter the message given when a
 *                user classifies a scroll
 * Arguments:     string title - the scroll's title
 *                string shelf - the shelf
 */
public void
library_classify_hook(string title, string shelf)
{
    write("Ok.\n");
}

/*
 * Function name: library_classify_prompt_shelf_input_hook
 * Description:   Redefine this to alter the message given to prompt
 *                the user to input a shelf name
 * Arguments:     string title - the title of the scroll being classified
 */
public void
library_classify_prompt_shelf_input_hook(string title)
{
    write("Which " + SHELF_TYPE + " do you wish to place " + title +
        " in?\n> ");
}

/*
 * Function name: library_deny_syntax_failure_hook
 * Description:   Redefine this to alter the message given when incorrect
 *                syntax is used for the "deny" command
 * Arguments:     string str - the arguments to the "deny" command
 * Returns:       1/0
 */
public int
library_deny_syntax_failure_hook(string str)
{
    notify_fail("Usage: " + query_verb() + " <title>\n");
    return 0;
}

/*
 * Function name: library_deny_unavailable_scroll_hook
 * Description:   Redefine this to alter the message given when a
 *                user attempts to deny a nonexistant scroll
 * Arguments:     string title - the scroll's title
 * Returns:       1/0
 */
public int
library_deny_unavailable_scroll_hook(string title)
{
    write("There is no scroll by that title that needs approval.\n");
    return 1;
}

/*
 * Function name: library_deny_hook
 * Description:   Redefine this to alter the message given when a
 *                user denies a scroll 
 * Arguments:     string title - the scroll's file
 */
public void
library_deny_hook(string title)
{
    write("Ok.\n");
}

/*
 * Function name: library_discard_syntax_failure_hook
 * Description:   Redefine this to alter the message given when incorrect
 *                syntax is used for the "discard" command
 * Arguments:     string str - the arguments to the "discard" command
 * Returns:       1/0
 */
public int
library_discard_syntax_failure_hook(string str)
{
    notify_fail("Usage: " + query_verb() + " <title>\n");
    return 0;
}

/*
 * Function name: library_discard_unavailable_scroll_hook
 * Description:   Redefine this to alter the message given when a
 *                user attempts to discard a nonexistant scroll
 * Arguments:     string title - the scroll's title
 * Returns:       1/0
 */
public int
library_discard_unavailable_scroll_hook(string title)
{
    write("There is no " + SCROLL_TYPE + " by that title.\n");
    return 1;
}

/*
 * Function name: library_discard_hook
 * Description:   Redefine this to alter the message given when a
 *                user discards a scroll
 * Arguments:     string title - the scroll discarded
 */
public void
library_discard_hook(string title)
{
    write("Ok.\n");
}

/*
 * Library routines
 */

/*
 * Function name: library_remove_scroll
 * Description:   Remove a scroll from the library.  If a removal directory
 *                is specified, the file will be moved there; otherewise,
 *                it is deleted.
 * Arguments:     string filename - the filename of the scroll file
 */
public void
library_remove_scroll(string filename)
{
    setuid();
    seteuid(getuid());

    if (strlen(removal_dir))
    {
        rename(filename, get_scroll_name(removal_dir));
    }
    else
    {
        rm(filename);
    }
}

/*
 * Function name: library_move_scroll
 * Description:   Move a scroll file to another directory.
 * Arguments:     string scroll_file - the filename of the scroll file
 *                string new_dir   - the destination directory
 * Returns:       1/0 - move successful/unsuccessful
 */
public int
library_move_scroll(string scroll_file, string new_dir)
{
    setuid();
    seteuid(getuid());

    return rename(scroll_file, get_scroll_name(new_dir));
}

/*
 * Function name: query_scroll_title
 * Description:   Given a scroll file, return the scroll's title
 * Arguments:     string file - The filename for the desired scroll
 * Returns:       The scroll's title
 */
public string
query_scroll_title(string file)
{
    string str = read_file(file, TITLE_LINE, 1);

    /* remove trailing "\n" */
    if (strlen(str) && (str[-1..] == "\n"))
    {
        str = str[..-2];
    }

    /* remove extra whitespace and return */
    return implode(explode(str, " ") - ({ "" }), " ");
}

/*
 * Function name: query_scroll_author
 * Description:   Given a scroll file, return the scroll's author
 * Arguments:     string file - the filename for the desired scroll
 * Returns:       The scroll's author
 */
public string
query_scroll_author(string file)
{
    string str = read_file(file, AUTHOR_LINE, 1);

    /* remove trailing "\n" */
    if (strlen(str) && (str[-1..] == "\n"))
    {
        str = str[..-2];
    }

    /* remove extra whitespace and return */
    return implode(explode(str, " ") - ({ "" }), " ");
}

/*
 * Function name: query_scroll_summary
 * Description:   Given a scroll file, return the scroll's summary
 * Arguments:     string file - the filename for the desired scroll
 * Returns:       The scroll's author
 */
public string
query_scroll_summary(string file)
{
    string str = read_file(file, SUMMARY_LINE, 1);

    /* remove trailing "\n" */
    if (strlen(str) && (str[-1..] == "\n"))
    {
        str = str[..-2];
    }

    /* remove extra whitespace and return */
    return implode(explode(str, " ") - ({ "" }), " ");
}

/*
 * Function name: query_scroll_text
 * Description:   Given a scroll file, return the scroll's text
 * Arguments:     string file - the filename for the desired scroll
 * Returns:       the scroll's text
 */
public string
query_scroll_text(string file)
{
    return read_file(file, TEXT_LINE);
}

/*
 * Function name: get_scrolls
 * Description:   Get the full pathnames of all scroll files in a given directory
 * Arguments:     string dir - the directory to search
 * Returns:       An array of pathname strings
 */
public string *
get_scrolls(string dir)
{
    string *scrolls;

    setuid();
    seteuid(getuid());

    scrolls = map(get_dir(dir), &operator(+)(dir));

    /* Any non-empty file is counted as a scroll */
    scrolls = filter(scrolls, &operator(>)(,0) @ file_size);

    return scrolls;
}
   
/*
 * Function name: get_scroll_info
 * Description:   For each of a given array of scroll files, add an element
 *                to a given mapping.  The elements map scroll title names
 *                to scroll filenames.
 * Arguments:     string *scrolls - An array of scroll files.
 *                mapping m     - A mapping in which to store the above
 *                                mentioned information.
 */ 
public void
get_scroll_info(string *scrolls, mapping m)
{
    int i;

    for (i = 0; i < sizeof(scrolls); i++)
    {
        m[lower_case(query_scroll_title(scrolls[i]))] = scrolls[i];
    }
}

/*
 * Function name: format_scroll_list
 * Description:   Given an array of scroll files, return a nicely formatted
 *                string which lists the given scrolls.
 * Arguments:     string *scrolls - an array of scroll filename strings
 * Returns:       A string description of the given scrolls
 */
public string
format_scroll_list(string *scrolls)
{
    int i;
    string str = "";

    for (i = 0; i < sizeof(scrolls); i++)
    {
        str += sprintf("%-" + MAX_TITLE_SIZE + "s %-13s %-=40s\n",
            query_scroll_title(scrolls[i]), query_scroll_author(scrolls[i]),
            query_scroll_summary(scrolls[i]));
    }

    return str;
}

/*
 * Function name: format_scroll_list_short
 * Description:   Return a short version of the scroll listing (See documentation
 *                for format_scroll_list())
 * Arguments:     string *scrolls - an array of scroll filename strings
 * Returns:       A string description of the given scrolls
 */
public string
format_scroll_list_short(string *scrolls)
{
    string *titles = map(scrolls, query_scroll_title);
    return sprintf("%-#70.2s\n", implode(titles, "\n"));
}

/*
 * Function name: update_scrolls
 * Description:   Update the in-memory scroll information when something
 *                has changed.
 */
public void
update_scrolls()
{
    string *scrolls, *shelves, shelf_list, shelf_list_short;
    int i;

    setuid();
    seteuid(getuid());

    scroll_map = ([]);
    appr_map = ([]);
    scroll_list = "";
    scroll_list_short = "";

    if (strlen(scroll_dir))
    {
        if (m_sizeof(scroll_shelves))
        {
            shelves = m_indices(scroll_shelves);

            for (i = 0; i < sizeof(shelves); i++)
            {
                scrolls = get_scrolls(scroll_dir + shelves[i] + "/");
                shelf_list = format_scroll_list(scrolls);
                scroll_list += shelf_list;
                shelf_list_short = format_scroll_list_short(scrolls);
                scroll_list_short += shelf_list_short;
                scroll_shelves[shelves[i]] = ({ shelf_list, shelf_list_short });
                get_scroll_info(scrolls, scroll_map);
            }
        }
        else
        {
            scrolls = get_scrolls(scroll_dir);
            scroll_list = format_scroll_list(scrolls);
            scroll_list_short = format_scroll_list_short(scrolls);
            get_scroll_info(scrolls, scroll_map);
        }
    }

    if (strlen(appr_dir))
    {
        scrolls = get_scrolls(appr_dir);
        appr_list = format_scroll_list(scrolls);
        appr_list_short = format_scroll_list_short(scrolls);
        get_scroll_info(scrolls, appr_map);
    }
}

/*
 * Function name: create_library
 * Description:   Initialize the library.  This should be called when the
 *                library object is created, AFTER it has been configured.
 */
public void
create_library()
{
    update_scrolls();
}

/*
 * Function name: library_configure_scroll
 * Description:   Configure a library scroll.  Redefine this to customize
 *                your library scrolls.
 * Arguments:     object scroll           - the scroll object
 *                string text_filename - the file name of the scroll file to use
 *                string scroll_name     - the name of the scroll
 */
public void
library_configure_scroll(object scroll, string text_filename, string scroll_name)
{
    scroll->set_long("A " + SCROLL_TYPE + " entitled \"" + scroll_name + "\".\n");
    scroll->set_name(scroll_types);
    
    if (sizeof(plural_scroll_types))
    {
        scroll->set_pname(plural_scroll_types);
    }

    scroll->add_name(scroll_name);
    scroll->add_prop(OBJ_I_NO_DROP, 1);
    scroll->set_file(text_filename);
}

/*
 * Function name: library_make_scroll
 * Description:   Create a scroll object for use in the library.  Override this
 *                if you do not wish to use the standard scroll object for
 *                scrolls.
 * Arguments:     string scroll_name - the name of the scroll we are creating
 * Returns:       A scroll object
*/
public object
library_make_scroll(string scroll_name)
{
    setuid();
    seteuid(getuid());

    return clone_object(SCROLL_OBJECT);
}

/*
 * Function name: library_give_scroll
 * Description:   Clone and configure a scroll
 * Arguments:     string text_filename - The filename of the scroll file to use
 *                string scroll_name     - The title of the scroll
 * Returns:       A configured scroll
 */
public object
library_give_scroll(string text_filename, string scroll_name)
{
    object scroll;

    scroll = library_make_scroll(scroll_name);
    library_configure_scroll(scroll, text_filename, scroll_name);

    /* Add a name unique to this library */
    scroll->add_name(SCROLL_ID);

    scroll->move(this_player(), 1);
    return scroll;
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
    if (!this_player()->query_wiz_level())
    {
        write("You don't have permission to do that.\n");
        return 0;
    }

    return 1;
}

/*
 * Function name: library_borrow_access
 * Description:   Redefine this function to limit permission to borrow scrolls
 * Returns:       1 - this_player() is permitted to borrow a scroll
 *                0 - this_player() is not permitted to borrow a scroll
 */
public int
library_borrow_access()
{
    return 1;
}

/*
 * Function name: library_borrow
 * Description:   Try to borrow a scroll from the library.
 * Arguments:     string str - any arguments to the command
 * Returns:       1/0 - Command success/failure
 */
public int
library_borrow(string str)
{
    string scroll_file;
    object scroll;

    /* Check for borrow permission */
    if (!library_borrow_access())
    {
        return 1;
    }

    if (!strlen(str))
    { 
        return library_borrow_syntax_failure_hook();
    }

    str = lower_case(str);

    if (!strlen((scroll_file = scroll_map[str])))
    {
        if (sscanf(str, "approval %s", str))
        {
            if (!library_approve_access() || !library_admin_access())
            {
                return 1;
            }
 
            if (!strlen(scroll_file = appr_map[str]))
            {
                return library_borrow_unavailable_approval_scroll_hook(str);
            }
        }
        else
        {                    
            return library_borrow_unavailable_scroll_hook(str);         
        }
    }

    scroll = library_give_scroll(scroll_file, str);

    library_borrow_hook(scroll, str);
    return 1;
}

/*
 * Function name: library_read_scroll
 * Description:   Display the text of a scroll to the reader
 * Arguments:     string text_filename - The filename of the scroll file to use
 *                string scroll_name     - The title of the scroll
 *                int mread            - true if more should be used
 * Returns:       A configured scroll
 */
public void
library_read_scroll(string text_filename, string scroll_name, int mread)
{
    setuid();
    seteuid(getuid());

    if (mread || (file_size(text_filename) > 4000))
    {
        this_player()->more(read_file(text_filename));
    }
    else
    {
        write(read_file(text_filename));
    }
}

/*
 * Function name: library_read
 * Description:   Try to read a scroll from the library.
 * Arguments:     string str - any arguments to the command
 * Returns:       1/0 - Command success/failure
 */
public int
library_read(string str)
{
    string scroll_file;

    /* Check for borrow permission */
    if (!library_borrow_access())
    {
        return 1;
    }

    if (!strlen(str))
    { 
        return library_borrow_syntax_failure_hook();
    }

    str = lower_case(str);

    if (!strlen((scroll_file = scroll_map[str])))
    {
        if (sscanf(str, "approval %s", str))
        {
            if (!library_approve_access() || !library_admin_access())
            {
                return 1;
            }

            if (!strlen(scroll_file = appr_map[str]))
            {
                return library_borrow_unavailable_approval_scroll_hook(str);
            }
        }
        else
        {                    
            return library_borrow_unavailable_scroll_hook(str);         
        }
    }

    library_read_scroll(scroll_file, str, query_verb() == "mread");

    return 1;
}

/*
 * Function name: library_return_access
 * Description:   Redefine this to limit permission to return scrolls
 * Returns:       1 - this_player() is permitted to return a scroll
 *                0 - this_player() is not permitted to return a scroll
 */
public int
library_return_access()
{
    return 1;
}

/*
 * Function name: library_return
 * Description:   Return a borrowed scroll
 * Arguments:     string str - any arguments to the command
 * Returns:       1/0 - Command success/failure
 */
public int
library_return(string str)
{
    if (!library_return_access())
    {
        return 1;
    }

    if (!sizeof(CMDPARSE_ONE_ITEM(str, "return_it", "return_access")))
    {
        return library_return_syntax_failure_hook(str);
    }

    return 1;
}

/*
 * Function name: return_access
 * Description:   Check to see if the given object is a scroll that can be
 *                returned to this library.
 * Arguments:     object ob - The object to check
 * Returns:       1 - the object can be returned to this library
 *                0 - the object cannot be returned to this library
 */
public int
return_access(object ob)
{
    return ((environment(ob) == this_player()) && ob->id(SCROLL_ID));
}

/*
 * Function name: return_it
 * Description:   Return a library scroll to the library
 * Arguments:     object ob - the scroll to return
 * Returns:       1 - the scroll was returned
 *                0 - the scroll was not returned
 */
public int
return_it(object ob)
{
    library_return_hook(ob);
    ob->remove_object();
    return 1;
}

/*
 * Function name: library_list_access
 * Description:   Redefine this to limit permission to list scrolls
 * Returns:       1 - this_player() is permitted to list scrolls
 *                0 - this_player() is not permitted to list scrolls
 */
public int
library_list_access()
{
    return 1;
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
    string shelf;

    if (!library_list_access())
    {
        return 1;
    }

    /* short listing of all scrolls */
    if (str == "titles")
    {
        if (!m_sizeof(scroll_map))
        {
            return library_no_scrolls_hook();
        }

        library_list_short_hook();
        return 1;
    }

    /* listing of shelf names */
    if (member_array(str, plural_shelf_types) >= 0)
    {
        if (!m_sizeof(scroll_shelves))
        {
            return library_no_shelves_hook();
        }

        library_list_shelves_hook();
        return 1;
    }

    /* long listing of a particular shelf */
    if (scroll_shelves[str])
    {
        library_list_shelf_long_hook(str);
        return 1;
    }

    if (strlen(str) && sscanf(str, "%s titles", shelf) && scroll_shelves[shelf])
    {
        library_list_shelf_short_hook(shelf);
        return 1;
    }

    /* long listing of approval scrolls */
    if (strlen(appr_dir) && (str == "approval"))
    {
        if (!library_approve_access() || !library_admin_access())
        {
            return 1;
        }

        if (!m_sizeof(appr_map))
        {
            return library_no_approval_scrolls_hook();
        }

        library_list_approval_long_hook();
        return 1;
    }

    /* short listing of approval scrolls */
    if (strlen(appr_dir) && (str == "approval titles"))
    {
        if (!library_approve_access() || !library_admin_access())
        {
            return 1;
        }

        if (!m_sizeof(appr_map))
        {
            return library_no_approval_scrolls_hook();
        }

        library_list_approval_short_hook();
        return 1;
    }

    /* at this point, if there's an argument, it's a syntax error */
    if (strlen(str))
    {
        return library_list_syntax_failure_hook(str);
    }

    /* long listing of all scrolls */

    if (!m_sizeof(scroll_map))
    {
        return library_no_scrolls_hook();
    }

    library_list_long_hook();
    return 1;
}

/*
 * Function name: library_validate_summary
 * Description:   Determine if a string is a valid scroll summary
 * Arguments:     string summary - the summary string
 * Returns:       1/0 - valid/invalid
 */
public int
library_validate_summary(string summary)
{
    if (!wildmatch("*[a-zA-Z0-9]*", summary))
    {
        write("\nThe summary must contain an alphanumeric character.\n" +
            "Please enter a valid summary. (~q to quit)\n> ");
        return 0;
    }

    return 1;
}

/*
 * Function name: library_write_get_summary
 * Description:   Catch input from the user to be used as the new
 *                scroll's summary
 * Arguments:     object who   - the user
 *                string title - the new scroll's title
 *                string input - the user's input
 * Returns:       1/0 - summary set/not set
 */
public int
library_write_get_summary(object who, string title, string input)
{
    if (input == "~q")
    {
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
 * Function name: get_scroll_name
 * Description:   Get a filename for a new scroll in a specified directory
 * Arguments:     string dir - a directory
 * Returns:       the filename
 */
public string
get_scroll_name(string dir)
{
    string *files;
    int i, tmp, last = -1;

    setuid();
    seteuid(getuid());

    files = get_dir(dir);
    for (i = sizeof(files) - 1; i >= 0; i--)
    {
        if (!sscanf(files[i], text_file_name + "%d", tmp))
        {
           continue;
        }

        if (tmp > last)
        {
            last = tmp;
        }
    }

    return dir + text_file_name + (last + 1);
}

/*
 * Function name: library_hook_get_approval_names
 * Description  : This routine can be redefined in the library code to provide
 *                the names of the players who are authorized to approve scrolls
 *                before they are added to the library. If this is the case,
 *                those players will receive a mail informing them of the fact
 *                that a new scroll has been submitted.
 * Returns      : string * - the list of names (in lower case).
 */
public mixed
library_hook_get_approval_names()
{
    return ({ });
}

/* 
 * Function name: add_scroll
 * Description:   Add a new scroll to the library
 * Arguments:     string title   - the scroll's title
 *                string summary - the scroll's summary
 *                string author  - the scroll's author
 *                string text    - the scroll's text
 *                int approval   - true if the scroll needs approval
 * Returns:       1/0 - scroll added/not added
 */
public int
add_scroll(string title, string summary, string author,
         string text, int approval)
{
    string dir = (approval ? appr_dir : scroll_dir);
    string *names;

    if (!approval && strlen(default_shelf))
    {
        dir += default_shelf + "/";
    }

    setuid();
    seteuid(getuid());

    /* Guild approval agents may be informed of the new scroll. */
    if (approval && sizeof(names = library_hook_get_approval_names()))
    {
        CREATE_MAIL("New scroll " + author, "Librarian",
            implode(names, ","), "",
            "Title: " + title + "\nSummary: " + summary + "\n");
    }

    if (!write_file(get_scroll_name(dir),
        sprintf("%|75s\n%|75s\n%|75s\n", title, summary, author) + text))
    {
         return 0;
    }

    update_scrolls();
    return 1;
}

/*
 * Function name: done_writing
 * Description:   Catch input from the user to be used as the new
 *                scroll's text and add the new scroll to the library
 * Arguments:     string title   - the scroll's title
 *                string summary - the scroll's summary
 *                string input   - the scroll's text
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

    if (!add_scroll(title, summary, "by " + this_player()->query_name(), 
        input, !!strlen(appr_dir)))
    {
        library_write_failed_hook();
    }
    else
    {
        write("Ok.\n");
    }

    return 1;
}

/*
 * Function name: library_validate_title
 * Description:   Determine if a string is a valid scroll title
 * Arguments:     string title - the title string
 * Returns:       1/0 - valid/invalid
 */
public int
library_validate_title(string title)
{
    if (strlen(title) > MAX_TITLE_SIZE)
    {
        write("\nThe title must be fewer than " + MAX_TITLE_SIZE +
            " characters long.\nPlease enter a valid title. (~q to quit)\n> ");
        return 0;
    }

    if (!wildmatch("*[a-zA-Z0-9]*", title))
    {
        write("\nThe title must contain an alphanumeric character.\n" +
              "Please enter a valid title. (~q to quit)\n> ");
        return 0;
    }

    update_scrolls();
  
    if (scroll_map[title])
    {
        write("\nThere is already a " + SCROLL_TYPE + " with that title.\n" +
              "Please enter a valid title. (~q to quit)\n> ");
        return 0;
    }

    return 1;
}

/*
 * Function name: library_write_get_title
 * Description:   Catch user input to be used as the new scroll's title
 * Arguments:     object who   - the user
 *                string input - the title
 * Returns:       1/0 - title set/not set
 */
public int
library_write_get_title(object who, string input)
{
    if (input == "~q")
    {
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
 * Function name: library_write_access
 * Description:   Redefine this function to limit permission to write scrolls
 * Returns:       1 - this_player() is permitted to write a scroll
 *                0 - this_player() is not permitted to write a scroll
 */
public int
library_write_access()
{
    write("You don't have permission to do that.\n");
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

    library_write_prompt_title_input_hook();

    input_to(&library_write_get_title(this_player()));
    return 1;
}

/*
 * Function name: library_approve_access
 * Description:   Redefine this function to limit permission to approve scrolls
 * Returns:       1 - this_player() is permitted to approve a scroll
 *                0 - this_player() is not permitted to approve a scroll
 */
public int
library_approve_access()
{
    return 1;
}

/*
 * Function name: library_approve
 * Description:   The "approve" command
 * Arguments:     string str - arguments to the "approve" command
 * Returns:       1/0 - syntax success/failure
 */
public int
library_approve(string str)
{
    string scroll_file;

    if (!library_approve_access() || !library_admin_access())
    {
        return 1;
    }

    if (!strlen(str))
    {
        return library_approve_syntax_failure_hook(str);
    }

    str = lower_case(str);

    if (!strlen(scroll_file = appr_map[str]))
    {
        return library_approve_unavailable_scroll_hook(str);
    }

    add_scroll(str, query_scroll_summary(scroll_file),
        query_scroll_author(scroll_file), query_scroll_text(scroll_file), 0);

    setuid();
    seteuid(getuid());

    rm(scroll_file);
    
    update_scrolls();

    library_approve_hook(str);
    return 1;
}

/*
 * Function name: library_classify_access
 * Description:   Redefine this function to limit permission to classify scrolls
 * Returns:       1 - this_player() is permitted to classify a scroll
 *                0 - this_player() is not permitted to classify a scroll
 */
public int
library_classify_access()
{
    return 1;
}

/*
 * Function name: library_classify_get_shelf
 * Description:   Catch input from the user and classify a scroll under
 *                the indicated shelf
 * Arguments:     object who   - the user
 *                string title - the scroll's title
 *                string input - the shelf name
 * Returns:       1/0 - scroll classified/not classified
 */
public int
library_classify_get_shelf(object who, string title, string input)
{
    string scroll_file; 

    set_this_player(who);

    if (!scroll_shelves[input])
    {
        library_classify_unavailable_shelf_hook(input);
        return 0;
    }

    if (!strlen(scroll_file = scroll_map[title])) 
    {
        library_classify_unavailable_scroll_hook(title);
        return 0;
    }

    library_move_scroll(scroll_file, scroll_dir + input + "/");

    update_scrolls();

    library_classify_hook(title, input);
    return 1;
}
    
/*
 * Function name: library_classify
 * Description:   The "classify" command
 * Arguments:     string str - arguments to the "classify" command
 * Returns:       1/0 - syntax success/failure
 */
public int
library_classify(string str)
{
    if (!library_classify_access() || !library_admin_access())
    {
        return 1;
    }

    if (!strlen(str))
    {
        return library_classify_syntax_failure_hook(str);
    }

    if (!strlen(scroll_map[str])) 
    {
        return library_classify_unavailable_scroll_hook(str);
    }

    library_classify_prompt_shelf_input_hook(str);
    input_to(&library_classify_get_shelf(this_player(), str));
    return 1;
}

/*
 * Function name: library_deny_access
 * Description:   Redefine this function to limit permission to deny scrolls
 * Returns:       1 - this_player() is permitted to deny a scroll
 *                0 - this_player() is not permitted to deny a scroll
 */
public int
library_deny_access()
{
    return 1;
}

/*
 * Function name: library_deny
 * Description:   The "deny" command
 * Arguments:     string str - arguments to the "deny" command
 * Returns:       1/0 - syntax success/failure
 */
public int
library_deny(string str)
{
    string scroll_file;

    if (!library_deny_access() || !library_admin_access())
    {
        return 1;
    }

    if (!strlen(str))
    {
        return library_deny_syntax_failure_hook(str);
    }

    str = lower_case(str);

    if (!strlen(scroll_file = appr_map[str]))
    {
        return library_deny_unavailable_scroll_hook(str);
    }

    library_remove_scroll(scroll_file);  

    update_scrolls();

    library_deny_hook(str);
    return 1;
}
 
/*
 * Function name: library_discard_access
 * Description:   Redefine this function to limit permission to discard scrolls
 * Returns:       1 - this_player() is permitted to discard a scroll
 *                0 - this_player() is not permitted to discard a scroll
 */
public int
library_discard_access()
{
    return 1;
}

/*
 * Function name: library_discard
 * Description:   The "discard" command
 * Arguments:     string str - arguments to the "discard" command
 * Returns:       1/0 - syntax success/failure
 */
public int
library_discard(string str)
{
    string scroll_file;

    if (!library_discard_access() || !library_admin_access())
    {
        return 1;
    }

    if (!strlen(str))
    {
        return library_discard_syntax_failure_hook(str);
    }

    str = lower_case(str);

    if (!strlen(scroll_file = scroll_map[str]))
    {
        return library_discard_unavailable_scroll_hook(str);
    }

    library_remove_scroll(scroll_file);

    update_scrolls();

    library_discard_hook(str);
    return 1;
}

/*
 * Function name: init_library
 * Description:   Add library commands
 */
public void
init_library()
{
    if (borrow_required)
    {
        add_action(library_borrow, "borrow");
        add_action(library_return, "return");
    }
    else
    {
        add_action(library_read, "read");
        add_action(library_read, "mread");
    }

    add_action(library_list,   "list");
    
    add_action(library_write,  "write");

    add_action(library_approve,  "approve");
    add_action(library_classify, "classify");
    add_action(library_deny,     "deny");
    add_action(library_discard,  "discard");
}

/*
 * Function name: library_exit_block
 * Description:   Returns true if this_player() is in possession of
 *                a scroll from this library.  It can be used as a block
 *                function for library exits.
 * Returns:       1/0 - library scroll possessed/not possessed
 */
public int
library_exit_block()
{
    return !!sizeof(filter(deep_inventory(this_player()), &->id(SCROLL_ID)));
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
        "Library commands available:\n" +
        help_cmd("List " + 
            (m_sizeof(scroll_shelves) ? "[<" + SHELF_TYPE + ">] " : "") +
            "[titles]", "List scrolls in the library.");

    if (m_sizeof(scroll_shelves))
    {
        str += help_cmd("List " + PLURAL_SHELF_TYPE, 
                        "List " + PLURAL_SHELF_TYPE + " in the library.");
    }

    if (borrow_required)
    {
        str += 
            help_cmd("Borrow <title>",
                     "Borrow a scroll for reading.") +
            help_cmd("Return <scroll>",
                     "Return a scroll to the library.");
    }
    else
    {
        str += help_cmd("Read <title>", "Read a scroll in the library.") +
               help_cmd("Mread <title>", "Mread a scroll in the library.");
    }

    str += help_cmd("Write", "Write a scroll and submit it to the library.");

    str += "\nAdministrator commands available:\n";

    if (strlen(appr_dir))
    {
        str += 
            help_cmd("Approve <title>",
                     "Approve a scroll for inclusion in the library.");

        if (borrow_required)
        {
            str += help_cmd("Borrow approval <title>",
                "Administrators may borrow scrolls which have not been " +
                 "approved by using the \"approval\" option.");
        }
        else
        {
            str += help_cmd("(m)read approval <title>",
                "Administrators may read scrolls which have not been " +
                "approved by using the \"approval\" option.");
        }

        str +=
            help_cmd("Deny <title>",
                 "Deny a scroll from inclusion in the library.") +
            help_cmd("List approval [titles]",
                 "Administrators may list scrolls that need approval with " +
                 "the \"approval\" option.");
    }

    str += help_cmd("Discard <title>", "Remove a scroll from the library.");

    if (m_sizeof(scroll_shelves))
    {
        str += help_cmd("Classify <title>",
                        "Assign a scroll to a " + SHELF_TYPE + ".");
    }

    return str + "\n";
}
