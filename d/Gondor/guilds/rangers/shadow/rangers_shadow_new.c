/*
 * /d/Gondor/guilds/rangers/shadow/rangers_shadow.c 
 *
 * The Ranger Guild shadow
 *
 * Original Rangers coded by Elessar
 * Recode by Gwyneth and Alto 2001-2002
 *
 * Modification log:
 *   Gwyneth, July 12, 2004: Put a cap on ranger rank
 *   Gwyneth, July 20, 2004: Master/specialist additions
 *   Tigerlily, July 21, 2004: Added message to approved apprentice
 */
inherit "/std/guild/guild_occ_sh";

#include <const.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <std.h>
#include <time.h>

#include "/d/Gondor/defs.h"
#include "../rangers.h"
#include "../titles.h"

#define RANGER_I_PREPARE_BRAWL "_ranger_i_prepare_brawl"
#define MOVED_WHILE_BRAWLING   3

#define VIRTUE_PROVIDER  (RANGERS_DIR + "virtue_skill_provider")

#define TEST_SOUL "/d/Gondor/guilds/rangers/soul/rangers_soul"

/* Global Variables
private int incognito_type = 0;
private int intro_type     = 0;
*/

private int gAutosneakOn   = 0;
private int gTeamAlarm = 0;

private object evade_object;

#define R_INCOGNITO     1
#define R_INTRO         2
#define R_KNOWN         4

#define TEAM_PROG_MSGS(x) ({ "You feel a twinge of guilt for giving " + \
        x + " such limited help.", "Your limited encounter with " + x +\
        " was a good start.", "Perhaps " + x + " learned a thing or two " +\
        "from you today.", "Your work with " + x + " was an investment " +\
        "in the future!", "You have advanced slightly after teaming with " +\
        x + ".", "You have advanced a little after teaming with " + x + ".",\
        "You feel you have advanced as a ranger for teaming with " + x + ".",\
        "Your confidence as a ranger was improved by teaching " + x + ".",\
        "Your confidence as a ranger has swelled after teaching " + x + ".",\
        "Your confidence as a ranger has grown tremendously after teaming " +\
        "with " + x + ".", "You beam with confidence! What a great " +\
        "experience for both " + x + " and yourself!", "After working so " +\
        "hard with " + x + ", you feel a great personal growth in your " +\
        "heart.", "You have done the guild a great service by working so " +\
        "hard with " + x + "!", "Your superiors are pleased by your " +\
        "efforts with " + x + ".", "Your superiors are very happy with " +\
        "your efforts with " + x + ".", "Your superiors are highly " +\
        "impressed by your work with " + x + ".", "Working with " + x +\
        " made you feel like a true ranger!", "Working with " + x +\
        " made you feel like a great ranger!", "Working with " + x + " made " +\
        "you feel like a leader among rangers!", "Your work with " + x +\
        " makes you feel legendary!" })

/* This is a binary combo of incognito_type and intro_type */
private int gFlags;

private int gMajorVirtue;

private int gMinorVirtue;

private mapping gAppTeam = ([]);

/* Prototypes */
public void    set_autosneak(int val);
public int     query_autosneak();
public int     query_guild_incognito_occ();
public int     query_is_officer();
public varargs int move_living(string h, mixed to, int dnt_flw, int no_glnc);
nomask public int query_ranger_legend();
public int query_ranger_incognito();
public int query_ranger_intro();
public int query_ranger_major_virtue();
public int query_ranger_minor_virtue();


/* Function name: query_ranger_level
 * Description  : Unique ranger function to give their membership level.
 *                Options are:
 *                0 - Not a ranger
 *                1 - Apprentice
 *                2 - Approved apprentice
 *                3 - Ranger of the North
 *                4 - Ranger of Ithilien
 */
public int
query_ranger_level()
{
    return (MANAGER->query_ranger_level(shadow_who->query_real_name()));
}

/* Function name: query_ranger_rank
 * Description  : A unique Ranger function that gives the Rangers 
 *                accumulated rank.
 * Returns      : int - the rank
 */
public int
query_ranger_rank()
{
    object who = shadow_who;
    int stats;

    stats = who->query_acc_exp(SS_OCCUP);
    stats += who->query_skill(SS_RANGER_TEAM);
    stats = who->exp_to_stat(stats);
    
    stats = ((stats / 3) + who->query_skill(SS_REWARDED));
    stats = min(stats, 200);
    return stats;
}

/* Function name: query_company
 * Description  : A unique Ranger function that gives the company
 *                that the player is in.
 * Returns      : string - the name of the company
 */
public string
query_company()
{
    return (MANAGER->query_ranger_company(shadow_who->query_real_name()));
}

public int
query_ranger_has_virtues()
{
    return 1;
}

/* Function name: query_ranger_major_virtue
 * Description  : A unique Ranger function that gives the major virtue.
 * Returns      : int - the enumerated version of the major virtue.
 */
public int
query_ranger_major_virtue()
{
    switch(query_ranger_level())
    {
        case APPRENTICE_LEVEL:
        case APPROVED_APP_LEVEL:
            return 0;
    }
    return (MANAGER->query_major_virtue(shadow_who->query_real_name()));
}

/* Function name: query_ranger_minor_virtue
 * Description  : A unique Ranger function that gives the minor virtue.
 * Returns      : int - the enumerated version of the minor virtue.
 */
public int
query_ranger_minor_virtue()
{
    switch(query_ranger_level())
    {
        case APPRENTICE_LEVEL:
        case APPROVED_APP_LEVEL:
            return 0;
    }
    return (MANAGER->query_minor_virtue(shadow_who->query_real_name()));
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
    object last_me;
    object me;
    
    me = query_shadow_who();
    last_me = me;
    while (me = shadow(me, 0))
    {
        // loop through to find the top level shadow who
        last_me = me;
    }   
    
    // We return now the top level shadow
    return last_me;
}


/* Function name: query_guild_tax_occ
 * Description  : Generic guild function that gives the amount of tax the 
 *                guild charges
 *                Apprentices receive a lower tax rate.
 * Returns      : int - The tax amount
 */
public int
query_guild_tax_occ()
{
    switch(query_ranger_level())
    {
    case APPRENTICE_LEVEL:
    case APPROVED_APP_LEVEL:
        return RANGERS_TAX_APPREN;
    case NORTH_LEVEL:
        return RANGERS_TAX_NORTH;
    case ITHILIEN_LEVEL:
        return RANGERS_TAX_FULL;
    default:
        return 0;
    }
}

/* Function name: query_guild_style_occ
 * Description  : Generic guild function that returns the guild style for this guild.
 * Returns      : string - the style
 */
public string
query_guild_style_occ()
{
    return RANGERS_STYLE;
}

/* Function name: query_guild_name_occ
 * Description  : Generic guild function that gives the guild name.
 * Returns      : string - the guild name
 */
public string
query_guild_name_occ()
{
    return RANGERS_GUILD_NAME;
}

/* Function name: query_guild_skill_name
 * Description  : Generic guild function that gives the name of the skill 
 *                used when a player uses the 'skills' command.
 * Arguments    : int skill - the skill number
 * Returns      : The name of the skill
 */
