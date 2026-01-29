/*
 *  The room of the library of the Society
 *  where the Nazgul can administer the library.
 *
 *  Olorin, 20-Jan-95
 *
 *    Modification log:
 *    11-Feb-1997, Olorin:    Added "move" and "dismantle shelf" commands.
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/room.c";
inherit "/d/Gondor/common/lib/library_office.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"

// Prototypes
int     do_create(string str);
string  do_read();
public  int     move_book(string str);
public  int     remove_shelf(string str);

// Global variables
static  string  open_lib = (MAGES_DIR + "society_library");

public void
create_room()
{
    set_short("in the Library of the Society of Morgul Mages");
    set_long(
        "In this room of the library in the Society of Morgul Mages "
      + "the Nazgul can review works that have been submitted for "
      + "inclusion into the library. "
      + "On one wall is a plaque with instructions how to do this.\n" );

    add_exit(MAGES_DIR + "mage_library", "west", 0, 0);
    add_exit(MAGES_DIR + "private_library", "down", 0, 0);

    add_prop(ROOM_I_INSIDE, 1);

    set_save_path(MAGES_DIR + "books/submissions");
    set_library(MAGES_DIR + "mage_library");
    set_log_file("morgul_lib");
    set_up_office();

    add_item(({"plaque", "instructions", }), do_read());
    add_cmd_item(({"plaque", "instructions", }), "read", do_read());
}

void
init()
{
    ::init();
    init_office();

    add_action( do_create,    "create" );
    add_action( move_book,    "move" );
    add_action( remove_shelf, "dismantle" );
}

/*
 * Function name: add_book_to_library
 * Description:   add a book to the library
 * Arguments:     s - name of the book
 * Returns:       1 if success, 0 else
 * Modified for a library using shelves: add <book> to shelf <shelf> in <mage|open> library
 */
public int
add_book_to_library(string s)
{
 string  book,
         shelf,
         which;

    s = capitalize( lower_case( s ) );
    if (sscanf( s, "%s to shelf %s in %s library", book, shelf, which ) < 3)
    {
        notify_fail( "Add which book to which shelf?\n"+
            "Try: add <book> to shelf <shelf> in <mage|open> library.\n" );
        return 0;
    }

    if (which == "society")
    {
        which = "open";
    }
    if ((which != "open") && (which != "mage"))
    {
        return 0;
    }
    if (which == "mage")
    {
        if (member_array( capitalize( shelf ), lib->query_shelf() ) < 0)
        {
            notify_fail( "There is no shelf with the name \""+
                capitalize( shelf )+"\" in the mage library!\n" );
            return 0;
        }
    }
    else if ((which == "open") || (which == "society"))
    {
        which = "open";
        if (member_array( capitalize(shelf), open_lib->query_shelf() ) < 0)
        {
            notify_fail( "There is no shelf with the name \""+
                capitalize( shelf )+ "\" in the Society library!\n");
            return 0;
        }
    }
    else
    {
        notify_fail( "There is no "+ which+ " library!\n" );
        return 0;
    }

    if (!sizeof( books[book] ))
    {
        return lib_hook_office_not_exist();
    }
    if (which == "mage")
    {
        lib->add_book(book, books[book][0], books[book][1], books[book][2]);
        lib->add_shelf_book( shelf, book );
        write( "You add the book to "+ lib->query_library_name()+ ".\n" );
    }
    else
    {
        open_lib->add_book( book, books[book][0],
            books[book][1], books[book][2] );
        open_lib->add_shelf_book( shelf, book );
        write( "You add the book to "+ open_lib->query_library_name()+
            ".\n" );
    }

    FIX_EUID

    log_file( log_file, "LIBRARY: "+ this_player()->query_name()+
        " added the book "+ book+ " ("+ books[book][0]+ ") to the shelf "+
        capitalize( shelf )+ " ("+ which+ ") on "+ ctime( time() )+ ".\n");

    if (query_book_author(books[book][1]) ==
        lower_case(this_player()->query_name()))
    {
        IDLENESS->increase_activity( this_player(), OTHER_LIB_CREATE );
    }
    else
    {
        IDLENESS->increase_activity( this_player(), OTHER_LIB_MOVE );
    }

    books = m_delete( books,book );
    save_object( lsave );
    check_desc();

    return 1;
}

