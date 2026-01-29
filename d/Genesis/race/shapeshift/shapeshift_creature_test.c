/*
 *  /d/Genesis/race/shapeshift/shapeshift_creature.c
 *
 *  Generic inherit for non humanoid shapeshift targets. This file combines
 *  a normal creature with the player specific functions, so that for the 
 *  game they are the same as normal player objects.
 *
 *  To set a duration of the shapeshift, use the following function. This
 *  will automatically pause the duration while shapeshifted.
 *
 *  set_shapeshift_duration(int duration_in_seconds)
 *
 *  You can redefine the following functions:
 *
 *  create_shapeshift_creature      Alter the creature's default values
 *  hook_pre_shapeshift_return      Called before the player becomes normal
 *  hook_post_shapeshift_return     Called after the player becomes normal
 *  hook_pre_shapeshift_transform   Called before the player transforms
 *  hook_post_shapeshift_transform  Called after the player transforms 
 *  hook_prepare_shapeshift_target  Called to configure this object for the
 *                                  linked player.
 *
 *  Created by Eowul, November 2008
 */

#include <std.h>
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <ss_types.h>
#include <files.h>
#include <language.h>
#ifndef OWN_STATUE
#include <living_desc.h>
#endif
#include <mail.h>
 
#include "/std/player/quicktyper.c"

inherit "/std/creature";
inherit "/std/combat/unarmed";

// Variables
private object  spell_effect;
private object  player;
private int     fuse;
private int     ld_alarm;
private int     shapeshift_duration_alarm;
private float   shapeshift_duration = -1.0;

// Prototypes
object  get_player();
void    set_shapeshift_duration(int duration);

// Defines
#define LINKDEATH_TIME    180.0 /* three minutes */

/*
 * Function name: create_shapeshift_creature
 * Description  : Configure this creature to your liking
 */
public void
create_shapeshift_creature()
{
}

/*
 * Function name: hook_pre_shapeshift_return
 * Description  : Called before the player is returned to their real body.
 *              : The player object is already in the room so it can be
 *              : used for VBFC's and the like.
 */
public void 
hook_pre_shapeshift_return()
{
    object env = environment(this_object());
    tell_room(env, QCTNAME(this_object()) + " returns to " 
        + player->query_possessive() + " " + player->query_race_name()
        + " form.\n", ({ this_object(), player }));
    this_object()->catch_tell("You feel yourself return to your "
        + player->query_race_name() + " form.\n");
}

/*
 * Function name: hook_post_shapeshift_return
 * Description  : Called after the player is returned to their real body.
 *              : The player object is already in the room so it can be
 *              : used for VBFC's and the like.
 */
public void
hook_post_shapeshift_return()
{
} 

/*
 * Function name: hook_prepare_shapeshift_target
 * Description  : Called after the settings are set, but before any movements
 *              : are made. Use this function to alter characteristics of your
 *              : creature based on the player
 */
public void
hook_prepare_shapeshift_target()
{
}

/*
 * Function name: hook_pre_shapeshift_transform
 * Description  : Called before the player is moved to their shapeshifted form
 *              : The player object is still in the room so it can be
 *              : used for VBFC's and the like.
 */
public void
hook_pre_shapeshift_transform()
{
    object env = environment(this_object());
    tell_room(env, QCTNAME(player) + " turns into "
        + LANG_ADDART(this_object()->query_nonmet_name()) + ".\n",
        ({ this_object(), player }));
    player->catch_tell("You feel yourself turn into "
        + LANG_ADDART(this_object()->query_nonmet_name()) + ".\n");
}

/*
 * Function name: hook_post_shapeshift_transform
 * Description  : Called after the player is moved to their shapeshifted form
 *              : The player object is still in the room so it can be
 *              : used for VBFC's and the like.
 */
public void
hook_post_shapeshift_transform()
{
}

/*
 * Function name: abort_shapeshift
 * Description  : Cancel the shapeshift
 */
public nomask void
abort_shapeshift()
{
    spell_effect->abort_shapeshift();
}

/* 
 * Function name: create_creature
 * Description  : Set the values needed for the shapeshifting, if you want
 *              : to redefine your monster, redefine create_shapeshift_creature
 */
public nomask void
create_creature()
{
    fuse = 0;

    create_shapeshift_creature();
}

/*
 * Function name: get_player
 * Description  : Get the player linked to this object
 * Returns      : the player object
 */
public nomask object
get_player()
{
    return player;
}

/*
 * Function name: set_spell_effect
 * Description  : Set the reference to the spell object
 * Arguments    : effect - the effect that controls the shapeshift
 */
