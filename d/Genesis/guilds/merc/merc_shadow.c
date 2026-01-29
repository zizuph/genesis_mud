/*
 * THIS WILL MOVE THE PLAYER TO THE SPARKLE SHADOW
 */
inherit "/std/guild/guild_occ_sh";

#include "/d/Krynn/common/defs.h"
#include <const.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>
#include <wa_types.h>
#include <options.h>
#include "merc.h"

#define ON 1
#define OFF 0

private int move_to_sparkle(object ob);


/*
 * This formula gives the mercenary an advantage of 100, given equal stats
 *   and skills. According to 'man task', against TASK_DIFFICULT, this yields
 *   32.08% success. 
 */

/* (skill(max of 100) * 2 + ((int + wis) / 2)) */
#define TASK_LIST       ({ SKILL_WEIGHT, 200, SS_MERC_TACTICS, SKILL_WEIGHT, 100, \
                        SKILL_AVG, TS_INT, TS_WIS, SKILL_END })
/* ((int + wis + dis) * 2 / 3) */
#define VICTIM_LIST     ({ SKILL_WEIGHT, 200, SKILL_AVG, TS_INT, TS_WIS, \
                        TS_DIS, SKILL_END })

#define BLOCK_BONUS(x)  x->query_skill(SS_MERC_TACTICS) * 2 + (x->query_stat(SS_INT) + x->query_stat(SS_WIS)) / 2

#define BLOCK_AVOID(x)  (x->query_stat(SS_INT) + x->query_stat(SS_WIS) + x->query_stat(SS_DIS)) * 2 / 3

int gLordStatus, gDefending, gDefending_alarm;
string gLord;
object gDefended;

/* object arrays for mercy use */
object *att_ob, *att_me;

/*
 * Function   : query_guild_tax_occ
 * Description: Standard function that returns the amount of
 *              tax the guild charges.
 * Returns    : int - The tax amount
 */
nomask public int
query_guild_tax_occ()
{
    int tax;
    string lord;

    lord = MCREST->query_members_lord(shadow_who->query_name());

    if (lord == "none")
	return MERC_TAX;

    if (lord != shadow_who->query_name())
	return MERC_FOLLOWER_TAX;

    switch(MCREST->query_lord_status(lord))
    {
        case MERC_STATUS_ASPIRING:
	    tax = MERC_ASPIRING_TAX;
	    break;
	case MERC_STATUS_LORD:
	    tax = MERC_LORD_TAX;
	    break;
	case MERC_STATUS_WARLORD:
	    tax = MERC_WARLORD_TAX;
	    break;
	default:
	    tax = MERC_TAX;
    }

    return tax;
}

/*
 * Function   : query_guild_style_occ
 * Description: Standard function to return the guild style for this
 *              guild - fighter, magic, cleric, thief or ranger.
 * Returns    : string - the style
 */
nomask public string
query_guild_style_occ()
{
    return MERC_STYLE;
}
 
/*
 * Function   : query_guild_name_occ
 * Description: Standard function that returns the guild name.
 *              This will be used in such things as listing
 *              your guilds while meditating.
 * Returns    : string - the guild name
 */
nomask public string
query_guild_name_occ()
{
    return MERC_NAME;
}

/* Function   : query_merc_level
 * Description: Unique militia function that gives the level of
 *              the member.
 * Returns    : int - the level of the member
 */
public nomask int
query_merc_level()
{
    return min(MAX_GUILD_LEVEL, shadow_who->query_stat(SS_OCCUP) / 10);
}

/* Function   : query_guild_title_occ
 * Description: Standard function that returns the title the
 *              mortal player has for this guild.
 * Returns    : string - the title
 */
