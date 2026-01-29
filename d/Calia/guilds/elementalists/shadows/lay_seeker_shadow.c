/* 
 * Elemental Seekers of Calia Guild Shadow
 *
 * This is the guild shadow for the Elemental Seekers of Calia. This is
 * a clerical layman guild. 
 *
 * Created by Petros, December 2010
 * Modified for Seekers by Jaacar, May 2016
 * Modified to properly execute dicharge/expel - Mirandus - 2020
 */

#pragma save_binary

#include <ss_types.h>
#include <macros.h>
#include <files.h>
#include "../defs.h"

inherit "/std/guild/guild_lay_sh";
#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Defines
#define BEEN_BAD_BOY "_been_bad_boy"
#define PUNISHER ({"Lord Pyros","Lord Diabrecho","Lady Gu","Lady Aeria","Psuchae"})
#define DEATH_OBJECT (ELEMENTALIST_OBJS + "elemental_punishment")

#define DEFAULT_TITLES ({ "Seeker of the Elementals", \
                          "Seeker of Allegiance", \
                          "Seeker of Association", \
                          "Seeker of Mystery", \
                          "Seeker of Servitude" })
            
// Prototypes
public void     initialize_seeker();
public object   query_top_shadow();
public void     notify_arrival(object player);
public void     notify_departure(object player);

// Global Variables
static string   * titles = DEFAULT_TITLES; 

private int gTeamAlarm = 0;	                                           	                               

public string
my_time()
{
    return (ctime(time())[4..9] + ": ");
}

public string 
query_guild_style_lay() 
{ 
    return GUILD_STYLE; 
}

public string 
query_guild_name_lay() 
{ 
    return GUILD_ES_NAME; 
}

int 
query_guild_tax_lay() 
{ 
    return GUILD_ES_TAX; 
}

/* 
 * Return 1 if they try to join an occupational or layman guild, since
 * Elemental Clerics use up both layman and occupational slots. Set up 
 * a notify fail to say why in response to the join action. 
 */ 
public int
query_guild_not_allow_join_lay(object player, string type, 
                               string style, string name) 
{
    switch (type)
    {
    case "layman":
        notify_fail("You are a member of the Elemental Seekers of Calia "
            + "and cannot devote yourself to other side studies.\n");
        return 1;
    }
    
    return ::query_guild_not_allow_join_lay(player, type, style, name);
}

void
init_lay_shadow(string str)
{
    ::init_lay_shadow(); 

    set_alarm(1.0, 0.0, initialize_seeker);
}

/*
 * Function:    init_seeker_titles
 * Description: Seeker titles are dependent on:
 *                a) guildstat
 */
public void
init_seeker_titles()
{
    setuid();
    seteuid(getuid());

    titles = DEFAULT_TITLES;  
}

public void
initialize_seeker()
{
    setuid();
    seteuid(getuid());
    
    // Make sure the command soul gets added
    shadow_who->add_cmdsoul(ES_SOUL);
    shadow_who->add_cmdsoul(SPELL_MANAGER_SOUL);

    shadow_who->update_hooks();
    
    // Every caster guild using the new Genesis magic system will
    // use the mana shadow to get the new regeneration rates for mana.
    if (!query_top_shadow()->has_mana_shadow())
    {
        clone_object(MANA_SHADOW)->shadow_me(shadow_who);
    }
    
    init_seeker_titles();
    notify_arrival(shadow_who);

    shadow_who->catch_tell("\nWelcome, " + query_guild_title_lay() + "!\n\n");    
}

public void
remove_shadow()
{
    // We use the removal of the shadow as a way to ensure that the
    // spells for the command soul are removed.
    ES_SOUL->remove_spells(shadow_who);
    
    // We also need to remove the mana shadow. This removal assumes
    // that the person can only have one caster guild shadow.
    query_top_shadow()->remove_mana_shadow();

    notify_departure(shadow_who);
    
    ::remove_shadow();    
}

public void
remove_object()
{
    if (IS_CLONE)
    {
        // We don't want to notify when the master object is being removed
        notify_departure(shadow_who);
    }
    ::remove_object();
}