public nomask void
set_spell_effect(object effect)
{
    if(fuse) return;
    
    spell_effect = effect;
}

/*
 * Function name: setup_for_player
 * Description  : Prepare this shapeshifted object for the given player
 * Arguments    : ob - the original player object
 */
public nomask void
setup_for_player(object ob)
{
    if(fuse) return;
    
    player = ob;
    set_living_name(player->query_real_name());
    add_name(player->query_real_name());
    
    fuse = 1;
    
    if(shapeshift_duration != -1.0) 
    {
        shapeshift_duration_alarm = set_alarm(shapeshift_duration, 0.0, 
            abort_shapeshift);
    }
    
}

/*
 * Function name: set_shapeshift_duration
 * Description  : Use this to give the shapeshift a limited duration
 * Arguments    : duration - the duration in seconds
 */
public nomask void
set_shapeshift_duration(int duration) 
{
    shapeshift_duration = itof(duration);
    if(shapeshift_duration_alarm) 
    {
        remove_alarm(shapeshift_duration_alarm);
        if(shapeshift_duration != -1.0) 
        {
            shapeshift_duration_alarm = set_alarm(shapeshift_duration, 
                0.0, abort_shapeshift);
        }
    }
}

/****************************************************************************
 * The following functions are used in a normal player, and are repeated here 
 * to make this object act as a real player. The majority will be passed on
 * to the original player object.
 ****************************************************************************/
 
public string
query_def_start()
{
    return player->query_def_start();
}

public nomask int
query_skill_decay()
{
    return player->query_skill_decay();
}

public nomask void
setup_skill_decay()
{
    player->setup_skill_decay();
}

nomask public int
save_player(string pl_name)
{
    player->save_player(pl_name);
}

nomask public string
query_real_name()
{
    return player->query_real_name();
}

public nomask int
query_option(int opt)
{
    return player->query_option(opt);
}

public nomask int
set_option(int opt, int val)
{
    player->set_option(opt, val);
}

public nomask int
query_wiz_level()
{
    return player->query_wiz_level();
}

public nomask string
query_default_start_location()
{
    return player->query_default_start_location();
}

public nomask int
set_default_start_location(string str)
{
    player->set_default_start_location(str);
}

public nomask string
query_temp_start_location()
{
    return player->query_temp_start_location();
}

public nomask int
set_temp_start_location(string str)
{
    player->set_temp_start_location(str);
}

public nomask int
query_age()
{
    return player->query_age();
}

public nomask void
set_mailaddr(string addr)
{
    player->set_mailaddr(addr);
}

public nomask int
query_login_time()
{
    return player->query_login_time();
}

public int
set_bit(int group, int bit)
{
    catch_tell("Due to technical limitations in your shapeshifted form, "
        + "there was an error recording a change in your player file. If "
        + "you receive this message while not completing a quest, please "
        + "contact a wizard.\n");
}

public int
clear_bit(int group, int bit)
{
    catch_tell("Due to technical limitations in your shapeshifted form, "
        + "there was an error recording a change in your player file. If "
        + "you receive this message while not completing a quest, please "
        + "contact a wizard.\n");
}

public int
test_bit(string dom, int group, int bit)
{
    return player->test_bit(dom, group, bit);
}

public mapping
query_aliases()
{
    return player->query_aliases();
}

public mapping
query_nicks()
{
    return player->query_nicks();
}

public nomask void
set_restricted(int seconds, int self)
{
    player->set_restricted(seconds, self);
}

public nomask void
reset_restricted(int self)
{
    player->reset_restricted(self);
}

public nomask int
query_restricted()
{
    return player->query_restricted();
}

public nomask mapping
query_remember_name()
{
    return player->query_remember_name();
}

public nomask void
set_remember_name(mapping nlist)
{
    player->set_remember_name(nlist);
}

public varargs mixed
query_remembered(mixed name)
{
    return player->query_remembered(name);
}

public int
add_remembered(string str)
{
    player->add_remembered(str);
}

public int
remove_remembered(string name)
{
    player->remove_remembered(name);
}

public void
set_whimpy(int flag)
{
    player->set_whimpy(flag);
}

public int
query_npc()
{
    return 0;
}


public int
query_exp()
{
    return player->query_exp();
}

public int
query_max_exp()
{
    return player->query_max_exp();
}

public int
query_exp_combat()
{
    return player->query_exp_combat();
}

varargs public float
query_brute_factor(int base = 0)
{
    return player->query_brute_factor(base);
}

public void
add_exp_combat(int exp)
{
    player->add_exp_combat(exp);
}

public int
query_exp_general()
{
    return player->query_exp_general();
}

