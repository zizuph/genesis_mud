/* 
 *    The library in Minas Morgul 
 *    copied from the Edoras library by Elessar  
 *    Olorin, Oct-1993 
 *
 *    Updated to use /d/Gondor/common/lib/library.c
 *
 *    Altered by Eowul in May 2009 to serve as the public library of the
 *    Morgul Mages.
 */
#pragma strict_types

#include <composite.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/morgulmage/morgulmage.h"

inherit "/d/Gondor/morgul/city/morgul.c";
inherit "/lib/guild_library";

private int     check_mage();

/*
 * Function name: create_morgul_room
 * Description  : Constructor
 */
void create_morgul_room()
{
    set_road(9);
    set_short_desc("in the Library of Minas Morgul");
    set_extraline(
        "You are in a very large hall with shelves along the walls, "
      + "more shelves on the floor, and all the shelves are filled "
      + "with books of all colours, sizes and ages. At a desk in the "
      + "north-eastern corner of the room stands an aging man, "
      + "probably the ancient scribe. A doorway leads out to the "
      + "place to the west. In a corner, a narrow stairway is leading "
      + "down. Your gaze stops at a poster by the open door, which "
      + "says: No talking! Further down on the poster you see some "
      + "instructions.");

    add_exit(MORGUL_DIR + "city/square",    "west", prevent_leave_with_books, 0);
    add_exit("mage_library", "down", check_mage, 2);

    add_item( ({ "shelf", "shelves" }), 
        "There are many shelves, each containing a different sort of books.\n");
        
    add_item(({"stairs", "stairway"}), 
        "In a corner, a narrow stairway is leading down into the cellars "
      + "under the library. Looking at the dark hole into which the stairs "
      + "disappear you can sense the powerful magic protecting the way "
      + "down.\n");
  
    add_item(({"ancient scribe", "scribe"}), 
        "He is an ancient man of dark complexion. He was probably born "
      + "in Harad, now he is in charge of the library here. His biggest "
      + "concern is probably to protect the valuable books from the orcs "
      + "in this town.\n");

    add_item("desk", "The desk is covered with pile upon pile of books.\n");

    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_INSIDE, 1);
    
    add_item(({"poster", "instructions", }), library_help);
    add_cmd_item(({"poster", "instructions", }), "read", library_help);
    
    // Start up the library
    set_library_save_path(MORGUL_LIBRARY_DIR + "public/");
    set_library_save_file(MORGUL_LIBRARY_DIR + "public_library");
    set_library_allow_new_books(1);
    set_library_log_file("morgulmage_public_library");    
    
    add_library_access_level("public", "Public access");
    add_library_access_level("nazgul", "The Nine");  

    set_library_librarian_level("nazgul");
    create_library();
}

int query_librarian(object player)
{
    // Wizards are librarians, as are the nazgul
    if(player->query_wiz_level() || player->query_nazgul())
        return 1;

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
    if(player->query_wiz_level() || player->query_nazgul()) 
    {
        return ({ "public", "nazgul" });
    }

    return ({ "public" });
}

void init()
{
    ::init();
    init_library();
}

void leave_inv(object ob, object to)
{
    library_leave_inv(ob, to);
    ::leave_inv(ob, to);
}

void library_hook_stop_leave(object player, object *books)
{
    player->catch_msg("A terrible dark power will not let you pass until " +
        "you return " + COMPOSITE_DEAD(books) + ".\n");
}

private int
check_mage()
{

    if (IS_MORGUL_MAGE(TP))
        return prevent_leave_with_books();
        
    if (TP->query_wiz_level())
    {
        write("This exit is closed for all mortals but Morgul mages!\n");
        return prevent_leave_with_books();
    }
    
    write("You dare not go down on the stairs. The way down seems to be "
        + "protected by powerful magic.\n");
    return 1;
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

    // Check for empty shelves
    if(sizeof(books) == 0)
    {
        write("You scan the shelf '" + shelf_data[0] + "' but find no books "
            + "of interest.\n");
        return;
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
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_PUBLIC_LIB_MOVE);

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
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_PUBLIC_LIB_CREATE);

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
            MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_PUBLIC_LIB_CREATE);
        else
            MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_PUBLIC_LIB_MOVE);
    }
    else
    {
        // Normal books 
        MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_PUBLIC_LIB_MOVE);
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
            MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_PUBLIC_LIB_READ);
        }
        else
        {
            MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_TYPICAL);
        }
    }
    else
    {
        MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_PUBLIC_LIB_READ);
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
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_PUBLIC_LIB_MOVE);

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
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_PUBLIC_LIB_MOVE);

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
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_PUBLIC_LIB_READ);

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
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_PUBLIC_LIB_MOVE);

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
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_PUBLIC_LIB_MOVE);

    return ::library_hook_rename_book(book_name, new_name);
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

    for(i=0;i<sizeof(shelves);i++)
    {
        write(sprintf("%-15s %s\n",
            (library_data["shelves"][shelves[i]][1]  == 
            query_library_librarian_level() ? "*" : "") +
            shelves[i],
            library_data["shelves"][shelves[i]][0]));
    }
    
    if (query_librarian(this_player())) {
        write("\nShelves marked with a * are only accessible to "
            + "librarians.\n");
    }
}
