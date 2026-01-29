/* 
 * Krynn's Wizards of High Sorcery shadow. It is based off Petros'
 * Academic code.  Arman, March 2016
 */

#pragma save_binary

inherit "/std/guild/guild_occ_sh";

#include <ss_types.h>
#include <macros.h>
#include <composite.h>
#include "/d/Krynn/common/defs.h"
#include "../defs.h"

// Defines
#define MANA_SHADOW     "/d/Genesis/specials/guilds/shadows/mana_shadow"
#define SOHM_MANAGER     (WOHS_LIBS + "sohm_manager")
#define GUILD_SUBLOC     WOHS_GUILD_NAME + " subloc"
#define LEADER_LOG ("/d/Krynn/guilds/wohs/logs/wohs_conclave")
#define EXP_LOG "/d/Krynn/guilds/wohs/logs/wohs_xp_gain"

#ifndef WOHS_STELLAR_ALIGNMENT
#define WOHS_STELLAR_ALIGNMENT   ("_wohs_stellar_alignment_spell_prop")
#endif

#include "/d/Genesis/specials/debugger/debugger_tell.h"
#include "/d/Krynn/guilds/sohm/remove_all_spells.h"

// Prototypes
public void     initialize_wohs();
public object   query_top_shadow();

int last_exp_check;

void remove_occ_member();
string robe_colour;

static string *wohs_white_titles = ({"Lesser White Wizard",
    "Wizard of the Ninth White Circle",
    "Wizard of the Eighth White Circle",
    "Wizard of the Seventh White Circle",
    "Wizard of the Sixth White Circle",
    "Wizard of the Fifth White Circle",
    "Wizard of the Fourth White Circle",
    "Wizard of the Third White Circle",
    "Wizard of the Second White Circle",
    "Wizard of the First White Circle",
    "Greater Wizard of the White Order of High Sorcery",
    "High Wizard of the White Order of High Sorcery",
    "Archwizard of the White Order of High Sorcery",});

static string *wohs_red_titles = ({"Lesser Red Wizard",
    "Wizard of the Ninth Red Circle",
    "Wizard of the Eighth Red Circle",
    "Wizard of the Seventh Red Circle",
    "Wizard of the Sixth Red Circle",
    "Wizard of the Fifth Red Circle",
    "Wizard of the Fourth Red Circle",
    "Wizard of the Third Red Circle",
    "Wizard of the Second Red Circle",
    "Wizard of the First Red Circle",
    "Greater Wizard of the Red Order of High Sorcery",
    "High Wizard of the Red Order of High Sorcery",
    "Archwizard of the Red Order of High Sorcery",});

static string *wohs_black_titles = ({"Lesser Black Wizard",
    "Wizard of the Ninth Black Circle",
    "Wizard of the Eighth Black Circle",
    "Wizard of the Seventh Black Circle",
    "Wizard of the Sixth Black Circle",
    "Wizard of the Fifth Black Circle",
    "Wizard of the Fourth Black Circle",
    "Wizard of the Third Black Circle",
    "Wizard of the Second Black Circle",
    "Wizard of the First Black Circle",
    "Greater Wizard of the Black Order of High Sorcery",
    "High Wizard of the Black Order of High Sorcery",
    "Archwizard of the Black Order of High Sorcery",});

static string *wohs_hunter_titles = ({"",
    ", Renegade Hunter",
    ", Renegade Hunter",
    ", Renegade Hunter",
    ", Acclaimed Renegade Hunter",
    ", Acclaimed Renegade Hunter",
    ", Acclaimed Renegade Hunter",
    ", Acclaimed Renegade Hunter",
    ", Renowned Renegade Hunter",
    ", Renowned Renegade Hunter",
    ", Renowned Renegade Hunter",
    ", Renowned Renegade Hunter",
    ", Illustrious Renegade Hunter",
    ", Illustrious Renegade Hunter",
    ", Illustrious Renegade Hunter",
    ", Illustrious Renegade Hunter",
    ", Master Renegade Hunter",});

public string 
query_guild_style_occ() 
{ 
    return WOHS_GUILD_STYLE; 
}

public string 
query_guild_name_occ() 
{ 
    return WOHS_GUILD_NAME; 
}

