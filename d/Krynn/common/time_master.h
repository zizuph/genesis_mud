/* These macros give access to the time_master.
 * Npcs, events, etc. should define their own flowchart in the
 * time_master.
 */

/* Help function to the name of a thread out of a pathname */
#include <macros.h>
#define PATH_ARRAY             explode(MASTER,"/")
#define FILENAME               PATH_ARRAY[sizeof(PATH_ARRAY)-1]


/* The master object these macros are applied to */
#define TIME_MASTER  "/d/Krynn/common/time_master"


/* Function name: ADD_EVENT
 * Arguments:     name   - name of the event.
 *                period - name of period following the event.
 *                event  - name of a function to call as event.
 * Description:   adds an event to the list.
 */
#define ADD_EVENT(name, period, event)                (TIME_MASTER)->add_time_event(name, period, event)

/* Function name: ADD_UNIQUE_EVENT
 * Arguments:
 * Description:
 */
//#define ADD_UNIQUE_EVENT(name, when, event)           (TIME_MASTER)->add_unique_event(name, when, event)
#define ADD_UNIQUE_EVENT(name, when, event)           ("/d/Krynn/common/clock/clock")->add_event(name, when, event)

/* Function name: ADD_PERIOD
 * Arguments:     name      - name of the period.
 *                length    - either (int) length of period
 *                            or (array)({a,b}) with length = a + random(b).
 *                event     - default event following end of period.
 *                interrupts- list of events that can end this period prematurely.
 * Description:   adds a period to the list.
 */
#define ADD_PERIOD(name, length, event, interrupts)   (TIME_MASTER)->add_time_period(name, length, event, interrupts)

/* Function name: CURRENT_PERIOD
 * Description:   get the name of the current period.
 * Returns:       name of the current period.
 */
#define CURRENT_PERIOD(thread)                        (TIME_MASTER)->query_current_period(thread)

/* Function name: INIT_THREAD, INIT_THIS_THREAD
 * Arguments:     name  - name of the thread (usually npc name).
 *                event - begin thread with this event.
 * Description:   If there is no thread 'name' running, start it with event.
 *                otherwise ignore. (The only way to change running threads
 *                is by using INTERRUPT_PERIOD).
 *
 * Note:          INIT_THIS_THREAD takes the filename of TO as the name
 *                argument. This used be normally used!
 */
#define INIT_THREAD(name, event)                      (TIME_MASTER)->init_thread(name, event)
#define INIT_THIS_THREAD(event)                       (TIME_MASTER)->init_thread(FILENAME, event)

/* Function name: END_THREAD
 * Arguments:     name - name of the thread (usually npc name).
 * Description:   Stop a thread (and it's period). Normally there should be no
 *                need to call this!
 */
#define END_THREAD(name)                              (TIME_MASTER)->end_thread(name)

/* Function name: INTERRUPT_PERIOD
 * Arguments:     thread - interrupt period of thread.
 *                event  - continue thread with event.
 * Description:   Interrupting a period only works when the given 'event' is
 *                allowed by the interrupt list. Otherwise ignore interrupt!
 * Returns:       1: interrupted, 0: ignored.
 */
#define INTERRUPT_PERIOD(thread, event)               (TIME_MASTER)->handle_interrupt(thread, event)


/* Special info for each flowchart. This is saved over reboots
 * in case some things need to be remembered, such as the position
 * of an npc.
 */
#define STORE_SPECIAL_INFO(info)              (TIME_MASTER)->store_special_thread_info(FILENAME, info)
#define QUERY_SPECIAL_INFO()                  (TIME_MASTER)->query_special_thread_info(FILENAME)
