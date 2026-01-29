// file name:        /d/Avenir/common/undraeth/d_std.c
// creator(s):       Nikklaus, Feb'97
// revision history: Nikklaus, Jul'97:  Macroed race_name identifications to
//                                      IS_DROW to patch for Gondor's slack
// purpose:          To handle std features of Undraeth npc's. Yes, it's an
//                   abomination probably, but the functionality
//                   included here would be impossible to inherit for both
//                   humanoids (monster class) and non-humanoids (creature
//                   class). Doesn't help that most functionality for npcs
//                   are predjudiced towards humanoids.
// note:             Half-done, half-baked. But I'm getting better.
// bug(s):
// to-do:            Finish a status system for drow and Union warriors to mark
//                   those lucky few who are above the law.
/*
 * Re-patriated code back to the Kalad domain.
 * Commented out Guild related code as it is never
 * returning to Kalad or Avenir.
 * 	- Lucius, June 2017
 */
# pragma strict_types
# pragma no_clone

# include <stdproperties.h>
# include <filter_funs.h>
# include <macros.h>

#define TO	this_object()
#define TP	this_player()

#define IS_DROW(who)	((who)->query_race_name() == "drow")

#define SUBLOC		"_my_extra_long_for_monster"

public mapping Attackers = ([ ]);
public object *Murderers = ({ });
string speak_msg;
string extra_long;
public int npc_guard_enabled = 0;  // Default - not a guardian
public mapping guarded_actions = ([ ]);   // Default - no restricted acts
static int prestige; /* The prestige changing variable */
public int drow_rank;

/* Drow filter, exists in shadow, too.
 */
public mixed filter_drow(mixed who) { return IS_DROW(who); }

// Functionality lifted from Krynn's set_extra_long.

/*
 * Function name: set_extra_long
 * Description:   Add an extra long description to the mobile 
 * Arguments:     str - The string
 */
void
set_extra_long(string str)
{
    extra_long = str;
    TO->add_subloc(SUBLOC, TO);
}

/*
 * Function name: show_subloc
 * Description:   This function is called to get the extra str
 * Arguments:     subloc  - The name of this sublocation
 *                me      - this_object()
 *                for_obj - Who wants this description
 * Returns:       The extra string to write
 */
string
show_subloc(string subloc, object me, object for_obj)
{
    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";

    if (subloc == SUBLOC)
	return extra_long;
}

/* Function name: get_drow_rank
 * Description:  Both player and npc drow have this, number 
 *               defining military rank.
 */
public int
get_drow_rank()
{
    return drow_rank;
}

/* Function name: set_drow_rank
 * Description:   Sets the npc's rank. 0 if left alone.
 */
public void
set_drow_rank(int rank)
{
    drow_rank = rank;
}

/*
 * Function name: help_friend
 * Description  : If this object is already in combat, we'll add an enemy
 *                (rather optimistically) to our enemy list, otherwise we'll
 *                attack.
 * Arguments:      object outlaw given us from init_living
 */
public void
help_friend(object ob)
{
    if (ob != TP && member_array(ob, TO->query_team_others()) < 0)
	TO->command("kill "+ob->query_name());
}

#if 0

/* Function name: notify_ob_attacked_me
* Description  : Called from attacked_by, maps the attacker with the attacked
* Arguments:    object attacker = object attacking
* Arguments    : object attacker, object attacked. Self-explanatory
*/
public void
notify_ob_attacked_me(object attacked, object attacker)
{
    if (ZHAH_DOEBLEND(TO) == ZHAH_DOEBLEND(attacked) && 
      CAN_SEE_IN_ROOM(TO) && CAN_SEE(TO, attacker))
	// If I have the same outlaw status (typically 0) and 
	// can see the attacker, I will take action, as long as the attacker 
	// doesn't outrank me.

	if (attacker->get_drow_rank() <=
	  TO->get_drow_rank())
	{
	    Attackers[attacker] = attacked;
	    help_friend(attacker);
	}
    // This matches the attacker to the attacked drow, to be counted 
    // among those responsible for his death if he dies.
}

/* Function name: notify_ob_killed_me
 * Description  : Called by a fellow drow's do_die, will consider anyone who
 *                was witnessed attacking the victim a murderer.
 */
