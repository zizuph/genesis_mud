/*
 * The Priesthood of Takhisis
 */

/* Navarre : Added check to ensure only one NightLady/NightLord can exist */

#pragma strict_types
#pragma no_inherit

#include "/d/Ansalon/common/defs.h"
#include "../guild.h"
#include "../admin/admin.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"
#include <ss_types.h>
#include <const.h>
#include <macros.h>
#include <wa_types.h>
#include <alignment.h>
#include <language.h>
#include <files.h>
#include <login.h>
#include <tasks.h>

#define ENCHANTMENT_INTERFACE   NOBJ + "enchantment_interface"

inherit "/std/guild/guild_occ_sh";
inherit ENCHANTMENT_INTERFACE;

mixed *gTitles = GUILD_TITLES;
int gBattlemovements = 1;

#undef AUTO_MOVE_BEHIND
#ifdef AUTO_MOVE_BEHIND
mapping gAttackers;
#endif

/****************************************************
 * Misc internal functions
 ****************************************************/

int
filter_death(object ob)
{
    if (ob->query_guild_name_occ() == GUILD_NAME &&
        ob->query_priest_level() >= GUILD_LEVEL_PRIEST &&
        present(MEDALLION_ID, ob))
        return 1;
    
    return 0;
}

public int
query_pot_member()
{
    return 1;
}

#ifdef COUNCIL_TITLES_IN_PRESENTATION
static string
add_subtitle(string title1, string title2)
{
    if (stringp(shadow_who->query_guild_title_lay()))
        return title1 + ", " + title2;
    else
        return title1 + " and " + title2;
}
#endif

varargs public int
query_priest_level(int gs = -1)
{
    if (gs < 0)
        gs = shadow_who->query_skill(PS_GUILD_LEVEL);

    if(gs > 149)
        gs = 149;
        
    switch(gs)
    {
        case 100..149:
            return 2;
        case 50..99:
            return 1;
        default:
            return 0;
    }
}

varargs public int
query_priest_sublevel(int gs = -1)
{
    if (gs < 0)
        gs = shadow_who->query_skill(PS_GUILD_LEVEL);

    if (gs > 149)
        gs = 149;
    return (gs % 50) / 10;
}

public string
query_priest_title()
{
    mixed rank,subrank;
    int i;
    string title;
    rank = query_priest_level();
    subrank = query_priest_sublevel();


    // Make sure that you can only be the NightLady or Nightlord if you are the leader of the guild.
    if(rank == 2 && (subrank == 4 || subrank == 5) && 
       GUILD_ADMIN->query_guild_leader() != query_shadow_who()->query_real_name())
    {
        subrank = subrank - 2;
    }

    if (query_shadow_who()->query_prop(POT_SPECIAL_TITLE))
        return query_shadow_who()->query_prop(POT_SPECIAL_TITLE);

/*
    if (GUILD_ADMIN->query_guild_leader() == query_shadow_who()->query_real_name())
    {
        rank = 2;
        subrank = 4;
    }
*/
    
    if(shadow_who->query_gender() == G_FEMALE)
        title = gTitles[rank][subrank * 2 + 1];
    else
        title = gTitles[rank][subrank * 2];

#ifdef COUNCIL_TITLES_IN_PRESENTATION
    i = member_array(shadow_who->query_real_name(), GUILD_ADMIN->query_guild_council());
    if (i >= 0)
    {
    	title = add_subtitle(title, COUNCIL_TITLES[i]);
    }
#endif
        
    return title + " of Takhisis";
}