string
do_read( void )
{
    IDLENESS->increase_activity( this_player(), MINOR_ACTIVITY );
    return
        "\n\t"+ capitalize( lib->query_library_name() )+ "\n"
      + "\n\tThe following commands are available:\n\n"
      + "\tlist                - list the submitted titles,\n"
      + "\tread <title>        - read a submitted title,\n"
      + "\treject <title>      - reject a submission,\n"
      + "\tadd <title> to shelf <shelf> in <mage|open> library -\n"
      + "\t               add a title to a shelf of the library,\n"
      + "\tmove <title> to shelf <name> in <mage|open> library -\n"
      + "\t               move a title to another shelf,\n"  
      + "\t               (works only within one library)\n"  
      + "\tcreate shelf <name> in <mage|open> library          -\n"
      + "\t               create a new shelf in the library.\n"
      + "\tdismantle shelf <name> in <mage|open> library       -\n"
      + "\t               dismantle an empty shelf.\n"
      + "\n\tTo remove old titles, go to the library.\n\n";
}

void
describe_shelf( string desc, string name, string which )
{
    if (!strlen(desc))
    {
        write( "No description given. No new shelf added!\n" );
        return;
    }

    if (which == "mage")
    {
        lib->add_shelf( name, desc );
    }
    else
    {
        open_lib->add_shelf( name, desc );
    }
    name = capitalize( name );
    write( "You create a new shelf \""+ name+ "\" in the "+ which+
        " library.\n" );
    say( QCTNAME( this_player() )+ " creates a new shelf \""+ name+
        "\" in the "+ which+ " library.\n" );
    log_file( log_file, "LIBRARY: "+ this_player()->query_name()+
        " added the shelf \""+ name+ "\" ("+ which+
        ") with the description: \""+ desc+ "\" on "+
        ctime( time() )+ ".\n" );
}

public int
do_create( string str )
{
 string  name, 
         which;

    if (!strlen( str ))
    {
        notify_fail( "Create what?\n" );
        return 0;
    }

    str = lower_case( str );
    if (sscanf( str, "shelf %s in %s library", name, which ) != 2)
    {
        notify_fail( "Create shelf <name> in <mage|open> library\n" );
        return 0;
    }

    if (which == "mage")
    {
        if (member_array( capitalize( name ), lib->query_shelf() ) >= 0)
        {
            notify_fail( "There is already a shelf \""+ capitalize( name )+
                "\" in the mage library!\n" );
            return 0;
        }
    }
    else if ((which == "open") || (which == "society"))
    {
        if (member_array( capitalize(name), open_lib->query_shelf() ) >= 0)
        {
            notify_fail( "There is already a shelf \""+ capitalize( name )+
                "\" in the Society library!\n" );
            return 0;
        }
    }
    else
    {
        notify_fail( "There is no "+ which+ " library!\n" );
        return 0;
    }

    write( "Enter the description of the new shelf \""+ capitalize( name )+
        "\":\n> ");
    input_to( &describe_shelf( , capitalize( name ), which ) );
    IDLENESS->increase_activity( this_player(), OTHER_LIB_CREATE );
    return 1;
}

/*
 * Function name: remove_shelf
 * Description:   Remove an empty shelf.
 * Argument:      "dismantle shelf <name> in <which> library"
 */