nomask public string
query_guild_title_occ()
{
    string tmp, lgender;
    int skill, pstatus, level, gender;

    skill  = shadow_who->query_skill(SS_MERC_TITLE);
    pstatus = MCREST->query_lord_status(shadow_who->query_name());
    gender = shadow_who->query_gender();
    level = query_merc_level();

    if (!skill)
        shadow_who->set_skill(SS_MERC_TITLE, 1);

    if (!gLord) 
	gLord = MCREST->query_members_lord(shadow_who->query_name());

    if(!gLordStatus)
        gLordStatus = MCREST->query_lord_status(gLord);

    if (skill == 3)
	return "";

    if (skill == 2)
	return "Mercenary";

    /* The cause titles */
    if (skill == 4)
    {
        lgender = MCREST->query_lord_gender(gLord);

        if (gLord == "none" || gLord == shadow_who->query_name())
        {
            if (gender == G_MALE)
                return MERC_MTITLES[level];
            else
                return MERC_FTITLES[level];
        }

        if (lgender == "none")
     	    lgender = "lord";

        if (gLordStatus > 2)
	    tmp = " of " + C(gLord) + " the War" + lgender;
        else
    	    tmp = " of " + C(lgender) + " " + C(gLord);

	if (pstatus < 2)
	{
	    if (shadow_who->query_stat(SS_OCCUP) > 200)
		return "Mythical Warrior"+tmp;

	    if (gender == G_MALE)
		return MERC_MTITLES[level] + tmp;
	    else
		return MERC_FTITLES[level] + tmp;
        }

        if (pstatus == 2)
        {
            if (shadow_who->query_stat(SS_OCCUP) > 200)
                if (gender == G_MALE)
		    return "Mythical Mercenary Lord"+tmp;
	        else
		    return "Mythical Mercenary Lady"+tmp;
	    
            if (gender == G_MALE)
		return MERC_LORD_TITLES[level] + tmp;
            else
		return MERC_LADY_TITLES[level] + tmp;
        }
    }

    if (pstatus < 2)
    {
	if (gender == G_MALE)
	    return MERC_MTITLES[level];
        else
	    return MERC_FTITLES[level];
    }

    if (pstatus == 2)
    {
        if (gender == G_MALE)
	    return MERC_LORD_TITLES[level];
        else
	    return MERC_LADY_TITLES[level];
    }

    if (pstatus == 3)
    {
        if (gender == G_MALE)
	    return MERC_WARLORD_TITLES[level];
        else
	    return MERC_WARLADY_TITLES[query_merc_level()];
    }

}

/* Function name: query_def_post
 * Description  : Standard function that gives the path to the
 *                guild's post office for mail upon login notification
 *                purposes.
 * Returns      : string - the pathname to the new postoffice
 */
public string
query_def_post()
{
    return shadow_who->query_def_post();
}

/*
 * Function name : query_guild_trainer_occ
 * Description  : Standard function that returns one or more references
 *                to the object that defines sk_train_max for the player.
 *                The returned reference can be a string reference, an
 *                object pointer or an array of those. Prevents skill decay.
 * Returns       : string * - an array of paths to the guild's trainers.
 */

nomask public mixed
query_guild_trainer_occ()
{
    return ({ MTRAIN, MTRAIN2, MTRAIN3 });
}

/*
 * Function name : query_guild_skill_name
 * Description  : Standard function to return a name for the guild's
 *                special skills in order to print them out nicely
 *                when a player uses the 'skills' command, rather than
 *                seeing 'special'.
 * Arguments     : int type - the number of the skill assigned by the
 *                 liege of the domain
 * Returns       : 0 if no skill of this guild, else the string.
 */
public mixed
query_guild_skill_name(int type)
{
    if (type == SS_MERC_TACTICS)
        return "mercenary tactics";

    return 0;
}

/*
 * Function name : query_guild_not_allow_join_occ
 * Description  : Standard function that deals with allowing or not
 *                allowing this member to join another guild. It is
 *                also called each time the player logs on, so race
 *                checks and such can be called here or in the
 *                query_guild_keep_player() function.
 * Arguments    : object player - the player to test
 *                string type   - the guild type
 *                string style  - the guild style
 *                string name   - the guild name
 * Returns      : int 1 - if the player is not allowed
 *                    0 - if the player is allowed
 */
