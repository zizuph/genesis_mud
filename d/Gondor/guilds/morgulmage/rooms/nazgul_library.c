/*
 *  Test library for the Morgul Mages.
 *
 */

#pragma save_binary
#pragma strict_types

#include <composite.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/morgulmage/morgulmage.h"

inherit "/d/Gondor/morgul/tower/tower.c";
inherit "/lib/guild_library";
inherit "/d/Genesis/lib/post.c";

// Variables
static  object  Key;

// Protoypes
int hang_cmd( string str );

/*
 * Function name: create_morgul_tower_room
 * Description  : Constructor
 */
void create_morgul_tower_room()
{
    set_level( 5 );
    set_room_type( "library" );
    set_extra_long( "This is a dark, candlelit room behind the Throne Room "+
        "of the Lord of the Nazgul. Here the Nazgul keep their secret and "+
        "arcane documents. Shelves full of scrolls and dark tomes line "+
        "the walls and a huge obsidian slab sits amid them, serving as "+
        "a desk and writing surface. Various bones and cured herbs are "+
        "hung about to serve as examples for the Ringwraiths in their "+
        "studies. A forbidding doorway leads past a black door to "+
        "the Throne Room." );

    add_item( ({"candle", "candles"}),
        "These candles are made of black wax, and burn with a " +
        "terrible stench. They burn constantly, tended by unseen " +
        "hands.\n" );

    add_item( ({"documents", "scrolls", "tomes", "books"}),
        "The scrolls and tomes sit carefully organized on the " +
        "horrible shelves. They are arranged according to subject. " +
        "The subjects you can see at a glance include: Necromancy, " +
        "Torture, Summoning, and Powers.\n" );

    add_item( ({"shelves", "bookcases"}),
        "These shelves are made of an almost ivory-white material. " +
        "Upon closer inspection, you see that the material is " +
        "actually bone! Somehow the bones of once-living creatures " +
        "were fused together into these shelves.\n" );

    add_item( ({"slab", "desk", "surface", "table"}),
        "This huge block of obsidian rests in the middle of the " +
        "library. The surface of the slab is marred by ages of use. " +
        "There is room enough for all of the Nine to study around the " +
        "table. You wonder where such a massive block came from. " +
        "At the front of the desk is a plaque with instructions.\n" );

    add_item( ({"bones", "herbs", "examples"}),
        "Various samples of components, reagents, and oddities hang " +
        "from the ceiling at various places. You see a dried sample " +
        "of the rare athelas leaf, a troll skull, and a fragment of " +
        "some long-broken spherical object, apparently of great value.\n" );

    add_item( ({"doorway", "door"}),
        "The door leads north into the Throne Room of the Lord of " +
        "the Nazgul.\n" );

    add_walls( "On one wall there is an iron hook fastened to it." );
    add_item( ({"hook", "iron hook", }), VBFC_ME( "key_hook" ) );
    add_floor();
    add_roof();

    add_prop(ROOM_I_LIGHT,1);
    add_prop(ROOM_I_INSIDE,1);

    add_exit(MORGUL_ROOM_DIR + "upper_throne_room", "north", 
        "@@prevent_leave_with_books@@", 0 );

    // Allow us to read the help
    add_item(({"plaque", "instructions", }), library_help);
    add_cmd_item(({"plaque", "instructions", }), "read", library_help);

    // Start up the library
    set_library_save_path(MORGUL_LIBRARY_DIR + "nazgul/");
    set_library_save_file(MORGUL_LIBRARY_DIR + "nazgul_library");
    set_library_allow_new_books(1);
    set_library_log_file("morgulmage_nazgul_library");
    set_library_book_type("scroll");

    add_library_access_level("nazgul", "The Nine");
    set_library_book_object("/d/Gondor/common/guild2/obj/nazgul_library_scroll");

    set_library_librarian_level("nazgul");

    create_library();
    reset_room();
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
    // Return the access level for nazgul
    if(player->query_wiz_level() || player->query_nazgul()) 
    {
        return ({ "nazgul" });
    }

    // Return the shelves
    return ({ });
}