public int
remove_shelf( string str )
{
 string  shelf,
         which;

    notify_fail( "Dismantle shelf <name> in <mage|open> library.\n" );
    if (!strlen(str))
    {
        return 0;
    }
    if (sscanf( lower_case( str ), "shelf %s in %s library", shelf, which)
        != 2)
    {
        return 0;
    }
    
    switch (which)
    {
    case "mage":
        if (member_array( capitalize( shelf ), lib->query_shelf() ) < 0)
        {
            notify_fail( "There is no shelf \""+ capitalize( shelf )+
                "\" in the mage library!\n" );
            return 0;
        }
        if (sizeof( lib->query_shelf_book( shelf ) ))
        {
            notify_fail( "There are still titles on the shelf \""+
                capitalize( shelf )+ "\" in the mage library.\n" );
                return 0;
        }
        lib->remove_shelf( shelf );
        break;
    case "open":
    case "society":
        if (member_array( capitalize(shelf), open_lib->query_shelf() ) < 0)
        {
            notify_fail( "There is no shelf \""+ capitalize( shelf )+
                "\" in the Society library!\n" );
            return 0;
        }
        if (sizeof( open_lib->query_shelf_book(shelf ) ))
        {
            notify_fail( "There are still titles on the shelf \""+
                capitalize( shelf )+ "\" in the Society library.\n" );
               return 0;
        }
        open_lib->remove_shelf(shelf);
        break;
    default:
        notify_fail( "There is no "+ which+ " library.\n" );
        return 0;
        break;
    }
    write( "You dismantle the empty shelf \""+ capitalize( shelf )+
        "\" in the "+ capitalize( which )+ " library.\n" );
    say( QCTNAME( this_player() )+ " dismantles the empty shelf \""+
        capitalize( shelf )+ "\" in the "+ capitalize( which )+
        " library.\n" );
    IDLENESS->increase_activity( this_player(), OTHER_LIB_MOVE );
    return 1;
}

public int
move_book_from_mage_to_open(string book, string shelf)
{
    NFN("This is not possible yet.");
    return 0;
}

public int
move_book_from_open_to_mage(string book, string shelf)
{
    NFN("This is not possible yet.");
    return 0;
}

/*
 * Function name: move_book
 * Description:   Move book from one shelf to another.
 * Argument:      str - command line argument:
 *                      move <book name> to shelf <shelf name> in <which> library
 * Returns:       1/0 - failure/success
 */
public int
move_book(string str)
{
 int     i, s;
 string  book,
         shelf,
         which,
        *shelves;

    notify_fail( "Move <name> to shelf <shelf> in <mage|open> library.\n" );
    if (!strlen( str ))
    {
        return 0;
    }

    if (sscanf( lower_case( str ), "%s to shelf %s in %s library", 
           book, shelf, which ) != 3)
    {
        return 0;
    }

    book  = capitalize( book );
    shelf = capitalize( shelf );
    switch (which)
    {
    case "mage":
        if (member_array( book, lib->query_names() ) > -1)
        {
            return lib->move_book( book, shelf );
        }
        else if (member_array( book, open_lib->query_names() ) > -1)
        {
            return move_book_from_open_to_mage( book, shelf );
        }
        break;
    case "open":
    case "society":
        if (member_array( book, open_lib->query_names() ) > -1)
        {
            return open_lib->move_book( book, shelf );
        }
        else if (member_array( book, lib->query_names() ) > -1)
        {
            return move_book_from_mage_to_open( book, shelf );
        }
        break;
    default:
        notify_fail( "There is no "+ which+ " library.\n" );
        return 0;
    break;
    }
    notify_fail( "There is no title \""+ book+
        "\" in the libraries of the Society!\n" );
    return 0;
}

public int list_books( string str )
{
    if (::list_books( str ) == 1)
    {
        IDLENESS->increase_activity( this_player(), 3* MINOR_ACTIVITY );
        return 1;
    }
    return 0;
}

public int read_book( string str )
{
    str = capitalize( lower_case( str ) );
    
    if (::read_book( str ) == 1)
    {
        if (query_book_author(books[str][1]) ==
            lower_case(this_player()->query_name()))
        {
            IDLENESS->increase_activity( this_player(), OTHER_LIB_READ );
        }
        else
        {
            IDLENESS->increase_activity( this_player(), TYPICAL_ACTIVITY );
        }
        return 1;
    }
    return 0;
}

public int remove_book( string str )
{
 string Book_author;

    str = capitalize( lower_case( str ) );
    Book_author = query_book_author( books[str][1] );
    
    if (::remove_book( str ) == 1)
    {
        if (Book_author != lower_case(this_player()->query_name()))
        {
            IDLENESS->increase_activity( this_player(), TYPICAL_ACTIVITY );
        }
        return 1;
    }
    return 0;
}
