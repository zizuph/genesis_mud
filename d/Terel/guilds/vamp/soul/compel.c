/* 
 * compel.c
 *
 * This provides the focus ability.
 *
 * Modifications:
 *   9/25/2009 - Fix runtime and incorrect targeting of compel
 *               command. (Petros)
 */

#include <composite.h>
#include <formulas.h>
#include <language.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include <filter_funs.h>
#include <std.h>

#include "../guild.h"

public int can_see(object ob)
{
    if (!living(ob))
    {
        return 0;
    }
    if (!CAN_SEE_IN_ROOM(ob))
    {
        return 0;
    }
    if (!CAN_SEE(ob,TP))
    {
        return 0;
    }
    return 1;
}

public void issue_command(object target,string cmd)
{
    TP->catch_msg("You exert your influence over " +
        QTNAME(target) + ".\n");
    int result=target->command(cmd);
    if (!result)
    {
        TP->catch_msg(QCTNAME(target) + " appears to be "+
            "unable to follow your command.\n");
    }
    setuid();
    seteuid(getuid());
    write_file(LOG_DIR+"compel_log",ctime(time()) + ": " +
        TP->query_real_name()+ " compel "+MASTER_OB(target) + " to " +
        cmd + "\n");
    
    object * watchers=WATCHERS(TP) - ({ target });
    
    if (!sizeof(watchers))
    {
        return;
    }
    foreach (object watcher : watchers)
    {
        if (IS_WIZ(watcher) ||
        watcher->resolve_task(TASK_FORMIDABLE,
             ({ SS_AWARENESS, SS_FORM_ILLUSION }))>0)
        {
            watcher->catch_msg("You think you see " + QTNAME(TP) +
            "'s lips moving.\n");
        }        
    }
}

public int compel(string str)
{
    notify_fail("Compel which prey?\n");
    
    if (!strlen(str))
    {
        return 0;
    }
    
    mixed * targets;
    object target;    
    string cmd;
    
    parse_command(str, environment(TP), "%l [to] %s", targets, cmd);
    if (!sizeof(targets))
    {
        return 0;
    }

    // targets contains an array. see man parse_command for the array
    // format. We need to determine the actual target from this array
    if (targets[0] < 0)
    {
        // We get the index by multiplying by -1
        target = targets[targets[0] * -1];
    }
    else if (targets[0] == 1)
    {
        // If it returns 1, then the first object is returned
        target = targets[1];
    }
    else if (targets[0] == 0 || targets[0] > 1)
    {
        if (sizeof(targets) > 2)
        {
            // specified more than one.
            write("You can only compel one at a time.\n");
            return 1;
        }
        target = targets[1];
    }

    if (!objectp(target))
    {
        return 0;        
    }
    
    if (!strlen(cmd))
    {
        TP->catch_msg("Compel " + QTNAME(target) + " to do what?\n");
        return 1;
    }
    
    if (target->query_dominated()!=TP)
    {
        TP->catch_msg(QCTNAME(target) + " is not under your "+
        "control.\n");
        return 1;
    }
    
    string word=explode(cmd," ")[0];
    
    if (target->query_humanoid())
    {
        switch (word)
        {
            case "agree":
            case "blush":
            case "clap":
            case "cry":
            case "dance":
            case "disagree":
            case "eyebrow":
            case "fret":
            case "gasp":
            case "giggle":
            case "greet":
            case "hug":
            case "laugh":
            case "listen":
            case "mumble":
            case "peer":
            case "kiss":
            case "scowl":
            case "sneeze":
            case "twiddle":
            case "weep":
            case "worship":
            
                issue_command(target,cmd);
                return 1;
        }
    }

    switch (word)
    {
        case "avert":
        case "back":
        case "beg":
        case "cringe":
        case "cough":
        case "cower":
        case "gasp":
        case "glare":
        case "grimace":
        case "groan":
        case "grovel":
        case "growl":
        case "hang":
        case "hiccup":
        case "jump":
        case "kick":
        case "kneel":
        case "nod":
        case "panic":
        case "pant":
        case "point":
        case "roar":
        case "scratch":
        case "shake":
        case "shudder":
        case "sigh":
        case "smell":
        case "stare":
        case "startle":
        case "swallow":
        case "sweat":
        case "tremble":
        case "wail":
        case "whimper":
        case "yawn":
            issue_command(target,cmd);
            return 1;
    }
    
    TP->catch_msg("You cannot compel " +QTNAME(target) + " to '"+
    cmd + "'.\n");
    return 1;
}