nomask public int
query_guild_not_allow_join_occ(object player, string type, string style,
  string name)
{
    /* This checks to make sure that the new guild is not occupational. */
    if (::query_guild_not_allow_join_occ(player, type, style, name))
        return 1;

    return 0;
} 

/*
 * Function name : query_leaving_penalty
 * Description   : function that determines the experience penalty a
 *		   mercenary will suffer for leaving the guild, based
 * 		   level. The penalty decreases as the experience of
 * 		   the mercenary (and how much he has benefitted the 
 *		   guild) increases.
 * Arguments     : none
 * Returns       : int - the amount of combat experience to deduct
 */
public int
query_leaving_penalty()
{
    int level = shadow_who->query_stat(SS_OCCUP) / 10;
    int pen;

    if (level >= FULL_PENALTY_LEVEL)
    {
        pen = FULL_PENALTY(shadow_who);
    }
    else if (level >= MID_PENALTY_LEVEL)
    {
	    pen = MID_PENALTY(shadow_who);
    }
    else if (level >= LOW_PENALTY_LEVEL)
    {
        pen = LOW_PENALTY(shadow_who);
    }
    else
    {
	    pen = NO_PENALTY(shadow_who);
    }

    return pen;
}

/*
 * Function name : remove_occ_merc
 * Description   : Unique militia function to remove a guild member with
 *                 all the proper clearing of skills/guild stat/soul/
 *                 shadow/guild object etc.
 * Arguments    : object who    - the member to expel
 *                string reason - the reason they are to be expelled
 * Returns       : 1 - success,  0 - fail
 */
public int
remove_occ_merc(object who, string reason)
{
    int ret, penalty;
    object emblem;
 
    if (!objectp(who))
        return 0;
 
    /* Remove special skills */
    who->remove_skill(SS_MERC_TACTICS);
    who->remove_skill(SS_MERC_TITLE);
    who->remove_skill(SS_MERC_RACK);

    /* Penalty for leaving determined by function query_leaving_penalty() */
    penalty = query_leaving_penalty();

    /* Lower the penalty for leaving for those who have bribed Maligant */
    if (who->query_prop(MALIGANT_REMOVED_LEAVE_PENALTY))
        penalty = 0;
    else if (who->query_prop(MALIGANT_REDUCED_LEAVE_PENALTY))
	penalty = penalty / 2;

    who->add_exp(-(penalty), 1);
 
    /* Clear the player's guild stat */
    shadow_who->clear_guild_stat(SS_OCCUP);
 
    /* Reset start location */
    if (who->query_default_start_location() == MSTART)
        who->set_default_start_location(who->query_def_start());
 
    /* Update the member list. */
    MJOIN->remove_member(shadow_who->query_real_name());

    /* Update the crest list */
    if (MCREST->query_crest_member(shadow_who->query_name()))
	MCREST->remove_crest_member(shadow_who->query_name());

    if (MCREST->query_crest_lord(shadow_who->query_name()))
	MCREST->remove_crest_lord(shadow_who->query_name());

    /* Give a message before removing the guild emblem. */
    emblem = present(MITEM_ID, shadow_who);
    if(objectp(emblem))
    {
        who->catch_tell("Your " + emblem->short() + " vanishes in puff of "+
	    "black smoke.\n");
        emblem->remove_object();
    }
 
    /* Remove the guild soul and update the commands. */
    shadow_who->remove_cmdsoul(MSOUL);
    shadow_who->update_hooks();
 
    /* Remove the mercenary from the guildhouse if he's there. */
    environment(shadow_who)->remove_merc_members(shadow_who);
 
    /* Keep a cycling log of those removed from the guild. */
    write_file(MERC_LOG, extract(ctime(time()), 4, 15) + " " +
        capitalize(shadow_who->query_real_name()) + " removed because of " +
        reason + ": "+penalty+" ("+
	(shadow_who->query_prop(MALIGANT_REMOVED_LEAVE_PENALTY) ? "REMOVED" : 
	   (shadow_who->query_prop(MALIGANT_REDUCED_LEAVE_PENALTY) ? "REDUCED" :
	   "NORMAL"))+").\n");
 
    /* Remove the guild shadow last.  This also resets tax to 0. */
    ret = remove_guild_occ();

    return ret;
}

 
/*
 * Function name : query_guild_keep_player
 * Description   : Standard function to test if we want to keep the
 *                 player in the guild when the shadow is autoloading
 *                 upon login.
 * Arguments     : who - the player to test
 * Returns       : 1 if keeping, 0 if not
*/
public int
query_guild_keep_player(object who)
{
    int align;
    string race, reason = "";
 
    setuid();
    seteuid(getuid());
    
    /*
     * Time for you to move now mate, lets go to Sparkle!
     *
     * Lunatari 2006
     */
    if(MOVE_MERCS == 1)
    {
        set_alarm(1.0, 0.0, &move_to_sparkle(who));

	
        who->catch_msg("You feel your body twitch slightly as" +
		       " you login to the realm.\n");

	return 0;
    }

    /* Wizards are exempt. */
    if (who->query_wiz_level())
        return 1;

    /* TEMPORARY 
     * For how long? Lunatari 2006-01-16
     */
    return 1;

    /* Throw out militia with alignment more evil than the min 
     * 
     * What is this doing here? Lunatari 2006-01-24
     */
    if (align < 0)
    {
        reason = ("evil: " + align);
        who->catch_tell("You are too evil to be trusted in Thornlin!\n");
    }

    /* Throw out all sorts of goblins. */
    if (who->query_race() == "goblin")
    {
        race = who->query_race_name();
        reason = ("goblin kind: " + race);
        who->catch_tell("No goblins are allowed in the mercenaries!\n"); 
    }

    /* Make sure the admin room is loaded */
    MJOIN->teleledningsanka();

    if (MJOIN->query_not_allowed(who->query_real_name()))
    {
        reason = ("not-allowed list");
        who->catch_tell("You have betrayed the mercenaries!\n");
    }
     
    /* Return 1 here so we can make a few adjustments of our own. */
    if (strlen(reason))
        set_alarm(1.0, 0.0, &remove_occ_merc(who, reason));
 
    return 1;
}

