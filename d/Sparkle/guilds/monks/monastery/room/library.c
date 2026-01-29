/*******************************************************************\
| LIBRARY.C                                                         |
\*******************************************************************/

/*
 * 98/??/?? Cirion	Created
 * 00/12/26 Manat	Fixed typos
 * 02/02/11 Arandir	Ported to new area
 * 03/12/16 Arandir     Added private section after AoB approval
 * 04/08/15 Arandir     Added the missing inside property
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

private object oTable;

//-------------------------------------------------------------------
//

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

/*
 * Function name : m_exit_library
 * Description   : Prevent the player from leaving the library
 *                 with a book in the inventory.
 *
 */

int m_exit_library ()
{
  if (library_exit_block ())
  {
    write ("You cannot leave with a library book.\n");
    return (TRUE);
  }
  else return (FALSE);
}

//-------------------------------------------------------------------

void create_room ()
{
  oTable = dg_clone_here (M_PATH_OBJ + "/library_table");

  set_short ("library");
  set_long  ("Tall bookshelves of red wood stand spaced around the " +
             "perimeter of this cool room. " +
             dg_embed_composite () +
             "Sunlight floods in through a large leaded-glass window " +
             "in the north wall, its rays made visible by the swirling " +
             "motes of dust falling slowly through the air. " +
             VBFC ("dg_get_description:" + file_name (oTable)) +
             "\n");

  add_prop (ROOM_I_INSIDE, TRUE);

  add_exit ("hall_lower_north", "east", &m_exit_library ());

  dg_add_entrance ("east", "You enter the cool, bright library.");

  // Indicate that a book needs to be borrowed before reading.

  set_borrow_required (TRUE);

  // Set directories where approved, submitted and removed
  // books are to be stored. Also add shelves, each shelf
  // is a subdirectory in the book directory, first shelf
  // is the default one, whatever that means.

  set_book_directory (M_PATH_LIBRARY_PUBLIC_BOOK);
  set_book_removal_directory (M_PATH_LIBRARY_PUBLIC_REMO);
  set_book_approval_directory (M_PATH_LIBRARY_PUBLIC_APPR);

  add_book_shelf ("general");
  add_book_shelf ("maps");
  add_book_shelf ("news");
  add_book_shelf ("lore");

  create_library ();

  add_item (({ "shelf", "shelves", "bookshelves", "bookshelf" }),
            "They are made of red wood and have a pyramidal shape, " +
            "with a wide base ending at elbow height and a somewhat " +
            "narrower but still robust upper section that stretches " +
            "up beyond an easy reach. A small sign on the very " +
            "bottom of the bookshelves can be read.\n");

  add_item (({ "base", "wide base", "shelf base", "bookshelf base" }),
            "The base is wide and robust, forming a sturdy support " +
            "for the tall upper section of the bookshelves. The " +
            "red wood of the base is decorated with carvings.\n");

  add_item (({ "upper section", "tall section" }),
            "The upper section of the bookshelves seems to have been " +
            "added after the wide base, to accommodate the growing " +
            "number of books that the library holds. It is capped " +
            "with a parapet.\n");

  add_item (({ "parapet" }),
            "The upper section of the bookshelves is capped with a " +
            "parapet. It is still far from the ceiling, but you do " +
            "not see what might be on it because it is equally far " +
            "from the floor.\n");

  add_item (({ "wood", "red wood" }),
            "The bookshelves are made of a sturdy wood, perhaps oak, finished " +
            "with a reddish stain. Where the bookshelves end, a carving in " +
            "the likeness of a dragon guarding scrolls in its talons " +
            "symbolizes the wisdom stored in the library.\n");

  add_item (({ "dragon", "carving", "carvings", "dragon carving", "dragon carvings" }),
            "The carving of a dragon guarding scrolls in its talons decorates " +
            "the bookshelves. It is exquisite in every detail, from the tough " +
            "scales to the reptilian eyes. Grand wings give the dragon a " +
            "majestic appearance, stretching from the floor up to the " +
            "parapet above you in a gentle arch.\n");

  add_item (({ "wing", "wings", "grand wing", "grand wings" }),
            "The wings of the dragon carving are arched in a gesture that is " +
            "both protective and threatening, completing the regal feel that " +
            "the artist embedded into the carving. The edges of the wings " +
            "seem to have another function though, for they stand out of " +
            "the carving in a regular pattern.\n");

  add_item (({ "window", "leaded-glass window", "glass" }),
            "The glass is clear but rather thick, causing it " +
            "to distort the sunlight just enough to create " +
            "random rainbows here and there. Strips of leaded " +
            "iron hold the glass panes in place.\n");

  add_item (({ "light", "sunlight" }),
            "Sunlight filters through the leaded-glass window, " +
            "strongly enough to brightly illuminate the room " +
            "for reading, yet not so strong as to cause the " +
            "pages of the books to fade.\n");

  add_item (({ "rainbow", "rainbows", "random rainbows" }),
            "You see one in the corner of your eye, but when " +
            "you turn to look, it is gone.\n");

  add_item ("sign", library_help ());
  add_cmd_item ("sign", "read", library_help());

  // Clone the livings that populate the library.

  dg_clone_here (M_PATH_NPC + "/aliya", "",
                 "Standing in the corner is a stern elf, watching over the library. ");
}

//-------------------------------------------------------------------

/*
 * Function name : m_action_climb_wings
 * Descriptipn   : Enter the restricted library area.
 *
 */

int m_action_climb_wings (string sArgs)
{
  object oActor = this_player ();

  if ((sArgs != "wing") && (sArgs != "wings")) return (FALSE);

  if (m_is_monk (oActor) ||
      dg_is_wizard (oActor))
  {
    write ("Holding on to the edges of the wings that stand out of " +
           "the dragon carving, you make your way up to the parapet " +
           "lining the upper section of the bookshelves.\n");
    say (QCTNAME (oActor) + " climbs up to the parapet lining the " +
         "upper section of the bookshelves.\n");
    oActor->move_living ("M", M_PATH_ROOM + "/library_parapet", TRUE, FALSE);
    say (QCTNAME (oActor) + " arrives climbing the edges of the wings " +
         "that stand out of the dragon carving.\n");
  }
  else
  {
    write ("You feel that would not be appropriate for a visitor.\n");
  }

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
  string *asAdjectives = ({ "small", "red", "iron-bound", "dusty",
                            "blue", "thick", "copper-bound", "old",
                            "tattered", "torn", "worn", "leather-bound" });
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
  oBook->set_short (sAdjective + " book");
}

//-------------------------------------------------------------------

