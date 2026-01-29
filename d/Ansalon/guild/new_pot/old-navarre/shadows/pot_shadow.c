/* 
 * Priests of Takhisis Guild Shadow
 *
 * This is the guild shadow for the Priests of Takhisis of Ansalon. This is
 * a clerical occupational and layman guild. Members of this guild serves
 * the evil god Takhisis.
 *
 * Navarre: Spring of 2013, based off the old shadow by Stralle.
 */
#pragma save_binary

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <files.h>
#include "/d/Ansalon/common/defs.h"
#include "../defs.h"

inherit "/std/guild/guild_occ_sh";

// Prototypes
public void     initialize_priest();
public object   query_top_shadow();
public void     notify_arrival(object player);
public void     notify_departure(object player);
public int query_priest_level(int gs = -1);
public string query_priest_title();
static void remove_player_not_kept_helper(object player, string log_msg,
                                          string player_msg);

mixed *gTitles = GUILD_TITLES;

/*
 * This function is called from autoload_shadow and is used to initialize the
 * shadow when it is loaded.
 *
 * @param str A string passed through from the function autoload_shadow, which
 *            contains type, style, and name of the guild.
 */
void
init_occ_shadow(string str)
{
    ::init_occ_shadow(); 

    set_alarm(1.0, 0.0, initialize_priest);
}

/*
 * This function is responsible for setting up the Priest as he wakes up, so
 * that he will have all his commands and spells available as well as the 
 * guild specific object. 
 * It also notifies all priests currently awake of this newest arrival.
 */
public void
initialize_priest()
{
    object medallion;
    object tattoo;
    
    shadow_who->set_guild_pref(SS_OCCUP, TAX_ARRAY[query_priest_level()]);
    
    setuid();
    seteuid(getuid());
    
    if (medallion = clone_object(MEDALLION_OBJ))
    {
        medallion->add_name(MEDALLION_ID);
        if (medallion->move(shadow_who, 1))
        {
            medallion->add_spell_object(shadow_who);
        }
    }

    // Make sure the command soul gets added
    shadow_who->add_cmdsoul(POT_SOUL);
    shadow_who->add_cmdsoul(SPELL_MANAGER_SOUL);

    shadow_who->update_hooks();
    
    // Every caster guild using the new Genesis magic system will
    // use the mana shadow to get the new regeneration rates for mana.
    if (!query_top_shadow()->has_mana_shadow())
    {
        clone_object(MANA_SHADOW)->shadow_me(shadow_who);
    }

    shadow_who->add_subloc("_priest_of_takhisis_", this_object());
    
    object start_room = environment(shadow_who);
    
    // If the function is available to greet the member as they wake up,
    // let them be greeted properly.
    if (start_room &&
        function_exists("servant_greet_member", start_room))
    {
        start_room->servant_greet_member(shadow_who);
    }
    
    shadow_who->command("$wear " + MEDALLION_ID);
    
    if (interactive(shadow_who))
    {
        GUILD_ADMIN->init_priest(shadow_who);
    }
     notify_arrival(shadow_who); 
}

public void
remove_shadow()
{
    // We use the removal of the shadow as a way to ensure that the
    // spells for the command soul are removed.
    POT_SOUL->remove_spells(shadow_who);
    
    // We also need to remove the mana shadow. This removal assumes
    // that the person can only have one caster guild shadow.
    query_top_shadow()->remove_mana_shadow();

    notify_departure(shadow_who);
    
    // Remove the guild soul
    shadow_who->remove_cmdsoul(GUILD_CMDSOUL);
    shadow_who->update_hooks();

    ::remove_shadow();    
}

/*
 * Function name: query_guild_style_occ
 * Description:   What styles is this guild? fighter, magic, cleric or thief.
 *                You should redefine this function to suite you.
 * Returns:       string - holding the style of guild
 */
public string 
query_guild_style_occ() 
{ 
    return GUILD_STYLE; 
}

/*
 * Function name: query_guild_name_occ
 * Description:   Returns the name of the guild this shadow represents.
 * Returns:       The name of the guild
 */
public string 
query_guild_name_occ() 
{ 
    return GUILD_NAME; 
}

/*
 * Function name: query_guild_tax_occ
 * Description:   This function returns the guild tax the priest will pay
 *                based on his current priest level.
 * Returns:       The Tax the player pays.
 */
int 
query_guild_tax_occ() 
{ 
    return TAX_ARRAY[query_priest_level()];
}

