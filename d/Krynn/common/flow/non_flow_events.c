/* non_flow_events
 *
 * Aridor, 12/20/95
 *
 * This is a special file which defines all the specific events
 * which are not connected to the actual time flow.
 * Events which should take place at specific times and dates or
 * which should take place in regular intervals should be placed
 * into this file.
 * Examples: -An npc which appears in a certain place for the night
 *            but is not around during the day.
 *           -An avalanche which closes off an exit fairly regularly.
 *            (And the flood which washes the exit free again).
 *           ...
 */

#include "/d/Krynn/common/defs.h"
#include TIME_FLOW
#define  DEBUG(x)  find_living("aridor")->catch_msg(x + "\n");

void
create_flow()
{
  //ADD_UNIQUE_EVENT("dragon_quest_out","*.*.*@6:00","move_dragon_out_of_cave");
  //ADD_UNIQUE_EVENT("dragon_quest_in","*.*.*@20:00","move_dragon_into_cave");


}
/* DON'T ADD ANYTHING HERE YET. IT JUST WON'T WORK :) */



