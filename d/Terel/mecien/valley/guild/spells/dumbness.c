/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
/*
 * Clone and move this object to a player if you want to make the
 * player dumb for a while.
 *
 * Made by Mortricia using Nick's /std/paralyze.c
 */
inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>

#define STD_TIME     90          /* Default duration */
#define STD_SAY_CMDS ({"say",\
                       "'",\
                       "rsay",\
                       "shout",\
                       "whisper",\
                       "scream",\
                       "laugh",\
                       "giggle",\
                       "ms",\
                       "mumble",\
                       "ponder",\
                       "think",\
                       "whistle",\
                       "sing",\
                       "ask"})

/*
 * Variables
 */
string stop_fun,      /* What function to call when stopped      */
       fail_message,  /* Message to write when command failed    */
       stop_message;  /* Message to write when dumbness ceased   */
object caster;        /* Who did this awful thing to me?         */
string *shadow_cmds;  /* What cmds will be prohibited?           */
int    remove_time;   /* The duration of this dumbness           */
object stop_object;   /* Object to call stop_fun in when stopped */

/*
 * Prototypes
 */
public void set_standard_dumbness();
public void stop_dumbness();
public void set_shadow_cmds(string *str);
public void set_caster(object ob);
public void set_stop_fun(string fun);
public void set_stop_object(object ob);
public void set_fail_message(string message);
public string *query_shadow_cmds();
public string query_caster();
public string query_stop_fun();
public object query_stop_object();
public string query_fail_message();

/*
 * Function name: create_dumbness
 * Description:   Set up standard dumbness
 */
public void
create_dumbness()
{
    set_standard_dumbness();
}

/*
 * Function name: create_object
 * Description:   The standard create routine.
 */
nomask void
create_object()
{
    set_no_show();
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
    add_prop(OBJ_M_NO_SELL, 1);

    create_dumbness();
}

/*
 * Function name: alt_say
 * Description:   Here all prohibited commands the player gives comes.
 * Argument:      str - The extra string the player sent.
 */
public varargs int
alt_say(string str)
{
    /* Only dumb in this object's environment */
    if (environment(this_object()) != this_player())
        return 0;

    if (fail_message)
        this_player()->catch_msg(query_fail_message());

    if (!this_player()->query_wiz_level()) return 1;

    write("However, being wizard this dumbness won't affect you at all.\n");
    return 0;
}

/*
 * Function name: init
 * Description:   Called when meeting an object
 */
public void
init()
{
    int i;

    ::init();
    
    if (remove_time)
        set_alarm(itof(remove_time), -1.0, stop_dumbness);

    for (i=0; i<sizeof(shadow_cmds); i++)
        add_action(alt_say, shadow_cmds[i], 1);
        
    if (this_player()->query_wiz_level())
        return;

    this_player()->add_prop(LIVE_M_MOUTH_BLOCKED, query_fail_message());
}

/*
 * Description: Set function to call when dumbness stops.
 */
public void set_stop_fun(string fun) { stop_fun = fun; }

/*
 * Description: Returns the function to call when dumbness stops
 */
public string query_stop_fun() { return stop_fun; }

/*
 * Description: Set which object to call the stop function in
 */
public void set_stop_object(object ob) { stop_object = ob; }
/*
 * Description: Returns which object to call the stop function in.
 */
public object query_stop_object() { return stop_object; }

/*
 * Description: Set the fail message when player tries to do something
 */
public void set_fail_message(string message) { fail_message = message; }

/*
 * Description: returns the fail message when player tries to do something
 */
public string query_fail_message()
{
    return check_call(fail_message, this_player());
}

/*
 * Description: Set how long time player should be dumb.
 */
public void set_remove_time(int time) { remove_time = time; }

/*
 * Description: Returns the dumbness duration time
 */
public int query_remove_time() { return remove_time; }

/*
 * Description: Set the message written when dumbness stops.
 */
public void set_stop_message(string message) { stop_message = message; }

/*
 * Description: Returns the message written when dumbness stops.
 */
public string query_stop_message() { return stop_message; }

/*
 * Function name: set_shadow_cmds
 * Description:   Set up which cmds that will be prohibited (e.g. say, rsay)
 * Arguments:     str - String array to hold the commands
 */
public void set_shadow_cmds(string *str) { shadow_cmds = str; }

/*
 * Function name: query_shadow_cmds
 * Description:   Return the cmds that are shadowed by this object
 * Arguments:     ---
 */
public string *query_shadow_cmds() { return shadow_cmds; }

public void set_caster(object ob) { caster = ob; }

public string
query_caster()
{
    if (caster) return QTNAME(caster);
    return "someone";
}

/*
 * Function name: set_standard_dumbness
 * Description:   Set up standard settings for a dumbness
 * Argumnets:     ---
 */
public void
set_standard_dumbness()
{
    set_stop_message("You stop being dumb.\n");
    set_fail_message("You have been cursed into dumbness by " +
                     query_caster() + ". You cannot do that right now.\n");
    set_shadow_cmds(STD_SAY_CMDS);
    set_remove_time(STD_TIME);
}

/*
 * Function name: stop_dumbness
 * Description:   This function is called if the dumbness shall stop due to
 *                the time running out.
 */
public void
stop_dumbness()
{
    if (stop_object && stop_fun && function_exists(stop_fun, stop_object))
        call_other(stop_object, stop_fun, environment(this_object()));
    else if (stop_message && environment(this_object()))
        environment(this_object())->catch_msg(stop_message);

    if (environment(this_object()))
        environment(this_object())->remove_prop(LIVE_M_MOUTH_BLOCKED);
    
    this_object()->remove_object();
}

/*
 * Description: Function called when wiz tries to stat this object.
 */
string
stat_object()
{
    int i;
    string str;

    str = ::stat_object();

    if (sizeof(shadow_cmds)) {
        str += "Sh. cmds:  ";
        for (i=0; i<sizeof(shadow_cmds); i++) {
            str += shadow_cmds[i] + " ";
        }
        str += "\n";
    }
    if (strlen(stop_fun))
        str += "Stop fun:  " + stop_fun + "\n";
    if (strlen(stop_message))
        str += "Stop mess: " + stop_message + "\n";
    if (strlen(fail_message))
        str += "Fail mess: " + query_fail_message() + "\n";
    if (remove_time)
        str += "Duration:  " + remove_time + "\n";
    if (stop_object)
        str += "Stop obj:  " + file_name(stop_object) + "\n";
    if (caster)
        str += "Caster:    " + caster->query_real_name() + "\n";

    return str;
}