public int
query_guild_level_occ()
{
    // 37 million guild exp or 240 guild stat for top level
    return WOHS_GUILD_LEVEL(query_shadow_who());
}

int
query_hunter_level_occ()
{
    int hunter_stat = WOHS_MANAGER->query_renegade_wohs_hunter(query_shadow_who());

    return MIN(16, hunter_stat);
}

int 
query_guild_tax_occ() 
{ 
    return GUILD_TAX_WOHS; 
}

void
init_occ_shadow(string str)
{
    ::init_occ_shadow(); 

    set_alarm(1.0, 0.0, initialize_wohs);
    set_alarm(3.0, 0.0, &query_guild_keep_player(shadow_who));
}

void
set_last_exp_check()
{
    last_exp_check = shadow_who->query_exp_combat();
    SOHM_MANAGER->set_wohs_xp_last_checked(shadow_who, last_exp_check);
}

/*
 * Check whether a team member is using the Stellar Alignment spell.
 *
 */

float
check_team_stellar_alignment(object actor)
{
    float alt_moon = 0.0;

    object *team = actor->query_team_others() & 
        all_inventory(environment(actor)) + ({ actor });

    foreach(object teammember: team)
    {
        if(teammember->query_prop(WOHS_STELLAR_ALIGNMENT))
        {
            // DEBUG("Stellar Alignment xp check.");

            string moon_phase = SOHM_MANAGER->query_wohs_moon_phase_aid(teammember);
            float moon_mod;

            // Moon phase affects the gaining of guild experience
            if(moon_phase == "night of the eye")
                moon_mod = 0.10;
            else if(moon_phase == "maximum")
                moon_mod = 0.06;
            else if(moon_phase == "partial")
                moon_mod = 0.03;
            else if(moon_phase == "none")
                moon_mod = 0.01;
            else
                moon_mod = 0.00;

            if(moon_mod > alt_moon)
                alt_moon = moon_mod;
        }
    }

    return alt_moon;
}

/* update_wohs_guild_experience() checks combat experience gained since 
 * last check and adds experience to the guild stat skill.
 */

