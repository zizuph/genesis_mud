/*******************************************************************\
| PERCH_0_0.C                                                       |
\*******************************************************************/

/*
 * 03/07/21 Arandir     Created
 * 03/07/23 Arandir     Added a hint about touching
 *
 */

#include "../defs.h"

inherit CC_ROOM_PERCH_BASE;

//-------------------------------------------------------------------

void create_room ()
{
  cc_create_perch (
    0, 0,
    "carrying a relief of a massive cavern hewn from sparkling ice and " +
    "silver-veined stone, littered with scales and bones mixed with a " +
    "great deal of ash. Marvelling at the realism of the relief, you " +
    "feel a sudden compulsion to touch it.",
    "carrying a relief of a massive cavern hewn from ice and stone. The relief " +
    "is dominated by a shimmering shape of a black dragon, ancient and mighty " +
    "in appearance. Marvelling at the realism of the relief, you feel a " +
    "sudden compulsion to touch it.",
    "terel black dragon",
    "The shimmering shape of the black dragon is amazingly detailed, from " +
    "leathery wings to huge and sharp claws, but what compels you most are " +
    "its eyes. They lend the shape a feeling of life and evil, so strong that " +
    "it sends a shiver down your spine.");
}

//-------------------------------------------------------------------