/*
public int 
calculate_adjusted_guild_stat()
{
    int real_guild_stat = shadow_who->query_stat(SS_LAYMAN);
    // We have our own calculation for guild stat here. Instead of basing
    // it on their "true" guild stat which can be gamed, we calculate
    // how much experience they've accrued since joining and convert that
    // into guild stat.
    setuid();
    seteuid(getuid());
    int starting_exp = GUILD_MANAGER->query_starting_exp(shadow_who);
    // use max exp instead of exp to help account for death situations. Also, we use "max" function in case query_max_exp isn't functioning correctly.
    int current_exp = max(shadow_who->query_max_exp(), shadow_who->query_exp()); 
    // We make it so that even if they "game" the system, we'll use 1/10 of
    // what they gamed as a minimum. This should help a bit with real death
    // situations
    int minimum_guild_stat = max(1, real_guild_stat / 10);
    int guild_exp = max(100, current_exp - starting_exp);
    // treat this adjusted exp as if the guild tax was 13
    int tax_rate = 13;
    int adjusted_guild_stat = shadow_who->exp_to_stat(guild_exp * tax_rate / (100 - tax_rate));
    // Separately, we also calculate practice level. A player can gain up to 50
    // guild stat by practicing a lot.
    int practice_level = GUILD_MANAGER->query_practice_level(shadow_who);
    int practice_adjustment = min(50, max(0, practice_level / 400));
    // Do the min/max adjustment. Range should be between 10% of real guild stat
    // up to the adjusted guild stat or real guild stat (whichever is lower)
    return min(real_guild_stat, max(minimum_guild_stat, adjusted_guild_stat)) + practice_adjustment;
}
/*
/*
 * Function name: query_stat
 * Description  : Get the compound value of a stat. Never less than 1.
 * Arguments    : int stat - Which stat to find.
 * Returns      : int - the stat value.
 */
 /*
public int
query_stat(int stat)
{
    int real_guild_stat = shadow_who->query_stat(stat);
    if (stat != SS_LAYMAN)
    {
        return real_guild_stat;
    }
    return calculate_adjusted_guild_stat();
}
*/

/*
 * Function:    query_seeker_level
 * Description: Returns the layman guild stat divided by 10.
 *              This will be used to determine the title
 *              of the player.
 */
public int
query_seeker_level()
{
    int level, cur_task;
    
    cur_task = GUILD_MANAGER->query_can_do_ec_task_six(shadow_who);
    if (cur_task)
    {
        level = 4;
        return level;
    }
    
    cur_task = GUILD_MANAGER->query_can_do_wor_task_four(shadow_who);
    if (cur_task)
    {
        level = 3;
        return level;
    }
    
    cur_task = GUILD_MANAGER->query_can_do_wor_task_three(shadow_who);
    if (cur_task)
    {
        level = 2;
        return level;
    }
    
    cur_task = GUILD_MANAGER->query_can_do_wor_task_two(shadow_who);
    if (cur_task)
    {
        level = 1;
        return level;
    }
    
    level = 0;
    return level; 
}


public string 
query_guild_title_lay() 
{
    int title_level, s;
    string full_title;

    title_level = query_seeker_level();

    s = sizeof(titles); 

    title_level = max(0, min(s - 1, title_level));
    full_title = titles[title_level];

    return full_title;
} 

/*
 * Function name: query_guild_trainer_lay
 * Description:   Return one or more references to the object that define
 *                sk_train_max for the player. The returned refernce can
 *                be a string reference, an object pointer or an array of
 *                those.
 * Returns:       See description.
 */
public mixed
query_guild_trainer_lay()
{
    return ({ ELEMENTALIST_TEMPLE + "ew_practice" });
}

/* function name: query_guild_keep_player
 * Description:   This gives you a chance to tell if you want to keep the
 *                the player when the shadow is autoloading when a player
 *                logs on.
 * Arguments:     player - the player
 * Returns:       1 - keep player, 0 - kick him out.
 */