/*
 * Function name : init_merc_occ_member
 * Description   : Add necessary guild items to the player and
 *                 do any other kind of initialization necessary
 *                 after a 1 second alarm to make sure that login
 *                 was completed.
 */
public nomask void
init_merc_occ_member()
{
    object mitem;
    string *notifications;
    int i;

     /* Clone the guild emblem and move it to the player. */
    if (objectp(mitem = clone_object(MITEM)))
    {
        mitem->move(shadow_who, 1);
    }

    /* Make sure the member list is updated minus wizards and juniors. */
    MJOIN->teleledningsanka();

    if (!shadow_who->query_wiz_level() &&
       extract(shadow_who->query_real_name(), -2) != "jr")
 
    MJOIN->add_member(shadow_who->query_real_name());

    /* If Mercenary has killed a mercenary npc, they are punished */
    /*     if they sleep at the mercenary guild.                  */
    if (MJOIN->query_warned(shadow_who->query_real_name())
       && shadow_who->query_default_start_location() == MSTART)
    {
        setuid();
	seteuid(getuid());

        MSTART->punish_merc(shadow_who);
    }

    if (MCREST->query_need_notification(shadow_who->query_name()))
    {
	notifications = MCREST->get_notifications(shadow_who->query_name());

        shadow_who->catch_msg("A messenger from the halls of the Mercenaries "+
	    "comes and relays the following information:\n");

	for (i = 0; i < sizeof(notifications); i++)
	    shadow_who->catch_msg(notifications[i]);
    }

    if (MCREST->query_registered_lord(shadow_who->query_name()) &&
	MCREST->query_have_applicant(shadow_who->query_name()))
	shadow_who->catch_msg("You have unresolved applications to your "+
	   "cause, you can handle these in the crest room of the Mercenary "+
	    "halls.\n");
  
    /* Add the guild's soul to the player. */
    shadow_who->add_cmdsoul(MSOUL);
    shadow_who->update_hooks();

    if (MJOIN->query_on_banish_list(shadow_who->query_name()))
    {
        shadow_who->add_prop(MALIGANT_REMOVED_LEAVE_PENALTY, 1);
        MJOIN->remove_from_banish_list(shadow_who->query_name());

        if (file_name(environment(shadow_who)) ==
	    "/d/Genesis/guilds/merc/room/start")
	{
	    tell_room(MSTART, "Several guards come and drag "+
		QTNAME(shadow_who)+" away to the north.\n", shadow_who);
	    shadow_who->catch_tell("Several guards come and drag you "+
		"roughly out of the Mercenary Halls, explaining that "+
		"you have been banished by powers beyond even Maligant's "+
		"control.\n");
	    shadow_who->move(MJOIN);
        }
        else
	{
	    shadow_who->catch_tell("You are being removed from the Mercenary "+
		"guild by powers beyond even Maligant's control.\n");
	}

	remove_occ_merc(shadow_who, "banished");

    }
}