public void
update_wohs_guild_experience()
{
    if(last_exp_check == 0)
    {
        // DEBUG("Last xp check called as zero.\n");
    }

    int current_exp = shadow_who->query_exp_combat();
    int wohs_avg_stat = shadow_who->query_average_stat();

    if(last_exp_check > current_exp)
    {
        last_exp_check = current_exp;
        SOHM_MANAGER->set_wohs_xp_last_checked(shadow_who, last_exp_check);
    }

    if(current_exp == last_exp_check)
        return;

    int gained_exp = current_exp - last_exp_check;
    float brute_factor = (1.0 - shadow_who->query_brute_factor());

    string moon_phase = SOHM_MANAGER->query_wohs_moon_phase_aid(shadow_who);
    string robe_colour = SOHM_MANAGER->query_wohs_order_colour(shadow_who);

    float moon_mod, robe_mod, race_mod;

    // gained experience converted to pre-brute xp. 38% considered 
    // guild stat xp                   
    int wohs_raw_exp = ftoi((itof(gained_exp) / brute_factor) * 0.38);

    // modifier to be changed dependent on moon phase, robe colour, 
    // and race.
   
    // Moon phase affects the gaining of guild experience
    if(moon_phase == "night of the eye")
        moon_mod = 0.10;
    else if(moon_phase == "maximum")
        moon_mod = 0.06;
    else if(moon_phase == "partial")
        moon_mod = 0.03;
    else if(moon_phase == "none")
        moon_mod = 0.01;
    else
        moon_mod = 0.00;

    // Check if team member with Stellar Alignment spell active has a
    // better moon phase.

    float alt_moon_mod = check_team_stellar_alignment(shadow_who);

    if(alt_moon_mod > moon_mod)
        moon_mod = alt_moon_mod;

    // Being a fence-sitting Order, the Red Robes progress slower than 
    // White or Black.
    if(robe_colour == "red")
        robe_mod = 0.0;
    else
        robe_mod = 0.02;

    // Humans gain a bonus to their advancement.
    if(shadow_who->query_race_name() == "human")
        race_mod = 0.02;
    else
        race_mod = 0.0;

    // The experience allocated to the WoHS guild stat is a fraction of the 
    // guild experience gained:   Base 7%, plus 0-10% moon modifier, plus 
    // 0-2% robe modifier, plus 0-2% race modifier for a maximum xp gain
    // of between 7% and 21%, the equivalent of progressing between 
    // extremely violent and slightly violent.

    int wohs_lvl_exp = ftoi(itof(wohs_raw_exp) * (0.07 + moon_mod + 
        robe_mod + race_mod));

    // Due to the nature of how experience is modified depending on 
    // stat average, guild experience is altered accordingly.

    if(wohs_lvl_exp > wohs_avg_stat)
        wohs_lvl_exp = wohs_lvl_exp * (4 * wohs_avg_stat) / 1000;

    // Testing shows some extreme values of xp gain at low levels, so
    // adding a cap in place, with some allowances for moon cycles.
    if((wohs_lvl_exp > (10 * wohs_avg_stat)) && 
       (moon_phase == "night of the eye"))
    {
       wohs_lvl_exp = (10 * wohs_avg_stat);
    }
    else if((wohs_lvl_exp > (7 * wohs_avg_stat)) && 
            (moon_phase == "maximum"))
    {
       wohs_lvl_exp = (7 * wohs_avg_stat);
    }
    else if((wohs_lvl_exp > (6 * wohs_avg_stat)) && 
            (moon_phase == "partial"))
    {
       wohs_lvl_exp = (6 * wohs_avg_stat);
    }
    else if((wohs_lvl_exp > (4 * wohs_avg_stat)) && 
            (moon_phase == "partial_penalty"))
    {
       wohs_lvl_exp = (4 * wohs_avg_stat);
    }
    else if((wohs_lvl_exp > (3 * wohs_avg_stat)) && 
            (moon_phase == "penalty"))
    {
       wohs_lvl_exp = (3 * wohs_avg_stat);
    }
    else if(wohs_lvl_exp > (5 * wohs_avg_stat))
    {
       wohs_lvl_exp = (5 * wohs_avg_stat);
    }

    // Reduce the total experience gain by 40% to slow down levelling
    wohs_lvl_exp = wohs_lvl_exp * 60 / 100;

    send_debug_message("wohs", capitalize(shadow_who->query_real_name())
        + " gained " +wohs_lvl_exp+ " wohs xp. Robe: " + robe_colour+
        ", moon phase: " +moon_phase+ ", race:  "+
        shadow_who->query_race_name()+ ". Raw xp: " + wohs_raw_exp+ 
        ".", (EXP_LOG + "_" + shadow_who->query_real_name()));

     if (wohs_lvl_exp > 0)
     {
         int guild_stat = shadow_who->query_skill(WOHS_GUILD_STAT);

         /* Add the experience to the guild skill stat */
         shadow_who->set_skill(WOHS_GUILD_STAT, guild_stat + wohs_lvl_exp);
     }

     // Make sure after experience is added the last_exp_check is reset.
     if (wohs_lvl_exp > 0)
     {
         last_exp_check = current_exp;  
         SOHM_MANAGER->set_wohs_xp_last_checked(shadow_who, last_exp_check);
     }
}

void
council_vote_initiated()
{
    shadow_who->catch_msg("You receive a magical message:         \n \n"+   
        "     _____________________________________________________ \n"+
        "    / \\                                                   \\ \n"+
        "   /___|                                                   | \n"+
        "   |\\_/___________________________________________________/ \n"+
        "    \\                                                     \\ \n"+
        "     \\                                                     \\ \n"+
        "      |   A vote has commenced for the position of the      | \n"+
        "      |   Master of your Order. To participate in the       | \n"+
        "      |   vote make your way to the Conclave lobby on       | \n"+
        "      |   the eighth floor, where you may cast your         | \n"+
        "      |   ballot for the Wizard you feel should lead        | \n"+
        "      |   your Order.                                       | \n"+
        "      |                                                     | \n"+
        "      |   - The Conclave of the Wizards of High Sorcery     | \n"+
        "      |                                                     | \n"+
        "     /                                                     / \n"+
        "    /_____________________________________________________/_ \n"+
        "   |/\\                                                      \\ \n"+
        "   \\\\_|                                                      | \n"+
        "    \\/______________________________________________________/ \n\n\n");

     return;
}


