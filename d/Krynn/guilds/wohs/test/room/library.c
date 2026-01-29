/* 
 * The library in the tower of Daltigoth - Test of High Sorcery.
 *
 */

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/wayreth/local.h"
#include "/d/Krynn/guilds/wohs/defs.h"
#include <ss_types.h>
#include <language.h>
#include <macros.h>
#include <mail.h>

inherit WOHS_TEST_BASE;

inherit "/lib/guild_library";

#define BOOKS_DIR "/d/Krynn/guilds/wohs/test/obj/"
#define HEARTROOM_ACTIVATED  "_wohs_test_heartroom_activated"
#define STEAL_BOOK           "_wohs_test_attempted_to_steal_grimoire"

int grimoire = 1;

/* Prototypes */
public void        init();
public mixed *     library_hook_get_approval_names();
varargs mixed      add_new_book(string title, string contents, 
                                string author, string shelf = "",
                                string filename = "", 
                                string book_id = "");

object orb, book;

void
reset_tower_room()
{
    if(!objectp(orb))
    {
       orb = clone_object("/d/Krynn/guilds/wohs/objs/test_orb");
       orb->move(TO);
    }
}

void
create_tower_room()
{
    set_short("great library of the crimson tower of High Sorcery");
    set_long("You find yourself in a huge library. Lined along the high " +
      "walls are shelves with numerous books of different materials, " + 
      "colours and sizes. A long study table stretches near the shelves " +
      "at the back of the room. There is a plaque near the entry " +
      "instructing on the use of the library.\n");

    add_item(({"walls","shelves","books","library","huge library","maps"}),
      "Along the walls of the huge library are shelves filled with books, " +
      "maps, ancient lore, and tomes of magic that you would only find in " +
      "a Tower of High Sorcery.\n");
    add_item(({"scrolls","tomes","tomes of lore"}),
      "Piled up on the long study table you notice scrolls and tomes of " +
      "lore. A lifetime of knowledge!\n");
    add_item(({"long study table","study table","table"}),
      "@@study_table");
    add_item(({"thin leather-bound grimoire","leather-bound grimoire",
      "grimoire"}),"@@grimoire_desc");

    add_cmd_item(({"grimoire","thin leather-bound grimoire","up grimoire",
       "up thin leather-bound grimoire","up grimoire"}),
       ({"get","pick","take"}),"@@take_grimoire");

   set_tell_time(25);
   add_tell("Books tumble from the shelves as the walls of the tower " +
       "vibrate furiously!\n");
   add_tell("The tower rocks violently, as if it had been struck by a " +
       "wave of force!\n");
   add_tell("The stones of the tower begin to crack as spiderwebs of " +
       "energy spread across them.\n");
   add_tell("The tower begins to shake and rumble ominously!\n");
   add_tell("The walls of the tower groan, as if they were being " +
       "constricted by a powerful coil of force.\n");

    add_exit(WOHS_TEST + "room/daltigoth_tower8", "west", "@@exit_library");

    set_library_book_object("/d/Krynn/wayreth/obj/wohs_book");

    setuid();
    seteuid(getuid());

    // Guild Library Specific Items
    set_library_save_path(BOOKS_DIR);
    set_library_allow_new_books(1);

    create_library();
    reset_tower_room();

    add_item(({"plaque", "instructions", }), library_help);
    add_cmd_item(({"plaque", "instructions", }), "read", library_help);

}

int
exit_library()
{
    if(present("_wohs_test_grimoire", TP))
    {
        write("The thin leather-bound grimoire magically vanishes and " +
            "returns to the long study table as you depart the library.\n");
        present("_wohs_test_grimoire", TP)->remove_object();
        TP->add_prop(STEAL_BOOK, 1);
        WOHS_MANAGER->add_wohs_test_props(TP, STEAL_BOOK, 1);
        grimoire = 1;
    }

    return 0;
}

string
return_grimoire(string str)
{
    if(!str)
      return "Return what?\n";

    if((str != "grimoire") && (str != "leather-bound grimoire") &&
       (str != "thin leather-bound grimoire") && 
       (str != "grimoire to the table")) 
      return "Return what?\n";

    if(present("_wohs_test_grimoire", TP))
    {
        write("You put the thin leather-bound grimoire back on the long " +
            "study table.\n");
        present("_wohs_test_grimoire", TP)->remove_object();
        grimoire = 1;
        return "";
    }

   write("You don't have a grimoire on you to return?\n");
    return "";
}

string
take_grimoire()
{
    if(grimoire)
    {
       write("You pick up the thin leather-bound grimoire off the long " +
           "study table.\n");
       say(QCTNAME(TP)+ " picks up the thin leather-bound grimoire off " +
           "the long study table.\n");

       setuid();
       seteuid(getuid());

       book = clone_object("/d/Krynn/guilds/wohs/test/obj/test_grimoire");
       book->move(TP);
       grimoire = 0;
       return "";
    }
    else
    {
       return "Get what?\n";
    }
}

string
study_table()
{
    if(grimoire)
      return "Near the back of the library is a long study table covered " +
         "with scrolls and tomes of lore. A thin leather-bound grimoire " +
         "catches your eye, sitting closed at the end of the table.\n";
    else
      return "Near the back of the library is a long study table covered " +
         "with scrolls and tomes of lore.\n";
}

string
grimoire_desc()
{
    if(grimoire)
      return "Sitting on the edge of a long study table is a thin "+
         "leather-bound grimoire. You could probably pick it up and " +
         "examine it in more detail.\n";
    else
      return "You find no grimoire.\n";
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
    add_action(return_grimoire, "return");

} /* init */


/*
 * Function name: query_librarian
 * Description  : See if a person is a librarian
 * Arguments    : player - the player we want to check
 * Returns      : 0 on failure, 1 on success
 */
public int 
query_librarian(object player)
{
    // By default only wizards are librarians. However, if you want,
    // return 1 here if we change that to allow players.
    //
    // Librarians have the ability to create/remove/delete, etc.
    return player->query_wiz_level();
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
    return ({ "arman" });
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

    CREATE_MAIL("New book " + author, "TestWoHSLibrary",
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

public void
leave_inv(object ob, object to)
{
    object   oldtp;

    library_leave_inv(ob, to);
    ::leave_inv(ob, to);
} 

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
 
    if (interactive(ob) && TP->query_prop(HEARTROOM_ACTIVATED))
       start_room_tells();
}

