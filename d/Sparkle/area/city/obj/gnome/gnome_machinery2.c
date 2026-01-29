/*
 *  /d/Sparkle/area/city/obj/gnome_machinery.c
 *
 *  This is some base code that can be used to create interworking
 *  machinery that passes effects along a chain of objects.
 *
 *  Created October 2008, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/object";

#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include "../../defs.h"


/* Global Variables */
public string      Forward_Movement = "";
public string      Fully_Forward = "";
public string      Backward_Movement = "";
public string      Fully_Backward = "";
public string      Long_Description = "This is your average,"
                                    + " run-of-the-mill piece of gnomish"
                                    + " machinery. It is utterly"
                                    + " nondescript.";
public string      Extra_Desc = ""; /* define if needed */
public string      Current_Activity = "f_backward"; /* default */
public object     *Next_Machine; /* What are the next machines triggered? */
public int         Immediate = 0;        /* True if we want this to trigger
                                          * the next machine as it moves,
                                          * rather than when it reaches its
                                          * fully_forward step. */
public float       Forward_Delay = 10.0; /* How long does it take the
                                          * machine to reach its fully_
                                          * forward state? Set to 0 if
                                          * indefinite movement. */
public float       Backward_Delay = 10.0;/* Same as above, but converse. */
public int         Do_Trigger = 1; /* False if we do not want this machine
                                    * to trigger anything. Default is true */
public int         Stop_Next = 0; /* True if the next machine should be
                                   * forced to the fully_* position when
                                   * this object reaches it. */

/* Prototypes */
public void        create_machine();
public nomask void create_object();
public string      describe();
public void        trigger_forward();
public void        trigger_f_forward();
public void        trigger_backward();
public void        trigger_f_backward();
public void        activate_next(string activ);

public void        set_forward(string s)       { Forward_Movement  = s; }
public void        set_f_forward(string s)     { Fully_Forward     = s; }
public void        set_backward(string s)      { Backward_Movement = s; }
public void        set_f_backward(string s)    { Fully_Backward    = s; }
public void        set_desc(string s)          { Long_Description  = s; }
public void        set_extra_desc(string s)    { Extra_Desc        = s; }
public void        set_activity(string s)      { Current_Activity  = s; }
public void        set_next_machine(object *o) { Next_Machine      = o; }
public void        set_immediate(int i)        { Immediate         = i; }
public void        set_f_delay(float f)        { Forward_Delay     = f; }
public void        set_b_delay(float f)        { Backward_Delay    = f; }
public void        set_do_trigger(int i)       { Do_Trigger        = i; }
public void        set_stop_next(int i)        { Stop_Next         = i; }

public string      query_activity()   { return Current_Activity;  }
public string      query_forward()    { return Forward_Movement;  }
public string      query_f_foward()   { return Fully_Forward;     }
public string      query_backward()   { return Backward_Movement; }
public string      query_f_backward() { return Fully_Backward;    }
public int         query_do_trigger() { return Do_Trigger;        }
public int         query_immediate()  { return Immediate;         }
public object *    query_next_mach()  { return Next_Machine;      }


/*
 * Function name:        create_machine
 * Description  :        dummy routine for inheriting objects 
 */
public void
create_machine()
{
} /* create_machine */


/*
 * Function name:        create_object
 * Description  :        set up the object
 */
public nomask void
create_object()
{
    set_name("machinery");
    add_name( ({ "machine", "_gnome_machinery" }) );

    add_adj( ({ "gnome", "gnomish" }) );

    set_short("non-descript machinery");
    set_long("@@describe@@");

    add_prop(OBJ_M_NO_GET, "It is rather fixed in place, hopefully your"
      + " tugging on it hasn't loosened any of the workings!\n");
    add_prop(OBJ_I_WEIGHT, 50000);
    add_prop(OBJ_I_VOLUME, 70000);

    create_machine();
} /* create_object */


/*
 * Function name:        describe
 * Description  :        Create a long description that includes the
 *                       current activity of the machinery.
 */
public string
describe()
{
    string  desc,
            connected = "";

    switch (Current_Activity)
    {
        case "moving_forward":
            desc = Forward_Movement;
            break;
        case "f_forward":
            desc = Fully_Forward;
            break;
        case "moving_backward":
            desc = Backward_Movement;
            break;
        default:
            desc = Fully_Backward;
            break;
    }

    if (sizeof(Next_Machine))
    {
        connected = " It appears to be connected to the "
          + Next_Machine[0]->short() + ".";
    }

    return Long_Description + connected + " It is currently " + desc + ".\n";
} /* describe */