public void
initialize_wohs()
{
    setuid();
    seteuid(getuid());
    
    // Make sure the command soul gets added
    shadow_who->add_cmdsoul(WOHS_SOUL);
    shadow_who->add_cmdsoul(SOHM_DIR + "souls/common_spell_soul");
    shadow_who->add_cmdsoul(SPELL_MANAGER_SOUL);

    shadow_who->update_hooks();
    
    // Every caster guild using the new Genesis magic system will
    // use the mana shadow to get the new regeneration rates for mana.
    if (!query_top_shadow()->has_mana_shadow())
    {
        clone_object(MANA_SHADOW)->shadow_me(shadow_who);
    }

    if (SOHM_MANAGER->query_renegade_wohs(shadow_who))    
        shadow_who->catch_tell("\nWare the realms, Renegade of High " +
            "Sorcery!\n\n");
    else
        shadow_who->catch_tell("\nWelcome to the realms, Wizard of " +
            "High Sorcery.\n\n");
    
    // Clone the guild object
    if (!present("sohm_guild_object", shadow_who))
    {
        clone_object(WOHS_GUILD_OBJECT)->move(shadow_who, 1);
    }

    if (!present("wohs_robe_object", shadow_who))
    {
        clone_object(WOHS_ROBE)->move(shadow_who, 1);
        shadow_who->command("$wear wohs_robe_object");
        shadow_who->command("$wear hood");
    }

    if (SOHM_MANAGER->query_renegade_wohs(shadow_who))
    {
       if (shadow_who->query_default_start_location() == (WOHS_STARTROOM))
       {
           shadow_who->set_default_start_location(shadow_who->query_def_start());
           shadow_who->catch_tell("You have been expelled from the " +
               "Tower of Wayreth!\n");
       }
    }

    set_alarm(1.0, 0.0, set_last_exp_check);

    if(QUERY_WHITE_COUNCIL(shadow_who))
       SOHM_MANAGER->add_council_last_login("white");
    if(QUERY_RED_COUNCIL(shadow_who))
       SOHM_MANAGER->add_council_last_login("red");
    if(QUERY_BLACK_COUNCIL(shadow_who))
       SOHM_MANAGER->add_council_last_login("black");

    string vote_order = SOHM_MANAGER->query_wohs_order_colour(shadow_who);

    //DEBUG("Order check: " +vote_order+ ".");

    if(SOHM_MANAGER->query_council_voting_open(vote_order))
    {
        // DEBUG("Council vote open");
        set_alarm(4.0, 0.0, council_vote_initiated);
    }

    /* add the guild subloc */
    shadow_who->add_subloc(GUILD_SUBLOC, this_object());

    // notify_arrival(shadow_who); 
}

public void
remove_shadow()
{
    // We use the removal of the shadow as a way to ensure that the
    // spells for the command soul are removed.
    WOHS_SOUL->remove_spells(shadow_who);
    (SOHM_DIR + "souls/common_spell_soul")->remove_spells(shadow_who);
    
    // We also need to remove the mana shadow. This removal assumes
    // that the person can only have one caster guild shadow.
    query_top_shadow()->remove_mana_shadow();
        
    ::remove_shadow();    
}

int
query_cantrip_spells_max()
{
    if(query_guild_level_occ() > 11)
        return 14;
    if(query_guild_level_occ() > 10)
        return 10;
    else if(query_guild_level_occ() > 8)
        return 9;
    else if(query_guild_level_occ() > 7)
        return 8;
    else if(query_guild_level_occ() > 5)
        return 7;
    else if(query_guild_level_occ() > 4)
        return 6;
    else if(query_guild_level_occ() > 1)
        return 5;
    else
        return 4;
}

int
query_minor_spells_max()
{
    if(query_guild_level_occ() > 9)
        return 6;
    else if(query_guild_level_occ() > 5)
        return 5;
    else
        return 4;
}

int
query_lesser_spells_max()
{
    if(query_guild_level_occ() > 2)
        return 3;
    else
        return 2;
}