varargs string
query_standing_desc(object who, object for_obj,
    int standing = PS_STANDING_MIN - 1)
{
    string str, desc;

    if (!who)
        who = this_player();
    
    if (standing == PS_STANDING_MIN - 1)
        standing = who->query_skill(PS_STANDING);
    else if (standing < PS_STANDING_MIN)
        standing = PS_STANDING_MIN;
    else if (standing > PS_STANDING_MAX)
        standing = PS_STANDING_MAX;

    if (objectp(for_obj) && for_obj != who)
        str = QCTNAME(who) + " is ";
    else
        str = "You are ";
    
    switch (standing)
    {
        case PS_STANDING_MIN..-1000:
            desc = "blasphemous";
            break;
        case -999..-700:
            desc = "perfidious";
            break;
        case -699..-500:
            desc = "out of grace with Takhisis";
            break;
        case -499..-300:
            desc = "disfavoured by Takhisis";
            break;
        case -299..-100:
            desc = "greatly out of touch with Takhisis";
            break;
        case -99..-40:
            desc = "out of touch with Takhisis";
            break;
        case -39..-10:
            desc = "in somewhat poor standing with Takhisis";
            break;
        case -9..10:
            desc = "without standing in the eyes of Takhisis";
            break;
        case 11..40:
            desc = "in somewhat good standing with Takhisis";
            break;
        case 41..100:
            desc = "poorly guided by Takhisis";
            break;
        case 101..300:
            desc = "in good standing with Takhisis";
            break;
        case 301..500:
            desc = "guided by Takhisis";
            break;
        case 501..700:
            desc = "favourable by Takhisis";
            break;
        case 701..1000:
            desc = "greatly guided by Takhisis";
            break;
        case 1001..PS_STANDING_MAX:
            if (who->query_gender() == G_FEMALE)
                desc = "the Handmaiden of Takhisis";
            else
                desc = "the Aide-de-camp of Takhisis";
            break;
    }
    
    return str + desc;
}

int
query_standing()
{
    return query_shadow_who()->query_skill(PS_STANDING);
}

void
set_standing(int standing)
{
    if (standing < PS_STANDING_MIN)
        standing = PS_STANDING_MIN;
    
    if (standing > PS_STANDING_MAX)
        standing = PS_STANDING_MAX;

    query_shadow_who()->set_skill(PS_STANDING, standing);
}

void
adjust_standing(int change)
{
    if (query_standing_desc(query_shadow_who(), 0,
        ADJUST_STANDING(query_standing(), change)) !=
        query_standing_desc(query_shadow_who(), 0, query_standing()))
    {
        tell_object(query_shadow_who(), "You feel " +
            (change > 0 ? "more" : "less") + " in touch with Takhisis.\n");
    }

    setuid();
    seteuid(getuid());
    
    if (file_size("/d/Ansalon/log/pot/standing") >= 50000)
        rename("/d/Ansalon/log/pot/standing", "/d/Ansalon/log/pot/standing.old");
    write_file("/d/Ansalon/log/pot/standing",
        sprintf("%-13s: %-40s %4d %4d\n",
        capitalize(query_shadow_who()->query_real_name()),
        calling_function(), query_standing(), change));
    
    set_standing(ADJUST_STANDING(query_standing(), change));
}

/*
 * Function:	s_allow_other_guilds
 * Description:	Check if the player is allowed to have joined
 *		other guilds.
 * Arguments:	player - The player to check
 * Returns:	1 -- Ok, 0 -- Not ok.
 */
static int
s_allow_other_guilds(object player)
{
    return 1;
}

/****************************************************
 * Redefined functions from the shadow
 ****************************************************/
/*
 * Function name: query_guild_style_occ
 * Description:	  Return the style of the guild
 */
public string 
query_guild_style_occ()
{ 
    return GUILD_STYLE;
}

/*
 * Function name: query_guild_name_occ
 * Description:	  Return the name of the guild
 */
public string 
query_guild_name_occ()
{
    return GUILD_NAME;
}

/*
 * Function name: query_guild_tax
 * Description:   Set the initial tax
 */
public int 
query_guild_tax_occ() 
{ 
    return TAX_ARRAY[query_priest_level()];
}

/*
 * Function name: query_guild_keep_player
 * Description:	  Called from the autoload function to determin
 *		  if we should keep the player or not.
 * Arguments:	  ob - The player object
 * Returns:	  1 -- Keep the player, 0 -- Dont keep the player
 */