public void
notify_ob_killed_me(object killed)
{
    object *killers;
    int i;

    if (!ZHAH_DOEBLEND(TO) && CAN_SEE_IN_ROOM(TO))
    {
	killers = FILTER_CAN_SEE(killed->query_enemy(-1), TO);
	if (!killers)
	    return;
	// Killers will be anyone who was involved in combat with
	// the deceased. We narrow this down to anyone I can see.

	for (i = sizeof(killers) - 1; i >= 0; i--)
	{
	    if (Attackers[killers[i]] == killed)
	    {
		if (present(killers[i], environment(this_object())))
		    Murderers += ({killers[i]});
		Attackers = m_delete(Attackers, killers[i]);
		// Any Attacker present at the time of killed's death will be 
		// considered responsible for the murder. All Attackers of killed
		// will be removed from the mapping.
	    }
	}
    }
}

/*
 * Function name: check_attackers
 * Description:   VBFC'd from LIVE_O_ENEMY_CLING. Compares those present,
 *                including those still in combat, and compares them with 
 *                those listed as Murderers. When a Murderer leaves, if a 
 *                drowish witness was present, he will raise an accusation.
* Returns:     Always false. not necessary to return a value for prop
 */
public int
check_attackers()
{
    int i;
    object *compare;

    while (member_array(0, m_indexes(Attackers)) > -1)
	Attackers = m_delete(Attackers, 0);
    // Clears Attackers who've been killed or left the game.

    if (!Murderers)
	return 0;

    compare = Murderers -
    FILTER_LIVE(all_inventory(environment(TO)));
    if (!compare)
	return 0;

    i = -1;
    while (++i < sizeof(compare))
    {
	Murderers -= ({compare[i]});
	D_LEGAL->add_outlaw(compare[i]);
	if (IS_DROW(compare[i]))
	    command("shout Doluth! Elgg lil dartreea del Undraeth!");
	else
	    command("shout Doeblend! Elgg lil ogglin del Undraeth!");
	find_player("nikklaus")->catch_tell(compare[i]+" murdered.\n");
    }
    return 0;
}

/*
 * Function name: was_attacked
 * Description  : Finds nearby drow and alerts them I've been attacked
 *                and who by.
 *                Called from attacked_by in drow and driders.
 */
public void
was_attacked(object attacker)
{
    int i;
    object *kin;

    if (!ZHAH_DOEBLEND(TO))
    {
	kin = filter(all_inventory(environment(TO)) - ({attacker}),
	  filter_drow);
	for (i = sizeof(kin) - 1; i >= 0; i--)
	    kin[i]->notify_ob_attacked_me(TO, attacker);

	if (npc_guard_enabled && !guarded_actions)
	    TO->set_follow(attacker->query_real_name(), 1);
    }
}

/*
* Function name: do_die
 * Description  : Checks for other drow around and alerts them that they've
 *                been killed, and who by.
 *                Called from do_die in drow and driders.
 */
public void
drow_die(object killer)
{
    int i;
    object *kin;

    if (!ZHAH_DOEBLEND(TO))
    {
	/*
		kin = FILTER_RACE(all_inventory(environment(TO)), "drow");
	 */
	kin = filter(all_inventory(environment(TO)) - ({killer}), filter_drow);
	for (i = sizeof(kin) - 1; i >= 0; i--)
	    kin[i]->notify_ob_killed_me(TO);
    }
}

#endif

/*
* Function name: set_speak
* Description:   Set the speak message for this monster.
* Arguments:     
* Returns:       
*/
void
set_speak(string msg)
{
    speak_msg = msg;
}

/*
 * Function name: query_speak
 * Description:   Returns the speak message for this monster.
 * Returns:       the message spoken.
 */
string
query_speak()
{
    return speak_msg;
}

/*
* Function name: speak
* Description:   
* Arguments:     
* Returns:       
*/
public int
speak(string who)
{
    if (!who)
    {
	write("You have a long chat with yourself.\n");
	say(QCTNAME(this_player()) + " is talking to " +
	  this_player()->query_objective() + "self again...\n");
	return 1;
    }

    notify_fail(capitalize(query_verb()) + " with who?\n");
    if(!TO->id(who))
	return 0;
    else
    {
	if (!this_object()->query_speak())
	{
	    this_player()->catch_msg("You speak briefly with " +
	      QNAME(this_object()) +
	      " but get a sinking feeling that " +
	      this_object()->query_pronoun() + " isn't going to respond.\n");
	    say(QCTNAME(this_player()) +
	      " tries to strike up a conversation with " +
	      QNAME(this_object()) + " but gets no response.\n");
	}
	else
	{
	    this_player()->catch_msg("You talk for a while with " +
	      QNAME(this_object()) +
	      ", about trivial matters. Eventually " +
	      this_object()->query_pronoun() + " says:\n" + query_speak());
	    say(QCTNAME(this_player()) + " starts speaking with " +
	      QNAME(this_object()) +
	      " but you can't hear what they are saying.\n");
	}
    }

    return 1;
}