public string
query_guild_skill_name(int skill)
{
    switch (skill)
    {
    case SS_HEARING:
        return "hearing";
    case SS_BRAWLING:
        return "brawling";
    case SS_AMBUSH:
        return "ambushing";
    case SS_REWARDED:
    case SS_RANGER_SPELL_LIST:
    case SS_RANGER_DISFAVOUR:
    case SS_RANGER_TEAM:
    case SS_RANGER_PRI_WEP:
    case SS_PUNISHED:
    case SS_PUNISHMENT:
    case SS_MASTER_TASK:
        return "";
    }

    return shadow_who->query_guild_skill_name(skill);
}

/* Function name: query_def_post
 * Description  : Generic guild function which gives the path to the guild's 
 *                post office for mail notification purposes.
 * Returns      : string - the pathname of the post office
*/
public string
query_def_post()
{
    switch(query_ranger_level())
    {
    case APPRENTICE_LEVEL:
    case APPROVED_APP_LEVEL:
        return RANGERS_HQ_POST;
    case NORTH_LEVEL:
        return RANGERS_NOR_POST;
    case ITHILIEN_LEVEL:
        return RANGERS_ITH_POST;
    default:
        return 0;
    }
}

/* Function name: query_guild_trainer_occ
 * Description  : Generic guild function that gives the path to the guild 
 *                trainer to prevent skill decay.
 * Returns      : string - the pathname of the training room
 */
public mixed
query_guild_trainer_occ()
{
    object provider = VIRTUE_PROVIDER->get_virtue_skills(
       query_ranger_major_virtue(),
       query_ranger_minor_virtue());
    return provider;
}

/* Function name: evict_ranger
 * Description  : Unique Ranger function that aids in escorting the player from 
 *                the guildhall upon being expelled.
 */
public void
evict_ranger()
{
    int size;
    object room, dest_room;
    string dest, filepath, base_dir, *file_array;

    if (!objectp(shadow_who))
        return;

    room = environment(shadow_who);

    if (!objectp(room))
        return;

    filepath = file_name(room);
    size = strlen(RANGERS_DIR);
    base_dir = extract(filepath, 0, size - 1);

    if (base_dir != RANGERS_DIR)
        return;

    filepath = extract(filepath, size);
    file_array = explode(filepath, "/");

    switch(file_array[0])
    {
    case "library":
    case "ambush":
    case "hq":
    case "tasks":
        dest = (DRUEDAIN_DIR + "rangerpath3");
        break;
    case "ithilien":
        dest = (ITH_DIR + "nforest/fpath/bushes5");
        break;
    case "north":
        dest = (FORNOST_DIR + "plaza");
        break;
    default:
        return;
    }

    dest_room = find_object(dest);
    dest_room->teleledningsanka();
    if (!objectp(dest_room))
        return;

    tell_object(shadow_who, "Two sturdy rangers arrive and escort you from " +
        "the room in grim silence.\n");
    tell_room(room, "Two sturdy rangers arrive and escort " +
        QTNAME(shadow_who) + " from the room in grim silence.\n", shadow_who);
    shadow_who->move_living("M", dest);

    tell_room(environment(shadow_who), "Two sturdy rangers escort " + 
        QTNAME(shadow_who) + " in, then silently depart.\n", shadow_who);
}


/* Function name: expel_ranger
 * Description  : Unique Ranger function to expel a guild member:
 *                - Remove guild specific skills
 *                - Clear occupational guild stat
 *                - Penalize for leaving
 *                - Reset starting location
 *                - Update member list
 *                - Remove guild emblem
 *                - Remove soul and update hooks
 *                - Remove from the guildhouse
 *                - Log the leaving with the reason
 *                - Call remove_guild_occ
 * Arguments    : string reason - the reason they are to be expelled
 *                int soft - Will punishment be withheld?
 */
public varargs void
expel_ranger(string reason, int soft = 0)
{
    object emblem, spellbook, councilkey;

    if (!objectp(shadow_who))
        return;

    /* Remove special skills and setup skill decay */
    shadow_who->setup_skill_decay();
    shadow_who->remove_skill(SS_BRAWLING);
    shadow_who->remove_skill(SS_HEARING);
    shadow_who->remove_skill(SS_REWARDED);
    shadow_who->remove_skill(SS_RANGER_SPELL_LIST);
    shadow_who->remove_skill(SS_RANGER_DISFAVOUR);
    shadow_who->remove_skill(SS_RANGER_TEAM);

    /* Clear the member's guild stat */
    shadow_who->clear_guild_stat(SS_OCCUP);

    /* Reset start location if they are using the ranger start. */
    if (member_array(shadow_who->query_default_start_location(), 
      RANGERS_START) != -1)
        shadow_who->set_default_start_location(shadow_who->query_def_start());

    /* Update the member list */
    MANAGER->remove_ranger(shadow_who->query_real_name());

    /* Penalty for leaving waived for soft expelling and apprentices */
    if (query_ranger_level() > APPROVED_APP_LEVEL && !soft)
    {
        shadow_who->add_exp(-(shadow_who->query_exp_combat()) / 6, 1);
        MANAGER->add_banished(shadow_who->query_real_name());
    }

    /* Tell them they are being expelled. */
    shadow_who->catch_tell("You have been expelled from the Rangers " + 
        (!reason ? "" : reason) + ".\n");

    /* Remove the guild emblem */
    emblem = present(RANGERS_EMBLEM_ID, shadow_who);
    if (objectp(emblem))
    {
        shadow_who->catch_tell("A white pigeon tugs at your " + 
            emblem->short() + " and flies away with it.\n");
        emblem->remove_object();
    }

    if (objectp(evade_object))
    {
        evade_object->dispel_effect(shadow_who);
    }

    /* Remove the ranger spellbook if present */
    spellbook = present("ranger_spell_book", shadow_who);
    if (objectp(spellbook))
    {
        shadow_who->catch_tell("Your " + spellbook->short() + 
            " suddenly disappears in a cloud of smoke.\n");
        spellbook->remove_object();
    }

    /* Remove the council key if present */
    councilkey = present("_Council_Key", shadow_who);
    if (objectp(councilkey))
    {
        shadow_who->catch_tell("Your " + councilkey->short() + 
            " suddenly disappears in a cloud of smoke.\n");
        councilkey->remove_object();
    }

    /* Remove the ranger soul */
    shadow_who->remove_cmdsoul(TEST_SOUL);
    shadow_who->remove_cmdsoul(SPELL_MANAGER_SOUL);
    shadow_who->update_hooks();

    /* Remove the member from the guildhouse if there. */
    evict_ranger();
    
    /* Keep a log of those removed from the guild. */
    MANAGER->rlog(RANGERS_LOG, capitalize(shadow_who->query_real_name()) + 
        " successfully removed from " + "the guild because of " + 
        reason + ".\n");

    /* Remove the guild shadow.  This also resets tax to 0. */
    remove_guild_occ();
}

