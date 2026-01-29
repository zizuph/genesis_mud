/*
 * Bribery Support
 *
 * To use these functions you need to call init_bribe from the init
 * function of the npc.
 */ 
#include <cmdparse.h>
#include <composite.h>
#include <macros.h>

#include "/d/Krynn/common/defs.h"

static mixed*  gBribe_action   = ({});
static string* gBribe_commands = ({"bribe"});
static mixed   gBribe_items   = 0;
static mapping gBribe_money = ([]);


/*
 * Function name: set_bribe
 * Description:   Set this in the npc when you want it to be bribable :)
 * Arguments:     br - A list of alternating numbers and things to say or do.
 *                 ({ num, todo, ... })
 *                num:  value in cc (this is accumulated amount of money a player
 *                      has given to this npc so far).
 *                todo: string: whisper the text to the payer, VBFC is supported.
 *                      function: call the function, if a string is returned, whisper that.
 */
public void
set_bribe(mixed br)
{
    gBribe_action = br;
}

/*
 * Function name: query_bribe
 * Description:   Query if and how this npc is bribable :)
 * Returns:       The list of alternating numbers and things to say.
 */
public mixed
query_bribe()
{
    return gBribe_action;
}

public void
add_bribe_commands(mixed cmds)
{
    if (!gBribe_commands)
        gBribe_commands = ({});

    if (pointerp(cmds))
        gBribe_commands += cmds;
    else if (stringp(cmds))
        gBribe_commands += ({ cmds });
}

public void
remove_bribe_commands(mixed cmds)
{
    if (!gBribe_commands)
        gBribe_commands = ({});

    if (pointerp(cmds))
        gBribe_commands -= cmds;
    else if (stringp(cmds))
        gBribe_commands -= ({ cmds });
}

public mixed
query_bribe_commands()
{
    return gBribe_commands;
}

public void
set_bribe_items(mixed par)
{
    if (intp(par) || pointerp(par))
        gBribe_items = par;
    else if (stringp(par))
        gBribe_items = ({ par });
}

public mixed
query_bribe_items()
{
    return gBribe_items;
}

/*
 * Function name: bribe
 * Description:   Called when someone want to bribe someone, possibly
 *                this npc. Detect if I am bribed, and if so, react
 *                according to the set_bribe settings.
 * Arguments:     str - the text as given by the player.
 * Returns:       1/0, depending on if I am the npc to be bribed or not.
 */
public int
bribe(string str)
{
    function f;
    mixed tmp;
    mixed who, what;
    int i, val = 0, done = 0;
    object clto = find_object("/cmd/live/things");
    string vb = query_verb();

    NF(C(vb) + " who with what?\n");

    if (!str || str == "")
        return 0;
    
    if (!parse_command(str,E(TP),"%l 'with' %i", who, what))
        return 0;

    who = CMDPARSE_STD->normal_access(who,0,clto);

    if (!who || !sizeof(who))
        return 0;
    
    who = who[0];
    if (who != TO)
        return 0;
    
    NF(C(vb) + " " + who->query_the_name(TP) + " with what?\n");
    
    what = CMDPARSE_STD->normal_access(what,"manip_give_access",clto);
    if (!gBribe_items)
        what = filter(what,operator(!)@operator(!)@&->query_coin_type());
    else if (pointerp(gBribe_items))
    {
	/* filter objects with the given names. This is a bit tough, 
	 * so we leave it out for now :)
	 */
    }
    
    if (!what || !sizeof(what))
        return 0;
    
    if (!gBribe_action || !sizeof(gBribe_action))
    {
	write(who->query_The_name(TP) + " does not seem interested " +
            "in being " + vb + (vb[-1..-1] == "e" ? "" : "e") + "d.\n");
	return 1;
    }
    
    tmp = find_object("/d/Krynn/common/void");
    f = &clto->manip_relocate_to(,tmp);
    
    what = filter(what,f);
    
    NF(C(vb) + " who with what?\n");
    if (!what || !sizeof(what))
        return 0;

    for(i=0;i<sizeof(what);i++)
        val += what[i]->query_value();

    write("You hand " + COMPOSITE_DEAD(what) + " to " +
        who->query_the_name(TP) + ".\n");

    val += gBribe_money[TP->query_real_name()];
    gBribe_money += ([TP->query_real_name():val]);

    if (!CAN_SEE_IN_ROOM(who) || !CAN_SEE(who,TP))
        write(who->query_The_name(TP) + " does not seem to notice you.\n");
    else 
    {
	if (sizeof(gBribe_action))
            for(i=sizeof(gBribe_action)-2;i>=0;i-=2)
                if (intp(gBribe_action[i]) && gBribe_action[i] <= val)
                {
                    if (functionp(gBribe_action[i+1]))
                    {
                        f = gBribe_action[i+1];
                        tmp = f();
                        if (stringp(tmp) && tmp != "")
                            command("whisper to " + TP->query_real_name() + " " + tmp);
                    }
                    else if (stringp(gBribe_action[i+1]))
                        command(TO->check_call("whisper to " + TP->query_real_name() + " " +
                            gBribe_action[i+1]));
                    else
                        command("whisper to " + TP->query_real_name() + " I would " +
                            "have told you a real secret, but my creator was too stupid " +
                            "to do it right. Please leave a bug report.");
                    done = 1;
                    break;
                }
	if (!done)
            command("whisper to " + TP->query_real_name() + " Heh, if you're trying" +
                " to bribe me, it's not _that_ easy!");
    }
    what->remove_object();
    return 1;
}

public void
init_bribe()
{
    int i, j = sizeof(gBribe_commands);
    
    for(i=0;i<j;i++)
        add_action("bribe", gBribe_commands[i]);
}