#if 0

/*
* Function name: get_drowsoul
* Description:     add given soul at the top of the cmdsoul list
* Arguments:       soul: filename of soul to be added
*                  who:  player the soul must be added to
* Returns:         1 if successful, 0 otherwise.
* Note:            this function taken from Tulix's Grunt shadow, with
*                  permission
*/
static void
get_drowsoul()
{
    TO->add_cmdsoul(DROW_SOUL);
    TO->update_hooks();
    return;
}

#endif

/* ******** Guard Functions *********** */

/*
 * Function name: guard_enable
 * Description:   Sets an npc to be a guardian.
 */
public void
guard_enable()
{
    npc_guard_enabled = 1;
}

/* Function name: query_guard_enabled
 * Description:   Checks whether this object is a guard
 *                Lets guards get away with certain things.
 * Returns:       0 if not, 1 if so
 */
public int query_guard_enabled() { return npc_guard_enabled; }

/* Function name: set_restricted_actions
 * Description:   Sets which actions the guard will prevent living from
 *               doing in its presence and how it will react.
 * Arguments:    mixed action - string describing the action, or mapping of 
		  actions:responses
 *               string response - function to be called with action taken
 *                 default for directions to blocked is npc_try_to_stop
 */
static varargs void
set_restricted_action(mixed action, string response)
{
    if (mappingp(action))
	guarded_actions += action;
    else if(stringp(action) && !response)
	guarded_actions += (["npc_try_to_stop": action]);
    else if (stringp(action))
	guarded_actions += ([response:action]);
}

/*
 * Function name: query_guarding
 * Description  : Here we check whether the living is authorized to
 *                to perform the commands this_object is guarding against
 * Returns      : Returns 0 if free to pass, 1 if restricted
 * Note:          This is to be redefined in other npcs.
 */
public int
query_guarding(object who)
{
    return !IS_DROW(who);
}

/* Function name: npc_try_to_stop
 * Description  : Called by default in an npc_guard_enabled npc when
 *                an unathorized living tries to pass in the direction
 *                it's guarding
 */
static int
npc_try_to_stop()
{
    TP->catch_msg(QCTNAME(this_object())+" stops you from going "
      +"in that direction.\n");
    say(QCTNAME(this_object())+" stops "+QTNAME(TP)+" from passing\n");
    return 1;

}

/* Function name: init_std
* Description  : This will compare living objects in environment with 
*                the outlaw mapping in d_society.
*                Called from init_living
 * Note:          help_friend() returns are void and cancel later add_actions
*/
public void
init_std()
{
    object *suspects;
    string *init_list;
    int i, jj;

    if (TO->query_guard_enabled())
    {
	// If this_object is outlawed, or this_player is a guard,
	// we'll just go on to later inits

	if (CAN_SEE_IN_ROOM(TO) && CAN_SEE(TO, TP))
	{
#if 0
	    if (ZHAH_DOEBLEND(TP))
		return help_friend(TP);
#endif

	    if (!IS_DROW(TP) && IS_DROW(TP->query_attack()))
		return help_friend(TP);
	    // If we enter a room and see combat, we'll give a 
	    // native the benefit of the doubt.

	    if (npc_guard_enabled && TO->query_guarding(TP))
	    {
		if (m_sizeof(guarded_actions))
		{
		    init_list = m_indexes(guarded_actions);
		    for (jj = sizeof(init_list) - 1; jj >=0; jj--)
		    {
			add_action(init_list[jj],
			  guarded_actions[init_list[jj]]);
		    }
		}
		else
		    return help_friend(TP);
		// If guarding against a type, player type
		// but not against specific actions, then 
		// autoattack.
	    }
	}
    }

    add_action(speak, "speak");
    add_action(speak, "chat");
    add_action(speak, "talk");
}

/*
* Function name: set_knight_prestige
* Description:   Set the prestige changing value in the mobile
* Arguments:     pres - the prestige, if > 0 it will add to the acc, if < 0
*                       it will add to the stat.
*/
int set_knight_prestige(int pres) { prestige = pres; }

/*
 * Function name: query_knight_prestige
 * Description:   Return the prestige this monster will affect a knight.
 * Returns:       The prestige.
 */
int query_knight_prestige() { return prestige; }

/*    Test functions and diagnostics    */

public mapping
list_attackers()
{
    return Attackers;
}

public object *
list_murderers()
{
    return Murderers;
}
