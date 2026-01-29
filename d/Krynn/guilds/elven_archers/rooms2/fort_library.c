/*
 *  /d/Krynn/guilds/elven_archers/rooms2/fort_library.c
 *  This is the guild library for the Elven Archers of Ansalon.
 *
 *  ...based on /d/Krynn/solace/poolbottom/rooms/library.c
 *  (SoHM guild library)
 *
 */

#include <ss_types.h>
#include <stdproperties.h>
#include <mail.h>

#include <macros.h>
#include <composite.h>
#include <filter_funs.h>

#include "/d/Krynn/common/defs.h"
#include "../guild.h"

#define BOOK_DIR "/d/Krynn/guilds/elven_archers/books"
#define BOOK_OBJ "archer_book.c"

#define MORTAL_LIBRARIAN "pann"
#define IMMORTAL_LIBRARIAN "vitwitch"

#define GUILDROOMS "/d/Krynn/guilds/elven_archers/rooms2/"
#define VIEWDEST "/d/Krynn/qualinesti/elf_camp/camp3"

inherit "/lib/guild_library";
inherit "/d/Krynn/guilds/elven_archers/rooms2/baseroom_fort";

/* Prototypes */
string             warrant_desc();
string             fineprint_desc();
public void        init();
public int         query_librarian(object player);
public mixed *     library_hook_get_approval_names();
void               library_hook_list_shelves(string *shelves);
void               library_hook_stop_leave(object player, object *books);
void               library_hook_list_books(string shelf_name, mixed *shelf_data, mixed *books);
void               library_hook_receive_book(object player, object book);
varargs mixed      add_new_book(string title, string contents, 
                                string author, string shelf = "",
                                string filename = "", 
                                string book_id = "");

string
warrant_desc()
{
    return "The warrant, sealed in wax on the wall, accords " + capitalize(MORTAL_LIBRARIAN) +
     " of the Elven Archers of Ansalon the solemn duty of Librarian of this place. Fine print"+
     " can be seen at the bottom of the warrant.\n";
}

string
fineprint_desc()
{
    return "The fine print reads:"+
           " If " + capitalize(MORTAL_LIBRARIAN) + " be unable or unwilling to undertake this duty, "+
           "a new holder of this office should be recommended to the Wizard "
              + capitalize(IMMORTAL_LIBRARIAN) + ".\n";
}


void
reset_krynn_room()
{       
    return;
}


create_krynn_room()
{

    set_short("a library in a treetop fortress");

    set_long(gBlurbPfx +
        " All about stands the Library of the Elven Archers of Ansalon. " +
        "Tall bookshelves of living gum trees fill the room, growing upward towards "+
        "the sky, crowned by ever flowering blossoms which draw the attention of bees. "+
        "By day, the overall effect is one of a maze of warmly illuminated pathways "+
        "to practical wisdom, abuzz with activity. By night, the bees are replaced by "+
        "fireflies in all seasons which lend their light to seekers of knowledge in "+
        "the wee small hours.  The books themselves are swaddled from the " +
        "elements in a sheen of wax, courtesy of the busy bees of the library. "+
        "There is a wax plaque near " +
        "the entry of the library to assist archers who wish to use the library. "+
        "A warrant is posted in this room, affixed by wax to an exposed branch. " +
        gBlurbSfx +
        " To the east can be seen a curious place from where a sweet smell emanates.\n");

    add_item(({"bookshelves","tall bookshelves","gum tree","gum trees","bookshelf","shelves","shelf"}),
        "Towering bookshelves of living gum fill the room in a natural order, leaving scant " +
        "space for archers to wend their way between in search of knowledge. The fresh scent " +
        "eucalypt oil fills the nostrils of knowledge seekers, conferring a sense of calm. "+
        "Bees tend and repair the surfaces of the books ensuring that they are well covered in wax "+
        "against the ravages of time and weather.\n");

    add_item(({"books","wax"}),
        "The library has an impressive number of books, arranged within bookshelves and "+
        "protected by beeswax. A plaque near the entry to the library " +
        "explains how to access those which might be of relevance to an inquiring mind.\n");

    add_item( ({"warrant",}), "@@warrant_desc");
    add_cmd_item(({"warrant", }), "read", warrant_desc);

    add_item( ({"fine print","fineprint",}), "@@fineprint_desc");
    add_cmd_item( ({"fine print","fineprint",}), "read", fineprint_desc);

    gViewFallDest = VIEWDEST;

    add_item(({"fort","fortress","treetop fortress"}),"@@fort_purpose");
    add_item(({"treetops","whispering treetops","branches"}),"@@fort_description");
    add_item(({"walls","wall"}),"@@fort_walls");
    add_item(({"stakes","stakes","strands","strand"}),"@@fort_stakes");
    add_item(({"loopholes","loophole","window","windows","ground","ground below"}),"@@fort_vantage");
    add_item(({"foliage"}),"@@fort_foliage");

    INSIDE

    add_exit(GUILDROOMS + "fort_reservoir","east",prevent_leave_with_books,0,0);

    set_library_save_file(GUILDROOMS + "fort_library");  // .o added by functions
    set_library_book_object(GUILD_OBJ + BOOK_OBJ);

    setuid();
    seteuid(getuid());

    // Guild Library Specific Items
    set_library_save_path(BOOK_DIR);
    set_library_allow_new_books(1);

    create_library();

    add_item(({"plaque", "instructions"}), library_help);
    add_cmd_item(({"plaque", "instructions"}), "read", library_help);

    add_cmd_item(({"down", "ground", "loophole", "window"}), "view", "@@view_down");
    set_tell_time(250);
    add_tell("Gum tree blossoms shift in the gentle breeze as bees buzz about their duty.\n");

}