public int
query_guild_keep_player(object player)
{
    int result = ::query_guild_keep_player(player);
    
    if (!result)
    {
        // Even the base shadow doesn't want to keep this player. Just return.
        return 0;
    }
    
    setuid();
    seteuid(getuid());
    // Conditions to kick out should be here, and should return 0
    if (GUILD_MANAGER->query_is_guild_expelled(player))
    {
        // Player has been kicked out of the guild, but somehow still has the
        // shadow. Do the kicking out here.
        player->catch_tell(sprintf("\n\n%'='|75s\n", "EXPELLED"));
        player->catch_tell(sprintf("\n%=-75s\n\n", "You have been expelled from the Elemental Seekers "
                                   + "guild by the Worshippers Council."));
        player->catch_tell(sprintf("%'='|75s\n\n", ""));
        GUILD_MANAGER->leave_seekers_guild(player);
        return 0;
    }
  
    if (GUILD_MANAGER->query_is_guild_discharged(player))
    {
        // Player has been kicked out of the guild, but somehow still has the
        // shadow. Do the kicking out here.
        player->catch_tell(sprintf("\n\n%'='|75s\n", "DISCHARGED"));
        player->catch_tell(sprintf("\n%=-75s\n\n", "You have been discharged from the Elemental Seekers "
                                   + "guild by the Worshippers Council."));
        player->catch_tell(sprintf("%'='|75s\n\n", ""));
        GUILD_MANAGER->leave_seekers_guild(player);
        return 0;
    }
  
    if (!GUILD_MANAGER->query_is_seeker(player))
    {
        // Player has been kicked out of the guild, but somehow still has the
        // shadow. Do the kicking out here.
        player->catch_tell(sprintf("\n\n%'='|75s\n", "REMOVED FROM GUILD"));
        player->catch_tell(sprintf("\n%=-75s\n\n", "You are no longer a member of "
                                   + "the Elemental Seekers guild."));
        player->catch_tell(sprintf("%'='|75s\n\n", ""));
        GUILD_MANAGER->leave_seekers_guild(player);
        return 0;
    }

    return 1;
}

/*
 * Function name: query_top_shadow
 * Description:   Because shadows exist in layers, sometimes you need
 *                to reference functions in a shadow above you. Calling
 *                functions can fail if one doesn't call from the top
 *                shadow. this function allows one to obtain the
 *                top most shadow, giving access to all functions.
 * Returns:       object - top level shadow
 */
public object
query_top_shadow()
{
    object last_me, me;
    
    me = shadow_who;
    last_me = me;
    while (me = shadow(me, 0))
    {
        // loop through to find the top level shadow who
        last_me = me;
    }   
    
    // We return now the top level shadow
    return last_me;
}

public int
is_elemental_seeker()
{
    return 1;
}

public object *
get_audience_for_notification(object player)
{
    if (!objectp(player))
    {
        return ({ });
    }

    object * members, * worshippers, * clerics, * wizards, *scops, * audience;
    
    string name = player->query_real_name();
    // Layman members will notify both clerics and worshippers
    members = filter(users(), &->is_elemental_seeker());
    worshippers = filter(users(), &->is_elemental_worshipper());
    clerics = filter(users(), &->is_elemental_cleric());
    scops = filter(users(), &->is_spirit_member());
    members -= clerics; // subtract and add to get rid of duplicates
    members += clerics;
    members -= worshippers;
    members += worshippers;
    members -= scops;
    members += scops;
    members -= ({ player }); // don't notify self.
    
    for (int i=0; i < sizeof(members); i++)
    {
    	if (GUILD_MANAGER->query_stop_all_notifications(members[i]))
    		members -= ({ members[i] });
    	else  if (GUILD_MANAGER->query_stop_seeker_notifications(members[i]))
    		members -= ({ members[i] });
    }
    
    wizards = filter(members, &->query_wiz_level());
    if (!sizeof(members))
    {
        return ({ });
    }
    
    if (!player->query_wiz_level() 
        && !wildmatch("*jr", player->query_real_name()))    
    {
        // Don't announce juniors and wizards to normal members
        audience = members;
    }
    else
    {
        // Wizards should always be notified about everyone
        audience = wizards;
    }
    return audience;
}