public void
add_exp_general(int exp)
{
    player->add_exp_general(exp);
}

public int
query_exp_quest()
{
    return player->query_exp_quest();
}

public void
add_exp_quest(int exp)
{
    catch_tell("As a shapeshifted creature, you are unable to receive "
        + "quest experience. This addition is not recorded.\n");
}

public void
add_exp(int exp, int battle)
{
    if(!battle) {
        catch_tell("As a shapeshifted creature, you are unable to receive "
            + "quest experience. This addition is not recorded.\n");    
        return;
    }
    player->add_exp(exp, battle);
}

public void
set_alignment(int a)
{
    player->set_alignment(a);
}

public int
query_alignment()
{
    return player->query_alignment();
}

public void
adjust_alignment(int align)
{
    return player->adjust_alignment(align);
}

void
set_learn_pref(int *pref_arr)
{
    player->set_learn_pref(pref_arr);
}

public mixed
query_learn_pref(int stat)
{
    player->query_learn_pref(stat);
}

public void
set_guild_pref(int guildstat, int tax)
{
    player->set_guild_pref(guildstat, tax);
}

public int
set_skill(int skill, int val)
{
    if(skill > SS_MUDLIB_SKILL_END) {
        player->set_skill(skill, val);
    } else {
        ::set_skill(skill, val);
    }
}

void
remove_skill(int skill)
{
    if(skill > SS_MUDLIB_SKILL_END) {
        player->remove_skill(skill);
    } else {
        ::remove_skill(skill);
    }   
}

public int
query_skill(int skill)
{
    if(skill > SS_MUDLIB_SKILL_END) {
        return player->query_skill(skill);
    } else {
        return ::query_skill(skill);
    }   
}

public nomask string
query_login_from() 
{
    return player->query_login_from();
}

public string
query_guild_title_occ()
{
    return player->query_guild_title_occ();
}

public int 
query_guild_not_allow_join_occ(object player, string type, 
    string style, string name) 
{
    return 1;
}

public string
query_guild_title_lay()
{
    return player->query_guild_title_lay();
}

public string
query_guild_name_lay()
{
    return player->query_guild_name_lay();
}

public int 
query_guild_not_allow_join_lay(object player, string type, 
    string style, string name) 
{
    return 1;
}

public string
query_guild_family_name()
{
    return player->query_guild_family_name();
}

public string
query_guild_title_craft()
{
    return player->query_guild_title_craft();
}

public string
query_guild_name_craft()
{
    return player->query_guild_name_occ();
}

public int 
query_guild_not_allow_join_craft(object player, string type, 
    string style, string name) 
{
    return 1;
}

public string
query_guild_title_race()
{
    return player->query_guild_title_race();
}

public string
query_guild_name_race()
{
    return player->query_guild_name_occ();
}

public int 
query_guild_not_allow_join_race(object player, string type, 
    string style, string name) 
{
    return 1;
}

/*
 * Function:    query_presentation
 * Description: Gives a presentation of the living in one line. Adapted
 *              from /std/living/description.c to support people being
 *              shown as another race in the who list or when they introduce
 *              themselves.
 * Returns:     The presentation string
 */
public string
query_presentation()
{
    string a, b, c;
    
    a = query_title(); 
    b = player->query_exp_title(); 
#ifndef NO_ALIGN_TITLE
    c = player->query_al_title();
#endif

    /* If there is no (guild) title, use the experience title as title. */
    if (!strlen(a) && strlen(b))
    {
        b = "the " + implode(map(explode(b, " "), capitalize), " ");
    }

    return query_name() +
	(strlen(a) ? (" " + a + ",") : "") +
	(strlen(b) ? (" " + b + ", ") : " ") +
	player->query_gender_string() + " " + 
        this_object()->query_race_name()
#ifndef NO_ALIGN_TITLE
	+ (strlen(c) ? (" (" + c + ")") : "")
#endif
	; /* Oke, it is ugly to have a semi-colon on a separate line. */
}

static nomask void
actual_linkdeath()
{
#ifdef STATUE_WHEN_LINKDEAD
#ifdef OWN_STATUE
    OWN_STATUE->linkdie(this_object());
#else   
    tell_room(environment(), LD_STATUE_TURN(this_object()), ({ }) );
#endif OWN_STATUE
#endif STATUE_WHEN_LINKDEAD

    /* People should not autosave while they are linkdead. */
// TODO: needs to be called in the player somehow    stop_autosave();

    if (ld_alarm)
    {
        SECURITY->notify(this_object(), 5);
        remove_alarm(ld_alarm);
        ld_alarm = 0;
    }
    set_linkdead(1);
    player->set_linkdead(1);

    /* Allow a shadow to take notice of the linkdeath. */
    this_object()->linkdeath_hook(1);
    /* Allow items in the top level inventory of the player to take notice
     * of the linkdeath.
     */
    all_inventory(this_object())->linkdeath_hook(this_object(), 1);
    
    if(shapeshift_duration_alarm)
    {
        mixed *alarm_data = get_alarm(shapeshift_duration_alarm);
        remove_alarm(shapeshift_duration_alarm);
        shapeshift_duration = alarm_data[2];
        shapeshift_duration_alarm = 0;
    }
}