/*
 * Function name : add_occ_shadow
 * Description   : Shadow an object with this shadow
 * Arguments     : object who - the object to shadow
 * Returns       : as shadow_me in /std/guild/guild_base.c
 */
int
add_occ_shadow(object who)
{
    int ret;
    ret = shadow_me(who, "occupational", MERC_STYLE, MERC_NAME);

    if (ret == 1)
        init_merc_occ_member();

    return ret;
}

/*
 * Function name: init_merc_shadow
 * Description  : This function is called from autoload_shadow and may
 *                be used to initialize the shadow when it's loaded.
 * Arguments    : The argument string sent to autoload_shadow.
 */
void
init_occ_shadow(string arg)
{
    /* delay so that player completes login before we continue */
    set_alarm(1.0, 0.0, &init_merc_occ_member());
}


/* Specials section of the shadow */


/*
 * Function   : query_my_shield()
 * Description: Get the shield, if any, worn by this person
 * Returns    : the shield object, or 0 if no shield is worn
 */
public object
query_my_shield()
{
    object *worn_armours;
    object shield;
    int i;

    worn_armours = shadow_who->query_armour(-1);

    for (i = 0; i < sizeof(worn_armours); i++)
    {
	if (worn_armours[i]->query_at() == A_SHIELD)
	    shield = worn_armours[i];
    }

    return shield;
}

/*
 * Function   : query_my_weapon()
 * Description: Get a wielded weapon of this person
 * Returns    : object of the weapon, or 0 if no weapon is wielded
 */
public object
query_my_weapon()
{
    object *wielded_weapons;
    wielded_weapons = shadow_who->query_weapon(-1);

    if (sizeof(wielded_weapons) == 1)
    {
       return wielded_weapons[0];
    }

    if (random(2) == 0)
	return wielded_weapons[0];
       else
	return wielded_weapons[1];
}

/*
 * Function   : query_defending()
 * Description: Is this person defending someone else?
 * Returns    : true if they are, false if they are not
 */
public int query_defending()
{
    return gDefending;
}

/*
 * Function   : query_defended()
 * Description: Whom is this person defending?
 * Returns    : the object of the defended person
 */
public object query_defended()
{
    return gDefended;
}

/*
 * Function   : set_defended()
 * Arguments  : ob: the object to defend
 * Description: Set whom this person is defending
 * Returns    : void
 */
void set_defended(object ob)
{
    gDefended = ob;
}

/*
 * Function   : set_defending()
 * Arguments  : i: 1 if yes, 2 if no
 * Description: Set if this person is defending someone else or not
 * Returns    : void
 */
void set_defending(int i)
{
    gDefending = i;
}

/*
 * Function   : reset_defending()
 * Description: Reset the defend other special
 * Returns    : void
 */
void reset_defending()
{
    shadow_who->catch_msg("You recover your position, and are ready to "+
	"defend another.\n");
    shadow_who->remove_prop(PLAYER_I_MDEFEND_RESETTING);
}

/*
 * Function   : stop_defending_silent()
 * Description: Stop defending another person with no messages sent
 * Returns    : void
 */