int
query_greater_spells_max()
{
    if(query_guild_level_occ() > 6)
        return 2;
    else
        return 1;
}

int
query_advanced_spells_max()
{
    if(query_guild_level_occ() > 11)
        return 2;
    else if(query_guild_level_occ() > 0)
        return 1;
    else
        return 0;
}

public int
query_wohs_alignment_penalty()
{
    robe_colour = SOHM_MANAGER->query_wohs_order_colour(shadow_who);

    // White robes that drop below 'trustworthy' get penalised
    if((robe_colour == "white") && (shadow_who->query_alignment() < 190))
        return 1;

    // Black robes that drop below 'unsympathetic' get penalised
    if((robe_colour == "black") && (shadow_who->query_alignment() > -240))
        return 1;

    // Red robes that become 'holy' or 'damned' get penalised
    if((robe_colour == "red") && ((shadow_who->query_alignment() < -929) || 
        (shadow_who->query_alignment() > 909)))
        return 1;

    return 0;
}


public string 
query_guild_title_occ() 
{
    robe_colour = SOHM_MANAGER->query_wohs_order_colour(shadow_who);

    if(SOHM_MANAGER->query_renegade_wohs(shadow_who))
    {
      switch(robe_colour)
      {
        case "white":
          return "Renegade " + wohs_white_titles[query_guild_level_occ()] 
                +", Exile of the Tower of Wayreth";
        case "red":
          return "Renegade " + wohs_red_titles[query_guild_level_occ()]
                +", Exile of the Tower of Wayreth";
        case "black":
          return "Renegade " + wohs_black_titles[query_guild_level_occ()]
                +", Exile of the Tower of Wayreth";
        default:
          return "Renegade Wizard of High Sorcery, Exile of the Tower "
                +"of Wayreth";
     }
    }

   if(query_wohs_alignment_penalty())
   {
      switch(query_guild_level_occ())
      {
        case 0:
          return "Lesser Grey Wizard";
          break;
        case 1..9:
          return "Grey Wizard";
          break;
        default:
          return "Grey High Wizard";
          break;
      }
   }

   string wohs_name = shadow_who->query_real_name();
   string wohs_gender;
   string robe_title;

   if(shadow_who->query_gender() == 1)
     wohs_gender = "Mistress";
   else
     wohs_gender = "Master";

/*
   if (SOHM_MANAGER->query_alt_wohs_title(shadow_who))
   {

       if (SOHM_MANAGER->query_is_council_white() == wohs_name)
          return wohs_gender + " of the Order of the White Robes"
             + wohs_hunter_titles[query_hunter_level_occ()];
       if (SOHM_MANAGER->query_is_council_red() == wohs_name)
          return wohs_gender + " of the Order of the Red Robes"
             + wohs_hunter_titles[query_hunter_level_occ()];
       if (SOHM_MANAGER->query_is_council_black() == wohs_name)
          return wohs_gender + " of the Order of the Black Robes"
             + wohs_hunter_titles[query_hunter_level_occ()];

   }
   else
   {
*/

       if (SOHM_MANAGER->query_is_council_white() == wohs_name)
          return wohs_gender + " of the White Order of High Sorcery"
             + wohs_hunter_titles[query_hunter_level_occ()];
       if (SOHM_MANAGER->query_is_council_red() == wohs_name)
          return wohs_gender + " of the Red Order of High Sorcery"
             + wohs_hunter_titles[query_hunter_level_occ()];
       if (SOHM_MANAGER->query_is_council_black() == wohs_name)
          return wohs_gender + " of the Black Order of High Sorcery"
             + wohs_hunter_titles[query_hunter_level_occ()];

//   }

   switch(robe_colour)
   {
     case "white":
       return wohs_white_titles[query_guild_level_occ()]
         + wohs_hunter_titles[query_hunter_level_occ()];
     case "red":
       return wohs_red_titles[query_guild_level_occ()]
         + wohs_hunter_titles[query_hunter_level_occ()];
     case "black":
       return wohs_black_titles[query_guild_level_occ()]
         + wohs_hunter_titles[query_hunter_level_occ()];
     default:
       return "Wizard of High Sorcery";
  }
} 

