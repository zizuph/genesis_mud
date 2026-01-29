/*******************************************************************\
| COUNCIL_TOME.C                                                    |
\*******************************************************************/

/*
 * 07/06/03 Arandir     Made the book skip to the last page on open
 * 03/06/10 Arandir	Ported to new area
 * 01/09/18 Manat       Moved to council directory
 * 00/06/18 Cirion	Created
 *
 */

#include <options.h>
#include <language.h>

#include "../defs.h"

inherit "/std/book";

inherit M_PLAYER_LIBS;

//-------------------------------------------------------------------

#define M_LINES_PER_PAGE        20

//-------------------------------------------------------------------

void create_book ()
{
  set_short ("thick red leather tome");
  set_name (({ "book", "tome", "log" }));
  add_adj (({ "thick", "red", "leather" }));

  set_long ("This is a large, thick tome, rich with " +
            "the history of the Dragon Order.\n");

  // The maximum number of pages is reset every
  // time the book is opened to compensate for
  // the fact that the book can grow at any
  // time ...

  set_max_pages (0);
}


/*
 * Function name : m_get_pages
 * Description   : Returns the number of pages of the book.
 *
 */

int m_get_pages ()
{
  int iPages = 0;
  while (strlen (read_file (M_FILE_LOG_COUNCIL, iPages * M_LINES_PER_PAGE + 1, M_LINES_PER_PAGE)) > 0)
  {
    iPages ++;
  }
  return (iPages);
}


/*
 * Function name : open_me
 * Description   : Opens the book and moves to the last page.
 *
 */

void open_me ()
{
  // This function uses undocumented behavior of the
  // book base class in both opening the book and
  // setting the pages !

  int iPages = m_get_pages ();

  // First open the book.

  ::open_me ();

  // Set the maximum number of pages and turn to the
  // last one so that reading is not so tedious.

  set_max_pages (iPages);
  what_page = iPages;

  if (iPages > 1) write ("You quickly scan forward to page " + LANG_WNUM (iPages) + ".\n");
}


/*
 * Function name : read_book_at_page
 *
 */

void read_book_at_page (int iPage, string sVerb)
{
  object oHim = this_player ();
  string sContents;

  if (m_is_council_member (oHim) || m_is_authorized_wizard (oHim))
  {
    DG_FIXUID;

    sContents = read_file (M_FILE_LOG_COUNCIL, (iPage - 1) * M_LINES_PER_PAGE + 1, M_LINES_PER_PAGE);
    if (strlen (sContents)) write (sContents);
                       else write ("This page is blank.\n");
  }
  else
  {
    write ("The words on the page seem to twist as you try to read them.\n");
  }
}

//-------------------------------------------------------------------

