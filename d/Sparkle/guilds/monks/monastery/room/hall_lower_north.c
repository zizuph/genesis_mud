/*******************************************************************\
| HALL_LOWER_NORTH.C                                                |
\*******************************************************************/

/*
 * 98/05/02 Cirion	Created
 * 00/12/26 Manat	Fixed typos
 * 01/12/28 Arandir	Ported to new area
 * 02/02/10 Arandir	Fixed so that the fresco items do not
 *			get added every time long desc is seen
 * 03/08/05 Arandir     Fixed references to sunlight
 * 03/09/06 Arandir     Fixed fresco descriptions
 * 03/12/02 Arandir     Fixed the fresco item order
 *
 */

#include <language.h>
#include <composite.h>
#include <stdproperties.h>

#include "../defs.h"

inherit M_ROOM_BASE;

inherit DG_OBJ_LIBS;

object oBlindMonk = 0;

//-------------------------------------------------------------------

string m_frescoes ();
void m_item_frescoes ();

//-------------------------------------------------------------------

void create_room ()
{
  set_short ("great hall north");
  set_long  ("Two great pillars of luminous green nephrite " +
             "frame the massive double wooden doors that " +
             "open to the outside. The high ceiling of " +
             "this hall is made from a lattice of dark " +
             "metal, through which pale light filters " +
             "and forms dappled patterns upon the floor. " +
             "Square tiles of rough stone make up the floor, " +
             "arranged with great precision. The hall continues " +
             "to the south. Through a wide archway " +
             "to the west, you can see many shelves lined " +
             "with tomes and scrolls. A narrower doorway " +
             "in the eastern wall opens onto a large spiral " +
             "stairwell that extends up and out of sight. " +
             "Inset into the east and west walls are tall " +
             "empty niches. " +
             m_frescoes () +
             dg_embed_livings ("hall_lower_south", " Standing in the south great hall, you see ", ".", "") +
             "\n");

  add_prop (ROOM_I_INSIDE, TRUE);

  add_exit ("lawn_ne", "north");
  add_exit ("stair_lower", "east");
  add_exit ("hall_lower_south", "south");
  add_exit ("library", "west");

  dg_add_entrance ("north", "You enter the great hall.");
  dg_add_entrance ("east", "You walk out of the stairwell into the great hall.");
  dg_add_entrance ("south", "You pass along the great hall, your footfalls making no noise on the smooth stone underfoot.");
  dg_add_entrance ("west", "You pass through the archway into the great hall.");

  dg_add_movement ("hall_upper_north", "You see movement through the grille floor in the great hall below.");

  add_item (({ "pillar", "pillars" }),
            "The pillars are enormous, reaching up to the " +
            "grand heights of the ceiling. They are made from " +
            "nephrite, a common, dull green jade, and their " +
            "polished surface is unadorned.\n" +
            dg_embed_action ("looks up at the grand nephrite pillars."));

  add_item (({ "ceiling", "lattice" }),
            "The ceiling high above your head is made from " +
            "a dark iron lattice, allowing pale light to " +
            "filter through and make dappled patterns of yellow " +
            "and white on the cold stone floor.\n" +
            dg_embed_action ("peers up at the lattice that makes up the ceiling."));

  add_item (({ "archway", "library", "west" }),
            "To the west is a wide stone archway, composed of the same " +
            "rough stone that makes up the floor. The arch is adorned " +
            "with bas relief images of books and scrolls. Through the " +
            "archway you can see a large library, whose shelves are " +
            "populated with scrolls and tomes.\n" +
            dg_embed_action ("peers east through the archway."));

  add_item (({ "tomes", "scrolls", "tome", "scroll", "book", "books", "shelves", "shelf" }),
            "You cannot make out any details of the library from here.\n");

  add_item (({ "door", "doorway" }),
            "It is a massive, curved wooden arch that leads out " +
            "to the windy lawn to the north. Its frame appears " +
            "to have once held strong doors, long since " +
            "removed.\n");

  m_item_floor_rough_tiles ();
  m_cmd_item_floor_rough_tiles ();

  m_item_frescoes ();

  reset_room ();
}


/*
 * Function name : m_frescoes
 *
 */

string m_frescoes ()
{
  string *asNames;
  string sFresco;
  int    iNames;

  asNames = m_get_council_members ();
  iNames = sizeof (asNames);

  switch (iNames)
  {
    case 0:
      sFresco = "The walls are grey and unadorned.";
      break;
    case 1:
      sFresco = "There is a single colorful fresco on the east wall.";
      break;
    default:
      sFresco = "There are " + LANG_WNUM (iNames) + " colorful frescoes " +
                "between the niches along the east and west walls.";
      break;
  };

  return (sFresco);
}


/*
 * Function name : m_item_frescoes
 *
 */

void m_item_frescoes ()
{
  string sCouncillor;
  string *asFrescoes;
  string *asNames;
  int    iName;

  asNames = m_get_council_members ();
  asFrescoes = ({ });

  switch (sizeof (asNames))
  {
    case 0:

      break;

    case 1:

      add_item (({ "fresco", asNames [0] }),
                "It's a colorful fresco, depicting " + LANG_ADDART (m_get_council_desc (asNames [0])) + ". " +
                "Below the fresco, '" + capitalize (asNames [0]) + "' " +
                "is inscribed in light etching.\n");

      break;

    default:

      for (iName = 0 ; iName < sizeof (asNames) ; iName ++)
      {
        sCouncillor = LANG_ADDART (m_get_council_desc (asNames [iName]));
        asFrescoes += ({ sCouncillor });
        add_item (({ asNames [iName],
                     "fresco " + LANG_WNUM (iName + 1),
                     LANG_WORD (iName + 1) + " fresco" }),
                  "It's a colorful fresco, depicting " + sCouncillor + ". " +
                  "Below the fresco, '" + capitalize (asNames [iName]) + "' " +
                  "is inscribed in light etching.\n");
      }

      add_item ("fresco",
                "There are " + LANG_WNUM (sizeof (asNames)) + " " +
                "frescoes adorning the wall, but you can " +
                "only look at one at a time.\n");

      add_item ("frescoes",
                "There are " + LANG_WNUM (sizeof (asNames)) + " " +
                "frescoes adorning the wall, showing the images of " +
                COMPOSITE_WORDS (asFrescoes) + ".\n");

      break;
  }
}

void reset_room ()
{
  // Clone the livings that populate the library.
  if (oBlindMonk == 0) oBlindMonk = dg_clone_here (M_PATH_NPC + "/regliak");
}

//-------------------------------------------------------------------

