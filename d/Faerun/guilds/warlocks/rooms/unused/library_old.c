/* /d/Faerun/guilds/warlocks/rooms/library.c
 *
 * Room in the guildhall. Library. Based on the MM library.
 *
 * Nerull, 2017
 *
 */
#include "/d/Faerun/defs.h"
#include "defs.h";
#include "../guild.h";
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <composite.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <tasks.h>
#include <macros.h>

inherit WARLOCK_STD_ROOM;
inherit "/lib/guild_library";


/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_warlock_room()
{
    seteuid(getuid());
    
    add_prop(ROOM_I_INSIDE, 1);

    set_short("A dark library");
    set_long("This is the dark library of the Warlock and Witches. It is here they learn the dark arts and mysteries of magic. The room is unusually cold. Rows of bookcases fill the room. Scrolls of all sizes fill the bookcases. Chairs and tables are scattered around the room, where visitors can sit and read, or pen new scrolls. A plaque hangs on a wall, and a large arch leads south.\n");


    add_exit(WARLOCK_ROOMS_DIR + "hall01", "south", 
    "@@prevent_leave_with_books@@",0);
    

    // Allow us to read the help
    add_item(({ "plaque", "instructions", }), library_help);
    add_cmd_item(({ "plaque", "instructions", }), "read", library_help);

    // Start up the library
    set_library_save_path(WARLOCK_GUILD_DIR + "library/");
    set_library_save_file(WARLOCK_GUILD_DIR + "warlock_library");
    set_library_allow_new_books(1);
    set_library_log_file("warlocks_library_log");
    set_library_book_type("scroll");

    add_library_access_level("warlock", "Warlocks of Hastur");

    set_library_book_object("/d/Faerun/guilds/warlocks/obj/warlock_library_scroll");

    set_library_librarian_level("warlock");

    create_library();

    reset_room();
}


void
reset_room()
{
}


/*
* Function name: init
* Description  : Add commands to the player
*/
void init()
{
    ::init();
    
    init_library();
}


/*
* Function name: library_hook_stop_leave
* Description  : Called when a player is stopped while carrying books,
*              : redefine it to give your own message.
* Arguments    : player - the player that's trying to leave
*              : books - an array with the books that have not 
*                been returned
*/
void library_hook_stop_leave(object player, object *books)
{
    player->catch_msg("You can't leave the library until " +
        "you return " + COMPOSITE_DEAD(books) + ".\n");
}


/*
* Function name: leave_inv
* Description  : Someone or something leaving our inventory
* Arguments    : ob - the object leaving
*              : to - where are we leaving to
*/
void leave_inv(object ob, object to)
{
    // Make the library do their things on leave
    library_leave_inv(ob, to);
    
    ::leave_inv(ob, to);

    if (!objectp(ob) || !objectp(to))
        return;

    if (!ob->query_no_show_composite())
        return;

    ob->set_no_show_composite(0);
}


/*
* Function name: query_player_access
* Description  : Return a list of the levels that the player have access to
* Arguments    : player - the player we want to check
* Returns      : an array with access levels
*/
string *query_player_access(object player)
{
    // Return the access level
    if (player->query_wiz_level() || player->query_warlock())
    {
        return ({ "warlock" });
    }

    // Return the shelves
    return ({});
}


/*
* Function name: library_hook_list
* Description  : Called when a player lists the contents of a shelf
* Arguments    : name - the name of the shelf being listed
*/
void library_hook_list_books(string name, mixed *shelf_data, mixed *books)
{
    // If we want to reward someone for something here.

    // Call the original function
    ::library_hook_list_books(name, shelf_data, books);
}


/*
* Function name: library_hook_remove_shelf
* Description  : Called when a shelf is removed, should give a nice message
* Returns      : a message
*/
string library_hook_remove_shelf(string shelf_name, int book_count)
{
    // If we want to reward someone for something here.

    // Return the original result
    return ::library_hook_remove_shelf(shelf_name, book_count);
}


/*
* Function name: library_help
* Description  : Get the help based on this_player()'s permissions
* Returns      : a string
*/
string library_help()
{
    // If we want to reward someone for something here.

    // Return the original text
    return ::library_help();
}