/* Function name: query_guild_not_allow_join_occ
 * Description  : Generic guild function that is called when our member 
 *                tries to join another guild. The type, style and name of the 
 *                other guild is sent as argument and we can deny
 *                our member to join that guild if we want.
 *                This is also called each time a player logs on.
 *                Reasons for denial:
 *                - Tried to join another occupational guild.
 *                - Tried to join a thief type guild.
 *                - Joined a racial guild that would change their
 *                  race to a banned race (only kender for now).
 *                WARNING!!! If the Shire orc racial plans on allowing
 *                humans to join their guild, we must test for that,
 *                as it is not included currently. However, it is
 *                tested for upon login.
 * Arguments    : object player - the player to test
 *                string type   - the guild type
 *                string style  - the guild style
 *                string name   - the guild name
 * Returns      : int 1 - if the player is denied
 *                    0 - if the player is allowed
*/
public int
query_guild_not_allow_join_occ(object player, string type, string style, 
  string name)
{
    /* This checks to make sure that the new guild is not occupational. */
    if (::query_guild_not_allow_join_occ(player, type, style, name))
    {
        return 1;
    }

    if (style == "thief")
    {
        player->catch_tell("Thieves are not allowed to be in the " + 
            RANGERS_GUILD_NAME + ".\n");
        return 1;
    }

    /* Handles a hobbit attempting to join the kender race guild, 
       as the kender race guild's name is lumped in with other
       valid branches of the guild (human/half-elf/elf/etc).
       The only option we have is to check if the player is a
       hobbit AND the guild has the Krynn Race guild name. */
    if (name == "Krynn Race" &&
      player->query_race_name() == "hobbit")
    {
        player->catch_tell("The " + RANGERS_GUILD_NAME + " do not trust the " +
            "kender race!\n");  
        return 1;
    }

    return 0;
}

/* Function name: check_banned_race
 * Description  : Unique Ranger function that tests if the race is allowed in 
 *                the guild. Starts the expelling of player if necessary.
 *                Called after a 10 second delay after logging 
 *                in and after dying from query_guild_keep_player(). 
 *                However, acts independantly from 
 *                query_guild_keep_player() due to the delayed
 *                action.
 *                
 * Arguments    : object who - the player to test
 */
public void
check_banned_race(object who)
{
    string race, reason;

    if (!objectp(who))
        return;

    /* Race restrictions */
    race = who->query_race_name();

    if (member_array(race, BANNED_RACE) != -1)
    {
        who->catch_tell("The " + RANGERS_GUILD_NAME + " do not trust the " 
            + race + " race!\n");
        reason = race + " race";
        expel_ranger(reason);
        return;
    }
}

/* Function name : query_guild_keep_player
 * Description   : Generic guild function called from autoload_shadow()
 *                 Test if we want to keep the player in the guild,
 *                 and call expel_ranger() if necessary.
 *                 Reasons for not keeping:
 *                  - Has a layman thief guild.
 *                  - Has an alignment below the minimum allowed.
 *                  - He has been marked to be removed in the manager
 *                 Calls check_banned_race to expel banned races
 *                 if necessary.
 * Arguments     : who - the player to test
 * Returns       : 1 if keeping, 0 if not
*/
public int
query_guild_keep_player(object who)
{
    int align;
    string *expelled = ({});
    string reason = "";

    /* Wizards are exempt */
    if (who->query_wiz_level())
    {
        return 1;
    }

    /* A Ranger may be marked for expulsion in the manager, either
       by an officer as punishment or because they timed out their
       apprentice time. */
    expelled = MANAGER->query_to_be_expelled(who->query_real_name());

    if (sizeof(expelled))
    {
        set_alarm(8.0, 0.0, &expel_ranger(expelled[0], expelled[1]));
        return 1;
    }

    /* Rangers are rogues, not thieves. */
    if (who->query_guild_style_lay() == "thief")
    {
        reason = "Thieves are not allowed to be in the " + 
            RANGERS_GUILD_NAME + "\n";
    }

    /* Wait a little bit to be sure that race shadows are loaded. */
    set_alarm(10.0, 0.0, &check_banned_race(who));

    align = who->query_alignment();

    /* Alignment warning. Give a warning, but keep them. */
    if (align < ALIGN_WARN)
    {
        who->catch_tell("Thoughts of the Dark Lord swirl through " +
            "your head unbidden, trying to weaken your resolve! You fear " +
            "for your soul!\n");
    }

    /* Alignment restriction reached */
    if (align < RAN_ALIGN_MIN)
    {
        who->catch_tell("Thoughts of the Dark Lord swirl through " +
            "your head unbidden as you are cast from the Rangers!\n");
        reason = "evil alignment: " + align;
    }

    /* If a reason is assigned, expel member for the reason given. */
    if (strlen(reason))
    {
        set_alarm(1.0, 0.0, &expel_ranger(reason));
        return 1;
    }
    
    return 1;
}

/* Function name: query_legend_skills
 * Description  : Unique Ranger function used to determine if a player has
 *                skills of legend level. This is one of three requirements
 *                of having the legend title.
 * Returns      : The percentage of skills a player has mastered. >= 100
 *                is legend skill level.
 */
public int
query_legend_skills()
{
    int ranger_level = query_ranger_level();
    int player_total;
    int company_total = TRAIN_CHOICE_DELTA[ranger_level - 1];
    int i = -1;
    int size = sizeof(SKILLS);

    while(++i < size)
    {
        company_total += COMPANY_SKILLS[ranger_level - 1][i];
	/* No legend status from elevated skills. */
        player_total += shadow_who->query_base_skill(SKILLS[i]);
    }

    return (100 * player_total) / company_total;
}

/* Function name: query_ranger_legend
 * Description  : Unique Ranger function that checks if this Ranger is 
 *                considered a legend or not. There are three requirements
 *                at this point: 100% or more of the Ranger skillset, legend
 *                guild stat and legend age.
 * Returns      : 1 if a legend, 0 if not
 */
nomask public int
query_ranger_legend()
{
    if ((shadow_who->query_stat(SS_OCCUP) >= LEG_STAT) &&
      (shadow_who->query_age() >= LEG_AGE) &&
      (query_legend_skills() >= 100))
    {
        return 1;
    }

    return 0;
}

/* Function name: query_is_officer
 * Description  : Unique Ranger function which returns whether they are an 
 *                officer of the Rangers or not.
 * Returns      : 1 if an officer, 0 if not
 */
public int
query_is_officer()
{
    return (MANAGER->query_is_council(shadow_who->query_real_name()));
}

/* Function name: query_guild_leader_occ
 * Description  : Generic guild function which returns whether they are an
 *                officer or not.
 * Returns      : 1 if an officer, 0 if not
 */
public int
query_guild_leader_occ()
{
    if (!query_ranger_incognito())
        return query_is_officer();
    return 0;
}

/* Function name: query_ranger_title
 * Description  : Unique Ranger function that returns the Ranger's title 
 *                depending on the query_ranger_intro() (short or long) and 
 *                query_ranger_incognito().
 * Arguments    : int intro - type of intro, short or long
 *                int incognito - 1 for hidden title, 0 for not
 * Returns      : string - the title string
 */
