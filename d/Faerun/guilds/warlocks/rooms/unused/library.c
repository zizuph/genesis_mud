/* /d/Faerun/guilds/warlocks/rooms/library.c
 *
 * Room in the guildhall. Library. Based on the MM library.
 *
 * Nerull, 2017
 *
 */
#include "/d/Faerun/defs.h"
#include "../guild.h";

inherit WARLOCK_STD_ROOM;
inherit "/lib/guild_library";

#define NO  0
#define YES 1

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
    set_long("This is the dark library of the Warlocks. It is " +
        "a repository of secrets, and where they learn the dark arts " +
        "and mysteries of magic. The room is unusually cold. Rows of " +
        "bookcases fill the room and scrolls of all sizes fills them. " +
        "Chairs and tables are scattered around the room, where visitors " +
        "can sit and read, or pen new scrolls. You see a plaque hanging " +
        "on the wall.\n");

    add_item(({"bookcases", "bookshelves", "bookcase", "bookshelf"}),
        "They are made of wood and are lined up in rows in the library. " +
        "The bookcases are large and sag under the weight of the scrolls " +
        "they hold.\n");
    add_item(({"scrolls"}),
        "They are rolls of parchment and are stacked in the bookcases. " +
        "Many of them look old, dusty, and faded. They are all sizes " +
        "from small scrolls, to large rolls.\n");
    add_item(({"tables"}),
        "The tables are large and scattered around the library. Some " +
        "are used to read scrolls and others used to write new ones. " +
        "They are sturdy looking, and some have chairs set around them.\n");
    add_item(({"chairs"}),
        "The chairs are sturdy looking and scattered around the library. " +
        "Some are wooden and surround some tables. Others are comfy " +
        "looking and set in the corners of the room.\n");
    add_item(({"parchment"}),
        "They are stiff, flat material made from prepared skins. The " +
        "parchemnts are part of the many scrolls that fill the bookcases. \n");
    add_item(({"comfy chairs"}),
        "These chairs are oversized and covered in dark fabrics. They " +
        "are padded and look comfortable.\n");
    add_item(({"wooden chairs"}),
        "These chairsare large and heavy looking, and covered with dark " +
        "fabric. They are square with padded armrests, and are spread " +
        "around the tables.\n");
    add_item(({"pens", "quills", "quill pen", "quill pens"}),
        "They are writing instrument made from a feather. The end has " +
        "been shaved down to a point and dipped in an inkwell for writing.\n");
    add_item(({"inkwell", "inkwells"}),
        "The inkwells are small glass containers. They are scattered " +
        "acrossed the tables and are filled with ink.\n");
    add_item(({"ink"}),
        "It is a black liquid used for writing. It fills the inkwells " +
        "that are the tables. \n");
    add_item(({"fabric", "dark fabric"}),
        "It is plush looking and used on the chairs.\n");

    add_exit(WARLOCK_ROOMS_DIR + "hall01", "south",
        "@@prevent_leave_with_books@@", NO);
//    add_exit(WARLOCK_ROOMS_DIR + "spells_rm", "north",
//        "@@prevent_leave_with_books@@", NO);

    add_domed_ceiling();
    add_walls();
    add_ground_plain();
    add_sconces();
    add_doorways();

//    set_library_save_path("/doc/examples/guild_library/advanced/books");
    set_library_save_path(WARLOCK_LIBRARY_DIR + "books");
    set_library_allow_new_books(YES);

    set_library_book_type("scroll");
    set_library_book_object(WARLOCK_LIBRARY_DIR + "blank_scroll");

    add_library_access_level("normal", "Everyone");
//    add_library_access_level("restricted", "Card owners");
    add_library_access_level("owner", "Owners");

    set_library_log_file("warlocks_library_log");
    set_library_librarian_level("owner");

    add_item(({"plaque", "instructions", }), library_help);
    add_cmd_item(({"plaque", "instructions", }), "read", library_help);

    reset_faerun_room();

    create_library();
}

void init()
{
    ::init();
    init_library();
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}

void leave_inv(object ob, object to)
{
    library_leave_inv(ob, to);
    ::leave_inv(ob, to);
}

int query_librarian(object player)
{
    if(player->query_wiz_level() || present(LIBRARY_CARD, player))
    {
        return 1;
    }
    return 0;
}

string *query_player_access(object player)
{

    if (player->query_wiz_level() || present(LIBRARY_CARD, player))
    {
        return ({ "normal", "owner" });
    }

    return ({ "normal" });
}

/*
 * Function name: library_help
 * Description  : Get the help based on this_player()'s permissions
 * Returns      : a string
 */
string library_help()
{
    string  result;
    string head_line = "\t+-------------------------------------------------------------+\n";
    string blank_line ="\t|                                                             |\n";
    // Header
        result = head_line;
        result += blank_line;
        result +="\t|  The following commands are available in this library:      |\n" +
           blank_line;

    // Regular commands
        result +="\t|    * list [shelf]       - list the available shelves, or    |\n" +
            "\t|                           scrolls on that shelf.            |\n" +
            "\t|    * catalog [shelf]    - same as the list command          |\n" +
            "\t|    * borrow [scroll ID] - borrow the scroll                 |\n" +
            blank_line;

    // Add text when we allow new books
    if(library_allow_new_books)
    {
        result +="\t|  To add to the library, get a [blank scroll]. When you have |\n" +
            "\t|  completed writing your scroll, [submit] it. It will be re- |\n" +
            "\t|  viewed by a librarian and added to the shelves.            |\n" +
            blank_line;
    }

    // Give the librarian extra options
    if(query_librarian(this_player()) || this_player()->query_wiz_level())
//    if(query_librarian(this_player() ))
    {
        result +="\t|  As a librarian, you can also do the following commands:    |\n" +
            "\t|    * renumber [old ID] to [new ID]                          |\n" +
            "\t|    * edit [scroll ID]                                       |\n" +
            "\t|    * assign  [scroll ID] to [shelf name]                    |\n" +
            "\t|    * create shelf [shelf name] with title [shelf title]     |\n" +
            "\t|    * rename [old shelf name] to [new shelf name]            |\n" +
            "\t|    * rename [scroll ID] to [new title]                      |\n" +
            "\t|    * change [shelf name] to [new title]                     |\n" +
            "\t|    * access [shelf name] for [level]                        |\n" +
            "\t|    * remove shelf [shelf name]                              |\n" +
            "\t|    * remove scroll [scroll ID]                              |\n" +
            blank_line;

    }

    result += head_line;

    // Gives more help for wizzes
    if(this_player()->query_wiz_level())
    {
        result += "\nImmortals can also 'lock' or 'unlock' specific scrolls for editing.\n";
    }

    return result;
}

/*
 * Function name: library_hook_list_books
 * Description  : Called when a player lists the contents of a shelf
 * Arguments    : name - the name of the shelf being listed
 */
void library_hook_list_books(string shelf_name, mixed *shelf_data, mixed *books)
{
    int i;

    // Check for empty shelves
    if(sizeof(books) == 0)
    {
        write("The shelf '" + shelf_name + "' is empty.\n");
        return;
    }

    // Display the list
    write(shelf_data[0] + ":\n\n");
    write(sprintf("%-10s %s\n", "ID", "Title"));
    write(sprintf("%-10s %s\n", "----------",
        "-----------------------------------------------------------------"));
    for(i=0;i<sizeof(books);i++)
    {
        write(sprintf("%-10s %s\n",
            books[i],
            library_data["books"][books[i]][1]));
    }
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
    player->catch_msg("The librarian won't let you leave with " +
        COMPOSITE_DEAD(books) + ".\n");
}