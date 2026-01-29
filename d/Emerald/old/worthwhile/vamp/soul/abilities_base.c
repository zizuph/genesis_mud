#pragma save_binary
#pragma strict_types
#pragma no_shadow

inherit "/cmd/std/command_driver";

#include "../guild.h"
#include "abilities.h"
#include <stdproperties.h>

/* Maps command names to indices in the cmd_info mapping.  This is done so
 * that information doesn't need to be stored multiple times for commands
 * which map to the same command info ("telepath" and "tpath", for example).
 */
static mapping cmd_to_index = ([]);

#define CMD_INFO_FUN       0
#define CMD_INFO_BREAK_FUN 1 
#define CMD_INFO_LEVEL     2
#define CMD_INFO_THIRST    3
#define CMD_INFO_MANA      4
#define CMD_INFO_FATIGUE   5
#define CMD_INFO_DELAY     6
#define CMD_INFO_ITEM_SIZE 7

/* Mapping containing information related to each ability.
 */
static mapping cmd_info = ([]);

/* Maps valid arguments to the "stop" command to their functions in this soul.
 */
static mapping m_stop_cmds = ([]);

#define M_ACTORS_ALARM_ID   0
#define M_ACTORS_BREAK_FUN 1
#define M_ACTORS_CMD_NAME  2
#define M_ACTORS_ITEM_SIZE 3

/* Maps an object pointer to an array of functions.  Each of the functions in
 * the array will be called when an actor (the object pointer key) completes
 * a vampire ability.
 */
static mapping m_actors = ([]);

int query_cmd_soul() { return 1; }

/* mapping of commands to their functions.
 * Function names prefixed by an underscore are meant to be hidden,
 * i.e. they will not be written using dump_cmds.
 * These are meant to be beneficial, informational, or taxable
 * commands, not simply emotes.
 * This is done with simple management of help files in mind.
 */
mapping query_cmdlist()
{
    return cmdlist;
}

string *replace_soul()
{
    object ob = previous_object();

    if (!SECURITY_CHECK(ob))
    {
        SECURITY_LOG(this_player(), "Illegal abilities soul.");
        return ({});
    }

    return 0;
}

/* write to a file the list of available commands.  If the name of
 * the command is prefixed by an underscore, it will not be included.
 */
varargs void dump_cmds(string file, int append)
{
    string *vamp_cmds, *dump_cmds;
  
    if (!strlen(file)) 
    { 
        return;
    }  

    vamp_cmds = m_indices(cmdlist);
    dump_cmds = filter(vamp_cmds, not @ &wildmatch("_*") @
        &operator([])(cmdlist));
  
    setuid();
    seteuid(getuid());

    if (!append && file_size(file) > -1)
    {
        rm(file);
    }

    if (!sizeof(dump_cmds))
    {
        write_file(file, "No commands");
    }
    else
    {
        dump_cmds = sort_array(dump_cmds);
        write_file(file, sprintf("%#-70s\n", implode(dump_cmds, "\n")));
    }
}

public void
reset_actor(object actor)
{
    int prop;

    /* remove the actor from the m_actors mapping */
    m_actors = m_delete(m_actors, actor);

    if (prop = actor->query_prop(LIVE_I_CONCENTRATE))
    {
        actor->add_prop(LIVE_I_CONCENTRATE, prop - 1);
    }
}

public void
complete_ability(function func)
{
    int tmp, success = func();
    mixed *a_info, *c_info;

    if (!this_player())
    {
        return;
    }

    if (!pointerp(a_info = m_actors[this_player()]))
    {
        return;
    }

    reset_actor(this_player());

    if (success)
    {
        c_info = cmd_info[a_info[M_ACTORS_CMD_NAME]];

        /* Add one-third of the thirst cost */
        if ((tmp = c_info[CMD_INFO_THIRST]) && (tmp -= (tmp / 3)))
        {
            this_player()->add_thirst(tmp);
        }

        /* Add one-third of the mana cost */
        if ((tmp = c_info[CMD_INFO_MANA]) && (tmp -= (tmp / 3)))
        {
            this_player()->add_mana(-tmp);
        }

        /* Add one-third of the fatigue cost */
        if ((tmp = c_info[CMD_INFO_FATIGUE]) && (tmp -= (tmp / 3)))
        {
            this_player()->add_fatigue(-tmp);
        }
    }
}

/* Function name: do_vamp_cmd
 * Description:   This is called when a player executes any of the vampire
 *                ability commands.  It does a few actions itself and calls
 *                the appropriate function to perform the command.
 * Arguments:     string str - the string given as arguments to the command.
 * Returns:       1 / 0 - success / failure
 */
int do_vamp_cmd(string str)
{
    mixed *info, *arr, ret, delay;
    string parse_str, verb = query_verb();
    object *oblist, sh;
    int  tmp;
    function f;

    if (!SECURITY_CHECK(this_player()))
    {
        SECURITY_LOG(this_player(), "Illegal abilities soul.  " +
           "Attempted command: " + query_verb() + 
           (strlen(str) ? " " + str : "") + ".");
        return 0;
    }

    /* get the information for this command */
    info = cmd_info[cmd_to_index[verb]];

    /* get the target function */
    f = info[CMD_INFO_FUN];

    ret = f(str);

    if (functionp(ret) || (ret == CMD_FAIL_WITH_COST))
    {
        /* Add one-third of the thirst cost */
        if (tmp = (info[CMD_INFO_THIRST] / 3))
        {
            this_player()->add_thirst(tmp);
        }

        /* Add one-third of the mana cost */
        if (tmp = (info[CMD_INFO_MANA] / 3))
        {
            this_player()->add_mana(-tmp);
        }

        /* Add one-third of the fatigue cost */
        if (tmp = (info[CMD_INFO_FATIGUE] / 3))
        {
            this_player()->add_fatigue(-tmp);
        }

        if (functionp(ret))
        {
            this_player()->add_prop(LIVE_I_CONCENTRATE,
                this_player()->query_prop(LIVE_I_CONCENTRATE) + 1);

            delay = info[CMD_INFO_DELAY];
            if (functionp(delay))
	    {
                delay = delay();
	    }

            arr = allocate(M_ACTORS_ITEM_SIZE);
            arr[M_ACTORS_ALARM_ID] = set_alarm(itof(delay), 0.0,
                &complete_ability(ret));
            arr[M_ACTORS_BREAK_FUN] = info[CMD_INFO_BREAK_FUN];
            arr[M_ACTORS_CMD_NAME] = cmd_to_index[verb];
            m_actors[this_player()] = arr;
        }
    }

    return !!ret;
}