public void
notify_arrival(object player)
{
    if (!objectp(player) || !IS_PLAYER_OBJECT(player))
    {
        return;
    }

    object * audience = get_audience_for_notification(player);
    map(audience, &->catch_msg("You sense the stirring of the elements "
        + "as " + capitalize(player->query_real_name()) + " awakens in the Temple.\n"));    
}

public void
notify_departure(object player)
{
    if (!objectp(player) || !IS_PLAYER_OBJECT(player))
    {
        return;
    }
    
    object * audience = get_audience_for_notification(player);
    map(audience, &->catch_msg("You sense a calming of the elements "
        + "as " + capitalize(player->query_real_name()) + " departs the realms.\n"));    
}

/*
 * Function name: punish_teaming
 * Description  : Punish teaming after a few minutes
 * Arguments    : object who - the questioned team member
 */

int
punish_teaming(object who, int warned)
{
    int success, align, ran_align;

    if (!objectp(who) || !objectp(shadow_who))
        return 1;

    switch(warned)
    {
	    case 0:
	        shadow_who->catch_tell("\nThe Elementals disapprove of your " +
	        	"joining forces with the Soulless, " + 
	        	who->query_the_name(shadow_who) + "!\n\n");
	
	        if (!gTeamAlarm)
	            gTeamAlarm = set_alarm(60.0, 0.0, &punish_teaming(who, 1));
	
	        break;
	
	    case 1:
	        if (objectp(who) &&
	            member_array(who, shadow_who->query_team_others()) != -1)
	        {
	            shadow_who->catch_tell("\nYou feel the building wrath of the " +
	                "Elementals as you remain in defiance of your Vows and " +
	                "continue to join forces with the Soulless, " +
	                who->query_the_name(shadow_who) + ".\n\n");
	            gTeamAlarm = set_alarm(90.0, 0.0, &punish_teaming(who, 2));
	        }
	        else
	        {
	            gTeamAlarm = 0;
	        }
	        break;
	
	    case 2:
	        if (objectp(who) &&
	            member_array(who, shadow_who->query_team_others()) != -1)
	        {
	            shadow_who->catch_tell("\nYou feel the Elementals "+
	            	" are both disappointed and angered by your "+
	            	"continued actions of defiance of your Vows.\n\n");
	            COUNCIL_LOG_BOOK->update_log_book(my_time() + 
	            capitalize(shadow_who->query_real_name()) +
	            " was warned for teaming with " +
	            capitalize(who->query_real_name()) + ".\n");
	            send_debug_message("cleric", capitalize(shadow_who->
	            	query_real_name()) + " was warned for teaming with " + 
	                capitalize(who->query_real_name()) + ".", EVENTS_LOG);
        	}
	        gTeamAlarm = 0;
	        break;

	    default:
	        break;
    }
}

/*
 * Function name:    set_leader
 * Description  :    Sets this living as a member in a team
 *                   It will fail if this living is a leader itself
 * Arguments    :    leader: The objectpointer to the leader of the team
 * Returns      :    True if successfull
 */
 
public int
set_leader(object leader)
{
    int i, size, current_exp, success;
    object *team;
    string name, ogname, lgname;

    if (leader == 0)
        success = shadow_who->set_leader(leader);

    else
    {
        // Make them join first so we can get team info. 
        success = shadow_who->set_leader(leader);
        
        // They couldn't join. Don't do anything else. 
        if (!success)
            return success;

        team = shadow_who->query_team_others();
        ogname = leader->query_guild_name_occ();
        lgname = leader->query_guild_name_lay();
        
        if (leader->query_wiz_level() || shadow_who->query_wiz_level())
            return success;

        if (success && member_array(ogname, BANNED_GUILDS) != -1)
        {
            punish_teaming(leader, 0);
            return success;
        }
        
        if (success && member_array(lgname, BANNED_GUILDS) != -1)
        {
            punish_teaming(leader, 0);
            return success;
        }
    }

    return success;
}

