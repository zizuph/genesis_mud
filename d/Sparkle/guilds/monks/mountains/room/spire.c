/*******************************************************************\
| SPIRE.C                                                           |
\*******************************************************************/

/*
 * 20/08/06 Lucius      Reset herbs
 * 06/09/24 Arandir     Connected to the catacomb rings
 * 06/09/17 Arandir     Added herbs
 * 02/07/27 Arandir	Created
 *
 */

#include <tasks.h>

#include "../defs.h"

inherit MT_ROOM_BASE;

inherit DG_CLOCK_LIBS;

//-------------------------------------------------------------------

string dg_long ();

//-------------------------------------------------------------------

/*
 * Function name : reset_room
 */

void reset_room ()
{
    set_searched(0);
}

/*
 * Function name : create_room
 *
 */

void create_room ()
{
  ::create_room ();
  set_short ("halfway up a tall spire");
  set_long  (&dg_long ());

  dg_add_herbs (DG_HERBS_CLIFFS);

  dg_add_climb (DG_PATH + "/monastery/room/lawn_ne",
                ({"up", "slope up", "spire up", "cliff up" }), TASK_ROUTINE,
                "You climb up the spire.",
                "climbs up the spire.",
                "arrives climbing up the spire.",
                "You try to climb up the spire but fail.",
                "tries to climb up the spire but fails.");

  dg_add_climb ("spikes_12",
                ({"down", "slope down", "spire down", "cliff down" }), TASK_ROUTINE,
                "You climb down the spire.",
                "climbs down the spire.",
                "arrives climbing down the spire.",
                "You try to climb down the spire but fail.",
                "tries to climb down the spire but fails.");

  add_cmd_item ("ledge", "climb", "Which ledge would you climb ?\n");

  dg_add_climb (DG_PATH + "/catacombs/room/ring_0",
                ({"east ledge", "eastern ledge", "ledge east" }), TASK_DIFFICULT,
                "You climb on the ledge east of you.",
                "climbs east.",
                "arrives climbing from a nearby crevice.",
                "You try to reach the eastern ledge but fail.",
                "tries to climb east but fails.");

  dg_add_climb (DG_PATH + "/catacombs/room/ring_8",
                ({"west ledge", "western ledge", "ledge west" }), TASK_DIFFICULT,
                "You climb on the ledge west of you.",
                "climbs west.",
                "arrives climbing from a nearby crevice.",
                "You try to reach the western ledge but fail.",
                "tries to climb west but fails.");

  dg_item_sky_outside ();

  mt_item_spire_near_climbable ();

  add_item (({ "crevice", "cliff", "spire" }),
            "You are resting in a comfortable spot formed by a " +
            "crevice in the steep side of the spire. Two " +
            "ledges seem to be just within your reach " +
            "both to the east and to the west.\n");

  add_item (({ "ledge", "ledges", "east ledge", "west ledge" }),
            "To the east and west and slightly below your position, " +
            "two wide ledges protrude from the side of the cliff.\n");

  add_item (({ "structure", "building" }),
            "It appears that some sort of a stone building is perched " +
            "atop the spire, but it is difficult to tell any details " +
            "from your position.\n");
}

/*
 * Function name : dg_long
 *
 */

string dg_long ()
{
  string sDesc;

  sDesc = "You are standing in an almost comfortable crevice " +
          "halfway up a tall spire. The steep side of the spire " +
          "provides shelter from wind.";

  if (dg_is_night ()) sDesc +=
    " The abundance of support for your hands and feet makes the " +
    "climb possible even in the dark, although you do have to " +
    "strain to see any sort of guidance at all. The only thing " +
    "that reassures you about your progress is a faint light " +
    "atop the spire.";
  else sDesc +=
    " Having passed the level of clouds, you cannot see as much " +
    "of the mountains below as you would like, but the glitter " +
    "of the peaks protruding through the white mist is still a " +
    "sight to behold. You can also see some sort of a stone " +
    "structure atop the spire.";

  sDesc += "\n";
  return (sDesc);
}

//-------------------------------------------------------------------