public int
query_guild_keep_player(object player)
{
    if (!s_allow_other_guilds(player))
        return 0;

    setuid();
    seteuid(getuid());

#ifdef RACES_BLOCK
    if (member_array(player->query_race_name(), RACES_BLOCK) >= 0)
    {
        GUILD_ADMIN->log(player, "left", "expelled due to changing race");
        player->punish_for_leaving(3);
        GUILD_ADMIN->remove_priest(player->query_real_name());
        player->catch_tell("You find it hard to concentrate. Faded " +
            "images comes back and forth in your mind, none making " +
            "any sense. Gradually they seem to blend into an apparition. " +
            "A multi-coloured five-headed dragon stares in anger at you. " +
            "A thundering voice speaks: Ye who choose so poorly I shall " +
            "grace with a choice of my own!\n");
        player->set_default_start_location(RACESTART[player->query_race()]);
        player->move_living("X", player->query_default_start_location());
        player->set_hp(50);
        return 0;
    }
#endif
            
    
    if (GUILD_ADMIN->query_priest_has_punishment(player->query_real_name(),
        P_EXPELLED))
    {
        GUILD_ADMIN->log(player, "left", "expelled from " +
            "query_guild_keep_player");
        player->punish_for_leaving(3);
        GUILD_ADMIN->remove_priest(player->query_real_name());
        player->catch_tell("You find it hard to concentrate. Faded " +
            "images comes back and forth in your mind, none making " +
            "any sense. Gradually they seem to blend into an apparition. " +
            "A multi-coloured five-headed dragon stares in anger at you, " +
            "no matter where you look, no matter if your eyelids are open " +
            "or not - the dragon remains the only image you see. Looking " +
            "down to escape the vision you realise in horror one of its " +
            "claws has reached inside your body. You writhe in agony as " +
            "your very lifesource is drained from you.\n");
        player->set_default_start_location(RACESTART[player->query_race()]);
        player->move_living("X", player->query_default_start_location());
        player->set_hp(50);
        return 0;
    }

    return 1;
}

/*
 * Function name: query_guild_not_allow_join_occ
 * Description:   Check if we allow that the player joins another guild
 * Arguments:	  player - The player
 *		  type, style, name - The type, style and name of the
 *		  intended guild
 * Returns:	  1 if we do not allow, else 0
 */
public int
query_guild_not_allow_join_occ(object player, string type, string style,
			string name)
{
    if (::query_guild_not_allow_join_occ(player, type, style, name))
        return 1;

    return 0;
}

/*
 * Function name: query_guild_title_occ
 * Description:	  Find the occupational title of the magic-user.
 * Returns:	  The occupational priest title.
 */
public string
query_guild_title_occ()
{
    return query_priest_title();
}

/* Function name: query_def_post
 * Description:   We change the default post office for our members.
 * Returns:	  string - the path to the new postoffice
 */
string
query_def_post() 
{
    /* Only bother using the guild's post office if the player is
     * using the guild's start location.
     */
    if (this_player()->query_default_start_location() == GUILD_START)
    {
        return GUILD_PO;
    }

    return query_shadow_who()->query_def_post();
}

/* Function name: query_guild_leader_occ
 * Description:   For the mailreader to recognise certain guildmembers
 *                as being allowed to have more mail in the mailbox
 * Returns:       int - 1/0, member of the council or not.
 */
int
query_guild_leader_occ()
{
    return (member_array(query_shadow_who()->query_real_name(),
        GUILD_ADMIN->query_guild_council()) >= 0);
}

/* 
 * Function name: add_occ_shadow
 * Description:   Shadow an object with this shadow
 * Arguments:     object who - the object to shadow
 * Returns:       as shadow_me in /std/guild/guild_base.c
 */
int
add_occ_shadow(object who)
{
    return shadow_me(who, "occupational", GUILD_STYLE, GUILD_NAME);
}

/*
 * Function name: remove_occ_member
 * Description:   remove this member from the guild
 */
void
remove_occ_member()
{
    object emblem, who = query_shadow_who();
    int i;

    /* Remove special skills */
    for (i=0; i<sizeof(PS_NUM); i++)
    {
    	who->remove_skill(PS_NUM[i]);
    }

    /* Clear the player's guild stat */
    who->clear_guild_stat(SS_OCCUP);

    /* Remove any instances of the guild emblem on the player */
    while (emblem = present(MEDALLION_ID, who))
    {
        emblem->remove_object();
    }

    /* If the player is using our start location, remove it */
    if (who->query_default_start_location() == GUILD_START)
    {
        who->set_default_start_location(who->query_def_start());
    }
    
    /* Remove the guild soul */
    who->remove_cmdsoul(GUILD_CMDSOUL);
    who->update_hooks();

    GUILD_ADMIN->remove_priest(who->query_real_name());

    /* Remove the guild shadow.  This also resets tax to 0. */
    remove_guild_occ();
}	

