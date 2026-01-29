/*
 *     Stage definitions for the War in Rohan.
 *
 *     ROHAN_STAGE_PEACE,                                   0
 *    (RQ_GANDALF_IN_BAGEND,		3018, Apr 12th.) (  1)
 *    (RQ_OSGILIATH_ATTACK,		3018, Jun 20th.) (  5)
 *     ROHAN_STAGE_PEACE_END,                 ????          9
 *     ROHAN_STAGE_GANDALF_CAPTIVE,     3018, Jul  1st.    10
 *     ROHAN_STAGE_HOSTILE,             3018, Jul  1st.    10
 *     ROHAN_STAGE_GANDALF_ESCAPED,     3018, Sep 20th.    20
 *    (RQ_LEFT_HOBBITON,		3018, Sep 23rd.) ( 10)
 *    (RQ_ARRIVED_IN_RIVENDELL, 	3018, Oct 20th.) ( 18)
 *    (RQ_LEFT_RIVENDELL,		3018, Dec 25th.) ( 20)
 *    (RQ_ARRIVED_IN_LOTHLORIEN,	3019, Jan 16th.) ( 28)
 *    (RQ_LEFT_LOTHLORIEN,		3019, Feb 16th.) ( 30)
 *     ROHAN_STAGE_HOSTILE_END,                            59
 *     ROHAN_STAGE_WAR,                 3019, Feb 25th.    60
 *     ROHAN_STAGE_WAR_END,                                69
 *     ROHAN_STAGE_BATTLE,              3019, Mar  2nd.    70
 *     ROHAN_STAGE_BATTLE_END,                             99
 *     ROHAN_STAGE_DEFEAT,              3019, Mar  4th.   100
 *     ROHAN_STAGE_VICTORY,             3019, Mar  4th.  1000
 *    (RQ_LEFT_HENNETH_ANNUN,		3019, Mar  8th.) ( 40)
 *    (RQ_ENTERED_MORDOR,		3019, Mar 15th.) ( 50)
 *    (RQ_QUEST_ENDED,			3019, Mar 25th.) (100)
 */
#ifndef GONDOR_ROHAN_STAGE_DEFS
#define GONDOR_ROHAN_STAGE_DEFS
#include "/d/Gondor/common/lib/clock.h"

#define ROHAN_STAGE_PEACE              0
#define ROHAN_STAGE_PEACE_END          9
#define ROHAN_STAGE_HOSTILE           10
#define ROHAN_STAGE_GANDALF_CAPTIVE   10
#define ROHAN_STAGE_GANDALF_ESCAPED   20
#define ROHAN_STAGE_HOSTILE_END       59
#define ROHAN_STAGE_WAR               60
#define ROHAN_STAGE_WAR_END           69
#define ROHAN_STAGE_BATTLE            70
#define ROHAN_STAGE_BATTLE_END        99
#define ROHAN_STAGE_DEFEAT           100 
#define ROHAN_STAGE_VICTORY         1000
#endif