public int
query_cmd_in_progress(object actor, string cmd_name)
{
    mixed *info = m_actors[actor];
    return (pointerp(info) ? (info[M_ACTORS_CMD_NAME] == cmd_name) : 0);
}

public int
stop_vamp_cmd_execution(object who)
{
    mixed *info = m_actors[who];
    if (pointerp(info))
    {
        remove_alarm(info[M_ACTORS_ALARM_ID]);
        reset_actor(who);
        return 1;
    }

    return 0;
}
    
/* Function name: break_command
 * Description:   Called from cmdhooks_break_spell in the guild shadow.
 *                This function is used to stop execution of a command
 *                when the player gets hit by an enemy (similar to standard
 *                spells).
 * Arguments:     object who - the object whose command is being broken
 */
void break_command(object who)
{
    mixed *info;
    function f;
 
//    break_drain(who);

    if (!pointerp(info = m_actors[who]) ||
        !(f = info[M_ACTORS_BREAK_FUN]))
    {
        return;
    }

    if (f(who))
    {
        stop_vamp_cmd_execution(who);
    }
}

/* The "stop" command is used to voluntarily stop execution
 * of certain commands.
 */
int _stop(string str)
{
    function f;

    if (f = m_stop_cmds[str])
    {
       return f(this_player());
    }

    return 0;
}

void add_stop_cmd(mixed stop_cmds, function stop_fun)
{
    int i;

    if (stringp(stop_cmds))
    {
        stop_cmds = ({ stop_cmds });
    }

    if (!pointerp(stop_cmds))
    {
        return;
    }

    for (i = 0; i < sizeof(stop_cmds); i++)
    {
        m_stop_cmds[stop_cmds[i]] = stop_fun;
    }
}
    
void add_vamp_cmd(mixed cmd, 
                  function fun,
                  int lvl,
                  int thirst,
                  int mana,
                  int fatigue,
                  int delay,
                  mixed stop_cmds,
                  function stop_fun,
                  function break_fun)
{
    int i;
    mixed *info, index;

    if (stringp(cmd))
    {
        cmd = ({ cmd });
    }

    if (!pointerp(cmd))
    {
        return;
    }

    index = cmd[0];

    info = allocate(CMD_INFO_ITEM_SIZE);
    info[CMD_INFO_FUN]  = fun;
    info[CMD_INFO_BREAK_FUN] = break_fun;
    info[CMD_INFO_LEVEL]     = lvl;
    info[CMD_INFO_THIRST]    = thirst;
    info[CMD_INFO_MANA]      = mana;
    info[CMD_INFO_FATIGUE]   = fatigue;
    info[CMD_INFO_DELAY]     = delay;
  
    cmd_info[index] = info;

    for (i = 0; i < sizeof(cmd); i++)
    {
        cmdlist[cmd[i]] = "do_vamp_cmd";
        cmd_to_index[cmd[i]] = index;
    }

    add_stop_cmd(stop_cmds, stop_fun);
}

varargs int levels_test(int silent,
                        object who = this_player(),
                        string command = query_verb())
{
    mixed *info;

    if (m_actors[who])
    {
        if (!silent)
        {
            who->catch_tell("You are currently focused on something else.\n");
        }

        return 0;
    }

    if (IS_WIZ(who))
    {
        return 1;
    }

    if (who->thirst() > 100)
    {
        if (!silent)
        {
            who->catch_tell("Your powers have weakened far too much.\n");  
        }

        return 0;
    }

    info = cmd_info[cmd_to_index[command]];

    if (info[CMD_INFO_MANA] && 
        (who->query_mana() < info[CMD_INFO_MANA]))
    {
        if (!silent)
        {
            who->catch_tell("You are mentally too weak for that.\n");
        }

        return 0;
    }
    
    if (info[CMD_INFO_FATIGUE] && 
        (who->query_fatigue() < info[CMD_INFO_FATIGUE]))
    {
        if (!silent)
        {
            who->catch_tell("You are too tired to do that.\n");
        }

        return 0;
    }

    return 1;
}

varargs int success_test(int silent,
                         object who = this_player(),
                         string cmd = query_verb())
{
    mixed *info;
    int suc;
 
    if (IS_WIZ(who))
    {
        return 1;
    }

    info = cmd_info[cmd_to_index[cmd]];

    if (info[CMD_INFO_LEVEL] &&
        ((suc = this_player()->power_check(info[CMD_INFO_LEVEL])) <= 0))
    {
        if (!silent)
        {
            who->catch_tell("You can't seem to manage it.\n");
        }

        return 0;
    }

    return suc;
}
    
void remove_object()
{
    map(m_indices(m_actors), stop_vamp_cmd_execution);
    destruct();
}