nomask public string
query_ranger_title(int intro = 0, int incognito = 0)
{
    string company = query_company(), title_text = "", specialty,
           name = capitalize(shadow_who->query_real_name());
    int mtask, avg_stat, rank = MANAGER->query_council(name);

    if (!strlen(company))
        return "Confused Ranger";

    if (incognito)
        return "";

    /* rintro brief, don't even show the company */
    if (!intro)
    {
        switch(company)
        {
        case "apprentice":
        case "approved":
            return "Ranger Apprentice";
        case "north":
        case "ithilien":
            return "Ranger of the Westlands";
        default:
            return "Confused Ranger";
        }
    }

    string major_virtue = query_ranger_major_virtue() ?
        " and " + MAJOR_VIRTUES_TO_NAME[
            query_ranger_major_virtue()] : "";

    /* rintro is full, show all */
    switch(rank)
    {
    case 0:
        return "Captain of the Rangers of " + 
            (company == "north" ? "the " : "") + capitalize(company)
                + major_virtue;
    case 1:
        return "Lieutenant of the Rangers of " + 
            (company == "north" ? "the " : "") + capitalize(company)
                + major_virtue;
    case 2:
        return "Sergeant of the Rangers of " + 
            (company == "north" ? "the " : "") + capitalize(company)
               + major_virtue;
    default:
        break;
    }
    /* Check for Masters and Specialists here. */
    if (MANAGER->query_is_master(name))
    {
        specialty = MANAGER->query_master_specialty(name);
        return ("Master " + specialty + " of the Rangers of " +
            (company == "north" ? "the North" : "Ithilien"))
            + major_virtue;
    }

    if (MANAGER->query_is_specialist(name))
    {
        specialty = MANAGER->query_specialist_specialty(name);
        rank = MANAGER->query_specialist_rank(name) - 1;

        mtask = member_array(specialty, MASTER_TITLES);

        return (SUB_MASTER_TITLES[mtask][rank] + " " + MASTER_TITLES[mtask] + 
          " of the Rangers of " + (company == "north" ? "the North" : "Ithilien"))
          + major_virtue;
    }

    avg_stat = query_ranger_rank();

    switch(company)
    {
    case "apprentice":
    case "approved":
        rank = COMP_REQUIREMENT / sizeof(APPRENTICE_TITLES);
        avg_stat = avg_stat / rank;
        avg_stat = (avg_stat <= 0 ? 0 : avg_stat);

        if (avg_stat >= (sizeof(APPRENTICE_TITLES) - 1))
        {
            if ((shadow_who->query_stat(SS_OCCUP) > COMP_REQUIREMENT)
                && (query_ranger_rank() >= APP_RANK_REQUIREMENT))
                avg_stat = sizeof(APPRENTICE_TITLES) - 1;
            else
                avg_stat = sizeof(APPRENTICE_TITLES) - 2;
        }

        return APPRENTICE_TITLES[avg_stat] + 
            (company == "approved" ? " Trusted" : "") + " Ranger Apprentice";

    case "north":
        if (query_ranger_legend())
            return "Legend of the Rangers of the North"
                + major_virtue;

        rank = MASTER_RANK / sizeof(MALE_TITLE);
        avg_stat -= (COMP_REQUIREMENT/6);
        avg_stat /= rank;
        avg_stat = (avg_stat >= sizeof(MALE_TITLE) ? 
            sizeof(MALE_TITLE) -1 : avg_stat);
        avg_stat = (avg_stat <= 0 ? 0 : avg_stat);

        return (MALE_TITLE[avg_stat] + " of the Rangers of the North") 
            + major_virtue;

    case "ithilien":
        if (query_ranger_legend())
            return "Legend of the Rangers of Ithilien"
                + major_virtue;


        rank = MASTER_RANK / sizeof(MALE_TITLE);
        avg_stat -= (COMP_REQUIREMENT/6);
        avg_stat /= rank;
        avg_stat = (avg_stat >= sizeof(MALE_TITLE) ? 
            sizeof(MALE_TITLE) -1 : avg_stat);
        avg_stat = (avg_stat <= 0 ? 0 : avg_stat);
        return (MALE_TITLE[avg_stat] + " of the Rangers of Ithilien")
            + major_virtue;

    default:
        return "Ranger of the Lost Company" + major_virtue;
    }
}

/* Function name: query_ranger_incognito
 * Description  : Unique Ranger function that gives the incognito status, 
 *                which is whether the Ranger's title will be displayed at all.
 * Returns      : 1 if the Ranger is incognito, 0 if the Ranger is not
 */
public int
query_ranger_incognito()
{
    /* Returns 1 if the Ranger is incognito, 0 if not */
    return ((gFlags & R_INCOGNITO) > 0);
}

/* Function name: set_ranger_incognito
 * Description  : Unique Ranger function which indicates whether the Ranger is
 *                incognito or not. Used in the title, maybe elsewhere if 
 *                incognito checks need to be made.
 * Arguments    : int incognito - what to set it to
 *                1 - Ranger is incognito
 *                0 - Ranger is not incognito
 */
public void
set_ranger_incognito(int incognito)
{
    if (incognito)
    {
        /* Set incognito on */
        gFlags = gFlags | R_INCOGNITO;
    }
    else
    {
        /* Set incognito off */
        gFlags = gFlags & ~R_INCOGNITO;
    }

    /* Update the arg string */
    shadow_who->add_autoshadow(MASTER + ":" + gFlags);
}

/* Function name: query_guild_incognito_occ
 * Description  : Mudlib function check if guild affiliation should be known
 * Returns      : 1 if guild affiliation should not be known
 *                0 if it should be known
 */
int
query_guild_incognito_occ()
{
    /* Returns 1 if Ranger is incognito, 0 if Ranger is not. */
    return(query_ranger_incognito());
}

/* Function name: query_ranger_intro
 * Description  : Unique Ranger function to determine if a long or short intro
 *                should be given. This is not the same as incognito, which is
 *                whether the title will be shown at all.
 * Returns      : 1 for long intro, 0 for short
 */
public int
query_ranger_intro()
{
    /* Returns 1 for long intro, 0 for short. */
    return ((gFlags & R_INTRO) > 0);
}

/* Function name: set_ranger_intro
 * Description  : Unique Ranger function that sets whether the long or short
 *                version of the title will be given. This is not the same as
 *                incognito, which is whether the title will be shown at all.
 * Arguments    : 1 for long, 0 for brief
 */
public void
set_ranger_intro(int r_intro)
{
    if (r_intro)
    {
        /* Sets Ranger's intro to be long. */
        gFlags = gFlags | R_INTRO;
    }
    else
    {
        /* Sets Ranger's intro to be short. */
        gFlags = gFlags & ~R_INTRO;
    }

    /* Update the arg string. */
    shadow_who->add_autoshadow(MASTER + ":" + gFlags);
}

/* Function name: query_ranger_known
 * Description  : Unique Ranger function to determine if a Ranger will
 *                be shown on rlist.
 * Returns      : 1 for known, 0 for unknown
 */
public int
query_ranger_known()
{
    /* Returns 1 for known, 0 for unknown. */
    return ((gFlags & R_KNOWN) > 0);
}

/* Function name: set_ranger_known
 * Description  : Unique Ranger function that sets whether a Ranger is
 *                known on rlist or not.
 * Arguments    : 1 for known, 0 for unknown
 */
public void
set_ranger_known(int r_known)
{
    if (r_known)
    {
        /* Sets Ranger's known to on. */
        gFlags = gFlags | R_KNOWN;
    }
    else
    {
        /* Sets Ranger's known to off. */
        gFlags = gFlags & ~R_KNOWN;
    }

    /* Update the arg string. */
    shadow_who->add_autoshadow(MASTER + ":" + gFlags);
}

