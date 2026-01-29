/*
 * /std/living/cmdhooks.c
 *
 * This is a subpart of /std/living.c
 *
 * All command hooks are handled here, wiz, soul, tool and spell commands.
 */

#include <macros.h>
#include <std.h>

/*
 * Variables, These are only accessed from routines in this module.
 */
static string 	*wiz_souls,		/* The wizard soul names */
		*soul_souls,		/* The ordinary soul names */
		*tool_souls,		/* The tool soul names */
		 gSpell,		/* The last spell cast. */
		 gArg;			/* The argument to that spell. */

static int	 gTime,			/* The time left for the spell to */
					/* get realized. */
                 aid;                   /* Alarm id for spells */

public void update_hooks();

int my_commands(string str);
int communicate(string str);

/*
 * Function name: cmdhooks_reset
 * Description  : Start the command parsing. The last added action is
 *                evaluated first, so speech is checked first.
 */
static void
cmdhooks_reset()
{
    update_hooks();
    add_action(my_commands, "", 1);
    add_action(communicate, "'", 1);
    add_action(communicate, "say");
}

/*
 * Must have it here for special with ' 
 */
public int
communicate(string str = "") 
{
    /* Doesn't the ''' look cute? It is the fastest ;-) */
    if (query_verb()[0] == ''')
    {
	str = extract(query_verb(), 1) + " " + str;
    }

    say( ({ METNAME + LD_SAYS + LD_UNDERSTANDS(str) + "\n",
	    TART_NONMETNAME + LD_SAYS + LD_UNDERSTANDS(str) + "\n",
	    UNSEEN_NAME + LD_SAYS + LD_UNDERSTANDS(str) + "\n" }) );

    if (this_player()->query_get_echo())
        write("You say: " + str + "\n");
    else
        write("Ok.\n");

    return 1;
}

/*
 * Function name:   start_souls
 * Description:     Tell the souls that we are using them, this is used to
 *		    add sublocations for the living object. Also call
 *		    'replace_soul' so that an obsolete soul can rederict
 *		    the usage to another newer soul/souls.
 * Arguments:       souls: an array with all souls that should be started
 */
nomask public string *
start_souls(string *souls)
{
    int il, rflag;
    mixed ob;
    string *replace_souls, *used_souls, *tmp;
    mapping replaced;

    used_souls = ({});
    replaced = ([]);

    do
    {
	rflag = 0;
	for (replace_souls = ({}), il = 0; il < sizeof(souls); il++)
	{
	    ob = souls[il];
	    catch(ob->teleledningsanka());
	    ob = find_object(ob);
	    if (ob)
	    {
		if (replaced[ob]) /* Dont replace twice */
		    continue;
		else
		{
		    tmp = ob->replace_soul();
		    replaced[ob] = 1;
		}

		if (stringp(tmp))
		{
		    replace_souls += ({ tmp });
		    rflag = 1;
		}
		else if (pointerp(tmp))
		{
		    replace_souls += tmp;
		    rflag = 1;
		    if (member_array(souls[il], tmp) >= 0)
			tmp = 0;
		}
		
		if ((tmp == 0) && (member_array(souls[il], used_souls) < 0))
		{
		    ob->using_soul(this_object());
		    used_souls += ({ souls[il] });
		}
	    }
	    else
		used_souls += ({ souls[il] });
	}
	if (rflag)
	    souls = replace_souls + ({});
    } while (rflag);

    return used_souls;
}

/*
 * Function name: query_cmdsoul_list
 * Description  : Give back the array with filenames of wizard souls.
 * Returns      : The wizard soul list.
 */
nomask public string *
query_wizsoul_list()
{
    if (SECURE_ARRAYS)
	return slice_array(wiz_souls, 0, sizeof(wiz_souls));
    else 
	return wiz_souls; 
}

/*
 * Function name:   load_wiz_souls
 * Description:     Load the wizard souls into the player.
 * Returns:         True if successful.
 */
nomask public int
load_wiz_souls()
{
    int rank;

    if (previous_object() != find_object(SECURITY))
	return 0;

    if (!strlen(geteuid(this_object())))
    {
	write("PANIC! Player has no euid!\n");
	return 0;
    }

    /* Only wizards can have wizard souls. */
    if (rank = SECURITY->query_wiz_rank(geteuid(this_object())))
        wiz_souls = WIZ_SOUL(rank)->get_soul_list();
    else
    {
	wiz_souls = ({ });
	return 1;
    }

    if (sizeof(wiz_souls) == 0)
    {
	write("Error loading wizard soul list. No wizard soul loaded.\n");
	return 0;
    }

    wiz_souls = start_souls(wiz_souls);

    return 1;
}

/*
 * Function name:   load_command_souls
 * Description:     Load the command souls into the player.
 * Returns:         Always 0
 */
nomask public int
load_command_souls()
{
    soul_souls = this_object()->query_cmdsoul_list();
    if (!sizeof(soul_souls))
	soul_souls = NPC_SOULS;

    soul_souls = start_souls(soul_souls);
    this_object()->update_cmdsoul_list(soul_souls);
}

/*
 * Function name:   load_tool_souls
 * Description:     Load the tool souls into the player.
 * Returns:         True upon success.
 */
nomask public int
load_tool_souls()
{
    int level;

    level = (int)SECURITY->query_wiz_level(geteuid(this_object()));
    if (!query_wiz_level() ||
	(WIZ_TYPE(level) < WIZ_NORMAL) ||
	!interactive(this_object()))
    {
	tool_souls = ({});
	return 0;
    }

    tool_souls = (string *)this_object()->query_tool_list();
    if (!sizeof(tool_souls))
    {
	this_object()->add_toolsoul(TRACER_TOOL_SOUL);
	tool_souls = (string *)this_object()->query_tool_list();
    }

    tool_souls = start_souls(tool_souls);
    this_object()->update_tool_list(tool_souls);
    return 1;
}

/*
 * Function name:   my_commands
 * Description:     Try to find and perform a command.
 * Arguments:       str - the argument string.
 * Returns:         True if the command was found.
 */
static int
my_commands(string str)
{
    int    i, rv, time, time2;
    object ob;
    mixed  *spell_list;
    string mess;
    string verb = query_verb();
    int    size;

    /* Don't waste the wiz-souls and toolsouls on mortals.
     */
    if (query_wiz_level())
    {
	/* This construct with while is faster than any for-loop, so keep
	 * it this way.
	 */
	size = sizeof(wiz_souls);
	i = -1;
	while(++i < size)
	{
	    ob = find_object(wiz_souls[i]);
	    if (!ob)
	    {
		if (catch(wiz_souls[i]->teleledningsanka()))
		    tell_object(this_object(),
			"Yikes, baaad soul: " + wiz_souls[i] + "\n");
		ob = find_object(wiz_souls[i]);
		if (!ob)
		    continue;
	    }
	    if (ob->exist_command(verb))
	    {
		ob->open_soul(0);
		export_uid(ob);
		ob->open_soul(1);
		rv = ob->do_command(verb, str);
		ob->open_soul(0);
		if (rv)
		    return 1;
	    }
	}

	size = sizeof(tool_souls);
	i = -1;
	while(++i < size)
	{
	    ob = find_object(tool_souls[i]);
	    if (!ob)
	    {
		if (catch(tool_souls[i]->teleledningsanka()))
		    tell_object(this_object(),
			"Yikes, baaad soul: " + tool_souls[i] + "\n");
		ob = find_object(tool_souls[i]);
		if (!ob)
		    continue;
	    }
	    if (ob->exist_command(verb))
	    {
		ob->open_soul(0);
		export_uid(ob);
		ob->open_soul(1);
		rv = (int)ob->do_command(verb, str);
		ob->open_soul(0);
		if (rv)
		    return 1;
	    }
	}
    }

    size = sizeof(soul_souls);
    i = -1;
    while(++i < size)
    {
	ob = find_object(soul_souls[i]);
	if (!ob)
	{
	    if (catch(soul_souls[i]->teleledningsanka()))
		tell_object(this_object(),
			    "Yikes, baaad soul: " + soul_souls[i] + "\n");
	    ob = find_object(soul_souls[i]);
	    if (!ob)
		continue;
	}
	if (ob->exist_command(verb))
	{
	    if (ob->do_command(verb, str))
		return 1;
	}
    }

    spell_list = (object *)this_object()->query_spellobjs();
    size = sizeof(spell_list);
    i = -1;
    while(++i < size)
    {
	if (stringp(spell_list[i]))
	    ob = find_object(spell_list[i]);
	else
	    ob = spell_list[i];
	if (!objectp(ob))
	{
	    if (catch(spell_list[i]->teleledningsanka()))
		tell_object(this_object(),
		    "Yikes, baaad spell soul: " + spell_list[i] + "\n");
	    ob = find_object(spell_list[i]);
	    if (!ob)
		continue;
	}
	if (ob->exist_command(verb))
	{
	    notify_fail("You already concentrate yourself upon another " +
		"spell.\n");
    	    if (aid && get_alarm(aid))
	    	return 0;

	    /* A call to 'start_spell_fail' indicates that we are
               preparing for casting the spell. This can be used to
	       deduct mana. If the spell is broken mana will still be lost.
	     */
	    if (ob->start_spell_fail(verb, str))
		return 1;

	    if (!ob->query_spell_mess(verb, str))
	    {
	        write("You start to concentrate upon the spell.\n");
	        mess = " closes " + query_possessive() + " eyes and looks " +
			"concentrated.";
    	        say(({ METNAME + mess + "\n",
	    	    TART_NONMETNAME + mess + "\n", "" }));
	    }

            time = ob->query_spell_time(verb, str);
	    time2 = (time < 1 ? 2 : time + 2) + 
		query_prop(LIVE_I_ATTACK_DELAY);
	    aid = set_alarm(itof(time2), 0.0, "cmdhooks_do_spell", 
			    ({ verb, str, time, ob }));
/*	    add_attack_delay(time, 0);
*/
	    return 1;
	}
    }

    return 0;
}

/*
 * Function name:   update_hooks
 * Description:     Initialize all tool- and commandsouls
 */
nomask public void
update_hooks()
{
    SECURITY->load_wiz_souls();
    load_tool_souls();
    load_command_souls();
}

/*
 * Function name:   cmdhooks_do_spell
 * Description:     Execute a spell
 */
void
cmdhooks_do_spell(mixed *arg)
{
    string spell, sparg;
    object spellob;
    int dtime;
    mixed fail;
    string fail_str;
    int i;

/*
    if (find_call_out("cmdhooks_do_spell") > 0)
	return 0;
*/

    spell = arg[0];
    sparg = arg[1];
    dtime = arg[2];
    spellob = arg[3];
    fail_str = 0;

    remove_prop(LIVE_I_ATTACK_DELAY);
    set_this_player(this_object());

    if (objectp(spellob))
    {
	if (spellob->exist_command(spell))
	{
	    if (stringp(fail = spellob->do_command(spell, sparg)))
		fail_str = fail;
	    if (intp(fail) && fail == 1)
		return;
	}
    }

    if (strlen(fail_str))
	write(fail_str);
    else
	write(LD_SPELL_FAIL);
    return;

}

/*
 * Function name:   cmdhooks_break_spell
 * Description:     Break the preparation for a spell. Note that the caster
 *		    still suffers the attack delay.
 * Returns:	    True if a spell was being prepared
 */
public int
cmdhooks_break_spell(string msg)
{
    if (aid && get_alarm(aid))
    {
	if (!strlen(msg))
	    tell_object(this_object(), LD_SPELL_CONC_BROKEN);
	else
	    this_object()->catch_msg(msg);
	this_object()->remove_prop(LIVE_I_CONCENTRATE);
	remove_alarm(aid);
	aid = 0;
	return 1;
    }
    return 0;
}
    
