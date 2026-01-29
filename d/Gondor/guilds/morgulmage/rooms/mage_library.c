/*
 *  Private library for the Morgul Mages.
 *
 */

#pragma save_binary
#pragma strict_types

#include <composite.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/morgulmage/morgulmage.h"

inherit "/d/Gondor/morgul/city/morgul.c";
inherit "/lib/guild_library";


/*
 * Function name: create_morgul_room
 * Description  : Constructor
 */
void create_morgul_room()
{
    set_road(9);
    set_short_desc("in the Library of the Society of Morgul mages in Minas Morgul");
    set_extraline( 
        "This is a damp cellar beneath the main hall of the library "
      + "of Minas Morgul. Here the mages of the Society "
      + "keep important documents. On one wall there is a plaque with "
      + "instructions. A narrow stairway connects this room to the "
      + "public library upstairs.");

    add_item( ({ "shelf", "shelves" }), 
        "There are many shelves, each containing a different sort of scrolls.\n");

    add_prop(ROOM_I_LIGHT,1);
    add_prop(ROOM_I_INSIDE,1);

    add_exit("public_library", "up", "@@prevent_leave_with_books@@");

    // Allow us to read the help
    add_item(({"plaque", "instructions", }), library_help);
    add_cmd_item(({"plaque", "instructions", }), "read", library_help);

    // Start up the library
    set_library_save_path(MORGUL_LIBRARY_DIR + "mage/");
    set_library_save_file(MORGUL_LIBRARY_DIR + "mage_library");
    set_library_allow_new_books(1);
    set_library_log_file("morgulmage_mage_library");
    set_library_book_type("scroll");

    add_library_access_level("tuvales", "Tuvales+");
    add_library_access_level("servants", "Servants+");
    add_library_access_level("conjurers", "Conjurers+");
    add_library_access_level("sorcerers", "Sorcerers+");
    add_library_access_level("warlocks", "Warlocks+");
    add_library_access_level("wraiths", "Wraiths+");
    add_library_access_level("necromancers", "Necromancers+");
    add_library_access_level("librarian", "The Librarian");
    add_library_access_level("nazgul", "The Nine");

    set_library_book_object("/d/Gondor/common/guild2/obj/library_scroll");

    set_library_librarian_level("nazgul");

    create_library();
}

/*
 * Function name: query_librarian
 * Description  : See if a person is a librarian
 * Arguments    : player - the player we want to check
 * Returns      : 0 on failure, 1 on success
 */
int query_librarian(object player)
{
    // Wizards are librarians, as are the nazgul
    if(player->query_wiz_level() || player->query_nazgul())
        return 1;

    string playername = player->query_real_name();
    
    if(MORGUL_MASTER->query_position("librarian") == playername)
        return 1;
        
    // Other members are no librarian.
    return 0;
}

/*
 * Function name: query_player_access
 * Description  : Return a list of the levels that the player have access to
 * Arguments    : player - the player we want to check
 * Returns      : an array with access levels
 */
string *query_player_access(object player)
{
    string  *access;
    int     rank;

    access = ({ "tuvales" });
    rank = player->query_morgul_level(-1);
    if(player->query_wiz_level()) 
    {
        rank = 100;
        access += ({ "nazgul" });
    }
    if(rank >= 1) access += ({ "servants" });
    if(rank >= 3) access += ({ "conjurers" });
    if(rank >= 8) access += ({ "sorcerers" });
    if(rank >= 13) access += ({ "warlocks" });
    if(rank >= 18) access += ({ "wraiths" });
    if(rank >= 21) access += ({ "necromancers" });
    if(player->query_nazgul()) access += ({ "nazgul" });
    if(query_librarian(player)) access += ({ "librarian" });

    // Return the shelves
    return access;
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
}

/*
 * Function name: library_hook_stop_leave
 * Description  : Called when a player is stopped while carrying books,
 *              : redefine it to give your own message.
 * Arguments    : player - the player that's trying to leave
 *              : books - an array with the books that have not been returned
 */