/* Layman shadowing functions
 */

/* Function name: query_guild_not_allow_join_lay
 * Description:   Makes sure we cannot join any layman guild.
 */
int
query_guild_not_allow_join_lay(object player, string type, string style,
    string name)
{
    if (type == "layman")
    {
        notify_fail("One layman guild is enough.\n");
        return 1;
    }
}

/* Function name: remove_guild_lay
 * Description:   Removes the player from the layguild. When removed from
 *                the occ guild, the lay part is no longer.
 * Returns:       int - 1, always.
 */
int
remove_guild_lay()
{
    return 1;
}

/* Function name: query_guild_style_lay
 * Description:   Returns what style of a layman guild we have.
 * Returns:       string - the style
 */
string
query_guild_style_lay()
{
    return GUILD_STYLE;
}

/* Function name: query_guild_name_lay
 * Description:   Returns what name of the layman guild we have.
 * Returns:       string - the name
 */
string
query_guild_name_lay()
{
    return GUILD_NAME;
}

/* Guild functions
 */

/*
 * Function name: punish_for_leaving
 * Description:   exact an exp punishment for leaving
 * Arguments:     int ratio - ratio of exp punishment, >= 3
 */
public varargs void 
punish_for_leaving(int ratio = 4)
{
    int trex;

    setuid();
    seteuid(getuid());

    if (ratio < 3)
        ratio = 3;

    trex = shadow_who->query_exp_combat() / ratio;
    shadow_who->add_exp(-trex);

    (GUILD_ADMIN)->log(query_shadow_who(), "admin", sprintf("Punished " +
        "for leaving. 1/%d (%d) exp removed by %s.", ratio, trex,
        (interactive(calling_object()) ?
         C(calling_object()->query_real_name()) :
         file_name(calling_object()))));
}

/***********************************/