nomask public void
linkdie()
{
    if (previous_object() != find_object(SECURITY))
    {
        return;
    }

    if (query_relaxed_from_combat())
    {
        actual_linkdeath();
    }
    else
    {
#ifdef STATUE_WHEN_LINKDEAD
#ifdef OWN_STATUE
        OWN_STATUE->nonpresent_linkdie(this_object());
#endif OWN_STATUE
#endif STATUE_WHEN_LINKDEAD

        tell_room(environment(), ({
            capitalize(query_real_name()) + " loses touch with reality.\n",
            "The " + query_nonmet_name() + " loses touch with reality.\n",
            "" }),
            ({ this_object() }) );

        ld_alarm = set_alarm(LINKDEATH_TIME, 0.0, actual_linkdeath);
    }
}

nomask public void
revive()
{
    if (MASTER_OB(previous_object()) != LOGIN_OBJECT)
    {
        return;
    }

    tell_object(this_object(), "You sense that you have " +
        MAIL_FLAGS[MAIL_CHECKER->query_mail(query_real_name())] + ".\n\n");

    player->set_login_from();
    player->fixup_screen();
    player->gmcp_map_reset();
    player->gmcp_team();
    
    /* If the player is not in combat, revive him. Else, just give a
     * a message about the fact that the player reconnected.
     */
    if (!ld_alarm)
    {
        set_linkdead(0);
        player->set_linkdead(0);

#ifdef OWN_STATUE
        OWN_STATUE->revive(this_object());
#else   
        tell_room(environment(), QCTNAME(this_object()) + " " +
            STATUE_TURNS_ALIVE + ".\n", ({ this_object() }) );
#endif OWN_STATUE

        /* We reset these variables so the player does not gain mana or
         * hitpoints while in LD.
         */
// TODO        player_save_vars_reset();
        save_vars_reset();

        /* Start autosaving again. */
        // TODO: start_autosave();

        /* Allow a shadow to take notice of the revival. */
        this_object()->linkdeath_hook(0);
        /* Allow items in the top level inventory of the player to take notice
         * of the revival.
         */
        all_inventory(this_object())->linkdeath_hook(this_object(), 0);
    }
    else
    {
        tell_room(environment(), ({ capitalize(query_real_name()) +
            " gets in touch with reality again.\n",
            "The " + query_nonmet_name() +
            " gets in touch with reality again.\n",
            "" }),
            ({ this_object() }) );

#ifdef OWN_STATUE
        OWN_STATUE->nonpresent_revive(this_object());
#endif OWN_STATUE
        remove_alarm(ld_alarm);
        ld_alarm = 0;
    }
    
    if(shapeshift_duration != 1.0) 
    {
        shapeshift_duration_alarm = set_alarm(shapeshift_duration, 0.0,
            abort_shapeshift);
    }
}

/*
 * Function name: switch_connection
 * Description  : Called when a player makes a new connection to this body
 *                without being linkdead first.
 */
nomask public void
switch_connection()
{
    if (MASTER_OB(previous_object()) != LOGIN_OBJECT)
    {
        return;
    }

    gmcp_map_reset();
    gmcp_team();
}

public int
query_met(mixed who)
{
    return player->query_met(who);
}

public void
add_introduced(string str)
{
    player->add_introduced(str);
}

public varargs mixed
query_introduced(string name)
{
    return player->query_introduced(name);
}

public int
remove_introduced(string str)
{
    player->remove_introduced(str);
}

public void
do_die(object killer)
{
    abort_shapeshift();
    player->heal_hp(-player->query_max_hp());
    player->do_die(killer);
}

public string
query_met_name()
{
    return player->query_met_name();
}

public int
id(string str)
{
    if ((str == query_real_name()) &&
        notmet_me(this_player()))
    {
        return 0;
    }

    return ::id(str);
}

public string *
parse_command_id_list()         
{ 
    string *ids;

    ids = ::parse_command_id_list();

    if (sizeof(ids) &&
        notmet_me(this_player()))
    {
        ids -= ({ query_real_name() });
    }

    return ids;
}
