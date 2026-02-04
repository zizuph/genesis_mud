/* yes_no.c created by Shiva@Genesis.
 *
 * use this object to catch a response to a yes-or-no question.
 * simply clone this object and call get_answer (see function below)
 * in it.  This object will in turn call a specified function with
 * an integer argument (1 = answer was "yes", 0 = answer was "no",
 * -1 = no answer given)
 *
 * Example of usage:
 *
 *   int some_func()
 *   {
 *     ...some code...
 *     write("Are you sure? (Yes / No)");
 *
 *     ob = clone_object("/d/Emerald/lib/yes_no");
 *     ob->get_answer(response, 20.0);
 *
 *     ...some code...
 *   }
 *
 *   void response(int answer)
 *   {
 *     if (answer > 0)
 *     {
 *       // answer was "yes"!
 *     }
 *     else if (answer < 0)
 *     {
 *       // no answer received
 *     }
 *     else // answer == 0
 *     {
 *       was "no"!
 *     }
 *   }
 *
 * Note:
 *   information can be passed back to the original object through
 *   get_answer.  For instance, if you want to pass the name of the 
 *   person who is asking a question back to the above object, use
 *   
 *   name = this_player()->query_name();
 *   ob->get_answer(&response(name), 20.0);
 *
 *   now the variable "name" will be passed as the first argument
 *   to the function "response", and the integer corresponding to the
 *   answer will be the second argument.
 */

inherit "/std/object";

#include <stdproperties.h>

static function replied_func;

void create_object()
{
    set_name("yes_no_object");
    set_no_show();
  
    remove_prop(OBJ_I_WEIGHT);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_VALUE);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_M_NO_GET, 1);
}

/* Function name: time_out
 * Description:   Remove this object.
 *                Calls the specified reply-function with -1 as the 
 *                argument corresponding to the answer (no response).
 * Arguments:     None
 * Returns:       None
 */
void time_out()
{
    replied_func(-1);
    remove_object();
}

/* Function name: get_answer
 * Description:   Moves this object to a target, and attempts to
 *                catch a yes-or-no response.
 * Arguments:   - object target - the object from which to get the answer.
 *              - function func - the function to be called with the
 *                    response as an argument.  The response is specified
 *                    with an integer value (1 = "yes"-response,
 *                                           0 = "no"-response,
 *                                          -1 = no response at all).
 *              - float timeout - time in seconds before this object
 *                    will time out (object removed and -1 response
 *                    returned).  If no timeout is specified, the object
 *                    will not timeout.
 * Returns:       True if object successfully set up to receive answer,
 *                False if not (object removed).
 */
varargs int get_answer(object target, function func, float timeout)
{
    if (move(target, 1))
    {
        remove_object();
        return 0;
    }
  
    if (!target || !func)
    {
        remove_object();
        return 0;
    }
  
    replied_func = func;
  
    if (!timeout)
    {
        timeout = 10.0;
    }

    if (timeout > 0.0)
    {
        set_alarm(timeout, 0.0, time_out);
    }
  
    return 1;
}

/* Function name: catch_all
 * Description:   Catch all commands entered by the player.
 *                Looks for a yes-or-no response.
 * Arguments:     string str - trailing part of a command
 * Returns:       True  - yes-or-no response found
 *                False - other command
 */
static int catch_all(string str)
{
    string cmd = query_verb();
  
    if (strlen(str))
    {
        return 0;
    }
  
    switch (cmd)
    {
        case "Y":
        case "y":
        case "Yes":
        case "yes":
        case "YES":
            replied_func(1);
            remove_object();
            return 1;
        case "N":
        case "n":
        case "No":
        case "no":
        case "NO":
            replied_func(0);
            remove_object();
            return 1;
        default:
            return 0;
    }
}

/* Function name: reset_object
 * Description:   Check every once in a while to see that 
 *                this object is still needed.
 */
void reset_object()
{
    if (!environment() || !living(environment()))
    {
        remove_object();
    }
}

/* Function name: init
 * Description:   Initialize this object.  
 */ 
void init()
{
    if (!living(environment()))
    {
        remove_object();
        return;
    }
  
    ::init();
  
    if (environment() != this_player())
    {
        return;
    }
  
    add_action(catch_all, "", 1);
}
