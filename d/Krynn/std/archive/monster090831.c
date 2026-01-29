/*
 * Some nice monster help functions, and specific functions for Krynn
 *
 * //Nick
 *
 * History:
 *   950922 Added npc_arm_me and query_level_adj /Rastlin 
 *   950923 Added query_level_desc /Rastlin
 *   970728 Added bribe functionality ~Aridor
 *   990316 Added npc_killed call and BelongsToArmy functions. ~Aridor
 *   030502 Reworked all combat hooks. ~Cotillion
 *   050525 Fixed bug in incompatible catch/answer_question(). Mercade
 *   090830 Added checks on 'str'!= 0 && typeof(str) == T_STRING. Navarre.
 */
#pragma save_binary
#pragma strict_types

#include <cmdparse.h>
#include <composite.h>
#include <macros.h>
#include <stdproperties.h>
#include <state_desc.h>
#include "/d/Krynn/common/defs.h"

inherit "/std/monster";
inherit "/d/Krynn/std/patrol";
inherit "/d/Krynn/std/act/actions";
inherit "/d/Krynn/std/act/follow";

int 	prestige; 	/* The prestige changing variable */
string 	extra_long; 	/* Any extra long description set */
int     do_intro = 0;   /* Should I intro back? */

string  gColor = "blue";
mapping gNpc_emotes = ([]), gNpc_adverbs = ([]);

static object  gWep_func, gArm_func;
static int     gWep_patch = 0;

string gBelongsToArmy = 0;

#define GRAVE_CONTROLLER "/d/Krynn/solace/graves/controller"
#define SUBLOC		 "_my_extra_long_for_monster"
#define WEP_ARM          "/d/Krynn/solamn/splains/obj/"

public void help_friend(object ob);
public void enemy_leave();


public void
create_krynn_monster()
{

}

/*
 * Function name: create_monster
 * Description:   The standard create.
 */
public nomask void
create_monster()
{
    /* By default all Krynn/Ansalon npcs are agressive towards
     * thieves. Override when necessary. */
    add_prop(LIVE_I_ATTACK_THIEF, 1);
    add_prop(LIVE_O_ENEMY_CLING, &enemy_leave());
    add_prop(NPC_I_NO_UNARMED, 1);

    create_krynn_monster();

    /* This is a fix to stop a problem with kenders attacking thieves.
     * The real fix is to fix all the separate kender npc files, but there
     * are too many.
     */
    if (query_race_name() == "kender")
    {
        add_prop(LIVE_I_ATTACK_THIEF, 0);
    }
    
}

public mapping
query_emotes()
{
    return secure_var(gNpc_emotes);
}

public mapping
query_emotes_adverb()
{
    return secure_var(gNpc_adverbs);
}


public void
add_emote_hook(string emote, float time, function func)
{
    if (gNpc_emotes[emote])
	gNpc_emotes = m_delete(gNpc_emotes, emote);

    gNpc_emotes += ([ emote : ({ time, func }) ]);
}


/*
 * Count the number of occurances of a certain symbol in a given string.
 */
int
count_symbol(string str, int symbol)
{
    int i, num = 0;

    for (i = 0; i < strlen(str); i++)
    {
        if (str[i] == symbol)
        {
            num++;
        }
    }
    return num;
}


/* 
 * Function name: catch_question
 * Description:	  This function is called in each living being someone asks a
 *		  question to.
 * Arguments:	  question - The question as put
 */