/* Function name: query_guild_title_occ
 * Description  : Generic guild function which handles the guild title, 
 *                brief title if query_ranger_intro() is set to 0,
 *                long ranger title if query_ranger_intro() is set to 1, 
 *                no title at all if query_ranger_incognito() is set to 1. 
 *                Since this function is not called for wizards, we do not 
 *                have to check for them.
 * Returns      : the title of the occupational guild
 */
public string
query_guild_title_occ()
{
    return query_ranger_title(query_ranger_intro(), query_ranger_incognito());
}

public int is_major_virtue_valid(int virtue)
{
    switch (virtue) {
        case 0:
            return 1;
        // Available to everyone
        case RANGER_MAJOR_VIRTUE_ENEMY_OF_THE_EAST:
        case RANGER_MAJOR_VIRTUE_HAND_OF_THE_KING:
            return 1;
        // Rangers of the North only
        case RANGER_MAJOR_VIRTUE_ENEMY_OF_THE_SHADOW:
        case RANGER_MAJOR_VIRTUE_SENTINEL_OF_IMLADRIS:
            return query_company() == "north";
        // Rangers of Ithilien only
        case RANGER_MAJOR_VIRTUE_DAUNTLESS_GUARDIAN:
        case RANGER_MAJOR_VIRTUE_DEFENDER_OF_OSGILIATH:
            return query_company() == "ithilien";
        // Rockfriends only
        case RANGER_MAJOR_VIRTUE_OLD_HATRED:
            return this_object()->query_guild_name_race() == 
            "Rockfriend guild";

        default:
          return 0;
    }
    return 1;
}

public int is_minor_virtue_valid(int virtue)
{
    switch (virtue) {
        case 0:
          return 1;
        // Available to everyone
        case RANGER_MINOR_VIRTUE_BLESSING_OF_THE_ELDAR:
            return 1;
        // Rockfriends only
        case RANGER_MINOR_VIRTUE_DEEP_SONGS:
            return this_object()->query_guild_name_race() == 
            "Rockfriend guild";
        // Thornlin Militia only
        case RANGER_MINOR_VIRTUE_WARDEN_OF_PELENNOR:
            return this_object()->query_guild_name_lay() ==
            "Thornlin Militia";
        // Noldor Elves only
        case RANGER_MINOR_VIRTUE_DEADLY_ARCHERS:
          return this_object()->query_guild_name_race() == 
              "Noldor of Imladris";
        // Adventuresome hobbits only
        case RANGER_MINOR_VIRTUE_ART_OF_DISAPPEARING:
            return this_object()->query_guild_name_race() == 
            "Adventuresome Hobbits Guild";
        // Dunedain only
        case RANGER_MINOR_VIRTUE_NOBLE_LINEAGE:
            return this_object()->query_guild_name_race() == 
            "Dunedain";
        // Potential quest limited in the future.
        case RANGER_MINOR_VIRTUE_FRIEND_OF_ROHAN:
        case RANGER_MINOR_VIRTUE_GIFTS_OF_ESTE:
            return 1;
        default:
          return 0;
    }
    return 1;
}

void test_valid_virtues()
{
    if (!is_major_virtue_valid(query_ranger_major_virtue()))
    {
        shadow_who->catch_tell("\n\nYou no longer qualify for the " +
            MAJOR_VIRTUES_TO_NAME[query_ranger_major_virtue()] + ".  You return " +
            "to specialize in the " + MAJOR_VIRTUES_TO_NAME[
            RANGER_MAJOR_VIRTUE_ENEMY_OF_THE_EAST] + ".\n\n");
        
        
        
        MANAGER->set_major_virtue(shadow_who->query_real_name(), 
            RANGER_MAJOR_VIRTUE_ENEMY_OF_THE_EAST);
    }
    if (!is_minor_virtue_valid(query_ranger_minor_virtue()))
    {
        shadow_who->catch_tell("\n\nYou no longer qualify for the " +
            MINOR_VIRTUES_TO_NAME[query_ranger_minor_virtue()] + ".  You return " +
            "to focus on the " + MINOR_VIRTUES_TO_NAME[
            RANGER_MINOR_VIRTUE_BLESSING_OF_THE_ELDAR] + ".\n\n");
        MANAGER->set_minor_virtue(shadow_who->query_real_name(), 
            RANGER_MINOR_VIRTUE_BLESSING_OF_THE_ELDAR);
    }
}

/* 
 * Function name: init_ranger_shadow
 * Description  : Unique Ranger function. This is called with a slight 
 *                delay after login. It clones the guild item, adds the 
 *                soul and does other things that are necessary upon login.
 */