void library_hook_stop_leave(object player, object *books)
{
    player->catch_msg("A terrible dark power will not let you pass until " +
        "you return " + COMPOSITE_DEAD(books) + ".\n");
}

/*
 * Function name: library_hook_list
 * Description  : Called when a player lists the contents of a shelf
 * Arguments    : name - the name of the shelf being listed
 */
void library_hook_list_books(string name, mixed *shelf_data, mixed *books)
{
    // Reward the Nazgul
    if(name == library_new_book_shelf)
    {
        // Give extra reward for listing the new arrival shelf
        MORGUL_MASTER->increase_activity( this_player(), 3 * ACTIVITY_MINOR);
    }
    else
    {
        // Normal rewards for regular shelves
        MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_MINOR);
    }

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
    // Reward the nazgul
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_OTHER_LIB_MOVE);

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
    // Reward the nazgul
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_MINOR);

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
    // Reward the nazgul
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_OTHER_LIB_CREATE);

    return ::library_hook_create_shelf(shelf_name, description);
}

/*
 * Function name: library_remove_book
 * Description  : Called when a book is removed
 * Arguments    : book_data - the information about the removed book
 */
void library_hook_remove_book(string name, mixed *book_data)
{
    // Reward the nazgul
    if(book_data[2] == library_new_book_shelf)
    {
        // If it's on the unpublished shelf, only reward if the book
        // is not written by the Nazgul himself
        if(this_player()->query_real_name() != book_data[3])
            MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_TYPICAL);
    }
    else
    {
        // Normal books 
        MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_TYPICAL);
    }

    // Call the original
    ::library_hook_remove_book(name, book_data);
}

/*
 * Function name: libraru_hook_move_book
 * Description  : Called after a book is moved from one shelf to the other
 * Arguments    : old_id - the previous name
 *              : new_id - the new name
 */
void library_hook_move_book(string book_id, string old_shelf, string new_shelf)
{
    // Reward the Nazgul
    if(old_shelf == library_new_book_shelf)
    {
        // If the book is on the unpublished shelf, reward the nazgul more
        // if he has written the book himself
        if(this_player()->query_real_name() == library_data["books"][book_id][3])
            MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_OTHER_LIB_CREATE);
        else
            MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_OTHER_LIB_MOVE);
    }
    else
    {
        // Normal books 
        MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_OTHER_LIB_MOVE);
    }

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
    // Reward the Nazgul
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_EMOTION / 2);

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

    // Reward the Nazgul
    if(data[2] == query_library_new_book_shelf())
    {
        if(data[3] == this_player()->query_real_name())
        {
            MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_OTHER_LIB_READ);
        }
        else
        {
            MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_TYPICAL);
        }
    }
    else
    {
        MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_OTHER_LIB_READ);
    }

    ::library_hook_read_direct(book_id, content);
}

/*
 * Function name: library_hook_change_shelf_title
 * Description  : Called when a shelf is renamed
 * Arguments    : shelf_name - the name of the shelf
 *              : description - the description of the shelf
 */
string library_hook_change_shelf_title(string shelf_name, string description)
{
    // Reward the Nazgul
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_OTHER_LIB_MOVE);

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
    // Reward the Nazgul
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_OTHER_LIB_MOVE);

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
    // Reward the Nazgul
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_OTHER_LIB_READ);

    ::library_hook_renumber_book(old_id, new_id);
}

/*
 * Function name: library_hook_change_access_level
 * Description  : Called when the access level of a shelf is changed
 * Arguments    : shelf_name - the name of the shelf
 *              : level - the new access level
 */
string library_hook_change_access_level(string shelf_name, string level)
{
    // Reward the Nazgul
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_OTHER_LIB_MOVE);

    return ::library_hook_change_access_level(shelf_name, level);
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
    // Reward the Nazgul
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_OTHER_LIB_MOVE);

    return ::library_hook_rename_book(book_name, new_name);
}