public void
catch_question(string question)
{
    int i,j, c, d;
    mixed ret_arr, arg1, arg2, arg3, arg4, arg5;
    
    if (dont_answer_unseen && (!TP->check_seen(this_object()) ||
        !CAN_SEE_IN_ROOM(this_object())))
    {
        set_alarm(itof(random(3) + 1), 0.0, "unseen_hook");
        return;
    }

    i = strlen(question);
    if (question[i - 1] == "."[0] || question[i - 1] == "?"[0])
    {
        question = extract(question, 0, i - 2);
    }
    
    posed_question = lower_case(question);

    /* The quick match. Question literally matches the ask term. */
    for (i = 0; i < sizeof(ask_arr); i++)
    {
        if (IN_ARRAY(posed_question, ask_arr[i][0]))
	{
	    set_alarm(itof(2 + random(4)), 0.0, &answer_question(({ ask_arr[i][1], TP }), ask_arr[i][2] ));
	    return;
	}
    }

    /* Expensive test. Process for vbfc on every ask term.
     * There are several options:
     * - there are % in the ask term and we match the exact number.
     * - there is no % in the ask term and get a matching result.
     */
    for (i = 0; i < sizeof(ask_arr); i++)
    {
        for(j = 0; j < sizeof(ask_arr[i][0]); j++)
        {
            /* Count the number of % symbols. If there are no %, then count
             * the single quotes for mandatory words. If there are none of
             * those either, we don't waste our breath on parse_command. */
            c = count_symbol(ask_arr[i][0][j], '%');
            if (!c)
            {
                c = - count_symbol(ask_arr[i][0][j], '\'');
                if (!c) continue;
            }

            /* parse_command returns 1 if it matches. If there are multiple %
             * then it will return the number of matched arguments. */
            d = parse_command(posed_question, environment(), ask_arr[i][0][j],
                arg1, arg2, arg3, arg4, arg5);

            if ( ((c > 0) && (c == d)) ||
                 ((c < 0) && (d == 1)) )
            {
                set_alarm(itof(2 + random(4)), 0.0, &answer_question(
                    ({ ask_arr[i][1], TP, arg1, arg2, arg3, arg4, arg5 }), ask_arr[i][2] ));
                return;
            }
        }
    }

    /* If the question cannot be answered, log the question */
    log_file("asks", ctime(time())[4..15] + " " + TP->query_name() +
        " asked "+ file_name(TO) + ": " + question + "\n",200000);

    if (default_answer)
    {
        set_alarm(itof(2 + random(4)), 0.0, 
            &answer_question( ({ default_answer }), default_answer_cmd )); 
    }
}


/*
 * Function name: answer_question
 * Description:   This function is called after a short delay when this mobile
 * 		  wants to react to a question
 * Arguments:  	  mixed arr - an array with answers.
 *                int cmd - if true, the answer is a command.
 */
public void
answer_question(mixed arr, int cmd)
{
    object env = environment(this_object());
    string str;

    arr += ({ 0,0,0,0,0,0,0 }); /* make sure the array is long enough */

    if ((env == environment(TP)) ||
        (env == TP) ||
	(not_here_func && call_other(this_object(), not_here_func, TP)))
    {
	if (cmd == 2)
        {
            str = call_other(this_object(), arr[0], arr[1],
                arr[2], arr[3], arr[4], arr[5], arr[6]);
	    if(str && T_STRING == typeof(str))
	    {
	      command(str);
	    }
        }
	else
	{
	    str = this_object()->check_call(arr[0], TP);

	    if (cmd)
	    {
	      if(str && T_STRING == typeof(str))
	      {
		command(str);
	      }
	    }
	    else if (atoi(str) == 0)
                tell_object(TP,str);
	}
    }
}


/*
 * Function name: set_knight_prestige
 * Description:   Set the prestige changing value in the mobile
 * Arguments:	  pres - the prestige, if > 0 it will add to the acc, if < 0
 *		  	 it will add to the stat.
 */
void
set_knight_prestige(int pres)
{
    prestige = pres; 
}

/*
 * Function name: query_knight_prestige
 * Description:	  Return the prestige this monster will affect a knight.
 * Returns:	  The prestige.
 */
int 
query_knight_prestige() 
{
    return prestige; 
}

/*
 * Combat Hook Functions
 *
 * These functions exist to support an easier interface to hook things
 * into the combat flow.
 * 
 * The various functions this mask have rather different ways, and some
 * are not really hooks at all. This makes it possible to inherit a 
 * combat module of sorts into npcs which will adjust their actions.
 */

/*
 * Function Name: attack_object
 * Description  : This is called by the combat system whenever we attack
 *                someone. It's here used to fire off a hook that should
 *                be used to get the npc to react to the attack.
 * Arguments    : ob - The enemy to attack.
 */
public void
attack_object(object ob)
{
    object *arr;
    
    ::attack_object(ob);

    this_object()->hook_attack(ob);
    
    arr = this_object()->query_team_others();
    arr->hook_friend_attack(this_object(), ob);
}

/*
 * Function name: attacked_by
 * Description:	  This function is called when somebody attacks this object
 *                It will call a number of hooks which should be used
 *                to make the npc answer the attack.
 *
 * Arguments:	  ob - The attacker
 */
