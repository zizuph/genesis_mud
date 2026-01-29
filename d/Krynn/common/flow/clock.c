/* Flowchart for the Clock of Krynn.
 */

#include "/d/Krynn/common/defs.h"
#include TIME_FLOW
#define  DEBUG(x)   find_living("boron")->catch_msg(x)
#define  CLOCK_FILE "/d/Krynn/common/clock/clock"
#define  CLOCK_RUN  5184000 /* 5 years */
#define  QUEST_MASTER  "/d/Krynn/common/quest_master"

/* This is the actual flowchart. It's a bipartite graph consisting of
 * events and periods. It should be complete!
 */
void
create_flow()
{
    ADD_EVENT("restart clock","clock runs", "restart_clock");
    ADD_PERIOD("clock runs", CLOCK_RUN,
           "restart clock", ({"restart clock"}));
    INIT_THIS_THREAD("restart clock");
}


/*
 * Function name: filter_krynn
 * Description:   Check and see if a player is anywhere with
 *                the world of Krynn.
 * Arguments:     pl - The player object
 * Returns:       True, false if not.
 */
static int
filter_krynn(object pl)
{
    object env = environment(pl);

    if (!env || !objectp(env))
        return 0;

    return (!(wildmatch("/d/Krynn/*", file_name(env)) |
              wildmatch("/d/Ansalon/*", file_name(env))) ? 0 :
          (!(env->query_prop(ROOM_I_INSIDE)) && !(env->query_no_time())));
}

/* Below follow the events */
void
restart_clock()
{
    object *oblist;

    /* at the end of the world we record the old state
     */
    "/d/Krynn/common/warfare/armymaster"->reset_warfare_state();

    /* then we reset the clock
     */
    (CLOCK_FILE)->reset_clock();

    /* trigger some stuff here in the domain and in other flowcharts.
     * INTERRUPT_PERIOD("kitiara","kitiara died");
     * INTERRUPT_PERIOD("verminaard","...");
     * etc.
     */
    INTERRUPT_PERIOD("kitiara","kitiara died");
    (QUEST_MASTER)->reset_quests_solved();

    /* Tell all players in Krynn/Ansalon a message */
    oblist = filter(users(), &filter_krynn());
    oblist->catch_msg("Suddenly, the world comes to a standstill.\n\n" +
              "Then, everything seems to blur and runs backwards " +
              "very fast.\n\nWhen things clear again, you feel the " +
              "world around has changed.\n");


    DEBUG("*TIME* Clock restarted.\n");
}

