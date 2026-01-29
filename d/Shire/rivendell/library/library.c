/*
 * Library of Rivendell
 * Updated on January 2019 by Finwe
 *
 * The library is open to anyone, and is maintained by mortals who have a 
 */
#pragma strict_types
#pragma save_binary

#include "local.h"
#include "/d/Shire/sys/defs.h"

inherit "/d/Shire/room";
inherit "/lib/guild_library";

void create_room()
{
    set_short("the Library of Imladris");
    set_long("This is the Library of Imladris. Rows of bookcases line " +
        "the walls. They are full of many books that contain collected " +
        "stories, songs, and knowledge of the Elves. The library is " +
        "quiet, and affords a place where you may write a book or two. " +
        "Against a wall hangs a sign.\n");

   add_item("desk",
        "The desk is used by a Bibliosoph to sort returned books.\n");    
    add_item("shelves",
        "The shelves are sturdy and full of books to read.\n");

    add_item("sign", 
        "Flowing words have been painted onto the sign. They were written " +
        "by someone skilled in the Common language and look like they " +
        "provide information aboutt he library.\n");
    add_cmd_item("chair", "sit in", 
        "You sit back and relax in one of the most comfortable " +
        "chairs in the room.\n");
    
    add_item(({"lamp","lamps"}),
        "They are attached to the walls and radiate a soft, " +
        "white light throughout the room.\n");
    add_item("ceiling",
        "Large richly carved beams hold up the roof high " +
        "above you.\n");
    add_item(({"walls", "wall"}),
        "The walls are an off-white color and lightly textured. " +
        "Lamps are attached to the walls.\n");
    add_item(({"windows","window"}),
        "The windows are large and equally " +
        "divided vertically into two sections with each " +
        "vertical section divided horizontally into four " +
        "squares. They windows are closed to preserve the " +
        "precious books and manuscripts in here. Large " +
        "curtains cover them.\n");
    add_item("curtains",
        "They are made from a heavy fabric and are closed.\n");
    add_item(({"floor", "down", "ground"}),
        "The floor is made from dark hardwoods and is very " +
        "clean. Large rugs cover the floor and muffle any " +
        "sounds here\n");
    add_item(({"rug", "rugs", "large rugs"}),
        "The large rugs are plush, filling the room with their " +
        "bright, luxurious colors.\n");

    set_library_save_path("/d/Shire/rivendell/library/");
// 0 = No new books, 1 = allow new books
    set_library_allow_new_books(1);

    set_library_book_type("book");
    set_library_book_object("/d/Shire/rivendell/library/library_book");

    add_library_access_level("normal", "Everyone");
    add_library_access_level("restricted", "Card owners");
    add_library_access_level("owner", "Owners");
    
    set_library_librarian_level("owner");
	//set_book_directory("/w/mayari/books");

    create_library();

    add_item(({"sign", "instructions", }), library_help);
    add_cmd_item(({"sign", "instructions", }), "read", library_help);

    add_exit("/d/Shire/rivendell/room/valley/u_cor03", "south");
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
    result = "The following commands are available in this library:\n\n";
    
    // Regular commands
    result += "" +
"   +---------------------------------------------------------------+\n" +
"   |                                                               |\n" +
"   |   The following commands are available in this library:       |\n" +
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
"   |   These commands are available to you as a Bibliosoph of      |\n" +
"   |   the Library of Imladris. You can use the first three        |\n" +
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
"   |                                                               |\n" +
"   |   IMPORTANT:                                                  |\n" +
"   |   If you create a shelf you should set the access             |\n" +
"   |   level (people that have read access to it) as well.         |\n" + 
"   |   Otherwise readers who are not Bibliosophs (or wizards)      |\n" + 
"   |   will not be able to 'see' the shelf or borrow any of the    |\n" +  
"   |   books it contains.                                          |\n" +
"   |                                                               |\n" +
"   |   To do this use the following command line:                  |\n" +
"   |   access <shelf name> for normal                              |\n" +
"   |                                                               |\n" ;																																														
	                                                                 }
    result += "" +
"   +---------------------------------------------------------------+\n";

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
    if(player->query_wiz_level() || present(LIBRARIAN, player))
        return 1;

    return 0;
}

string *query_player_access(object player)
{
    if (present(LIBRARIAN, player) || player->query_wiz_level()) 
    {
        return ({ "normal", "restricted", "owner" });
    }

    if (present("_library_card", player)) 
    {
        return ({ "normal", "restricted" });
    }

    return ({ "normal" });
}