void
attacked_by(object ob)
{
    object *arr;
    
    /* This is done before the :: calls so we easily can check if 
     * we already were in combat. */
    this_object()->hook_attacked(ob);
    
    ::attacked_by(ob);
    
    arr = this_object()->query_team_others();
    arr->hook_friend_attacked(this_object(), ob);
}

/*
 * Function name: notify_death
 * Description  : Called when we die. It will fire off the correct hooks.
 */
void
notify_death(object killer)
{
    object *arr;

    ::notify_death(killer);

    this_object()->hook_killed(killer);
    
    arr = this_object()->query_team_others();
    arr->hook_friend_killed(this_object(), killer);

    if (gBelongsToArmy)
        E(TO)->npc_killed(gBelongsToArmy);
}

/*
 * Function name: notify_you_killed_me
 * Description:   This functions is called when 'I' kill something
 * Arguments:     ob - The object I killed
 */
void
notify_you_killed_me(object ob)
{
    object *arr;

    seteuid(getuid(this_object()));
    GRAVE_CONTROLLER->killed(this_object(), capitalize(ob->query_real_name()));

    this_object()->hook_killed_enemy(ob);
    
    arr = this_object()->query_team_others();
    arr->hook_friend_killed_enemy(this_object(), ob);
}

/*
 * Function Name: enemy_leave
 * Description  : This is called whenever the LIVE_O_ENEMY_CLING prop
 *                is called in a Krynn npc. It's used to find out
 *                when an enemy leaves combat.
 *                I'd like this to be changed to a more suitable function
 *                when one is added to the lib.
 */
void
enemy_leave()
{
    /* Only calls from the combat system are interesting */
    if (calling_function(-1) != "cb_adjust_combat_on_move")
        return;
    
    this_object()->hook_enemy_left(this_player(), 
        this_player()->query_prop(LIVE_S_LAST_MOVE));
}

/*
 * The prop can't be removed, overwriting it should still work though.
 */
public int
remove_prop_live_o_enemy_cling()
{
    return 1;
}

/*
 * Default Combat Hooks
 *
 * Redifine these if you want your npc to do something else.
 */

/*
 * Function name: help_friend
 * Description:   Help my friends by attacking their attacker
 * Arguments:     attacker - The person who attacked my friend
 */
public void
help_friend(object ob)
{
    if (ob && !query_attack() && environment(ob) == environment())
    {
        command("say You scum, stop fighting my friend!");
        this_object()->action_attack(ob);
    }
}

/*
 * Function name: hook_friend_attacked
 * Description:   This is called when someone attacks a team member of mine
 * Arguments:     friend - My team mate
 *		  attacker - The attacker
 */
void
hook_friend_attacked(object friend, object attacker)
{
    if (query_attack())
	return;

    if (random(10))
	set_alarm(rnd(), 0.0, &help_friend(attacker));
}

/*
 * Function name: hook_friend_attack
 * Description  : This is called when my friend attacks someone.
 *                We help out most of the time.
 */ 
void
hook_friend_attack(object friend, object enemy)
{
    if (query_attack())
        return;
    
    if (random(10))
        set_alarm(rnd(), 0.0, &help_friend(enemy));
}

/*
 * Function name: set_extra_long
 * Description:   Add an extra long description to the mobile 
 * Arguments:     str - The string
 */
void
set_extra_long(string str)
{
    extra_long = str;
    remove_subloc(SUBLOC);
    add_subloc(SUBLOC, this_object());
}

/*
 * Function name: show_subloc
 * Description:   This function is called to get the extra str
 * Arguments:     subloc  - The name of this sublocation
 *		  me      - this_object()
 * 		  for_obj - Who wants this description
 * Returns:	  The extra string to write
 */
string
show_subloc(string subloc, object me, object for_obj)
{
    if (subloc == SUBLOC)
    {
        if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	{
	    return "";
	}

        return check_call(extra_long);
    }

    return ::show_subloc(subloc, me, for_obj);
}

/*
 * Function name: react_introduce
 * Description:   React to an introduction. The default is to introduce
 *                back at the person who introduced/was introduced.
 *                Redefine this function if you want your own introduction.
 * Arguments:     who introduced to me. Can be 0 if there was no one specific.
 */
public varargs void
react_introduce(mixed who = 0)
{
    object ob;
    who = lower_case(who);
    
    if (!(ob = find_player(who)))
        return;
    
    this_object()->action_introduce(ob);
}

/*
 * Function name: add_introduced
 * Description:   Called when someone introduced to the npc.
 * Arguments:     who was introduced. this_player() did the
 *                introduction. not necessarily the same as
 *                who.
 */