string
show_subloc(string subloc, object on_obj, object for_obj)
{
    string s;

    if (subloc != "_priest_of_takhisis_")
        return shadow_who->show_subloc(subloc,on_obj,for_obj);

    if (on_obj->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (on_obj->query_armour(A_R_HAND))
        return "";

    switch (query_priest_level())
    {
    	case 0:
    	    s = "a tattoo of a black dragon";
    	    break;
    	case 1:
    	    s = "a black tattoo of a five-headed dragon";
    	    break;
    	case 2:
    	    s = "a tattoo of a five-headed multi-coloured dragon";
    	    break;
    }

    if (on_obj == for_obj)
        return "You have " + s + " on your right wrist.\n";
    else
        return C(HE(on_obj)) + " has " + s + " on " + HIS(on_obj) +
        " right wrist.\n";
}

static void
s_init_priest()
{
    object med,tat;
    string *souls;
    int i, size;

    query_shadow_who()->set_guild_pref(SS_OCCUP,
        TAX_ARRAY[query_priest_level()]);

    setuid();
    seteuid(getuid());
    
    if (med = clone_object(MEDALLION_OBJ))
    {
    	med->add_name(MEDALLION_ID);
        if (med->move(query_shadow_who()))
        {
            med->move(shadow_who, 1);
            med->add_spell_object(query_shadow_who());
        }
    }

    souls = query_shadow_who()->query_cmdsoul_list();
    for (i = 0, size = sizeof(souls) ; i < size ; i++)
        query_shadow_who()->remove_cmdsoul(souls[i]);

    /* add the guild's soul to the player */
    query_shadow_who()->add_cmdsoul(GUILD_CMDSOUL);

    for (i = 0 ; i < size ; i++)
    {
        if (souls[i] != GUILD_CMDSOUL)
            query_shadow_who()->add_cmdsoul(souls[i]);
    }
    
    query_shadow_who()->update_hooks();

    query_shadow_who()->add_subloc("_priest_of_takhisis_",this_object());

    if (E(query_shadow_who()) &&
        function_exists("servant_greet_member",E(query_shadow_who())))
        E(query_shadow_who())->servant_greet_member(query_shadow_who());

    query_shadow_who()->command("$wear " + MEDALLION_ID);

    if (interactive(query_shadow_who()))
    {
        GUILD_ADMIN->init_priest(query_shadow_who());
        query_shadow_who()->remove_skill(143006);
    }
}

void
init_occ_shadow(string str)
{
    set_alarm(3.0,0.0,s_init_priest);
}

/***********************************/


public mixed
query_guild_trainer_occ()
{
    return ({
    	NTEMPLE + "lvl2/abbey",      // Terwed
    	NTEMPLE + "dung2/guard",        // Gruzz
    	NTEMPLE + "dung1/workshop",   // Erdin
    	NTEMPLE + "dung1/herbshop",     // Alister
    	});
}

/*
 * Guild specific adverbs
 */
string
full_adverb(string str)
{
    if (strlen(str) > 2)
    {
        if (wildmatch(str + "*", "malevolently"))
            return "malevolently";
    }

    return shadow_who->full_adverb(str);
}

/*
 * Function name: query_guild_skill_name
 * Description:   When a players uses the skills command he should get the
 *  the skill names, not the 'special' string.
 * Arguments:     type - the number of the skill
 * Returns:  0 if no skill of mine, else the string.
 */
mixed
query_guild_skill_name(int type)
{
    int i;

    if ( (i = member_array(type, PS_NUM)) < 0)
        return 0;
    else
        return PS_DESC[i];
}

/*
 * Function name: has_allowed_priest_alignment
 * Description:   Checks if the player has an allowed alignment for his level
 * Returns:       1 if alignment is ok, 0 if it's too high
 */
public int
has_allowed_priest_alignment()
{
    if (shadow_who->query_alignment() > ALIGN_LIMIT[query_priest_level()])
        return 0;
    else
        return 1;
}

/**********************************************************
 * Shadowed functions within the player object
 **********************************************************/
/*
 * Function name: set_alignment
 * Description:	  Sets the alignment of a player, we will check if
 * 	          the alignment is getting out of bounds for a priest
 * Arguments:	  a - The amount of points
 */
public void
set_alignment(int a)
{
    if (!has_allowed_priest_alignment() &&
        a <= ALIGN_LIMIT[query_priest_level()])
    {
    	tell_object(shadow_who,"Once more you shelter in the embrace " +
    	"of the Queen of Darkness, and she grants you use of her " +
    	"powers again.\n");
    }
	
    shadow_who->set_alignment(a);

    if(a > ALIGN_LIMIT[query_priest_level()])
    {
        /* If we become too 'good' in Takhisis eyes, she will not
         * listen to our prayers (not allow us casting spells)
         * They will be restored first when praying at the altar
         */
        shadow_who->set_skill(PS_SPELLS, 0);
        present(MEDALLION_ID, shadow_who)->m_remove_all_spells();
        
        tell_object(shadow_who,"You have strayed too far from " +
        "the Queen of Darkness, and she removes her hands from " +
        "you until you redeem yourself.\n");
    }
}

public void
do_die(object killer)
{
    object ob;
    
    seteuid(getuid());

    if (query_shadow_who()->query_hp() > 0)
        return query_shadow_who()->do_die(killer);
    
    if (ob = present(MEDALLION_ID, query_shadow_who()))
    {
        tell_object(query_shadow_who(), "You clutch your medallion as " +
            "you take your last breath.\n");
        tell_room(environment(query_shadow_who()),
            QCTNAME(query_shadow_who()) + " clutches " +
            HIS(query_shadow_who()) + " " + LANG_SHORT(ob) + ", a pale " +
            "expression on " + HIS(query_shadow_who()) + " face.\n",
            query_shadow_who());
        filter(users() - ({ query_shadow_who() }),
            filter_death)->catch_tell("Your medallion twitches suddenly. A " +
            "feeling of loss enters your mind briefly.\n");
    }
    
    adjust_standing(RND_RANGE(-250, 50));
  
    return query_shadow_who()->do_die(killer);
}        

public void
enter_inv(object ob, object from)
{
    if (function_exists("create_object", ob) == POISON_OBJECT)
        adjust_standing(RND_RANGE(-60, 20));

    query_shadow_who()->enter_inv(ob, from);
}

public void
run_away()
{
    adjust_standing(RND_RANGE(-70, 20));
    
    query_shadow_who()->run_away();
}

public void
notify_you_killed_me(object victim)
{
    object *obj,gem;
    int i;

    obj = shadow_who->query_tool(-1);
    for (i=0; i<sizeof(obj); i++)
    {
    	if (obj[i]->id("_ansalon_soul_gem"))
    	    gem = obj[i];
    }

    if (gem && (E(victim) == E(shadow_who)) && gem->trap_soul(victim))
    {
        shadow_who->catch_msg("You hear a disembodied scream of rage and " +
        "pain as you trap " + victim->query_the_name(shadow_who) +
        "'s soul in your " + gem->short() + ".\n");

        tell_room(E(victim), "You hear a disembodied scream of rage and " +
        "pain.\n", ({ victim, shadow_who }));
    }

    if (victim->query_guild_name_occ() == "Solamnian Knights")
        adjust_standing(RND_RANGE(victim->query_average_stat() / 4, 5));
    else if (victim->query_average_stat() >
        query_shadow_who()->query_average_stat())
    {
        if (victim->query_alignment() >= ALIGN_NEUTRAL)
            adjust_standing(RND_RANGE(victim->query_alignment() / 100, 5));
        else
            adjust_standing(RND_RANGE(-(victim->query_alignment()) / 120, 2));
    }

    shadow_who->notify_you_killed_me(victim);
}

#ifdef AUTO_MOVE_BEHIND
int
auto_mb_formula(object attacker)
{
    int tmp, rnd;

#ifdef 0
    if (query_shadow_who()->resolve_task(TASK_DIFFICULT + 100,
        ({TS_DIS, SS_AWARENESS, TS_OCC})) > 0 && random(100) < 20)
        return 1;
#else
    tmp = query_shadow_who()->resolve_task(TASK_DIFFICULT + 100,
        ({TS_DIS, SS_AWARENESS, TS_OCC}));
    rnd = random(100);
    
    GUILD_ADMIN->log(query_shadow_who(), "mb", attacker->query_real_name() +
        "(" + file_name(attacker) + "): formula: " + tmp + ", rnd: " + rnd);

    if (tmp > 0 && rnd < 66)
       return 1;
#endif
    
    return 0;
}

int
query_battlemovements()
{
    return gBattlemovements;
}

void
set_battlemovements(int state)
{
    gBattlemovements = !(!state);
}

/* Klockrent namn: Battlemovements!!!!!!!!!!!!!!!11
 */

public void
attacked_by(object ob)
{
    object *team, *enemies, defender;
    int x, flag = 0;
    string msg,omsg,dmsg;

    find_player("stralle")->catch_tell("#mb# me: " + query_shadow_who()->query_name() + ", enemy: " + ob->query_name() + "\n");

    if (!query_battlemovements())
    {
        find_player("stralle")->catch_tell("#mb# Bailed out due to pl have turned it off\n");
        return query_shadow_who()->attacked_by(ob);
    }

    /* gAttackers = ([ attacker : time ])
     */
    if (((x = member_array(ob, m_indices(gAttackers))) >= 0) &&
        gAttackers[x] < time())
        flag = 1;

    /* If formula returns false we fail.
     * However, if we have previously succeeded within the
     * timeframe (flag is set), we succeed
     */
    if (!flag && !auto_mb_formula(ob))
    {
        find_player("stralle")->catch_tell("#mb# Bailed out due to formula failed\n");
        return query_shadow_who()->attacked_by(ob);
    }
    
    /* If we are not in team, we cannot move behind
     */
    team = query_shadow_who()->query_team_others();
#ifdef 0
    if (!sizeof(team) && objectp(query_shadow_who()->query_leader()))
        team = (query_shadow_who()->query_leader())->query_team() +
            ({ query_shadow_who()->query_leader() });
    else if (!team)
#else
    if (!team)
#endif
    {
        find_player("stralle")->catch_tell("#mb# Bailed out due to not in team\n");
        return query_shadow_who()->attacked_by(ob);
    }

    find_player("stralle")->catch_tell("#mb# team: " + implode(map(team->query_real_name(), capitalize), " ") +
        ", team_others: " + implode(map((query_shadow_who()->query_team_others())->query_real_name(), capitalize), " ") + "\n");

//    GUILD_ADMIN->log(query_shadow_who(), "mb", "team: " + 
//       implode(map(team->query_real_name(), capitalize), " "));

    for (x = 0 ; x < sizeof(team) ; x++)
    {
        /* Exclude everyone not within the Dragomary from the team var
         */
        if (!team[x]->query_guild_member("Dragonarmy"))
        {
            team = exclude_array(team, x, x);
            x--;
        }
    }
    
    find_player("stralle")->catch_tell("#mb# team: " + implode(map(team->query_real_name(), capitalize), " ") +
        ", team_others: " + implode(map((query_shadow_who()->query_team_others())->query_real_name(), capitalize), " ") + "\n");
//    GUILD_ADMIN->log(query_shadow_who(), "mb", "team: " + 
//       implode(map(team->query_real_name(), capitalize), " "));


    /* If when excluding the team var has no contents, ie we are not
     * teaming with any Dragonarmy members, we cannot move behind
     */
    if (!sizeof(team))
    {
        find_player("stralle")->catch_tell("#mb# Bailed out due to no da's in team\n");
        return query_shadow_who()->attacked_by(ob);
    }

    /* If we are lead by another, the leader becomes our tank
     * Otherwise, a random teammember becomes the tank
     */
    if (query_shadow_who()->query_leader())
        defender = query_shadow_who()->query_leader();
    else
        defender = team[random(sizeof(team))];

    /* Naturally our defender must be in the same room
     */
    while (environment(defender) != environment(query_shadow_who()))
    {
        team -= ({ defender });
        if (sizeof(team))
            defender = team[random(sizeof(team))];
        else
        {
            find_player("stralle")->catch_tell("#mb# Failed due to no teammembers in the same room\n");
            return query_shadow_who()->attacked_by(ob);
        }
    }

    GUILD_ADMIN->log(query_shadow_who(), "mb", "team: " +
        implode(map(team->query_real_name(), capitalize), " ") +
        ", defender: " + capitalize(defender->query_real_name()));

    find_player("stralle")->catch_tell("#mb# Succeeded, defender: " + capitalize(defender->query_real_name()) + "\n");
        
    /* Remove this when this works
     */
//    return query_shadow_who()->attacked_by(ob);

    switch (random(2))
    {
        case 0:
            msg = "You snap a quick order to " + QTNAME(defender) +
                " to aid you against your enemy.\n";
            omsg = QCTNAME(query_shadow_who()) + " snaps a quick " +
                "order to " + QTNAME(defender) + " to aid " +
                HIM(query_shadow_who()) + " against " +
                HIS(query_shadow_who()) + " enemy.\n";
            dmsg = QCTNAME(query_shadow_who()) + " snaps a quick " +
                "order to you to aid " + HIM(query_shadow_who()) +
                " against " + HIS(query_shadow_who()) + " enemy.\n";
            break;
        case 1:
            msg = "You strategically position yourself so that " +
                QTNAME(defender) + " stand between you and your " +
                "enemy.\n";
            omsg = QCTNAME(query_shadow_who()) + " strategically " +
                "positions " + HIM(query_shadow_who()) + "self " +
                "between " + QTNAME(query_shadow_who()) + " and " +
                HIS(query_shadow_who()) + " enemy.\n";
            dmsg = QCTNAME(query_shadow_who()) + " strategically " +
                "positions " + HIM(query_shadow_who()) + "self " +
                "between you and " + HIS(query_shadow_who()) +
                " enemy.\n";
            break;
    }

    query_shadow_who()->catch_msg(msg);
    tell_room(environment(query_shadow_who()), omsg,
        ({ query_shadow_who(), defender }));
    defender->catch_msg(dmsg);

    /* Make the attacker, attack our defender instead and have the
     * defender attack the attacker
     */
    ob->stop_fight(defender);
    ob->attack_object(defender);
//    defender->attack_object(ob);

    defender->catch_msg("You attack " + QTNAME(ob) + ".\n");
    ob->catch_msg(QCTNAME(defender) + " attacks you!\n");

    /* If we have remembered more than 8 previous attackers, do
     * fifo on the list
     */
    if (m_sizeof(gAttackers) >= 8)
        gAttackers = m_delete(gAttackers, m_indices(gAttackers)[0]);
    
    /* Make any further attempts to attack us by attacker fruitless
     * within a certain timeframe, as to not have the attacker spam
     * the kill command in order to rely on statistics to break
     * the move behind
     */
    if (!gAttackers)
      gAttackers = ([]);
      
    gAttackers += ([ ob : time() + random(60) + 120 ]);

    return query_shadow_who()->attacked_by(ob);
}
#endif