mixed
query_guild_trainer_occ()
{
    return ({ "/d/Krynn/wayreth/tower/mage_skills",
              "/d/Krynn/wayreth/tower/norm_skills",
              "/d/Krynn/wayreth/tower/laboratory",
              "/d/Krynn/wayreth/tower/yard04",
           });
}

/*
 * Function name: acceptable_wohs_member
 * Description:   test to see if the player is an acceptable member of this
 *                guild.
 * Arguments:     object who - the player to test
 * Returns:       0 or a string message saying why the player isn't acceptable
 */
mixed
acceptable_wohs_member(object who)
{
    string race_name = who->query_race_name();

    if(IN_ARRAY(race_name, WOHS_INELIGIBLE_RACES))
    {
        send_debug_message("wohs", capitalize(who->query_real_name())
            + " has been expelled from the Wizards of High Sorcery due " +
            "to changing to in inappropriate race (" +race_name+ ").", 
            LEADER_LOG);

        return "Your spellbook starts smouldering and then suddenly " +
          "burns into ashes. A " +race_name+ " cannot be a Wizard " +
          "of High Sorcery.\n";
    }
    return 0;
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

    // player->catch_tell("DEBUG: query guild keep queried.\n");
    
    if (!result)
    {
        // Even the base shadow doesn't want to keep this player. Just return.
        return 0;
    }
    
    setuid();
    seteuid(getuid());
    // If the person's data file indicates that they are not a member,
    // we don't want to keep this player.
    if (!WOHS_MANAGER->query_is_member(player))
    {
        return 0;
    }

    mixed why;

    if (stringp(why = acceptable_wohs_member(player)))
    {
        player->catch_msg(why);

        set_alarm(1.0, 0.0, remove_occ_member);
        return 1;
    }
    
    return 1;
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
        notify_fail("A Wizard of High Sorcery is fully committed to " +
            "their magic, and cannot afford a layman guild.\n");
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
    return WOHS_GUILD_STYLE;
}

/* Function name: query_guild_name_lay
 * Description:   Returns what name of the layman guild we have.
 * Returns:       string - the name
 */