void
init_ranger_shadow()
{
    int num, check;
    object emblem, sbook, ckey;
    string company, name, specialty;

    if (!objectp(shadow_who))
        return;

    name = shadow_who->query_real_name();
    company = MANAGER->query_ranger_company(name);

    /* Add the soul to the member */
    shadow_who->add_cmdsoul(TEST_SOUL);
    shadow_who->add_cmdsoul(SPELL_MANAGER_SOUL);
    shadow_who->update_hooks();

    setuid();
    seteuid(getuid());

    /* See if the Ranger needs to vote in elections. */
    if (!MANAGER->query_voted(company, name) && MANAGER->query_election(company))
        shadow_who->catch_tell("\n\nThere is an election that needs " +
            "your vote in the board room!\n\n\n");

    /* Move the guild emblem to the player forcefully 
       and check if they need to vote on members. */
    switch(company)
    {
    case "north":
        emblem = clone_object(RANGERS_NOR_EMBLEM);
        num = MEMBER_VOTE_NOR->query_needs_to_vote(name);
        if (num > 1)
            shadow_who->catch_tell("\n\nYou have " + LANG_NUM2WORD(num) +
                " potential candidates to vote on in " +
                "the great hall.\n\n");
        else if (num == 1)
            shadow_who->catch_tell("\n\nYou have one potential candidate " +
                "to vote on in the great hall.\n\n\n");
        break;

    case "ithilien":
        emblem = clone_object(RANGERS_ITH_EMBLEM);
        num = MEMBER_VOTE_ITH->query_needs_to_vote(name);
        if (num > 1)
            shadow_who->catch_tell("\n\nYou have " + LANG_NUM2WORD(num) +
                " potential candidates to vote on " +
                "by the waterfall.\n\n\n");
        else if (num == 1)
            shadow_who->catch_tell("\n\nYou have one potential candidate " +
                "to vote on by the waterfall.\n\n\n");
        break;

    default:
        emblem = clone_object(RANGERS_APP_EMBLEM);
        if (MANAGER->query_ranger_company(name) == "apprentice")
        {
            shadow_who->catch_tell("You have " + 
                CONVTIME(MANAGER->query_apprentice_time(name) - time()) +
                " left in your apprenticeship.\n");
        }
        if (MANAGER->query_ranger_company(name) == "approved")
        {
            if (MANAGER->query_voted_in(name, "ithilien"))
                shadow_who->catch_tell("You have been approved " +
                    "to join the Ithilien Company.\n\n");
            if (MANAGER->query_voted_in(name, "north"))
                shadow_who->catch_tell("You have been approved " +
                "to join the North Company.\n\n");
        }


        break;
    }

    emblem->move(shadow_who, 1);
    emblem->set_emblem_short(shadow_who);
    emblem->set_emblem_long(shadow_who);

    // Evade is reserved for full rangers.
    switch(company)
    {
        case "north":
        case "ithilien":
            evade_object = clone_object(RANGERS_DIR + "ranger_evade_obj");
            evade_object->set_caster(shadow_who);            
            evade_object->set_target(shadow_who);
            evade_object->move(shadow_who);
            evade_object->start();
        break;
    }    

    if (shadow_who->query_skill(SS_RANGER_SPELL_LIST))
    {
        sbook = clone_object(SPELLBOOK);
        sbook->move(shadow_who, 1);
    }

    if (MANAGER->query_council(name) == CAPTAIN_POSITION ||
        MANAGER->query_council(name) == LIEUTENANT_POSITION ||
        MANAGER->query_council(name) == SERGEANT_POSITION)    
    {
        ckey = clone_object(RANGERS_COUNCILKEY);
        ckey->move(shadow_who, 1);
    }

    /* Give out rewards/punishments. If any are coming, the 
     * manager will award them. */
    //set_alarm(1.0, 0.0, &MANAGER->reward_ranger(name));
    MANAGER->reward_ranger(name);
    MANAGER->punish_ranger(name);
    MANAGER->unpunish_ranger(name);

    check = MANAGER->query_specialist_rank(name);
    if (!check)
    {
        if (query_ranger_rank() < SPECIALTY_RANK)
        {
            /* Too low rank for specialty */
            MANAGER->remove_specialist(name);
            MANAGER->rlog(company, "Failed to assign a specialty to " + name +
                "as they are not yet experienced enough as a Ranger.");
        }
        else
        {
            MANAGER->advance_specialist(name, 1);
            specialty = MANAGER->query_specialist_specialty(name);
            shadow_who->catch_tell("\nYou have been assigned the new " +
                "task of being " + LANG_ADDART(specialty) + ".\n");
            MANAGER->rlog(company, capitalize(name) + " was made " + 
                LANG_ADDART(specialty));
        }
    }
    /* Update the member list here */
    name = shadow_who->query_real_name();
    if (!strlen(MANAGER->query_ranger_company(name)))
        if (MANAGER->add_ranger(name, "apprentice"))
            shadow_who->catch_tell("For some reason, you are not on " +
                "the list of Ranger members, and will be an apprentice " +
                "until you clear the matter up. Beware, as an apprentice, " +
                "you will automatically be removed from the guild unless " +
                "you become approved or join a company by " +
                ctime(time() + APPRENTICE_TIME_OUT) + ".\n");
                
    // Every caster guild using the new Genesis magic system will
    // use the mana shadow to get the new regeneration rates for mana.
    if (!query_top_shadow()->has_mana_shadow())
    {
        clone_object(MANA_SHADOW)->shadow_me(query_shadow_who());
    }
    set_alarm(3.0, 0.0, test_valid_virtues);            
}

/*
 * Function name: init_occ_shadow
 * Description  : Generic guild function that is called when the member
 *                logs in. Any variables that need to be stored over
 *                login/logout can be initialized here.
 * Arguments    : string str - init string 
 */
public void
init_occ_shadow(string str)
{
    /* Set the Rangers preferences. */
    gFlags = atoi(str);

    /* Delay so that player completes login before we continue. */
    set_alarm(1.0, 0.0, init_ranger_shadow);
}

/* 
 * Function name: change_emblem
 * Description  : Unique ranger function. Used to replace rank-specific
 *                emblem after promotion/demotion.
 */
int
change_emblem(string rank)
{
    object player = TO->query_shadow_who(),
           emblem, old_emblem;
    object *inv;
    string name = player->query_real_name();
    inv = all_inventory(player);
    rank = lower_case(rank);

    if (!sizeof(filter(inv, &->id(RANGERS_EMBLEM_ID))))
    {
        return 0;
    }

    /* Remove the old guild token */
    old_emblem = present(RANGERS_EMBLEM_ID, player);
    if (objectp(old_emblem))
    {
        old_emblem->remove_object();
    }

    switch(rank)
    {
        case "apprentice":
            emblem = clone_object(RANGERS_APP_EMBLEM);
            break;
        case "north":
            emblem = clone_object(RANGERS_NOR_EMBLEM);
            break;
        case "ithilien":
            emblem = clone_object(RANGERS_ITH_EMBLEM);
            break;
        default:
            emblem = clone_object(RANGERS_APP_EMBLEM);
            break;
    }

    /* Add the new guild token */
    emblem->move(shadow_who, 1);
    emblem->set_emblem_short(shadow_who);
    emblem->set_emblem_long(shadow_who);

    return 1;
}

/**************STEALTH CODE FOLLOWS****************************/
/* Function name: set_autosneak
 * Description  : A unique Ranger function which sets autosneak on or off.
 * Arguments    : 1 for autosneak on or 0 for autosneak off
 */
public void
set_autosneak(int autosneak)
{
    gAutosneakOn = autosneak;
}
 
/* Function name: query_autosneak
 * Description  : A unique Ranger function which queries what the Ranger's
 *                autosneak is set to.
 * Returns      : gAutosneakOn variable - 1 for on, 0 for not
 */
public int
query_autosneak()
{
    return gAutosneakOn;
}

/* Function name: move_living
 * Description  : Masked function used handle sneaking any time one is moved.
 *                See the mudlib function for details on the arguments.
 */
public varargs int
move_living(string how, mixed to_dest, int dont_follow, int no_glance)
{
    int hiding, retval, val, bval, did_sneak;
    object me = shadow_who;
 
    if (me->query_prop(RANGER_I_PREPARE_BRAWL))
    {
        me->add_prop(RANGER_I_PREPARE_BRAWL, MOVED_WHILE_BRAWLING);
    }

    if (!gAutosneakOn || me->query_prop("_fogey_is_limping_"))
    {
        retval = me->move_living(how, to_dest, dont_follow, no_glance);
        return retval;
    }

    if (me->query_prop(OBJ_I_LIGHT) &&
      (me->query_prop(OBJ_I_LIGHT) >
      environment(this_player())->query_prop(OBJ_I_LIGHT)))
    {
        me->catch_tell("You cannot sneak shining like that.\n");
        retval = me->move_living(how, to_dest, dont_follow, no_glance);
        return retval;
    }
    else if (objectp(me->query_attack()))
    {
        me->catch_tell("You are still too shaken from combat for "
            + "stealthy movement.\n");
        retval = me->move_living(how, to_dest, dont_follow, no_glance);
        return retval;
    }

    hiding = environment(me)->query_prop(ROOM_I_HIDE);
    bval = me->query_skill(SS_SNEAK) * 2 + me->query_skill(SS_HIDE) / 3;
    bval = (bval - hiding) / 2;
 
    if (hiding < 0 || bval <= 0)
    {
        me->catch_tell("It's too difficult to sneak from here.\n");
        retval = me->move_living(how, to_dest, dont_follow, no_glance);
        return retval;
    }

    val = bval + random(bval);
    me->add_prop(OBJ_I_HIDE, val);
    me->add_prop(LIVE_I_SNEAK, 1);

    retval = me->move_living(how, to_dest, dont_follow, no_glance);

    hiding = environment(me)->query_prop(ROOM_I_HIDE);
    bval = me->query_skill(SS_HIDE);
    bval = (bval - hiding) / 2;
 
    if (hiding < 0 || bval <= 0)
    {
        me->catch_tell("It's too difficult to hide in here, you're " +
            "visible again.\n");
        me->reveal_me(0);
        return retval;
    }
 
    if (me->query_prop(OBJ_I_LIGHT) &&
      (me->query_prop(OBJ_I_LIGHT) > environment(me)->query_prop(OBJ_I_LIGHT)))
    {
        me->catch_tell("You cannot hide here, shining like that!\n");
        this_player()->reveal_me(1);
        return retval;
    }
 
    val = bval + random(bval);
    this_player()->add_prop(OBJ_I_HIDE, val);
    return retval;
}