public void stop_defending_silent()
{
    int skill = shadow_who->query_skill(SS_MERC_TACTICS);
    float reset = itof(random(15 - skill / 10) + (10 - skill / 10) + 5);

    if (!shadow_who->query_prop(PLAYER_I_MDEFEND_RESETTING))
        set_alarm(reset, 0.0, "reset_defending");

    shadow_who->add_prop(PLAYER_I_MDEFEND_RESETTING, time());
    gDefended->remove_defender(shadow_who);
    gDefended = 0;
    set_defending(OFF);

    if (gDefending_alarm)
	remove_alarm(gDefending_alarm);
}

/*
 * Function   : stop_defending()
 * Description: stop defending another person and send the appropriate messages
 * Returns    : void
 */
public void stop_defending()
{
    int skill = shadow_who->query_skill(SS_MERC_TACTICS);
    float reset = itof(random(15 - skill / 10) + (10 - skill / 10) + 5);

    if (query_defending())
    {
        if (environment(gDefended) == environment(shadow_who) &&
		sizeof(gDefended->query_enemy(-1)))
        {
	gDefended->catch_msg(shadow_who->query_The_name(gDefended)+" falls "+
	   "out of position and is no longer defending you.\n");
	shadow_who->catch_msg("You fall out of position and are no longer "+
	   "defending "+gDefended->query_the_name(shadow_who)+".\n");
        tell_room(environment(shadow_who), QCTNAME(shadow_who)+" falls out of "+
           "position and is no longer defending "+QTNAME(gDefended)+".\n",
	   ({ shadow_who, gDefended }));
        }
        else if (environment(gDefended) == environment(shadow_who))
        {
            gDefended->catch_msg(shadow_who->query_The_name(gDefended)+" moves "+
	        "from "+POSSESSIVE(shadow_who)+" position at your side.\n");
	    shadow_who->catch_msg("You move from your position at "+
		gDefended->query_the_name(shadow_who)+"'s side.\n");
            tell_room(environment(shadow_who), QCTNAME(shadow_who)+" moves from "+
		POSSESSIVE(shadow_who)+" position at "+QTNAME(gDefended)+
		"'s side.\n",
		({ shadow_who, gDefended }));
        }
        else
        {
            shadow_who->catch_msg("You stop trying to defend "+
		gDefended->query_the_name(shadow_who)+" because "+
		PRONOUN(gDefended)+" is no longer here.\n");
        }
        set_alarm(reset, 0.0, "reset_defending");
        shadow_who->add_prop(PLAYER_I_MDEFEND_RESETTING, time());
        gDefended->remove_defender(shadow_who);
	    gDefended = 0;
     	set_defending(OFF);
    }
    else
    {
        shadow_who->catch_msg("You are not defending anyone else.\n");
    }

    if (gDefending_alarm)
	remove_alarm(gDefending_alarm);
}

/*
 * Function   : leave_env()
 * Arguments  : from: the old room, to: the new room
 * Description: Move a person from one room to another
 * Returns    : void
 */
public void leave_env(object from, object to)
{
    if (query_defending())
        stop_defending();

    if (shadow_who->query_prop(MERC_O_ADVANCING))
        shadow_who->stop_advance(shadow_who);

    if (shadow_who->query_prop(MERC_O_RETREATING))
	shadow_who->stop_retreat(shadow_who);	
}

/*
 * Function   : defend_other()
 * Arguments  : ob: the person I will defend
 *		i: 1 if that person is defended already, 0 if they are not
 * Description: 
 * Returns    : 
 */