/*
 * Function name: init
 * Description  : Add commands to the player
 */
void init()
{
    ::init();
    init_library();
    post_init();

    add_action( hang_cmd  , "hang"   );
    add_action( hang_cmd  , "put"    );
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
    post_leave_inv(ob, to);
    ::leave_inv(ob, to);

    if (!objectp(ob) || !objectp(to))
        return;

    if (!ob->id("key") || !ob->query_no_show_composite())
        return;

    ob->set_no_show_composite(0);
}

/*
 * Function name: hang_cmd
 * Description  : Command to hang the key back on the hook
 * Arguments    : str - command line arguments
 * Returns      : 0 on failure, 1 on success
 */
public int
hang_cmd( string str )
{
 object  ob,
         key_here;
 string  vb = query_verb();

    if (!strlen( str ))
    {
        return 0;
    }
    
    str = lower_case(str);

    if (!parse_command( str, this_player(),
        " [the] %o [back] 'on' / 'onto' [the] 'hook'", ob ))
    {
        notify_fail( capitalize( vb )+ " what on what?\n");
        return 0;
    }

    if (!ob->id( "key" ))
    {
        write( "You can only "+ vb+ " a key onto that hook.\n" );
        return 1;
    }

    if (objectp( key_here = present( "key" ) ) && 
        key_here->query_no_show_composite())
    {
        write( "There is already another key hanging on the hook!\n" );
        return 1;
    }

    write( "You "+ vb+ " the "+ Key->short()+ " onto the hook.\n" );
    say( QCTNAME( this_player() )+ " hangs "+ LANG_ADDART( ob->short() )+
        " onto the hook on the wall.\n" );
    ob->move( this_object() );
    ob->set_no_show_composite( 1 );
    MORGUL_MASTER->increase_activity( this_player(), 4*ACTIVITY_MINOR );
    return 1;
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
    MORGUL_MASTER->increase_activity( this_player(), 2*ACTIVITY_MINOR );

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
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_NAZ_LIB_MOVE);

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
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_NAZ_LIB_CREATE );

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
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_NAZ_LIB_MOVE );

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
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_NAZ_LIB_MOVE);

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
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_NAZ_LIB_READ );

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
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_NAZ_LIB_MOVE);

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
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_NAZ_LIB_MOVE);

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
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_NAZ_LIB_READ);

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
    // Reward the Nazgul
    MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_NAZ_LIB_MOVE);

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
	if(stringp(text) && strlen(text))
	{
		// Reward the Nazgul
		MORGUL_MASTER->increase_activity( this_player(), ACTIVITY_NAZ_LIB_WRITE);
	}

	::done_editing(book_id, text);
}

/*
 * Function name: reset_room
 * Description  : Called to reset items in the room 
 */
void
reset_room()
{
    if (!objectp( Key ))
    {
        Key = clone_object(MORGUL_OBJ_DIR + "tower_key" );
            Key->set_no_show_composite( 1 );
        Key->move( this_object() );
    }
    return;
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

string
key_hook()
{
    object  key_here;
    string  desc =
        "On one wall there is an iron hook fastened to it.";

    if (!objectp(key_here = present("key")) ||
        !key_here->query_no_show_composite())
        desc += " The hook is empty.";
    else
        desc += " There is a "+key_here->short()+" hanging on the hook.";

    return BSN(desc);
}

/* 
 * Function name: add_aliases
 * Description  : Add aliases to the mailreader
 * Arguments    : rdr - the mail reader to add to
 */
void
add_aliases(object rdr)
{
    rdr->set_alias("nazgul", MORGUL_MASTER->query_nazgul_names());
    rdr->set_alias("guildmaster", 
           GONDOR_MASTER->query_domain_aliases(MORGUL_S_GUILD_NAME));
}

public int
query_prevent_snoop()
{
    FIX_EUID;
    if (SECURITY->query_wiz_dom(this_interactive()->query_real_name()) 
        == "Gondor")
    {
        return 0;
    }
    return ::query_prevent_snoop();
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
            shelves[i],
            library_data["shelves"][shelves[i]][0]));
    }
}
