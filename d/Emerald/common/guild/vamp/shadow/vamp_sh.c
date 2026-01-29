/* vamp_sh.c created by Shiva@Genesis 8/14/95
 * this is the vampire guild shadow.
 *
 * Lucius Nov 30 2007: Changed query_guild_not_allow_join_occ() to allow
 *                     for joining a craft guild.
 * Lucius Dec 01 2007: Added a news file and time-check to print a message
 *                     telling vamps to read it when it's updated.
 */

inherit "/std/guild/guild_occ_sh";

#include "../guild.h"
#include "../voptions.h"
#include "/d/Emerald/sys/skills.h"
#include <std.h>
#include <stdproperties.h>
#include <language.h>
#include <files.h>

#define DEBUG_WHO shadow_who
#define DEBUG_LEVEL 255
#define DEBUG_ON
#undef DEBUG_ON
#include "/d/Emerald/sys/debug.h"

// prototypes are kept in shadow.h
#include "shadow.h"

#include "blood.c"
#include "darkvision.c"
#include "vamp_death.c"
#include "sunlight.c"
#include "vamp_abilities.c"
#include "vamp_combat.c"
#include "vamp_desc.c"
#include "vamp_heal.c"
#include "vamp_dark.c"
#include "vamp_move.c"
#include "vamp_options.c"
#include "vamp_stats.c"
#include "wizstat_vamp.c"
#include "vamp_drain.c"
#include "unseen.c"

#include "ambush_sh.c"

#define SW shadow_who

void kick_out_vamp(object player);
string query_sire();
void update_covenmaster_status();

object
query_vamp_shadow()
{
    return this_object();
}

int
is_emerald_vampire() 
{
    return 1;
}

/*
 * Function name: query_guild_name_occ
 * Description:   Return the guild's name
 * Returns:       The guild's name
 */
string
query_guild_name_occ()
{
    return GUILD_NAME;
}

/*
 * Function name: query_guild_style_occ
 * Description:   Return the guild's style
 * Returns:       The guild's style
 */
string
query_guild_style_occ()
{
    return GUILD_STYLE;
}

/*
 * Function name: query_guild_tax_occ
 * Description:   Returns the guild's tax
 * Returns:       The guild's tax
 */
int
query_guild_tax_occ()
{
    return GUILD_TAX;
}

/*
 * Function name: login_vampire
 * Description:   This is called only when a vampire logs in.
 */
static nomask void
login_vampire(void)
{
    /* Notify other vampires of login */
    if (!IS_WIZ(SW) && !IS_JR(SW))
    {
	int i, time_logged_out;
        object *vamps = VAMPS(users());
        string name = SW->query_real_name();
        mixed sire = query_sire();
        string coven = query_vamp_coven();

        for (i = 0; i < sizeof(vamps); i++)
        {
            if (!vamps[i]->query_vamp_option(VOPT_NOTIFY_LOGIN))
            {
                continue;
            }

            if (!IS_WIZ(vamps[i]) &&
                ((name == vamps[i]->query_sire()) ||
                (vamps[i]->query_real_name() == sire) ||
                (coven != vamps[i]->query_vamp_coven())))
            {
                continue;
            }

            tell_object(vamps[i], "Your sensitive mind detects " +
                LANG_POSS(SW->query_name()) + " awakening.\n");
        }

        /* Taks this out until we figure out a good way to allow
         * for other covens to designate homes
         */
#if 0
        if (environment(SW) &&
            !QP(SW, LIVE_O_LAST_ROOM) && 
            !QP(SW, LIVE_I_ENTERED_VAMP_STARTLOC))
        {
            /* the player is using a startloc other than the vamp
             * startloc, so increase his thirst according to the 
             * amount of time he's been away
             */
            setuid();
            seteuid(getuid());
            if ((time_logged_out = time() -
                file_time(PLAYER_FILE(SW->query_real_name()) + ".o")) > 600)
            {
                add_thirst(MIN(50, MAX(100, time_logged_out / 60)));
            }
        }    
#endif
    }
}

