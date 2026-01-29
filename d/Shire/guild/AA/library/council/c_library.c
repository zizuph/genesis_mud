/*
 * Council library for the AA guild
 * Updated on February 2019 by Finwe
 *
 * The library is open only to those who can enter the AA Council. 
 */
#pragma strict_types
#pragma save_binary

#include "/d/Shire/sys/defs.h"
#include "../../guild.h"
inherit "/d/Shire/room";
inherit "/lib/guild_library";

void create_room()
{
    set_short("the Council Library of the Army of Angmar");
    set_long("This is the Council Library of the Army of Angmar. " +
        "Bookcases line the walls, and are full of countless books " +
        "that document the Army. The library is quiet and affords a " +
        "place where you may write a book or two. Against a wall hangs " +
        "a sign.\n");

   add_item("desk",
        "The desk is sturdy looking and sits in a corner of the room. " +
        "It is surrounded by hard looking chairs.\n");    
    add_item(({"shelves", "book cases", "book cases"}),
        "The shelves are sturdy and full of books to read.\n");

    add_item("sign", 
        "Flowing words have been painted onto the sign. They were written " +
        "by someone skilled in the Common language and look like they " +
        "provide information aboutt he library.\n");
    add_cmd_item("chair", "sit in", 
        "You sit back and relax in one of the hard chairs in the room.\n");
    
    add_item(({"lamp","lamps"}),
        "They are attached to the walls and fill the room with light.\n");
    add_item("ceiling",
        "It is rugged and gray colored. Lamps are spread around, filling " +
        "the room with light.\n");
    add_item(({"walls", "wall"}),
        "The walls cut into the mountain. They are rugged looking " +
        "and gray colored.\n");
    add_item(({"floor", "down", "ground"}),
        "The floor is smooth. Large rugs cover the floor and muffle any " +
        "sounds here.\n");
    add_item(({"rug", "rugs", "large rugs"}),
        "The large rugs are plush and cover the ground.\n");

    set_library_save_path("/d/Shire/guild/AA/library/council/");
// 0 = No new books, 1 = allow new books
    set_library_allow_new_books(1);

    set_library_book_type("book");
    set_library_book_object("/d/Shire/guild/AA/library/library_book");

    add_library_access_level("normal", "Everyone");
    add_library_access_level("restricted", "Card owners");
    add_library_access_level("owner", "Owners");
    
    set_library_librarian_level("normal");

    create_library();

    add_item(({"sign", "instructions", }), library_help);
    add_cmd_item(({"sign", "instructions", }), "read", library_help);
    add_exit(AA_DIR+"rooms/council","east");

//    add_exit("/d/Shire/rivendell/room/valley/u_cor03", "south");
}

/*
 * Function name: library_help
 * Description  : Get the help based on this_player()'s permissions
 * Returns      : a string
 */
string library_help()
{
    string  result;

    // Header
    result = "The Dark Lord demands records be kept on all who serve Him. " +
        "You do that here in this library.\n\n";
    
    // Regular commands
    result += "" +
"   +---------------------------------------------------------------+\n" +
"   |                                                               |\n" +
"   |   The following commands are available to you:                |\n" +
"   |                                                               |\n" +
"   |   list [shelf]     - List the available shelves, or books     |\n" +
"   |                      on that shelf.                           |\n" +
"   |   catalog [shelf]  - same as the list command                 |\n" +
"   |   borrow <book>    - borrow the book with the id <book>       |\n" +
"   |                                                               |\n" ;



    // Add text when we allow new books

    if(library_allow_new_books)
    {
        result += "" +
"   |   You can add to the library. This is done by 'write book'    |\n" +
"   |   or you can get a 'blank book'. When the new book is done,   |\n" +
"   |   'submit' it.                                                |\n" +
"   |                                                               |\n";


    }

    // Give the librarian extra options
    if(query_librarian(this_player()) || this_player()->query_wiz_level())
    {
        result += "" +
"   |   These commands are available to you as a leader of the      |\n" +
"   |   great Army of Angmar! You can use the first three           |\n" +
"   |   characters of the commands as a shortcut.                   |\n" +
"   |                                                               |\n" +
"   |   (ren)umber <old id> to <new id>                             |\n" +
"   |   (edi)t <book id>                                            |\n" +
"   |   (ass)ign  <book id> to <shelf name>                         |\n" +
"   |   (cre)ate shelf <shelf name> with title <shelf title>        |\n" +
"   |   (ren)ame <old shelf name> to <new shelf name>               |\n" +
"   |   (ren)ame <book id> to <new title>                           |\n" +
"   |   (cha)nge <shelf name> to <new title>                        |\n" +
"   |   (acc)ess <shelf name> for <level>                           |\n" +
"   |   (rem)ove shelf <shelf name>                                 |\n" +
"   |   (rem)ove book <book id>                                     |\n" +
"   |                                                               |\n" ;

    }

    result += "" +
"   +---------------------------------------------------------------+\n" ;

    // Gives more help for wizzes
    if(this_player()->query_wiz_level())
    {
        result += "\nImmortals can also 'lock' or 'unlock' specific " +
            "books for editing.\n";
    }

    return result;
}


void init()
{
    ::init();
//    init_library();

    add_action(library_read_cmd,        "read");
    add_action(library_read_cmd,        "mread");
    add_action(library_list_cmd,        "list");
    add_action(library_list_cmd,        "catalog");
    add_action(library_list_cmd,        "catalogue");
    add_action(library_borrow_cmd,      "borrow");

    // Allow the addition of books
    if(library_allow_new_books)
    {
        add_action(library_blank_cmd,   "blank");
        add_action(library_blank_cmd,   "write");
    }

    // Give the librarian extra options
    if(!query_librarian(this_player()) && !this_player()->query_wiz_level())
        return;

    add_action(library_renumber_cmd,    "renumber");
    add_action(library_renumber_cmd,    "ren");

    add_action(library_assign_cmd,      "assign");
    add_action(library_assign_cmd,      "ass");

    add_action(library_create_cmd,      "create");
    add_action(library_create_cmd,      "cre");

    add_action(library_rename_cmd,      "rename");
    add_action(library_rename_cmd,      "ren");

    add_action(library_change_cmd,      "change");
    add_action(library_change_cmd,      "cha");

    add_action(library_access_cmd,      "access");
    add_action(library_access_cmd,      "acc");

    add_action(library_remove_cmd,      "remove");
    add_action(library_remove_cmd,      "rem");

	add_action(library_edit_cmd,		"edit");
	add_action(library_edit_cmd,		"edi");

    // Only allow wiz chars beyond this point
    if(!this_player()->query_wiz_level())
        return;

    // Allow immortals to lock books
    add_action(library_lock_cmd,        "lock");
    add_action(library_lock_cmd,        "unlock");
}

void leave_inv(object ob, object to)
{
    library_leave_inv(ob, to);
    ::leave_inv(ob, to);
}

int query_librarian(object player)
{
//    if(player->query_wiz_level() || present(LIBRARIAN, player))
        return 1;

//    return 0;
}


// anyone can access the library who can enter the room
string *query_player_access(object player)
{
/*
    if (present(LIBRARIAN, player) || player->query_wiz_level()) 
    {
        return ({ "normal", "restricted", "owner" });
    }

    if (present("_library_card", player)) 
    {
        return ({ "normal", "restricted" });
    }
*/
    return ({ "normal" });
}