/*
 * Function name:   team_join
 * Description:     Sets this living as the leader of another.
 *                  Mask parent so that teaming with enemy guilds affects
 *                  cleric's alignment. 
 * Arguments:       members: The objectpointer to the new member of my team
 *                  NOTE: Had to change 'member' to 'members' because of weird
 *                  macro error (/d/Calia/guilds/elementalists/shadows/
 *                  occ_cleric_shadow.c: Missing '(' in macro call line 2309)
 * Returns:         True if member accepted in the team
 */

public int
team_join(object members)
{
    int success;
    string ogname, lgname;

    success = shadow_who->team_join(members);
    if (!success || members->query_wiz_level() || shadow_who->query_wiz_level())
        return success;

    ogname = members->query_guild_name_occ();
    lgname = members->query_guild_name_lay();

    if (success && member_array(ogname, BANNED_GUILDS) != -1)
        punish_teaming(members, 0);
    
    if (success && member_array(lgname, BANNED_GUILDS) != -1)
        punish_teaming(members, 0);
        
    return success;
}

public void
elementals_stop_fight(object me, object target, string caller)
{
    int i;
    string pn;

    i = random(5);
    pn = PUNISHER[i]; 

    seteuid(getuid());
    me->stop_fight(target);
    target->stop_fight(me);
    if (file_name(me) == caller)
    {
        if (me->query_prop(BEEN_BAD_BOY))
        {
            tell_room(environment(me), pn +" suddenly "+
                "appears, looking very angry.\n");
            tell_object(me, pn+" points at you and screams "+
                "out in anger: You have been warned, but have not "+
                "listened!  Action must be taken!\nSuddenly, you feel "+
                "mentally and physically weakened.\n" + pn +
                " smiles wickedly, and disappears.\n");
            tell_room(environment(me),pn+" points at "+
                QTNAME(me) +" and screams out in anger:  You have " +
                "been warned, but have not "+
                "listened!  Action must be taken!\n"+
                pn +" smiles wickedly, and disappears.\n"+
                QTNAME(me)+" looks visibly drained.\n",me);
            me->set_mana(0);
            me->heal_hp(-(me->query_max_hp()/2));
                COUNCIL_LOG_BOOK->update_log_book(GUILD_MANAGER->my_time() +
                    capitalize(me->query_real_name())+" has been "+
                    "punished by "+ pn +" for attacking "+
                    capitalize(target->query_real_name())+".\n");
            if (me->query_hp() <= 0)
            {
                DEATH_OBJECT->load_me();
                me->do_die(find_object(DEATH_OBJECT));
            }
        }
        else 
        {
            tell_room(environment(me), pn + " suddenly "+
                "appears, looking slightly annoyed.\n");
            tell_object(me, pn + " whispers to you: Do not "+
                "attack another in our family again, or you shall "+
                "feel the wrath of the Elementals.  I hope I make "+
                "myself clear.\n");
            tell_room(environment(me), pn + " whispers to "+
                QTNAME(me)+".\n",me);
            tell_room(environment(me), pn + " disappears.\n");
            me->add_prop(BEEN_BAD_BOY,1);
        }
    }
    else
    {
        tell_room(environment(me), pn + " suddenly appears, "+
            "looking very angry.\n" + pn + " shouts: I don't "+
            "know which of you did it, but you had best behave!  "+
            "You aren't going to like it if I have to come back!\n"+
            pn + " disappears.\n");
    }
}

public void
attack_object(object target)
{
    if (IS_MEMBER(target))
    {
        int i;
        object temp;

        for (i = 0; i < 20; i++)
        {
            if (calling_object(-i))
                temp = calling_object(-i);
            else
                break;
        }
        set_alarm(1.0, 0.0,
              &elementals_stop_fight(shadow_who, target, file_name(temp)));
    }
    shadow_who->attack_object(target);
}

public varargs void
add_prop(string prop, mixed val)
{    
    if (prop == LIVE_I_UNDEAD && val != 0)
    {
        query_shadow_who()->catch_tell("You can feel the unclean forces "
            + "of the Soulless wrack your body, and you struggle "
            + "internally. Gradually, you feel the soothing calm of "
            + "Psuchae cleanse your body of the abominating effects.\n");
        return;
    }
    
    query_shadow_who()->add_prop(prop, val);
}