/*
 * Function name: start_vampire
 * Description:   This is called when the vampire enters the game or when
 *                he is given a new shadow.  It initializes certain routines,
 *                adds properties to the vampire, etc.
 */
void
start_vampire()
{
#ifdef GUILD_CLOSED
    SW->clear_guild_stat(SS_OCCUP);
    remove_guild_occ();
    return;
#endif

    if (!SECURITY_CHECK(SW))
    {
        SECURITY_LOG(SW, "Illegal shadow.");
        remove_guild_occ();
        return;
    }

    start_blood();
    start_heal();
    init_vamp_options();

  
    // we are undead!
    AP(SW, LIVE_I_UNDEAD, &min(100) @ &operator(/)(, 2) @ query_effective_vamp_stat);

#ifdef VAMP_DEATH_RES
    // we are resistant to death magic
    CP(SW, PRE_OBJ_MAGIC_RES + MAGIC_I_RES_DEATH, 20);
#endif
    // we're resistant to poisons
    CP(SW, PRE_OBJ_MAGIC_RES + MAGIC_I_RES_POISON, 15);
    // we're resistant to magical healing
    AP(SW, PRE_OBJ_MAGIC_RES + "_magic_i_res_healing", 100);

    setuid();
    seteuid(getuid());
  
    if (QUERY_PUNISH(SW, EXPEL) > 0)
    {
        kick_out_vamp(SW);
        return;
    }

    if (QUERY_PUNISH(SW, BANISH) > 0)
    {
        SW->catch_tell("You have been banished from your coven!\n");
        set_vamp_coven(ROGUE_VAMPIRE);
    }

#ifdef VAMP_CMDSOUL
    if (SW->add_cmdsoul(VAMP_CMDSOUL))
    {
        SW->update_hooks();
    }
#endif

#ifdef VAMP_ABILITIES
    if (SW->add_cmdsoul(VAMP_ABILITIES))
    {
        SW->update_hooks();
    }
#endif

    update_covenmaster_status();

#if defined (GUILD_EMBLEM) && !defined (GUILD_EMBLEM_AUTOLOADING)
    COTO(GUILD_EMBLEM, SW);
#endif
//  Experimental?  Unused?
//    "/d/Emerald/common/guild/vamp/spells/vamp_spells"->mkspells(SW);
}

/* 
 * Function name: add_vamp_shadow
 * Description:   Shadow an object with this shadow
 * Arguments:     object who - the object to shadow
 * Returns:       as shadow_me in /std/guild/guild_base.c
 */
int
add_vamp_shadow(object who)
{
    int ret = shadow_me(who, "occupational", GUILD_STYLE, GUILD_NAME);

    if (ret == 1)
    {
        start_vampire();
    }

    return ret;
}

/*
 * Function name: start_player
 * Description:   This is called when the player enters the game, after
 *                most of the login routines have finished.
 */
void
start_player()
{
#ifndef NO_AUTO_NEWS
    string news = (VAMP_HELP_DIR + "news.help");

    if ((file_size(news) > 0) &&
	(file_time(news) >= SW->query_login_time()))
    {
	set_alarm(2.0, 0.0, &(SW)->catch_tell(
		"\n=============================================\n"+
		"  Your blood sings to you of new knowledge.\n"+
		"  Check \"help vampire news\" for updates.\n"+
		"=============================================\n\n"));
    }
#endif

    SW->start_player();
    start_vampire();
    login_vampire();
}

varargs int
make_new_vamp(object who, mixed sire, int offset, string coven)
{
    int ret;

    setuid();
    seteuid(getuid());

    MANAGER->clear_member(who);

    // This has to happen first, or else the new member will be considered
    // invalid.
    MANAGER->add_member(who);

    ret = add_vamp_shadow(who);

    if (ret == 1)
    {
        SW->clear_guild_stat(SS_OCCUP);
        SW->clear_guild_stat(SS_LAYMAN);

        MANAGER->set_scars(SW, SW->query_scar());
        MANAGER->set_scar_age(SW, SW->query_age());
        MANAGER->set_start_age(SW, SW->query_age());
        MANAGER->set_sire(SW, sire);
        MANAGER->set_base_power_offset(SW, offset);
        MANAGER->set_coven(SW, coven);
        MANAGER->set_last_embrace_time(SW, time());
    }

    return ret;
}