/* 
 * Return 1 if they try to join an occupational or layman guild, since
 * the Priests of Takhisis use up both layman and occupational slots. Set up 
 * a notify fail to say why in response to the join action. 
 * 
 * Returns: 0 if allowed to join, 1 if we are not allowed to join.
 */ 
public int
query_guild_not_allow_join_occ(object player, string type, 
                               string style, string name) 
{
    if (type == "occupational")
    {
        notify_fail("You are a member of the Priests of Takhisis " +
                    "and do not dare to devote yourself to anyone other " +
                    "than Takhisis.\n");
        return 1;
    }
    return ::query_guild_not_allow_join_occ(player, type, style, name);
}

/*
 * Function name: query_guild_title_occ
 * Description  : This function should return the occupational title off
 *                the player. 
 * Returns      : string - the title for the player.
 *                The title will be incorporated in the format
 *                "the <race title>, <occ title> and <lay title>"
 *                if the player is a member of all major guild types.
 */
public string 
query_guild_title_occ() 
{
    return query_priest_title();
} 

/*
 * Function name: query_guild_trainer_occ
 * Description:   This function should return the guild trainers for the
 *                guild.
 * Returns:       Return one or more references to the object that define
 *                sk_train_max for the player. The returned refernce can
 *                be a string reference, an object pointer or an array of
 *                those.
 */
public mixed
query_guild_trainer_occ()
{
      return ({
    	NTEMPLE + "lvl2/abbey",         // Terwed
    	NTEMPLE + "dung2/guard",        // Gruzz
    	NTEMPLE + "dung1/workshop",     // Erdin
    	NTEMPLE + "dung1/herbshop",     // Alister
    	});
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
    
    if (member_array(player->query_race_name(), RACES_BLOCK) >= 0)
    {
       string race_block_msg = "You find it hard to concentrate. Faded " +
            "images comes back and forth in your mind, none making " +
            "any sense. Gradually they seem to blend into an apparition. " +
            "A multi-coloured five-headed dragon stares in anger at you. " +
            "A thundering voice speaks: Ye who choose so poorly I shall " +
            "grace with a choice of my own!\n";
            
       string log_msg_race = "expelled due to changing race";
       
       remove_player_not_kept_helper(player, log_msg_race, race_block_msg);
       return 0;
    }
    
    if (GUILD_ADMIN->query_priest_has_punishment(player->query_real_name(),
        P_EXPELLED))
    {
        string expelled_msg = "You find it hard to concentrate. Faded " +
            "images comes back and forth in your mind, none making " +
            "any sense. Gradually they seem to blend into an apparition. " +
            "A multi-coloured five-headed dragon stares in anger at you, " +
            "no matter where you look, no matter if your eyelids are open " +
            "or not - the dragon remains the only image you see. Looking " +
            "down to escape the vision you realise in horror one of its " +
            "claws has reached inside your body. You writhe in agony as " +
            "your very lifesource is drained from you.\n";
    
        string log_msg_expelled = "expelled from query_guild_keep_player";
        
        remove_player_not_kept_helper(player, log_msg_expelled, expelled_msg);
        return 0;
    }
    return 1;
}

/*
 * This is a helper method to the query_guild_keep_player function, to
 * prevent duplicating code. This function writes a message to the log for
 * why the player was kicked out. It also apply the appropriate punishment
 * and moving the player to the default start location for the race, while
 * resetting the start location.
 * 
 * @param player The player that is being kicked out.
 * @param log_msg The message string to write to the admin log file to 
 *                explain why the player was kicked out.
 * @param player_msg The message string to provide to the player when being 
 *                   kicked out.
 */
static void
remove_player_not_kept_helper(object player, string log_msg,
                              string player_msg)
{
    setuid();
    seteuid(getuid());  
    GUILD_ADMIN->log(player, "left", log_msg);
    player->punish_for_leaving(3);
    GUILD_ADMIN->remove_priest(player->query_real_name());
    player->catch_tell(player_msg);
    player->set_default_start_location(RACESTART[player->query_race()]);
    player->move_living("X", player->query_default_start_location());
    player->set_hp(50);
}
/*
 * Function name: query_def_post
 * Description  : We change the default post office for our members.
 * Returns      : string - the path to the new postoffice
 */
string
query_def_post()
{
    // Only bother using the guild's post office if the player is using the
    // guild's start location.
    if (shadow_who->query_default_start_location() == GUILD_START)
    {
        return GUILD_PO;
    }
    return shadow_who->query_def_post();
}