public int defend_other(object ob, int i)
{
    object shield = query_my_shield();
    object otherdef;
    int skill = shadow_who->query_skill(SS_MERC_TACTICS);
    float duration = itof(skill / 2 + random(skill));

    gDefending_alarm = set_alarm(duration,0.0, "stop_defending");

    if (i == 1)
    {
        shadow_who->catch_msg("You move beside "+ob->query_the_name(shadow_who)+
	    " and begin to defend "+OBJECTIVE(ob)+" with your "+
	    shield->short()+".\n");
        ob->catch_msg(shadow_who->query_The_name(ob)+" moves beside you and "+
	    "begins to defend you with "+POSSESSIVE(shadow_who)+" "+
	    shield->short()+".\n");
        tell_room(environment(shadow_who), QCTNAME(shadow_who)+" moves beside "+
            QTNAME(ob)+" and begins to defend "+OBJECTIVE(ob)+" with "+
	    POSSESSIVE(shadow_who)+" "+shield->short()+".\n", ({ shadow_who, ob }));
        ob->add_defender(shadow_who, 1);
	set_defended(ob);
        set_defending(ON);
        return 1;
    }

    otherdef = ob->query_defenders()[0];
    shadow_who->catch_msg("You notice "+otherdef->query_the_name(shadow_who)+
	" already defending "+ob->query_the_name(shadow_who)+". You move to "+
	ob->query_the_name(shadow_who)+"'s opposite side, and begin to defend "+
	OBJECTIVE(ob)+" with your "+shield->short()+".\n");
    ob->catch_msg(shadow_who->query_The_name(ob)+" moves to your side opposite "+
	otherdef->query_the_name(ob)+" and begins to defend you with "+
	POSSESSIVE(shadow_who)+" "+shield->short()+", too.\n");
    otherdef->catch_msg(shadow_who->query_The_name(otherdef)+" moves to "+
        ob->query_the_name(otherdef)+"'s side opposite you, and begins to "+
        "defend "+OBJECTIVE(ob)+", too.\n");
    tell_room(environment(shadow_who), QCTNAME(shadow_who)+" moves to the "+
        "other side of "+QTNAME(ob)+" and begins to defend "+OBJECTIVE(ob)+
	" along with "+QTNAME(otherdef)+".\n", ({ ob, shadow_who, otherdef }));
    ob->add_defender(shadow_who, 2);
    set_defended(ob);
    set_defending(ON);
    return 1;
}

/*
 * Function   : query_not_attack_me()
 * Arguments  : who: the attacker, aid: the attack ID
 * Description: Determines whether an attack is successful
 * Returns    : true if the attack fails, false if the attack succeeds
 */
int query_not_attack_me(object who, int aid)
{
    object combat_object = who->query_combat_object();
    int attack = combat_object->query_attack(aid), task_value, chance;
    object def, shield, leader;
    int block_bonus, enemy_bonus;

    if (gDefending == 1)
        return shadow_who->query_not_attack_me(who, aid);

    if (!attack)
        return shadow_who->query_not_attack_me(who, aid);

    if (!(shield = query_my_shield()))
        return shadow_who->query_not_attack_me(who, aid);

    if (shadow_who->query_prop(LIVE_I_STUNNED))
	    return shadow_who->query_not_attack_me(who, aid);

    task_value = TASK_DIFFICULT;

    /* If merc can't see opponent, make blocking much more difficult */
    if (!CAN_SEE(shadow_who, who))
    {
        task_value = task_value + 
	    ((100 - shadow_who->query_skill(SS_BLIND_COMBAT)) * 3);
    }

    if (!gLord) 
        gLord = MCREST->query_members_lord(shadow_who->query_name());

    /*
     * Add a bonus if Mercenary is being led by his lord, +3% for
     *    lord, +6% for warlord.
     */
    if ((leader = shadow_who->query_leader()) && 
	   (gLord == leader->query_name()))
    {
        switch(MCREST->query_lord_status(leader->query_name()))
        {
	      case MERC_STATUS_LORD:
		    task_value -= 20;
		    break;
	      case MERC_STATUS_WARLORD:
		    task_value -= 40;
		    break;
	      default:
		  break;
        }
    }

    /* Add this check to limit the max effectiveness of block */
    block_bonus = BLOCK_BONUS(shadow_who);
    enemy_bonus = BLOCK_AVOID(who);
	
    /*
     * A max of 66% blocking due to merc task list of 200 more than 
     * enemy task list 
     * 
     * Need to check this, the TAX doc says 33% block.
     */
    if (block_bonus >= enemy_bonus + 200)
    	task_value = task_value + 2 * (block_bonus - (enemy_bonus + 200));

    chance = shadow_who->resolve_task(task_value, TASK_LIST, who, VICTIM_LIST);

    if (chance > 0)
    {

	shadow_who->catch_msg("You block "+who->query_the_name(shadow_who)+"'s "+
            "attack with your "+shield->short()+".\n");
        who->catch_msg(shadow_who->query_The_name(who)+" blocks your "+
            "attack with "+POSSESSIVE(shadow_who)+" "+shield->short()+".\n");
        shadow_who->tell_watcher(QCTNAME(shadow_who)+" blocks "+QTNAME(who)+"'s "+
            "attack with "+POSSESSIVE(shadow_who)+" "+shield->short()+".\n", 
	    ({ def, who, shadow_who }));

	return 1;
    }
            
    return shadow_who->query_not_attack_me(who, aid);
}