/*
 * Function name: query_guild_not_allow_join_occ
 * Description:   Determine whether or not this vampire is allowed to
 *                join a given guild.
 * Arguments:     object player - this vampire
 *                string type   - the type of the guild this vampire is
 *                                attempting to join. 
 *                string style  - the style of the guild this vampire is
 *                                attempting to join. 
 *                string name   - the name of the guild this vampire is
 *                                attempting to join.
 * Returns:       1/0 may not join / may join
 */
int
query_guild_not_allow_join_occ(object player, string type,
    string style, string name)
{
    /* Wizards can join anything they want.  Note that this allows multiple occ
     * guilds, which can lead to some conflicts.
     */
    if (IS_WIZ(SW))
        return 0;

    if (::query_guild_not_allow_join_occ(player, type, style, name))
        return 1;

    if (type == "layman")
	return 1;

    /* Allow race + craft */
    return 0;
}

/*
 * Function name: drink_alco
 * Description:   Drinks alcohol of given potency
 * Arguments:     as drink_alco() on /std/living.c
 * Returns:       Always 0 for non-wizards.
 */
int
drink_alco(int strength, int ask)
{
    object previous;
    int success, intox;

    if (IS_WIZ(shadow_who))
    {
        return shadow_who->drink_alco(strength, ask);
    }

    // Allow drinking of magical drinks. This isn't entirely fool
    // proof, but it covers most of the bases (all standards drinks
    // and potions).
    previous = previous_object();
    if (previous &&
        (function_exists("command_drink", previous) ||
         IS_POTION_OBJECT(previous) || IS_DRINK_OBJECT(previous)) &&
        previous->query_prop(MAGIC_AM_MAGIC))
    {
        intox = shadow_who->query_intoxicated();
        if ((success = shadow_who->drink_alco(strength, ask)) && !ask)
        {
            // Drinking shouldn't actually affect intox
            shadow_who->set_intoxicated(intox);
        }

        return success;
    }

    return 0;
}

/*
 * Function name: drink_soft
 * Description:   Drinks a given amount of liquid
 * Arguments:     as drink_soft() on /std/living.c
 * Returns:       Always 0 for non-wizards.
 */
int
drink_soft(int amnt, int ask)
{
    object previous;
    int soak, success;

    if (IS_WIZ(shadow_who))
    {
        return shadow_who->drink_soft(amnt, ask);
    }

    // Allow drinking of magical drinks. This isn't entirely fool
    // proof, but it covers most of the bases (all standards drinks
    // and potions).
    previous = previous_object();
    if (previous &&
        (function_exists("command_drink", previous) ||
         IS_POTION_OBJECT(previous) || IS_DRINK_OBJECT(previous)) &&
        previous->query_prop(MAGIC_AM_MAGIC))
    {
        soak = shadow_who->query_soaked();
        if ((success = shadow_who->drink_soft(amnt, ask)) && !ask)
        {
            // Drinking shouldn't actually affect soaked
            shadow_who->set_soaked(soak);
        }

        return success;
    }

    return 0;
}

/* 
 * Function name: eat_food
 * Description:   Eats a given amount of food
 * Arguments:     as eat_food() on /std/living.c
 * Returns:       Always 0 for non-wizards.
 */ 
int
eat_food(int amount, int ask)
{
    return (IS_WIZ(SW) ? SW->eat_food(amount, ask) : 0);
}


/*
 * Function name: query_guild_trainer_occ
 * Description:   return the path(s) to the guild's skill trainer(s)
 * Returns:       as above
 */
mixed
query_guild_trainer_occ()
{
    return ({ 
              "/d/Emerald/mist_tower/obj/frustum",
           });
}

/*
 * Function name: kick_out_vamp
 * Description:   Remove this vampire from the guild, applying all
 *                punishments.
 */