/* 
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();
    init_library();

} /* init */


public int 
query_librarian(object player)
{
    string name;
    int return_value;

    return_value = 0;

    name = player->query_real_name();

    if ( name == MORTAL_LIBRARIAN ) return_value++;
    if ( name == IMMORTAL_LIBRARIAN ) return_value++;

    if ( return_value > 1 ) return_value = 1;

    if ( (player->query_wiz_level()) && !return_value )
        write("Note that " + capitalize(IMMORTAL_LIBRARIAN) +
            " holds immortal Librarian privileges here.\n");

    return return_value;
}


/*
 * Function name: library_hook_get_approval_names
 * Description  : This routine can be redefined in the library code to provide
 *                the names of the players who are authorized to approve books
 *                before they are added to the library. If this is the case,
 *                those players will receive a mail informing them of the fact
 *                that a new book has been submitted.
 * Returns      : string * - the list of names (in lower case).
 */
public mixed *
library_hook_get_approval_names()
{
    return ({ MORTAL_LIBRARIAN, IMMORTAL_LIBRARIAN });
} /* library_hook_get_approval_names */


/*
 * Function name: add_new_book
 * Description  : Add a new book to the shelves
 * Arguments    : title - the title of the book
 *              : contents - the contents of the book
 *              : author - the author of the book
 *              : shelf (optional) - the shelf on which to place the book
 *              : filename (optional) - which filename to use for storing the
 *              :       content
 *              : book_id (optional) - the id by which the book is known
 * Returns      : a filename which contains the contents or 0 on failure
 *
 * I mask this from the parent so that I can have it generate a mail
 * and send it to whoever I have deemed to be the current guild
 * librarian.
 */
varargs mixed
add_new_book(string title, string contents, 
             string author, string shelf = "", string filename = "", 
             string book_id = "")
{
    mixed  submitted = ::add_new_book(title, contents, author, shelf,
                         filename, book_id);
    string *names = library_hook_get_approval_names();

    if (!submitted)
    {
        return 0;
    }

    CREATE_MAIL("New book " + author, "ElvArchLib",
                implode(names, ","), "",
                "========================================================="
              + "======================\n"
              + "Title: " + title + "\n"
              + "========================================================="
              + "======================\n\n"
              + contents + "\n"
              + "---------------------------------------------------------"
              + "----------------------\n");

    return submitted;
} /* add_new_book */


void library_hook_receive_book(object player, object book)
{
    // Write messages
    player->catch_msg("You find the " + library_book_type +
        " that you were looking " +
        "for and ease it out from its waxy wooden nook.\n");
    tell_room(environment(player), QCTNAME(player) + " seems to " +
        "have found the " + library_book_type + " " +
        player->query_pronoun() + " was " +
        "looking for and eases it out of its nook.\n", player);
}


void library_hook_list_books(string shelf_name, mixed *shelf_data, mixed *books)
{
    int i;

    // Check for empty shelves
    if(sizeof(books) == 0)
    {
        write("The shelf '" + shelf_name + "' is sadly without anything interesting to you.\n");
        return;
    }

    // Display the list
    write(shelf_data[0] + ":\n\n");
    write(sprintf("%-10s %s\n", "Number", "Title"));
    write(sprintf("%-10s %s\n", "----------",
        "-----------------------------------------------------------------"));
    for(i=0;i<sizeof(books);i++)
    {
        write(sprintf("%-10s %s\n",
            books[i],
            library_data["books"][books[i]][1]));
    }
}


void library_hook_list_shelves(string *shelves)
{
    int i;

    write("You find the following shelves of living wood:\n\n");
    write(sprintf("%-25s %-35s %s\n",
        "Shelf", "Description", "Access level"));
    write(sprintf("%-25s %-35s %s\n",
        "-------------------------",
        "-----------------------------------",
        "---------------"));

    for(i=0;i<sizeof(shelves);i++)
    {
        write(sprintf("%-25s %-35s %s\n",
            shelves[i],
            library_data["shelves"][shelves[i]][0],
            query_access_desc(library_data["shelves"][shelves[i]][1])));
    }
}

void library_hook_stop_leave(object player, object *books)
{
    player->catch_msg("As you make to leave, there is increased buzzing "+
        "from the gumtree flowers above. The noise reminds you that " +
        COMPOSITE_DEAD(books) + " belongs in the library, under wax.\n");
}


/* 
 * Function name: leave_inv
 * Description:   Called when objects leave this container or when an
 *                object is about to change its weight/volume/light status.
 * Arguments:     ob: The object that just left this inventory.
 *                to: Where it went.
 *
 * This function is redefined to force players to stand up before
 * leaving if they are currently sitting in a chair. Also, we set up
 * some special library leave functions.
 */
public void
leave_inv(object ob, object to)
{
    object   oldtp;

    library_leave_inv(ob, to);
    ::leave_inv(ob, to);
} 