/* Function name : check_seen
 * Description   : Masks check_seen to allow rangers to
 *                 follow each other while in team. True if
 *                 this object can be seen by a given object.
 * Arguments     : for_obj: The object for which
 *                 visibility should be checked
 * Returns       : 1 if this object can be seen
*/
public int
check_seen(object for_obj)
{
    /* The observer is not a ranger, do the normal check_seen */
    if (!RANGERS_MEMBER(for_obj))
    {
        return query_shadow_who()->check_seen(for_obj);
    }

    /* The one being observed has no team that would need
       to mask this check */
    if((member_array(for_obj, shadow_who->query_team()) == -1) &&
      (for_obj != shadow_who->query_leader()))
    {
        return query_shadow_who()->check_seen(for_obj);
    }

    /* There is a ranger on the team. Bypass the awareness check
       when viewing his/her leader.*/
    else
    {
        if (!objectp(for_obj) ||
             shadow_who->query_no_show() ||
             (!for_obj->query_wiz_level() &&
              (for_obj->query_prop(LIVE_I_SEE_INVIS) <
               shadow_who->query_prop(OBJ_I_INVIS))))
        {
            return 0;
        }

        return 1;
    }
}

/* Teaming functions follow: Rewarding for teaming with apprentices
   and punishment for teaming with enemy guilds (not evil players who
   may have a different view of alignment, such as the SU who believe
   the only evil is disobeying their gods. */
/*
 * Function name:    reward_app_teaming
 * Description  :    Rewards teaming with apprentices. This adds a number
 *                   of points to a reserved skill which is used to calculate
 *                   the rank of the Ranger. A Ranger who gives time to
 *                   help apprentices is held in more esteem within the guild.
 *                   To reward both RP time and combat time, which are both
 *                   helpful to the apprentice, time and combat time are
 *                   rewarded.
 * Arguments    :    string - The apprentice's name
 *                   int - the current combat exp
 */
public void
reward_app_teaming(string appname, int exp_combat)
{
    int exp_diff, msg_num; 
    float skill, time_diff;

    if (member_array(appname, m_indexes(gAppTeam)) == -1)
        return;

    /* Find combat experience gained since teaming began. */
    exp_diff = exp_combat - gAppTeam[appname][1];

    /* Find time elapsed since teaming began. */
    time_diff = itof(time() - gAppTeam[appname][0]);

    if (time_diff < 900.0)
        return;

    /* Maximum of 5 hours teaming reward */
    time_diff = min(18000.0, time_diff);

    /* 10% of apprentice's combat exp */
    skill = itof(exp_diff) * 0.1;

    /* 50 points per half hour */
    skill += ((time_diff / 1800.0) * (50.0));

    /* We've gotten the needed variables. Let's remove the entry. */
    gAppTeam = m_delete(gAppTeam, appname);

    /* Set the skill to a reasonable level based on time spent with the
       apprentice and exp gained by the apprentice during that time. */
    shadow_who->set_skill(SS_RANGER_TEAM, 
        shadow_who->query_skill(SS_RANGER_TEAM) + ftoi(skill));

    msg_num = ftoi(skill)/20;
    msg_num = msg_num > 19 ? 19 : msg_num;
    msg_num = msg_num <= 0 ? 0 : msg_num;

    shadow_who->catch_tell(TEAM_PROG_MSGS(capitalize(appname))[msg_num] + "\n");
    
    
    /* Let's log it to make sure it's working ok. The log can be removed
       once it's confirmed to be working well. */
    setuid();
    seteuid(getuid());
    MANAGER->rlog(RANGERS_WIZ_LOG, 
        capitalize(shadow_who->query_real_name()) + " gained " +
        "skill of " + ftoi(skill) + " for teaming with " + capitalize(appname) +
        " for " + CONVTIME(ftoi(time_diff)) + " who gained " + 
        exp_diff + " combat experience.");
}

/*
 * Function name: apprentice_add
 * Description  : Add an apprentice to the shadowed player's list.
 * Arguments    : object app - the apprentice to add
 */
