/*******************************************************************\
| LIBRARY_PARAPET.C                                                 |
\*******************************************************************/

/*
 * 03/12/18 Arandir     Created off the public library
 * 04/03/06 Arandir     It was possible to leave with a scroll
 * 04/08/15 Arandir     Added the missing inside property
 * 05/01/07 Arandir	Couple of extra shelves
 * 20/08/06 Lucius	Added book return when teleporting
 *
 */

#include <math.h>
#include <macros.h>
#include <stdproperties.h>

#include "../defs.h"

inherit M_ROOM_BASE;

inherit "/lib/library";
inherit DG_OBJ_LIBS;

// From /lib/library
#define BOOK_ID    (MASTER + "_library_book")

//-------------------------------------------------------------------

void
leave_inv(object ob, object dest)
{
    if (living(ob))
    {
	foreach(object book: filter(deep_inventory(ob), &->id(BOOK_ID)))
	    return_it(book);
    }

    ::leave_inv(ob, dest);
}

void create_room ()
{
  set_short ("library parapet");
  set_long  ("A narrow parapet lines the bookshelves, filled with scrolls " +
             "that are considered private by the librarian and thus moved " +
             "here, where a casual visitor does not come. A low railing " +
             "prevents you from falling down, should you happen to " +
             "become too ensorcelled by the scrolls. " +
             dg_embed_livings ("library", "You see ", " in the library below.", "The library below is silent and empty.") +
             "\n");

  add_prop (ROOM_I_INSIDE, TRUE);

  // Indicate that a book needs to be borrowed before reading.

  set_borrow_required (TRUE);

  // This part of the library holds scrolls rather than books.

  set_book_type ("scroll");
  set_plural_book_type ("scrolls");

  // Set directories where approved, submitted and removed
  // books are to be stored. Also add shelves, each shelf
  // is a subdirectory in the book directory, first shelf
  // is the default one, whatever that means.

  set_book_directory (M_PATH_LIBRARY_PRIVATE_BOOK);
  set_book_removal_directory (M_PATH_LIBRARY_PRIVATE_REMO);
  set_book_approval_directory (M_PATH_LIBRARY_PRIVATE_APPR);

  add_book_shelf ("lore");
  add_book_shelf ("maps");
  add_book_shelf ("news");
  add_book_shelf ("guilds");
  add_book_shelf ("general");
  add_book_shelf ("equipment");

  create_library ();

  add_item (({ "shelf", "shelves", "bookshelves", "bookshelf" }),
            "They are made of red wood and have small niches to " +
            "safely store the invaluable scrolls. A small sign " +
            "on the very top of the bookshelves can be read.\n");

  add_item (({ "parapet" }),
            "You stand upon a narrow wooden parapet that provides " +
            "access to the very top of the bookshelves.\n");

  add_item (({ "wing", "wings", "carving", "carvings", "dragon carving", "dragon carvings" }),
            "The dragon carving that facilitated your climb is just below " +
            "the parapet, a reliable way back for those of nimble limbs.\n");

  add_item ("sign", library_help ());
  add_cmd_item ("sign", "read", library_help());
}

//-------------------------------------------------------------------

/*
 * Function name : m_action_climb_wings
 * Descriptipn   : Leave the restricted library area.
 *
 */

int m_action_climb_wings (string sArgs)
{
  object oActor = this_player ();

  if ((sArgs != "down") && (sArgs != "wing") && (sArgs != "wings")) return (FALSE);

  if (library_exit_block ())
  {
    write ("You cannot leave with a library scroll.\n");
    return (TRUE);
  }

  write ("Holding on to the edges of the wings that stand out of " +
         "the dragon carving, you make your way down from the " +
         "parapet lining the upper section of the bookshelves.\n");
  say (QCTNAME (oActor) + " climbs the edges of the wings that " +
       "stand out of the dragon carving.\n");
  oActor->move_living ("M", M_PATH_ROOM + "/library", TRUE, FALSE);
  say (QCTNAME (oActor) + " arrives climbing down from the parapet " +
       "lining the upper section of the bookshelves.\n");

  return (TRUE);
}

//-------------------------------------------------------------------

/*
 * Function name : init
 * Description   : Initialize the library functions.
 *
 */

void init ()
{
  ::init ();

  init_library ();

  add_action (m_action_climb_wings, "climb");
}

//-------------------------------------------------------------------

/*
 * Function name : library_admin_access
 * Description   : Limit library administration to certain people.
 * Returns       : Boolean whether access is enabled.
 *
 */

int library_admin_access ()
{
  // Administration is limited to council members and authorized wizards.

  if (m_is_council_member (this_player ()) |
      m_is_authorized_wizard (this_player ()))
  {
    return (TRUE);
  }
  else
  {
    write ("You do not have permission to do that.\n");
    return (FALSE);
  };
}

/*
 * Function name : library_write_access
 * Description   : Limit writing books to certain people
 * Returns       : Boolean whether access is enabled.
 *
 */

int library_write_access ()
{
  // Writing books is limited to monks and wizards.

  if (m_is_monk (this_player ()) |
      dg_is_wizard (this_player ()))
  {
    return (TRUE);
  }
  else
  {
    write ("Only members may author books here.\n");
    return (FALSE);
  };
}

/*
 * Function name : library_configure_book
 * Description   : Configure a library book. Redefined to add a
 *                 nice short description for the book based
 *                 on the file name of the book.
 *   oBook         : The book object.
 *   sFileName     : The file name of the book file.
 *   sBookName     : The name of the book.
 *
 */

void library_configure_book (
  object oBook,
  string sFileName,
  string sBookName)
{
  string *asAdjectives = ({ "small", "red", "iron-lined", "dusty",
                            "blue", "thick", "copper-lined", "old",
                            "tattered", "torn", "worn", "leathery" });
  string sAdjective, sName;
  int    iIndex, iSize;

  ::library_configure_book (oBook, sFileName, sBookName);

  // Filter out spaces from the book name because NAME_TO_RANDOM
  // is rumored to choke out on them. Remember to use 5 digits
  // prime number in the macro too ...

  iSize = sizeof (asAdjectives);
  sName = implode (explode (sBookName, " "), "");
  iIndex = NAME_TO_RANDOM (sName, 32999, iSize);

  sAdjective = asAdjectives [iIndex];

  oBook->add_adj (sAdjective);
  oBook->set_short (sAdjective + " scroll");
}

//-------------------------------------------------------------------

