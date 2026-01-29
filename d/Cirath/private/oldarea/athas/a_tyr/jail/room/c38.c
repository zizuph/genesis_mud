 /* /d/Cirath/athas/a_tyr/jail/room/c38
  * Outside the front entrance.
  * Decius, February 1996
  */

inherit "/std/room";
#include "defs.h"
#include "descs.h"

void
create_room()
{
  ::create_room();
  set_long(
    "Stone statues of noble lions flank this gravel path "+
    "leading south towards the most infamous of Tyr's landmarks: "+
    "Pandora's Tower. Once home to the King's High Templar, "+
    "the stone tower is now but a shell of it's former glory, "+
    "housing the city's jail and main barracks. "+
    "To the west you see an ebony statue marking Pandora's End.\n");

  set_short(
    "A gravel pathway outside Pandora's Tower");

  add_exit(TZ_JAIL+"room/c36.c","south",0,1);
  add_exit(TZ_SLAVE+"rd_pe_03","west",0,1);
}