void
kick_out_vamp(object player)
{
#ifdef GUILD_EMBLEM_ID
    object ob;
  
    while (ob = present(GUILD_EMBLEM_ID, player))
    {
        ob->remove_object();
    }
#endif

    setuid();
    seteuid(getuid());
  
    MANAGER->clear_member(player);

    player->catch_msg("A shudder goes through your body, and you drop to your"
      + " knees, overcome with a devastating feeling of loss. Almost"
      + " immediately the feeling fades, and you sense, inexplicably,"
      + " life rushing into your body from the very ether which surrounds"
      + " you.\n\nYou are no longer a Vampire!\n\n");

  
    vampire_death(0);
}

/* 
 * Function name: query_sire
 * Description:   Get the name of the sire of this vampire
 * Returns:       This vampire's sire's name.
 */
string
query_sire()
{
    setuid();
    seteuid(getuid());
  
    return lower_case(MANAGER->query_sire(SW));
}

/*
 * Function name: query_vamp_covenmaster
 * Description:   Find out if this vamp is a covenmaster
 * Returns:       0 - not a covenmaster
 *                1 - honorary covenmaster (domain wizards and arches++)
 *                2 - official covenmaster
 */
int
query_vamp_covenmaster()
{
    /* Emerald wizzes, and wizards of arch level or more are considered
     * covenmasters.
     */
    if (EMRLD_WIZ(SW) || IS_WIZ(SW) >= WIZ_ARCH)
    {
        return 1;
    }
  
    setuid();
    seteuid(getuid());
  
    return (MANAGER->is_covenmaster(SW) ? 2 : 0);
}

string
query_vamp_coven()
{
    setuid();
    seteuid(getuid());

    return MANAGER->query_coven(SW);
}

void
set_vamp_coven(string coven)
{
    setuid();
    seteuid(getuid());

    MANAGER->set_coven(SW, coven);
    MANAGER->remove_personal_title(SW);
    MANAGER->set_punishment(SW, 0);

    if (coven == ROGUE_VAMPIRE)
    {
        if (SW->query_default_start_location() == VAMP_STARTLOC)
        {
            SW->set_default_start_location(SW->query_def_start());
        }

        set_vamp_option(VOPT_NOTIFY_LOGIN, 0);
    }

    update_title();
}

void
update_covenmaster_status()
{
#ifdef VAMP_COVENMASTER_CMDSOUL
    if (query_vamp_covenmaster())
    {
        SW->add_cmdsoul(VAMP_COVENMASTER_CMDSOUL);
        SW->update_hooks();
    }
    else
    {
        if (SW->remove_cmdsoul(VAMP_COVENMASTER_CMDSOUL))
        {
            SW->update_hooks();
        }
    }
#endif
}

int
query_guild_leader_occ() 
{ 
    return (query_vamp_covenmaster() == 2);
}

/*
 * Function name: query_guild_skill_name
 * Description:   Give a name for a given skill number if it is one
 *                of ours.
 * Arguments:     int skill - the skill number
 * Returns:       The name of the skill or 0 if it is not a vampire skill.
 */
mixed
query_guild_skill_name(int skill)
{
#ifdef SS_VAMP_FOCUS
    if (skill == SS_VAMP_FOCUS)
    {
        return "mental focus";
    }
#endif

#ifdef SS_VAMP_SLASH
    if (skill == SS_VAMP_SLASH)
    {
        return "slash";
    }
#endif

#ifdef SS_VAMP_CELERITY
    if (skill == SS_VAMP_CELERITY)
    {
        return "celerity";
    }
#endif

    return 0;
}

string
full_adverb(string str)
{
    string adverb;

    setuid();
    seteuid(getuid());

    if (strlen(adverb = ADVERB_MANAGER->full_adverb(str)))
    {
        return adverb;
    }

    return SW->full_adverb(str);
}

mixed
query_prop(string prop)
{
    if (prop == LIVE_I_SEE_DARK)
    {
        reset_darkvision();
    }

    return SW->query_prop(prop);
}

void
remove_vamp_sh()
{
    remove_shadow();
}

int query_vampire()
{
    return 1;
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
    /* The guild is closed. Old members need to be removed if they should
     * ever log in again. (Gorboth)
     */
    kick_out_vamp(player);
    
    return 0;
}

 