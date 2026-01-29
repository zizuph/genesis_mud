/*******************************************************************\
| BALCONY_TEMPLE.C                                                  |
\*******************************************************************/

/*
 * 98/06/14 Cirion	Created
 * 02/05/01 Arandir	Ported to new area without rewrite
 * 03/04/25 Arandir     Polished up
 * 03/08/05 Arandir     Typofixed an extra newline
 * 03/12/19 Arandir     Typofixed long description
 *
 */

#include "../defs.h"

inherit M_ROOM_BASE;

//-------------------------------------------------------------------

void create_room ()
{
  set_short ("temple balcony");
  set_long ("This narrow balcony stands halfway up the eastern " +
            "wall of the massive, eerily lit temple. A small " +
            "doorway to the east enters into the southern " +
            "end of the upper hall. The edge of the balcony is " +
            "unprotected by any railing or guard.\n");

  add_exit ("hall_upper_south", "east");

  dg_add_entrance ("east",
                   "You walk out onto a narrow balcony " +
                   "that looks over the vast temple, giving you " +
                   "a feeling of vertigo.");

  add_item (({ "temple" }),
            "The great temple spreads down below, leading " +
            "westward to a vast statue of a noble dragon, at " +
            "the base of which lies a simple altar.\n");
  add_item (({ "dragon", "statue" }),
            "It is enormous, reaching up to the western part of " +
            "the ceiling, on the level with the balcony.\n");
  add_item (({ "altar" }),
            "It is simple, resting between the claws of the " +
            "statue.\n");
  add_item (({ "balcony", "ledge", "railing"}),
            "This is a very narrow, simple balcony looking out " +
            "over the great temple. The thick stone slab seems " +
            "unsupported from below.\n");
}

//-------------------------------------------------------------------