/*
* Function name: library_hook_create_shelf
* Description  : Construct a message
* Returns      : a string
*/
string library_hook_create_shelf(string shelf_name, string description)
{
    // If we want to reward someone for something here.

    return ::library_hook_create_shelf(shelf_name, description);
}


/*
* Function name: library_remove_book
* Description  : Called when a book is removed
* Arguments    : book_data - the information about the removed book
*/
void library_hook_remove_book(string name, mixed *book_data)
{

    // If we want to reward someone for something here.

    // Call the original
    ::library_hook_remove_book(name, book_data);
}


/*
* Function name: libraru_hook_move_book
* Description  : Called after a book is moved from one shelf to the other
* Arguments    : old_id - the previous name
*              : new_id - the new name
*/
void library_hook_move_book(string book_id, string old_shelf, 
string new_shelf)
{
    // If we want to reward someone for something here.

    // Call the original
    ::library_hook_move_book(book_id, old_shelf, new_shelf);
}


/*
* Function name: library_hook_receive_book
* Description  : Write the messages for a player receiving a new book
* Arguments    : player - the player receiving the book
*              : book - the book the player receives
*/
void library_hook_receive_book(object player, object book)
{
    // If we want to reward someone for something here.

    ::library_hook_receive_book(player, book);
}


/*
* Function name: library_hook_read_direct
* Description  : Called when a player directly reads a book
* Arguments    : content - the text of the book
*/
void library_hook_read_direct(string book_id, string content)
{
    mixed data;

    data = query_book_data(book_id);

    // If we want to reward someone for something here.

    ::library_hook_read_direct(book_id, content);
}


/*
* Function name: library_hook_change_shelf_title
* Description  : Called when a shelf is renamed
* Arguments    : shelf_name - the name of the shelf
*              : description - the description of the shelf
*/
string library_hook_change_shelf_title(string shelf_name, 
string description)
{
    // If we want to reward someone for something here.

    return ::library_hook_change_shelf_title(shelf_name, description);
}


/*
* Function name: library_hook_rename_shelf
* Description  : Called when a shelf is renamed
* Arguments    : shelf_name - the original name
*              : new_name - the new name of the shelf
*/
string library_hook_rename_shelf(string shelf_name, string new_name)
{
    // If we want to reward someone for something here.

    return ::library_hook_rename_shelf(shelf_name, new_name);
}


/*
* Function name: library_hook_renumber_book
* Description  : Called after a book has been renumbered
* Arguments    : old_id - the original id of the book
*              : new_id - the new id of the book
*/
void library_hook_renumber_book(string old_id, string new_id)
{
    // If we want to reward someone for something here.

    ::library_hook_renumber_book(old_id, new_id);
}


/*
* Function name: library_hook_rename_book
* Description  : Called after a book is renamed
* Arguments    : string book_name - the id of the book
*              : new_name - the new title of the book
* Returns      : a string
*/
string library_hook_rename_book(string book_name, string new_name)
{
    // If we want to reward someone for something here.

    return ::library_hook_rename_book(book_name, new_name);
}


/*
* Function name: done_editing
* Description  : Called after editing is complete
* Arguments    : book_id - the book being edited
*              : text - the text of the book
*/
void done_editing(string book_id, string text)
{
    if (stringp(text) && strlen(text))
    {
        // If we want to reward someone for something here.
    }

    ::done_editing(book_id, text);
}


/*
* Function name: silent_room
* Description  : Mask this function to allow the Nine to use this room as
*                any other. The King will deal with spammers among them.
* Arguments    : string str - the command line argument.
* Returns      : int 0 - always.
*/
int
silent_room(string str)
{
    return 0;
}


/*
* Function name: library_hook_list_shelves
* Description  : Called when a player lists the available shelves
* Arguments    : shelves - the array of shelves the player has access to
*/
void library_hook_list_shelves(string *shelves)
{
    int i;

    write("You find the following shelves:\n\n");
    write(sprintf("%-15s %s\n",
        "Shelf", "Description"));
    write(sprintf("%-15s %s\n",
        "---------------",
        "------------------------------------------------------------"));

    for (i = 0; i<sizeof(shelves); i++)
    {
        write(sprintf("%-15s %s\n",
            shelves[i],
            library_data["shelves"][shelves[i]][0]));
    }
}