/*
 * Function name:        trigger_forward
 * Description  :        When called, this causes the machinery to
 *                       enter Forward_Movement setting, which will
 *                       stop after the Forward_Delay time and enter the
 *                       fully_forward setting unless there is an
 *                       indefinite movement indicated by a 0 value for
 *                       Forward_Delay.
 */
public void
trigger_forward()
{
    tell_room(environment(this_object()), capitalize(
        LANG_THESHORT(this_object()) + " begins " + Forward_Movement
      + ".\n"));
    Current_Activity = "moving_forward";

    if (Immediate) /* Should this immediately trigger the next machine? */
    {
        if (sizeof(Next_Machine) && Do_Trigger) /* Is there a Next_Machine? */
        {
            activate_next("forward");
        }
    }

    if (Forward_Delay) /* Does this movement eventually end? */
    {
        set_alarm(Forward_Delay, 0.0, &trigger_f_forward());
    }
} /* trigger_forward */


/*
 * Function name:        trigger_f_forward
 * Description  :        Called when the machine has reached its fully
 *                       forward state. If Immediate was set to 0, then
 *                       it is at this time that the Next_Machine is
 *                       triggered to begin forward_movement.
 */
public void
trigger_f_forward()
{
    tell_room(environment(this_object()), capitalize(
        LANG_THESHORT(this_object()) + " stops moving, and is now "
      + Fully_Forward + ".\n"));
    Current_Activity = "f_forward";

    if (Stop_Next) /* Should the Next_Machine be f_forward now? */
    {
        activate_next("f_forward");
    }
    else if (!Immediate && Do_Trigger) /* Should the Next_Machine
                                        * trigger now? */
    {
        activate_next("forward");
    }

} /* trigger_f_forward */


/*
 * Function name:        trigger_backward
 * Description  :        When called, this causes the machinery to
 *                       enter Backward_Movement setting, which will
 *                       stop after the Backward_Delay time and enter the
 *                       fully_backward setting unless there is an
 *                       indefinite movement indicated by a 0 value for
 *                       Backward_Delay.
 */
public void
trigger_backward()
{
    tell_room(environment(this_object()), capitalize(
        LANG_THESHORT(this_object()) + " begins " + Backward_Movement
      + ".\n"));
    Current_Activity = "moving_backward";

    if (Immediate && Do_Trigger) /* Should this immediately trigger
                                  * the next machine? */
    {
        if (sizeof(Next_Machine)) /* Is there a Next_Machine? */
        {
            activate_next("backward");
        }
    }

    if (Backward_Delay) /* Does this movement
                         * eventually end? */
    {
        set_alarm(Backward_Delay, 0.0, &trigger_f_backward());
    }
} /* trigger_backward */


/*
 * Function name:        trigger_f_backward
 * Description  :        Called when the machine has reached its fully
 *                       backward state. If Immediate was set to 0, then
 *                       it is at this time that the Next_Machine is
 *                       triggered to begin backward_movement.
 */
public void
trigger_f_backward()
{
    tell_room(environment(this_object()), capitalize(
        LANG_THESHORT(this_object()) + " stops moving, and is now "
      + Fully_Backward + ".\n"));
    Current_Activity = "f_backward";



    if (Stop_Next) /* Should the Next_Machine be f_backward now? */
    {
        activate_next("f_backward");
    }
    else if (!Immediate && Do_Trigger) /* Should the Next_Machine
                                        * trigger now? */
    {
        activate_next("backward");
    }
} /* trigger_f_backward */


/*
 * Function name:        activate_next
 * Description  :        have the next machine(s) do something
 * Arguments    :        string activ - what do we want it to do?
 */
public void
activate_next(string activ)
{
    if (!sizeof(Next_Machine))
    {
        return 0;
    }

    foreach (object next_m: Next_Machine)
    {
        switch(activ)
        {
            case "forward":
                next_m->trigger_forward();
                break;
            case "f_forward":
                next_m->trigger_f_forward();
                break;
            case "backward":
                next_m->trigger_backward();
                break;
            case "f_backward":
                next_m->trigger_f_backward();
                break;
        }
    }
} /* activate_next */