/*
 * Function name: query_guild_leader_occ
 * Description:   For the mailreader to recognize council members to be
 *                allowed to have more mail in the mailbox.
 * Returns:       int - 1/0, member of the council or not.
 */
int
query_guild_leader_occ()
{
    return (member_array(shadow_who->query_real_name(),
            GUILD_ADMIN->query_guild_council()) >= 0);
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

/*
 * This function will have all PoT members return 1 when checked if they are
 * a pot member. This is used to find guild members.
 * Returns 1 for all members and 0 for all non members (as they don't have
 * this function).
 */
public int
query_pot_member()
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

    object* members;
    object* wizards;
    object* audience;
    
    string name = player->query_real_name();

    // Members will notify other clerics upon arrival
    members = filter(users(), &->query_pot_member());
    members -= ({ player }); // don't notify self.
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
    map(audience, &->catch_msg("You sense a stirr of power " 
        + "as " + capitalize(player->query_real_name()) + " awakens.\n"));    
}

public void
notify_departure(object player)
{
    if (!objectp(player) || !IS_PLAYER_OBJECT(player))
    {
        return;
    }
    
    object * audience = get_audience_for_notification(player);
    map(audience, &->catch_msg("You feel more alone as " +
    capitalize(player->query_real_name()) + " departs the realms.\n"));    
}

/*
 * This is a filter function that is used in the do_die function to filter
 * POT members that are at priest level or higher and wearing their 
 * medallion. 
 */ 
int
filter_death(object ob)
{
    if (ob->query_guild_name_occ() == GUILD_NAME &&
        ob->query_priest_level() >= GUILD_LEVEL_PRIEST &&
        present(MEDALLION_ID, ob))
    {
        return 1;
    }
    return 0;
}

/*
 * This function calculates the priest level based on the PS_GUILD_LEVEL
 * skill.
 * Returns 0 for Cleric, 1 for Priest and 2 for High Priest.
 */
varargs public int
query_priest_level(int gs = -1)
{
    // If no specific value is specified we get the value from the skill.
    if (gs < 0)
    {
        gs = shadow_who->query_skill(PS_GUILD_LEVEL);
    }

    // The value is capped at 149.
    if (gs > 149)
    {
        gs = 149;
    }
        
    // Devide into 3 groups, Cleric 0, Priest 1, and High Priest 2.
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
    {
        gs = shadow_who->query_skill(PS_GUILD_LEVEL);
    }
    
    if (gs > 149)
    {
        gs = 149;
    }
    return (gs % 50) / 10; // Between 0 and 4.
}

/*
 * This function figures out what title the specific priest should have.
 * It is based off of the query_priest_level and query_priest_sublevel 
 * functions. It adds a special check to make sure only the leader of the
 * guild can have the highest title.
 */
public string
query_priest_title()
{
    mixed rank,subrank;
    int i;
    string title;
    rank = query_priest_level(); // 0-2 
    subrank = query_priest_sublevel(); // 0-4


    // Make sure that you can only be the NightLady or Nightlord if you are
    // the leader of the guild.
    if (rank == 2 && (subrank == 4) && 
       GUILD_ADMIN->query_guild_leader() != shadow_who->query_real_name())
    {
        subrank = subrank - 2;
    }

    string special_pot_title = shadow_who->query_prop(POT_SPECIAL_TITLE);
    
    if (special_pot_title)
    {
        return special_pot_title;
    }
    
    if (shadow_who->query_gender() == G_FEMALE)
    {
        title = gTitles[rank][subrank * 2 + 1];
    }
    else
    {
        title = gTitles[rank][subrank * 2];
    }

#ifdef COUNCIL_TITLES_IN_PRESENTATION
    i = member_array(shadow_who->query_real_name(), GUILD_ADMIN->query_guild_council());
    if (i >= 0)
    {
    	title = add_subtitle(title, COUNCIL_TITLES[i]);
    }
#endif
    return title + " of Takhisis";
}

/*
 * This is used when the council members wants to add a special title 
 * to reflect a current task they are focusing on, like inquisitor.
 */
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

/*
 * This function builds the appropriate description for the priests current
 * standing in the guild.
 * 
 * @param who The player requesting to know the standing.
 * @param for_obj The player who's standing is requested.
 * @param standing The standing value to get the description for.
 */