string
query_guild_name_lay()
{
    return WOHS_GUILD_NAME;
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
is_wohs()
{
    return WOHS_IS_MEMBER(shadow_who);
}


/* 
 * Function name: query_guild_skill_name
 * Description:   Give a names for the guild's special skills
 * Arguments:     type - the number of the skill
 * Returns:          0 if no skill of mine, else the string.
 */
mixed
query_guild_skill_name(int type)
{
    if (type == WOHS_GUILD_SKILL)
    {
        return "arcane focus";
    }

    return 0;
}

/*
 * Function name: query_def_post
 * Description:   We change the default post office for our members. 
 * Returns:  The new postoffice
 */

string
query_def_post() 
{ 
   return "/d/Krynn/wayreth/tower/post"; 
}

/*
 * Function name: show_subloc
 * Description:   This function is called each time someone looks at us
 * Arguments:     subloc  - Our subloc
 *		  me      - I
 *		  for_obj - The looker
 * Returns:	  The string the looker shall see
 */
string
show_subloc(string subloc, object me, object for_obj)
{ 
    string str;
    if (subloc != GUILD_SUBLOC)
    {
        return me->show_subloc(subloc, me, for_obj);
    }

    if(!WOHS_MANAGER->query_wohs_test_marking(me) ||
       !WOHS_MANAGER->query_wohs_test_marking_status(me))
    {
	return "";
    }
    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
    {
	return "";
    }
    if (for_obj == me)
    {
        if(WOHS_MANAGER->query_wohs_test_marking(me) == "mark_of_andras")
	   str = "Along your right forearm you have a horrifying black " +
                 "tattoo of an obsessed man that writhes manically - " +
                 "the mark of Andras - a reminder of the ordeals you " +
                 "faced in the Test of High Sorcery.\n";
        else if(WOHS_MANAGER->query_wohs_test_marking(me) == "mark_of_scarring")
	   str = "You have horrific scarring all over your body - a " +
                 "reminder of your ordeals in the Test of High Sorcery.\n";
        else if(WOHS_MANAGER->query_wohs_test_marking(me) == "mark_of_bronzing")
	   str = "Your skin is tinted a metallic bronze - a marking " +
                 "from the magical fires you faced in the Test of High " +
                 "Sorcery.\n";
        else
	   str = "You have the mark of a Wizard of High Sorcery.\n";
    }
    else
    {
        if(WOHS_MANAGER->query_wohs_test_marking(me) == "mark_of_andras")
	   str = capitalize(me->query_pronoun()) + " has a horrifying " +
               "black tattoo of an obsessed man that writhes manically " +
               "on " +HIS(me)+ " right forearm.\n";
        else if(WOHS_MANAGER->query_wohs_test_marking(me) == "mark_of_scarring")
	   str = capitalize(me->query_pronoun()) + " has horrific " +
               "scarring criss-crossing " +HIS(me)+ " body.\n";
        else if(WOHS_MANAGER->query_wohs_test_marking(me) == "mark_of_bronzing")
	   str = capitalize(me->query_pronoun()) + " has skin tinted a " +
               "metallic bronze.\n";
        else
	   str = capitalize(me->query_pronoun()) + " has the mark of a " +
                 "Wizard of High Sorcery.\n";
    } 

    return str;
}

/*
 * Function name: remove_occ_member
 * Description:   remove this member from the guild
 */
void
remove_occ_member()
{
    // Clear guild stat, remove guild learn, and begin skill decay
    shadow_who->clear_guild_stat(SS_OCCUP); 
    shadow_who->setup_skill_decay(); 
    shadow_who->set_guild_pref(SS_OCCUP, 0);

    // Remove all spells from memory and spellbook, 
    // defined in remove_all_spells.h
    remove_all_spells(shadow_who);

    // Reset the start location of the person leaving the guild
    if (shadow_who->query_default_start_location() == (WOHS_STARTROOM))
    {
        shadow_who->set_default_start_location(shadow_who->query_def_start());
    }

    // Remove the command soul
    shadow_who->remove_cmdsoul(WOHS_SOUL);
    shadow_who->remove_cmdsoul(SOHM_DIR + "souls/common_spell_soul");
    shadow_who->update_hooks();

    // Reset the guild stat and skill
    shadow_who->remove_skill(WOHS_GUILD_STAT);
    shadow_who->remove_skill(WOHS_GUILD_SKILL);
    
    // Remove the guild object
    object guild_object = present("wohs_guild_object", shadow_who);
    if (objectp(guild_object))
    {
        guild_object->remove_object();
    }

    object guild_robe = present("wohs_robe_object", shadow_who);
    if (objectp(guild_robe))
    {
        guild_robe->remove_object();
    }
    
    // Update the Guild Manager
    string name = shadow_who->query_real_name();

    WOHS_MANAGER->remove_member(shadow_who);
    WOHS_MANAGER->remove_wohs_members_list(name);

    send_debug_message("wohs", capitalize(shadow_who->query_real_name())
        + " is no longer a Wizard of High Sorcery.", LEADER_LOG);

    shadow_who->remove_guild_occ();

    //shadow_who->catch_msg("DEBUG: Got to end of remove_occ_member\n");

}

public string
customize_guild_spell_effect_messages(object *effects, string message_text)
{
    mixed active_effect_spells = map(all_inventory(this_player()),
        &->query_spell_names()) - ({ 0 });

    if (!sizeof(active_effect_spells)) return 0;
    string *possible_spells = ({ });
    foreach(string *spell : active_effect_spells)
    {
        possible_spells -= spell;
        possible_spells += spell;
    }
    return "\n                     Currently Active Potions \n"
        + "                     ======================== \n\n"
        + break_string("You can cast " + 
          COMPOSITE_WORDS(sort_array(possible_spells)) + ".", 71) + "\n";
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
    int currently_penalised = query_wohs_alignment_penalty();

    shadow_who->set_alignment(a);

    if(!currently_penalised && query_wohs_alignment_penalty())
    {
        tell_object(shadow_who,"You have strayed too far from " +
        "the philosophies of your chosen Order. Until remedied you will " +
        "not benefit from the phases of the moons of magic.\n");

        send_debug_message("wohs", capitalize(shadow_who->query_real_name())
        + " has strayed from their Order's path and is now a Grey Robed " +
          "Wizard.", LEADER_LOG);

        if(QUERY_WHITE_COUNCIL(shadow_who))
        {
            tell_object(shadow_who,"You are no longer Head of your " +
               "Order.\n");
            send_debug_message("wohs", capitalize(shadow_who->query_real_name())
             + " is removed as Head of the Order of the White Robes for " 
             + "straying from the Order's path.", LEADER_LOG);
            WOHS_MANAGER->remove_council_white();
        }
        if(QUERY_RED_COUNCIL(shadow_who))
        {
            tell_object(shadow_who,"You are no longer Head of your "  
             + "Order.\n");
            send_debug_message("wohs", capitalize(shadow_who->query_real_name())
             + " is removed as Head of the Order of the Red Robes for "  
             + "straying from the Order's path.", LEADER_LOG);
            WOHS_MANAGER->remove_council_red();
        }
        if(QUERY_BLACK_COUNCIL(shadow_who))
        {
            tell_object(shadow_who,"You are no longer Head of your "
             + "Order.\n");
            send_debug_message("wohs", capitalize(shadow_who->query_real_name())
             + " is removed as Head of the Order of the Black Robes for " 
             + "straying from the Order's path.", LEADER_LOG);
            WOHS_MANAGER->remove_council_black();
        }

         object guild_robe = present("wohs_robe_object", shadow_who);
         if (objectp(guild_robe))
         {
               tell_object(shadow_who,"Your robe begins to unravel and " +
                   "reform!\n");
               shadow_who->command("$remove hood");
               guild_robe->set_robe_colour("grey");
         }
    }

    if(currently_penalised && !query_wohs_alignment_penalty())
    {
        tell_object(shadow_who,"Your actions once again reflect " +
        "the philosophies of your chosen Order. You will again " +
        "benefit from the phases of the moons of magic.\n");

        send_debug_message("wohs", capitalize(shadow_who->query_real_name())
        + " is no longer a Grey Robed Wizard.", LEADER_LOG);

         object guild_robe = present("wohs_robe_object", shadow_who);
         if (objectp(guild_robe))
         {
               tell_object(shadow_who,"Your robe begins to unravel and " +
                   "reform!\n");
               shadow_who->command("$remove hood");
               guild_robe->set_robe_colour(WOHS_MANAGER->query_wohs_order_colour(shadow_who));
         }
    }
}

void
kick_renegade_from_guild()
{
      WOHS_JOINROOM->leave_guild(query_shadow_who());
}

public void
do_die(object killer)
{
    object ob;
    
    seteuid(getuid());

    if (query_shadow_who()->query_hp() > 0)
        return query_shadow_who()->do_die(killer);
    
    if(SOHM_MANAGER->query_renegade_wohs(query_shadow_who()))
    {
      tell_object(query_shadow_who(), "With your death as a renegade, " +
         "you are expelled from the Wizards of High Sorcery.\n");
        send_debug_message("wohs", capitalize(shadow_who->query_real_name())
        + " has suffered a death as a Renegade, and is expelled from " +
          "the Wizards of High Sorcery.", LEADER_LOG);

      set_alarm(2.0, 0.0, kick_renegade_from_guild);

    }

    return query_shadow_who()->do_die(killer);
} 

public void
notify_you_killed_me(object victim)
{
    // DEBUG("Combat exp: " +query_shadow_who()->query_exp_combat()+ ".");

    if(SOHM_MANAGER->query_renegade_wohs(victim))
    {
      string victim_name = victim->query_real_name();

      tell_object(query_shadow_who(), "In slaying " +capitalize(victim_name)+ 
      " you are recognised by your Order as a Renegade Hunter.\n");
      SOHM_MANAGER->set_renegade_wohs_hunter(shadow_who);
    }     

    send_debug_message("wohs", capitalize(shadow_who->query_real_name())
        + " killed " +victim->short()+ ", av stat: " +victim->query_average_stat()+
        ".", (EXP_LOG + "_" + shadow_who->query_real_name()));
    update_wohs_guild_experience();  

    shadow_who->notify_you_killed_me(victim);
}
