/*
 * A candle, some code stolen from Nosferatu, the rest made by Nick
 * May 30, 1992
 * Modified by Mortricia, May 1996 (call_outs -> alarms)
 */
inherit "/std/object";

#include <stdproperties.h>      /* All prop definitions */
#include <macros.h>             /* QCTNAME and QTNAME macro */
#include <language.h>

#define MAXTIME 400             /* How long will the candle burn? */
#define WHAT    "candle"
#define PWHAT   "candles"
#define ADJ     "long"

int time_left = MAXTIME;        /* How much time is left? */
int aid = 0;                    /* Alarm id               */

/*
 * Function name: create_object
 * Description:   The standard create routine.
 */
public void
create_object()
{
    set_name(WHAT);
    set_pname(PWHAT);
    set_short("@@my_short");       /* Different short desc if lit. */
    set_pshort("@@my_pshort");     /* Different plural short desc if lit. */
    set_adj(ADJ);
    set_long("@@my_long");         /* Different long desc if lit. */
    add_prop(OBJ_I_LIGHT, 0);
    add_prop(OBJ_I_WEIGHT, "@@my_weight");
    add_prop(OBJ_I_VOLUME, "@@my_volume");
    add_prop(OBJ_I_VALUE,  "@@my_value"); /* Value depends on usefulness. */
}

/*
 * Function name: my_weight
 * Description:   A VBFC gets here when someone wants to know the weight of
 *                this object.
 * Returns:       The weight
 */
public int
my_weight()
{
    int t = time_left;

    if (aid)
        t = ftoi(get_alarm(aid)[2]);

    return (t * 243) / MAXTIME + 7;
}

/*
 * Function name: my_volume
 * Description:   A VBFC gets here when someone wants to know the volume of
 *                of this object.
 * Returns:       The volume
 */
public int
my_volume()
{
    int t = time_left;

    if (aid)
        t = ftoi(get_alarm(aid)[2]);

    return (t * 390) / MAXTIME + 10;
}

/*
 * Function name: my_value
 * Description:   A VBFC gets here when someone wants to know
 *                the value of this object.
 * Returns:       The value
 */
public int
my_value()
{
    int t = time_left;

    if (aid)
        t = ftoi(get_alarm(aid)[2]);

    return (t * 30) / MAXTIME + 5;
}

/*
 * Function name: my_short, my_pshort, my_long
 * Description:   We change the short, plural short and long description of
 *                the candle if it's lit.
 * Returns:       The description.
 */
public string
my_short()
{
    string str = ADJ + " " + query_name();
    
    if (aid) {
        return "burning " + str;
    } else {
        return str;
    }
}

public string
my_pshort()
{
    string str = ADJ + " " + query_pname();
    
    if (aid) {
        return "burning " + str;
    } else {
        return str;
    }
}

public string
my_long()
{
    string str;

    str = "It is a very simple looking " + query_name() + ".";
    if (aid)
        str += " It is lit.";
    return str + "\n";
}

/*
 * Function name: burned_out
 * Description:   If this function is called the candle has burned out.
 */
public void
burned_out()
{
    object ob = environment();

    add_prop(OBJ_I_LIGHT, 0);
    remove_adj("burning");
    time_left = 0;
    aid = 0;

    if (!ob)
        return;

    if (living(ob))
    {
        tell_object(ob, "Your " + short() + " goes out.\n");
        tell_room(environment(ob), "The " + short() + " " + QTNAME(ob) +
                  " is holding goes out.\n", ob);
    }
    else
        tell_room(ob, "The " + short() + " goes out.\n");
}

/*
 * Function name: do_light
 * Description:   The player tries to light something.
 * Arguments:     str - the string describing what he  wants to light.
 * Returns:       1/0
 */
public int
do_light(string str)
{
    object ob;

    /* Is it this candle he's trying to light or something else? */
    notify_fail("Light what?\n");
    if (!parse_command(str, environment(), "%o", ob) ||
        ob != this_object())
        return 0;


    if (!time_left)
    {
        write("You try to light your " + short() + " but fail... This " +
              short() + " is useless!\n");
        return 1;
    }

    if (aid)
    {
        write("Your " + query_name() + " is already lit.\n");
        return 1;
    }

    write("Ok.\n");
    say(QCTNAME(this_player()) + " lights " + LANG_ADDART(short()) +
        ".\n");
        
    add_prop(OBJ_I_LIGHT, 1);
    add_adj("burning");
    aid = set_alarm(itof(time_left), -1.0, burned_out);
    
    return 1;
}

/*
 * Function name: do_extinguish
 * Description:   The player tries to extinguish something
 * Arguments:     str - The string describing what to extinguish
 * Returns:       1/0
 */
public int
do_extinguish(string str)
{
    object ob;

    /* Is it this candle he tries to extinguish? */
    notify_fail("Extinguish what?\n");
    if (!parse_command(str, environment(), "%o", ob) ||
        ob != this_object())
        return 0;

    if (!aid)
    {
        write("Your " + short() + " isn't lit.\n");
        return 1;
    }

    add_prop(OBJ_I_LIGHT, 0);
    remove_adj("burning");
    time_left = ftoi(get_alarm(aid)[2]);
    remove_alarm(aid);
    aid = 0;
    write("Ok.\n");
    say(QCTNAME(this_player()) + " extinguishes " + LANG_ADDART(short()) +
        ".\n");
    return 1;
}

/*
 * Function name: query_can_light
 * Description:   Allows the servant to check if the candle can be lit.
 * Returns:       int time_left, 0 if can't be lit
 */
public int
query_can_light()
{
    if (aid) {
        return 0;
    }
    return time_left;
}

/*
 * Function name: init
 * Description:   Here we add some commands to the player.
 */
public void
init()
{
    ::init();
    add_action(do_light,      "light");
    add_action(do_extinguish, "extinguish");
}