varargs string
query_standing_desc(object who, object for_obj,
                    int standing = PS_STANDING_MIN - 1)
{
    string str, desc;

    if (!who)
    {
        who = this_player();
    }
    
    if (standing == PS_STANDING_MIN - 1)
    {
        standing = who->query_skill(PS_STANDING);
    }
    else if (standing < PS_STANDING_MIN)
    {
        standing = PS_STANDING_MIN;
    }
    else if (standing > PS_STANDING_MAX)
    {
        standing = PS_STANDING_MAX;
    }

    if (objectp(for_obj) && for_obj != who)
    {
        str = QCTNAME(who) + " is ";
    }   
    else
    {
        str = "You are ";
    }
    
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
            {
                desc = "the Handmaiden of Takhisis";
            }
            else
            {
                desc = "the Aide-de-camp of Takhisis";
            }
            break;
         default:
             desc = "the bugged priest of Takhisis"; // Should never happen.
    }    
    return str + desc;
}

/*
 * This function returns the current standing for this player.
 * Returns: A number between -1200 and 1200.
 */
int
query_standing()
{
    return shadow_who->query_skill(PS_STANDING);
}

/*
 * This function sets this players standing.
 * 
 * @param standing The number to set the standing to, it will be adjusted to
 *                 be a number between -1200 and 1200.
 */
void
set_standing(int standing)
{
    if (standing < PS_STANDING_MIN)
    {
        standing = PS_STANDING_MIN;
    }
    else if (standing > PS_STANDING_MAX)
    {
        standing = PS_STANDING_MAX;
    }
    shadow_who->set_skill(PS_STANDING, standing);
}

void
adjust_standing(int change)
{
    if (query_standing_desc(shadow_who, 0, 
                            ADJUST_STANDING(query_standing(), change)) !=
        query_standing_desc(shadow_who, 0, query_standing()))
    {
        tell_object(shadow_who, "You feel " +
            (change > 0 ? "more" : "less") + " in touch with Takhisis.\n");
    }

    setuid();
    seteuid(getuid());
    
    if (file_size("/d/Ansalon/log/pot/standing") >= 50000)
    {
        rename("/d/Ansalon/log/pot/standing",
               "/d/Ansalon/log/pot/standing.old");
    }
    write_file("/d/Ansalon/log/pot/standing",
               sprintf("%-13s: %-40s %4d %4d\n",
               capitalize(shadow_who->query_real_name()),
               calling_function(), query_standing(), change));
    
    set_standing(ADJUST_STANDING(query_standing(), change));
}


/*
 * This function takes the spell level and spell success values and 
 * calculates the standing the player should be adjusted with.
 * This function is called from all spells cast.
 *
 * @param spell_level The spell level specified in all POT spells. 
 *                    Harder spells to cast will reward with better standing.
 * @param spell_success If the spell was cast successful the adjustment in
 *                      standing will be positive.
 */
void
adjust_standing_by_spell_level(int spell_level, int spell_success)
{
   int adjustAmount = 0;
   
   if (spell_success > 0)
   {
       adjustAmount = random(8) ? RND_RANGE(spell_level * 3, 10)
                                : RND_RANGE(-10, 10);
   }  
   else
   {
       adjustAmount = RND_RANGE(-5, 5);
   }
   adjust_standing(adjustAmount);
}

/*
 * Function name: remove_occ_member
 * Description:   remove this member from the guild
 */
void
remove_occ_member()
{
    object emblem;
    int i;

    /* Remove special skills */
    for (i = 0; i < sizeof(PS_NUM); i++)
    {
    	shadow_who->remove_skill(PS_NUM[i]);
    }

    /* Clear the player's guild stat */
    shadow_who->clear_guild_stat(SS_OCCUP);

    /* Remove any instances of the guild emblem on the player */
    while (emblem = present(MEDALLION_ID, shadow_who))
    {
        emblem->remove_object();
    }

    /* If the player is using our start location, remove it */
    if (shadow_who->query_default_start_location() == GUILD_START)
    {
        shadow_who->set_default_start_location(shadow_who->query_def_start());
    }
    
    GUILD_ADMIN->remove_priest(shadow_who->query_real_name());
    
    // Get rid of the spell and mana souls.
    shadow_who->remove_shadow();

    /* Remove the guild shadow.  This also resets tax to 0. */
    remove_guild_occ();
}	


/*
 * Function name: query_guild_not_allow_join_lay
 * Description:   Makes sure we cannot join any layman guild.
 */