public void
add_introduced(string who)
{
    if (do_intro && !query_attack())
        set_alarm(rnd() * 2.0, 0.0, &react_introduce(who));
}

/*
 * Function name: set_introduce
 * Description:   Switch reacting to introduction on or off.
 * Arguments:     on: 1, off:0
 */
public void
set_introduce(int on)
{
    do_intro = on;
}

/* Function name: query_introduce
 * Description:   Returns the state of automatic introductions
 * Returns:       int - 1 on, or 0 off
 */
public int
query_introduce()
{
    return do_intro;
}

/*
 * Function name: wield
 * Description:   Called from the weapon the NPC is trying to
 *                wield. The purpose of the function is to
 *                remove the standard wield messages.
 * Arguments:     wep - The weapon to wield.
 * Returns:       True or the result from other functions.
 */
public nomask mixed
wield(object wep)
{
    mixed tmp;

    if (!gWep_patch)
    {
        gWep_patch = 1;
        gWep_func = wep->query_wf();

        if (stringp((tmp = ::wield(wep))))
            gWep_patch = 0;
        else
            wep->set_wf(TO);

        return tmp;
    }
    else
    {
        gWep_patch = 0;
        wep->set_wf(gWep_func);

        if ((!gWep_func) || (!(tmp = gWep_func->wield(wep))))
            return 1;
        else
            return tmp;
    }
}

/*
 * Function name: wear
 * Description:   Called from the armour the NPC is trying to
 *                wear. The purpose of the function is to remove
 *                the standard wear messages.
 * Arguments:     arm - The armour to wear,
 * Returns:       True or the result from other function.
 */
public nomask mixed
wear(object arm)
{
    mixed tmp;

    arm->set_af(gArm_func);

    if ((!gArm_func) || (!(tmp = gArm_func->wear(arm))))
        return 1;
    else
        return tmp;
}

/*
 * Function name: wear_arm
 * Description:   Makes sure that 'wear' gets called, if
 *                the armour gets worn.
 * Arguments:     arm - The armour to wear.
 * Returns:       True or the result from ::wear_arm
 */
public nomask mixed
wear_arm(object arm)
{
    mixed tmp;

    gArm_func = arm->query_af();
    
    if (!stringp((tmp = ::wear_arm(arm))))
        arm->set_af(TO);

    return tmp;
}

/*
 * Function name: query_level_adj
 * Description:   Return the proper adjectiv.
 * Arguments:     level - The level of the monster, 1 - 8
 */
public string
query_level_adj(int level)
{
    string *levels = ({ "weak", "small", "average", "strong", "muscular", 
                            "powerful", "tough", "lethal" });
    
    level--;

    if ((level < 0) || level >= sizeof(levels))
        return "strange";
    
    return levels[level];
}

/*
 * Function name: query_level_desc
 * Description:   Get a proper description depending on the level
 * Arguments:     level - The level, 1 - 8
 * Returns:       The proper level string.
 */
public string
query_level_desc(int level)
{
    string *descs = ({ "He doesn't look very threatening.",
                           "He looks threatening.", 
                           "You better not mess with him.",
                           "He looks like he is a good fighter.",
                           "He looks like he is a very good fighter.",
                           "He seems to be able to kill you easily.",
                           "He looks like he is an extremely good fighter.",
                           "He looks like he can crush you in no time!",
                           });
    level--;
    
    if ((level < 0) || level >= sizeof(descs))
        return "He looks strange.";
    
    return descs[level];

}


/* created by Aridor 08/24/93 */

/*
 * Function name: set_color
 * Description:   Set the new color on the monster, ie blue, red, black.
 *                Depending on which army it belongs to.
 * Arguments:     str - The new color.
 */
public void
set_color(string str)
{
    gColor = str;
}

/*
 * Function Name: query_color
 * Description  : Returns the color of the npc if its set.
 */
public string
query_color()
{
    return gColor;
}

/*
 * Function name: set_belongs_to_army
 * Description:   This function is automatically called from the
 *                warfare routines (Krynn/common/warfare/*) in order
 *                to indentify this npc as belonging to a specific army.
 * Arguments:     the Npc Name
 */
void
set_belongs_to_army(string npc)
{
    gBelongsToArmy = npc;
}

/*
 * Function name:
 * Description:
 * Arguments:
 * Returns:
 */