void
apprentice_add(object app)
{
    /* If there is a previous value, something has gone wrong and this
       will reset it in any case, so there is no need to check if the
       name is already on the list. Only check for full Ranger. */
    if (query_ranger_level() > APPROVED_APP_LEVEL)
    {
        gAppTeam += ([ app->query_real_name() : ({ time(), 
            app->query_exp_combat() }) ]);
    }
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
        shadow_who->catch_tell("\nThe Valar disapprove of your teaming " +
            "with the enemy, " + who->query_the_name(shadow_who) + "!\n\n");

        if (!gTeamAlarm)
            gTeamAlarm = set_alarm(60.0, 0.0, &punish_teaming(who, 1));

        break;

    case 1:
        if (objectp(who) &&
            member_array(who, shadow_who->query_team_others()) != -1)
        {
            shadow_who->catch_tell("\nYou feel the building wrath of the " +
                "Valar as you remain on the team of your enemy, " +
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
            shadow_who->catch_tell("\nThe lidless eye of Sauron clouds " +
                "your vision as you feel the presence of the Valar " +
                "lessen.\n\n");
            align = who->query_alignment();
            align = min(-210, align);

            ran_align = shadow_who->query_alignment();
            align /= 3;
            ran_align += align;
            shadow_who->set_alignment(ran_align);
            MANAGER->rlog(RANGERS_WIZ_LOG, 
                capitalize(shadow_who->query_real_name()) +
                " had alignment adjusted by " + align + " to " +
                ran_align + " for teaming with " + 
                capitalize(who->query_real_name()) + ".");
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
    int i, size, current_exp, success, outlaw;
    object *team;
    string name, gname;

    if (leader == 0)
    {
        /* Find the other team members before this member leaves the team. */
        team = shadow_who->query_team_others();

        if (query_ranger_level() == APPRENTICE_LEVEL)
        {
            /* Get the arguments for reward_app_teaming */
            name = shadow_who->query_real_name();
            current_exp = shadow_who->query_exp_combat();

            /* The one leaving is an apprentice. Cycle through the other
            team members to see if any are full Rangers who get a reward. */
            for (i = 0, size = sizeof(team); i < size; i++)
            {
                if (team[i]->query_ranger_level() > APPROVED_APP_LEVEL)
                    team[i]->reward_app_teaming(name, current_exp);
            }
        }
        else if (query_ranger_level() > APPROVED_APP_LEVEL)
        {
            /* The one leaving is a full ranger. Cycle through the other
               team members to see if any are apprentices for a reward. */
            for (i = 0, size = sizeof(team); i < size; i++)
            {
                name = team[i]->query_real_name();
                if (member_array(name, m_indexes(gAppTeam)) != -1)
                    reward_app_teaming(name, team[i]->query_exp_combat());
            }
        }

        /* Let them leave the team now that we've gotten all the team info. */
        success = shadow_who->set_leader(leader);
    }
    else
    {
        /* Make them join first so we can get team info. */
        success = shadow_who->set_leader(leader);
        
        /* They couldn't join. Don't do anything else. */
        if (!success)
            return success;

        team = shadow_who->query_team_others();

        if (query_ranger_level() == APPRENTICE_LEVEL)
        {
            /* Add this apprentice's name to the other team's Ranger's lists.
               The function being called will check for full Ranger status. */
            for (i = 0, size = sizeof(team); i < size; i++)
            {
                team[i]->apprentice_add(shadow_who);
            }
        }
        else if (query_ranger_level() > APPROVED_APP_LEVEL)
        {
            /* This is a full Ranger. Add any apprentices in the team. */
            for (i = 0, size = sizeof(team); i < size; i++)
            {
                if (team[i]->query_ranger_level() == APPRENTICE_LEVEL)
                    apprentice_add(team[i]);
            }
        }

        gname = leader->query_guild_name_occ();
        outlaw = (MANAGER->query_is_outlaw(gname) || 
            MANAGER->query_notorious_outlaw(gname));
        /* The militia already checks teaming with these guilds. */
        if (( !outlaw && 
          shadow_who->query_guild_name_lay() != MILITIA_S_GUILD_NAME ) ||
          ( outlaw ))
        {
            /* Code for punishing teaming with enemy guilds and outlaws. */
            if (leader->query_wiz_level() || shadow_who->query_wiz_level())
                return success;

            if (shadow_who->query_skill(SS_MASTER_TASK) == 4)
            {
                log_file("alignadj", shadow_who->query_name() + " followed " +
                    "enemy being, " + leader->query_name() + ", avoiding " +
                    "penalty as Emissary. " + ctime(time()) + ".\n");
                return success;
            }

            if (success && member_array(gname, BANNED_GUILDS) != -1)
                punish_teaming(leader, 0);
         }
    }

    return success;
}

/*
 * Function name:   team_join
 * Description:     Sets this living as the leader of another.
 *                  Mask parent so that teaming with enemy guilds affects
 *                  ranger's alignment.
 * Arguments:       member: The objectpointer to the new member of my team
 * Returns:         True if member accepted in the team
 */
public int
team_join(object member)
{
   int success, outlaw;
   string gname;

    success = shadow_who->team_join(member);
    if (!success || member->query_wiz_level() || shadow_who->query_wiz_level())
        return success;

    gname = member->query_guild_name_occ();
    outlaw = (MANAGER->query_is_outlaw(gname) || 
             MANAGER->query_notorious_outlaw(gname));
    /* The militia already checks for these guilds, but not for outlaws. */
    if (( !outlaw && 
      shadow_who->query_guild_name_lay() != MILITIA_S_GUILD_NAME ) ||
      ( outlaw ))
    {
        if (member_array(gname, BANNED_GUILDS) != -1)
        {
            if (shadow_who->query_skill(SS_MASTER_TASK) == 4)
            {
                log_file("alignadj", shadow_who->query_name() + " lead " +
                    "enemy being, " + member->query_name() + ", avoiding " +
                    "penalty as Emissary. " + ctime(time()) + ".\n");
                return success;
            }

            punish_teaming(member, 0);
        }
    }

    return success;
}


/* Code dealing with alignment and killing follows */

/*
 * Function name: notify_you_killed_me
 * Description  : This function is called in a living when they kill
 *                something. We mask it to make sure the Ranger is
 *                behaving.
 * Arguments    : object killed - the killed living
 * Returns      : 1/0
 */
public int
notify_you_killed_me(object killed)
{
    string killed_race = (string)killed->query_race();
    mixed whom;

    /* you have to do this in case more than one shadow defines 
       the function, Olorin */
    shadow_who->notify_you_killed_me(killed);
    seteuid(getuid(TO));
    if (interactive(killed))
    {
        if (killed->query_guild_name_occ() == RANGERS_GUILD_NAME)
            tell_object(shadow_who, "Oh no! You have killed one of " +
                "your own!\nConsider this a warning from the Ranger " +
                "Council.\n");

        MANAGER->rlog(RANGERS_WIZ_LOG, capitalize(shadow_who->query_name()) + 
            " killed " + capitalize(killed->query_real_name()) + 
            ", a player (" + killed_race + ").\n");
    }
    else if (killed->id("Cityguard") || killed->id("_gondor_guard"))
    {
        tell_object(shadow_who,
          "You should not go around killing cityguards and the like.\n");

        tell_object(shadow_who,
          "Consider this a warning from the Rangers Guild.\n");
    }
    else if(killed->id("ranger"))
    {
        tell_object(shadow_who,
          "Oh no! You killed one of your own guild!\n" +
          "Consider this a warning from the Ranger Council.\n");
    }
    else if(killed->id("rohirrim"))
    {
        tell_object(shadow_who,
          "You should not go around killing Rohirrim, who are our allies!\n" +
          "Consider this a warning from the Rangers Guild.\n");
    }
    else if((function_exists("create_captain", killed) == 
      "/d/Genesis/ship/captain") ||
      (function_exists("create_monster", killed) == 
      "/d/Genesis/ship/captain"))
    {
        tell_object(shadow_who, "You should not go around killing " +
            "ship captains!\nConsider this a warning from the Rangers " +
            "Guild.\n");
    }
    else if((whom = killed->query_prop(GONDOR_M_LOG_RANGER_KILL)))
    {
        tell_object(shadow_who,
          "You should not go around killing the allies of the White Tower!\n" +           "Consider this a warning from the Rangers Guild.\n");
    }
    return 1;
}

/*
 * Function name: check_alignment
 * Description  : called from set_alignment() and adjust_alignment() to
 *                ensure that player is still worthy of being a ranger.
 */
public void
check_alignment()
{
    int align = shadow_who->query_alignment();

    if (align < RAN_ALIGN_MIN)
    {
        shadow_who->catch_tell("The Dark Lord has tempted you too much!\n" +
          "You are no longer worthy of being a Ranger!\n");
        if (!shadow_who->query_wiz_level())
            expel_ranger("for becoming too evil");
        else
            shadow_who->catch_tell("Your wizardhood protects you from being "+
              "evicted from the Rangers.\n");
    }
    else if (align < ALIGN_WARN)
    {
        shadow_who->catch_tell("You are giving in to the temptation of " +
          "the Dark Lord!\nMend your ways or you will become unworthy of " +
          "being a ranger!\n");
    }
}

/*
 * Function name: set_alignment
 * Description  : Masks set_alignment so that we can check if the Ranger
 *                has gotten too evil.
 * Arguments    : int a - the new alignment.
 */
public void
set_alignment(int align)
{
    shadow_who->set_alignment(align);
    check_alignment();
}

/*
 * Function name: adjust_alignment
 * Description  : Masks adjust_alignment so that we can check if the Ranger
 *                has gotten too evil.
 * Arguments    : int align - the new alignment of the quest
 */
public void
adjust_alignment(int align)
{
    shadow_who->adjust_alignment(align);
    check_alignment();
}