int
query_guild_not_allow_join_lay(object player, string type, string style,
                               string name)
{
    if (type == "layman")
    {
        notify_fail("Takhisis demands your full attention.\n");
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
    {
        ratio = 3;
    }
    
    trex = shadow_who->query_exp_combat() / ratio;
    shadow_who->add_exp(-trex); // Death Recovery Works on this as well.

    (GUILD_ADMIN)->log(query_shadow_who(), "admin", sprintf("Punished " +
        "for leaving. 1/%d (%d) exp removed by %s.", ratio, trex,
        (interactive(calling_object()) ?
         C(calling_object()->query_real_name()) :
         file_name(calling_object()))));
}

/*
 * This function adds some flavor to the description of the members based of
 * their rank in the guild. 
 * It adds tattoo descriptions to the subloc.
 */
string
show_subloc(string subloc, object on_obj, object for_obj)
{
    string s;

    if (subloc != "_priest_of_takhisis_")
    {
        return shadow_who->show_subloc(subloc,on_obj,for_obj);
    }
        
    if (on_obj->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
    {
        return "";
    }
    
    if (on_obj->query_armour(A_R_HAND))
    {
        return "";
    }

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
    {
        return "You have " + s + " on your right wrist.\n";
    }
    return C(HE(on_obj)) + " has " + s + " on " + HIS(on_obj) +
           " right wrist.\n";
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
        {
            return "malevolently";
        }
    }
    return shadow_who->full_adverb(str);
}

/*
 * Function name :   query_guild_skill_name
 * Description   :   When a players uses the skills command he should get the
 *                   the skill names, not the 'special' string.
 * Arguments     :   type - the number of the skill
 * Returns       :   0 if no skill of mine, else the string.
 */
mixed
query_guild_skill_name(int type)
{
    int i;

    if ((i = member_array(type, PS_NUM)) < 0)
    {
        return 0;
    }
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
    {
        return 0;
    }
    return 1;
}

/*
 * Function name : set_alignment
 * Description   : Sets the alignment of a player, we will check if
 * 	               the alignment is getting out of bounds for a priest
 * Arguments     : a - The amount of points
 */
public void
set_alignment(int a)
{
    if (!has_allowed_priest_alignment() &&
        a <= ALIGN_LIMIT[query_priest_level()])
    {
    	tell_object(shadow_who, "Once more you shelter in the embrace " +
    	"of the Queen of Darkness, and she grants you use of her " +
    	"powers again.\n");
    }
	
    shadow_who->set_alignment(a);

    if (a > ALIGN_LIMIT[query_priest_level()])
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

    // If the player has more than 0 hit points we just let the global
    // code handle it.
    if (shadow_who->query_hp() > 0)
    {
        return shadow_who->do_die(killer);
    }
    
    if (ob = present(MEDALLION_ID, query_shadow_who()))
    {
        tell_object(query_shadow_who(), "You clutch your medallion as " +
                    "you take your last breath.\n");
        tell_room(environment(query_shadow_who()),
            QCTNAME(shadow_who) + " clutches " +
            HIS(shadow_who) + " " + LANG_SHORT(ob) + ", a pale " +
            "expression on " + HIS(shadow_who) + " face.\n",
            shadow_who);
        filter(users() - ({ shadow_who }),
            filter_death)->catch_tell("Your medallion twitches suddenly. A " +
            "feeling of loss enters your mind briefly.\n");
    }
    
    adjust_standing(RND_RANGE(-250, 50));
  
    return shadow_who->do_die(killer);
}        

public void
enter_inv(object ob, object from)
{
    if (function_exists("create_object", ob) == POISON_OBJECT)
    {
        adjust_standing(RND_RANGE(-60, 20));
    }
    shadow_who->enter_inv(ob, from);
}

public void
run_away()
{
    adjust_standing(RND_RANGE(-70, 20));
    
    shadow_who->run_away();
}


public void
notify_you_killed_me(object victim)
{
    object *obj,gem;
    int i;

    obj = shadow_who->query_tool(-1);
    for (i = 0; i < sizeof(obj); i++)
    {
    	if (obj[i]->id("_ansalon_soul_gem"))
        {
    	    gem = obj[i];
        }
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
    {
        adjust_standing(RND_RANGE(victim->query_average_stat() / 4, 5));
    }
    else if (victim->query_average_stat() >
             shadow_who->query_average_stat())
    {
        if (victim->query_alignment() >= ALIGN_NEUTRAL)
        {
            adjust_standing(RND_RANGE(victim->query_alignment() / 100, 5));
        }
        else
        {
            adjust_standing(RND_RANGE(-(victim->query_alignment()) / 120, 2));
        }
    }
    shadow_who->notify_you_killed_me(victim);
}




