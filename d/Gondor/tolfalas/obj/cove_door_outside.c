/*
 * /d/Gondor/tolfalas/obj/cove_door_out.c
 *
 *  Toby - 28 Aug 2006
 *
 *  The cave in the secret cove on Tolfalas
 *  'home' for the rowboat of the Black Numenorean
 *
 *  Modification log:
 */

inherit "/std/door";

#include "/d/Gondor/defs.h"

#pragma strict_types

void
create_door()
{
   set_door_id("iron");
   set_pass_command(({"in", "west"}));
   set_door_name(({"door","heavy door","heavy iron door","iron door"}));
   set_open_desc("Bolted into the wall is a heavy iron door that stand " +
                 "open. The door is blackened to blend in well with the " +
                 "wall of the cliff, it will take you inside what must be a cave.\n");
   set_closed_desc("Bolted into the wall is a heavy iron door that is " +
                   "closed. The door is blackened to blend in well with the " +
                   "wall of the cliff, it will take you inside what must be a cave.\n");
   set_other_room(TOLFALAS_DIR + "room/cove_cave01");
   set_fail_pass("The heavy door is closed, maybe you should open it?\n");
   set_open(0);
   set_str(25);
}