/*
 * Function   : reset_merc_special()
 * Description: Reset the mattack special, this will be called from the shadow
 *              aswell as the soul.
 *
 * Added by Lunatari 2006-01-18
 */
void
reset_merc_special()
{
    if (shadow_who->query_skill(SS_MERC_AUTOMATTACK) && shadow_who->query_attack())
    {
        shadow_who->remove_prop(PLAYER_I_MATTACK_RESETTING);
	      shadow_who->command("$mattack");
      	return;
    }

    if (shadow_who->query_skill(SS_MERC_AUTOMATTACK))
    {
        shadow_who->remove_prop(PLAYER_I_MATTACK_RESETTING);
      	return;
    }

    shadow_who->catch_msg("\nYou feel able to attack again.\n\n");
    shadow_who->remove_prop(PLAYER_I_MATTACK_RESETTING);
}

/*
 * Function   : query_merc_shadow_version()
 * Description: A simple check to have some kind of version control of
 *              the shadow within the player compared to functions in the soul.
 */
int
query_merc_shadow_version()
{
  return MERC_SHADOWVERSION;
}

/*
 * Function   : adjust_combat_on_move
 * Description: This will be called when a player moves around to 
 *              block the bouncing ability of Mattack.
 *
 * Added by Lunatari 2006-01-18
 */
public void
adjust_combat_on_move(int leave)
{
   shadow_who->adjust_combat_on_move(leave);

   if (!leave)
   {
     if(shadow_who->query_prop(PLAYER_I_MATTACK_PREPARING))
     {
        shadow_who->catch_msg("Your movement prevents you from"+
          " completing your attack.\n");
   	    shadow_who->remove_prop(PLAYER_I_MATTACK_PREPARING);
	      shadow_who->add_prop(PLAYER_I_MATTACK_RESETTING,time());
	      set_alarm(itof(MATTACK_FAILSAFE), 0.0, reset_merc_special);
     }
   }
}

#define NEW_DIR "/d/Sparkle/guilds/mercs/"
#define MOVE_AGENT (NEW_DIR + "lib/move_agent")
#define NEW_SHADOW (NEW_DIR + "lib/merc_sadow")
#define NEW_LOG    (NEW_DIR + "log/shadow_move.log")
#define MOVE_LOG(x) write_file(NEW_LOG, ctime(time()) + " " + (x))

private int
move_to_sparkle(object ob)
{
    mixed err;
    string who = capitalize(ob->query_real_name());

    setuid();
    seteuid(getuid());

    MOVE_LOG("Sparkle Move shadow loaded for player " + who + ".\n");

    err =
	catch(MOVE_AGENT->log("Sparkle Move shadow loaded for player " + who + ".\n"));

  if(err)
  {
      MOVE_LOG("Cannot communicate with the move agent, reason: " + err);
      return 0;
  }
  
  // try to call move agent in the other domain
  // zero return value means it is not possible to move
  if (!(MOVE_AGENT->move(ob)))
  {
      MOVE_LOG("Sparkle move failed for player " + who +".\n");
      return 0;
  }

  // here try to purge all old guild things if some still exist

  MOVE_LOG("Sparkle move finished for player " + who + ".\n");

  return 1;
}
