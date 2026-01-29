/* 
 * Krynn's School of High Magic shadow. It is based off Petros'
 * Academic code.  Arman, January 2016
 */

#pragma save_binary

inherit "/std/guild/guild_occ_sh";

#include <ss_types.h>
#include <macros.h>
#include <const.h>
#include <composite.h>
#include "../defs.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/guilds/sohm/remove_all_spells.h"

// Defines
#define MANA_SHADOW     "/d/Genesis/specials/guilds/shadows/mana_shadow"
#define LEADER_LOG ("/d/Krynn/guilds/wohs/logs/wohs_conclave")
#define MAX_GUILD_LEVEL 8
#define INITIATE_LEVEL 3
#define NOVITIATE_LEVEL 6

#define LEFT_TEST       "_wohs_test_left_test"

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Prototypes
public void     initialize_sohm();
public object   query_top_shadow();

void remove_occ_member();

static string *apprentice_titles = ({"Fresh Tyro of Sorcery",
  "Minor Student of Sorcery",
  "Student of Sorcery",
  "Lesser Apprentice of Sorcery",
  "Apprentice of Sorcery",
  "Lesser Novitiate of Sorcery",
  "Novitiate of Sorcery",
  "Devoted Novitiate of Sorcery",
  "Experienced Novitiate of Sorcery",});

public string 
query_guild_style_occ() 
{ 
    return GUILD_STYLE; 
}

public string 
query_guild_name_occ() 
{ 
    return GUILD_NAME; 
}

int
query_guild_level_occ()
{
    return MIN(MAX_GUILD_LEVEL, query_shadow_who()->query_stat(SS_OCCUP) / 12);
}

int 
query_guild_tax_occ() 
{
    if(query_guild_level_occ() > NOVITIATE_LEVEL)
      return GUILD_TAX_ASPIRANT;
    else if(query_guild_level_occ() > INITIATE_LEVEL)
      return GUILD_TAX_NOVITIATE;
    else 
      return GUILD_TAX_INITIATE; 
}

void
init_occ_shadow(string str)
{
    ::init_occ_shadow(); 

    set_alarm(1.5, 0.0, initialize_sohm);
    set_alarm(3.0, 0.0, &query_guild_keep_player(shadow_who));
}

void
invite_sohm_to_wohs_test()
{
    shadow_who->catch_msg("You receive a magical message:         \n \n"+   
          "     _____________________________________________________ \n"+
          "    / \\                                                   \\ \n"+
          "   /___|                                                   | \n"+
          "   |\\_/___________________________________________________/ \n"+
          "    \\                                                     \\ \n"+
          "     \\                                                     \\ \n"+
          "      |   The Conclave of the Wizards of High Sorcery       | \n"+
          "      |   invite you to the Hall of Mages in the Tower      | \n"+
          "      |   of Wayreth, for an opportunity to take the        | \n"+
          "      |   Test and join one of the Orders of High Magic.    | \n"+
          "      |                                                     | \n"+
          "      |   If you choose to take the Test, come prepared.    | \n"+
          "      |                                                     | \n"+
          "      |   The Test of High Sorcery isn't to be taken        | \n"+
          "      |   lightly, for death is the penalty for failure!    | \n"+
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

void
left_wohs_test()
{
    // remove mirror portal from spellbook
    if(SOHM_MANAGER->query_scribed_spell(query_shadow_who(),"dotonobsule"))
    {
        int memorised_spells = SOHM_MANAGER->query_cantrips_memorised(query_shadow_who()) - 1;

        SOHM_MANAGER->set_cantrips_memorised(query_shadow_who(), memorised_spells);
        SOHM_MANAGER->unmemorise_spell(query_shadow_who(), "dotonobsule_memorised");
        SOHM_MANAGER->unscribe_spell_from_spellbook(query_shadow_who(), "dotonobsule");
    }

    shadow_who->catch_msg("You receive a magical message:         \n \n"+   
          "     _____________________________________________________ \n"+
          "    / \\                                                   \\ \n"+
          "   /___|                                                   | \n"+
          "   |\\_/___________________________________________________/ \n"+
          "    \\                                                     \\ \n"+
          "     \\                                                     \\ \n"+
          "      |   You have left the Test of High Sorcery through    | \n"+
          "      |   the Void. Return to the Hall of Mages and enter   | \n"+
          "      |   the shadows to continue the Test.                 | \n"+
          "      |                                                     | \n"+
          "      |   However be warned, there will be no further       | \n"+
          "      |   chances. If you are forced in to the Void again,  | \n"+
          "      |   it will result in failure of the Test.            | \n"+
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

void
failed_wohs_test()
{
    DEBUG("Failed Test function called after two quit or linkdeaths.");
    tell_object(query_shadow_who(), "\n\n\n\nYou have failed the Test of High Sorcery. You " +
           "will need to recover and study before you may attempt to re-sit it again.\n\n\n\n");

    SOHM_MANAGER->remove_started_wohs_test();
    SOHM_MANAGER->remove_player_started_wohs_test(query_shadow_who());
    SOHM_MANAGER->remove_invited_wohs_test(query_shadow_who());
    SOHM_MANAGER->remove_wohs_test_props(query_shadow_who());
    SOHM_MANAGER->add_wohs_test_props(query_shadow_who(), "_previously_failed_wohs_test", 1);

    // remove mirror portal from spellbook
    if(SOHM_MANAGER->query_scribed_spell(query_shadow_who(),"dotonobsule"))
    {
        int memorised_spells = SOHM_MANAGER->query_cantrips_memorised(query_shadow_who()) - 1;

        SOHM_MANAGER->set_cantrips_memorised(query_shadow_who(), memorised_spells);
        SOHM_MANAGER->unmemorise_spell(query_shadow_who(), "dotonobsule_memorised");
        SOHM_MANAGER->unscribe_spell_from_spellbook(query_shadow_who(), "dotonobsule");
    }

    // Failing the test drops the aspirant down a level, approximately 400k of
    // guild experience away from being able to sit the Test again.
    query_shadow_who()->set_guild_stat(SS_OCCUP, 1000000); 

    send_debug_message("wohs", capitalize(shadow_who->query_real_name())
        + " has failed the Test of High Sorcery.", LEADER_LOG);
}

void
failed_wohs_test_die_function()
{
    set_alarm(8.0, 0.0, failed_wohs_test);

    object test_room = environment(shadow_who);

    if(shadow_who->query_ghost())
        return;

    tell_object(query_shadow_who(), "\n\n\n\nMagical mists circle around you, strangling you.\n\n\n\n");
    tell_room(environment(query_shadow_who()), "Magical mists circle around " +QTNAME(query_shadow_who())+
                          ", strangling " +HIM(query_shadow_who())+ ".\n", 
                          ({ query_shadow_who() }), query_shadow_who());
    query_shadow_who()->command("$wail");
    query_shadow_who()->set_hp(-10000);
    query_shadow_who()->do_die(test_room);
}

public void
initialize_sohm()
{
    setuid();
    seteuid(getuid());
    
    // Make sure the command soul gets added
    shadow_who->add_cmdsoul(SOHM_SOUL);
    shadow_who->add_cmdsoul(SOHM_SOULS   + "common_spell_soul");
    shadow_who->add_cmdsoul(SPELL_MANAGER_SOUL);

    shadow_who->update_hooks();
    
    // Every caster guild using the new Genesis magic system will
    // use the mana shadow to get the new regeneration rates for mana.
    if (!query_top_shadow()->has_mana_shadow())
    {
        clone_object(MANA_SHADOW)->shadow_me(shadow_who);
    }
    
    shadow_who->catch_tell("\nWelcome, Aspiring Magus of High Magic.\n\n");
    
    // Clone the guild object
    if (!present("sohm_guild_object", shadow_who))
    {
        clone_object(SOHM_GUILD_OBJECT)->move(shadow_who, 1);
    }

    // Message of invite for SoHM members to join WoHS
    if(SOHM_MANAGER->query_invited_wohs_test(shadow_who) &&
       !SOHM_MANAGER->query_aspirant_title(shadow_who) &&
       !shadow_who->query_ghost() &&
       !SOHM_MANAGER->query_player_started_wohs_test(shadow_who))
    {
        set_alarm(4.0, 0.0, invite_sohm_to_wohs_test);
    }

    // Warning for SoHM members who quit or LDd from the Test
    if(SOHM_MANAGER->query_player_started_wohs_test(shadow_who) &&
       (SOHM_MANAGER->query_wohs_test_prop(shadow_who, LEFT_TEST) < 2))
    {
        set_alarm(4.0, 0.0, left_wohs_test);
        SOHM_MANAGER->add_wohs_test_props(shadow_who, LEFT_TEST, 1);
    }

    // Test failure function called when quit or LDd twice out of a Test
    if((SOHM_MANAGER->query_wohs_test_prop(shadow_who, LEFT_TEST) == 2))
    {
        set_alarm(4.0, 0.0, failed_wohs_test_die_function);
    }

    // notify_arrival(shadow_who); 
}

public void
remove_shadow()
{
    // We use the removal of the shadow as a way to ensure that the
    // spells for the command soul are removed.
    SOHM_SOUL->remove_spells(shadow_who);
    (SOHM_SOULS   + "common_spell_soul")->remove_spells(shadow_who);
    
    // We no longer need to remove the mana shadow. 

    // query_top_shadow()->remove_mana_shadow();
        
    ::remove_shadow();    
}


/* query_cantrip_spells_max returns the maximum number of cantrip
 * level spells a SoHM can memorise.
 * First level SoHMs can memorise 2 cantrips; Levels two to four can memorise 
 * 3 cantrips; Beyond level 4 a SoHM can memorise up to 4 cantrips.
 */

int
query_cantrip_spells_max()
{
    if(query_guild_level_occ() > 2)
      return 4;
    else if(query_guild_level_occ() > 0)
      return 3;
    else
      return 2;
}

int
query_minor_spells_max()
{
    if(query_guild_level_occ() > 4)
      return 4;
    else if(query_guild_level_occ() > 3)
      return 3;
    else if (query_guild_level_occ() > 1)
      return 2;
    else
      return 1;
}

int
query_lesser_spells_max()
{
    if(query_guild_level_occ() > 6)
      return 2;
    else if(query_guild_level_occ() > 5)
      return 1;
    else
      return 0;
}

int
query_greater_spells_max()
{
    if(query_guild_level_occ() > 7)
      return 1;
    else
      return 0;
}

int
query_advanced_spells_max()
{
      return 0;
}

public string 
query_guild_title_occ() 
{
    if(query_guild_level_occ() == 8)
    {
     string title = SOHM_MANAGER->query_specialisation_form(shadow_who);
     
     string aspirant_title;
     string location = "of Ansalon";

     if(SOHM_MANAGER->query_alt_layman_title(shadow_who))
     {
      if(SOHM_MANAGER->query_alt_guild_title_occ(shadow_who, "layman"))
        return SOHM_MANAGER->query_alt_guild_title_occ(shadow_who, "layman");            
     }

     if(SOHM_MANAGER->query_alt_race_title(shadow_who))
     {
      if(SOHM_MANAGER->query_alt_guild_title_occ(shadow_who, "race"))
        return SOHM_MANAGER->query_alt_guild_title_occ(shadow_who, "race");
     }

     if(SOHM_MANAGER->query_alt_craft_title(shadow_who))
     {
      if(SOHM_MANAGER->query_alt_guild_title_occ(shadow_who, "craft"))
        return SOHM_MANAGER->query_alt_guild_title_occ(shadow_who, "craft");
     }

     if(SOHM_MANAGER->query_aspirant_title(shadow_who))
        aspirant_title = "";
     else
        aspirant_title = ", Aspirant of High Sorcery";        
     
     switch (title)
     {
       case "transmutation":
         return "Transmuter of Ansalon" + aspirant_title;         
       case "illusion":
         return "Illusionist of Ansalon" + aspirant_title;
       case "divination":
         return "Diviner of Ansalon" + aspirant_title;
       case "enchantment":
          if(shadow_who->query_gender() == 1)
            return "Enchantress of Ansalon" + aspirant_title;
          else            
            return "Enchanter of Ansalon" + aspirant_title;
       case "conjuration":
          if(shadow_who->query_gender() == 1)
            return "Conjuress of Ansalon" + aspirant_title;
          else
            return "Conjurer of Ansalon" + aspirant_title;
       case "abjuration":
         return "Abjurer of Ansalon" + aspirant_title;
       default: 
         return "Experienced Novitiate of Sorcery";
      }
     }
    else return apprentice_titles[query_guild_level_occ()];
} 

mixed
query_guild_trainer_occ()
{
    return ({ SOHM_ROOM + "training",
              SOHM_ROOM + "training_elements",
              "/d/Krynn/solace/poolbottom/room/alchemy_lab",
           });
}

/*
 * Function name: acceptable_sohm_member
 * Description:   test to see if the player is an acceptable member of this
 *                guild.
 * Arguments:     object who - the player to test
 * Returns:       0 or a string message saying why the player isn't acceptable
 */
mixed
acceptable_sohm_member(object who)
{
    string race_name = who->query_race_name();

    // who->catch_tell("DEBUG: acceptable race queried.\n");

    if(IN_ARRAY(race_name, SOHM_INELIGIBLE_RACES))
    {
        //who->catch_tell("DEBUG: You were not an acceptable member " +
        //                "because you are a " +race_name+ ".\n");
        return "Your spellbook starts smouldering and then suddenly burns " +
          "into ashes. You recall the words of Master Theobald telling " +
          "you that a " +race_name+ " cannot " +
          "study at the School of High Magic.\n";
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
    if (!SOHM_MANAGER->query_is_member(player))
    {
        return 0;
    }

    mixed why;

    if (stringp(why = acceptable_sohm_member(player)))
    {
        player->catch_msg(why);
	// query_shadow_who()->catch_tell("DEBUG: You are removed as occ "+
        // "member because you were not an acceptable member.\n");
        set_alarm(1.0, 0.0, remove_occ_member);
        return 1;
    }
    
    return 1;
}

/*
 * Function name: query_guild_not_allow_join_occ
 * Description:  Check if we allow that the player joins another guild. 
 * Arguments:     player - the player
 *  type, style, name - the type, style and name of the
 *intended guild.
 * Returns:  1 if we do not allow, else 0
 */
int
query_guild_not_allow_join_occ(object player, string type, string style,
  string name)
{
    
    if (::query_guild_not_allow_join_occ(player, type, style, name))
        return 1;

    notify_fail("The School of High Sorcery demands the utmost " +
                "loyalty and dedication.\n");

    setuid();
    seteuid(getuid());
    
    if (name == "Orcs of Middle Earth")
    {
        player->catch_msg("The School of High Magic does not accept " +
            "orcs! You will need to burn your spellbook to become an " +
            "orc.\n");            
        return 1;
    }
    
    return 0;
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
is_sohm()
{
    return IS_MEMBER(shadow_who);
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
    if (type == SOHM_GUILD_SKILL)
    {
        return "arcane focus";
    }

    return 0;
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
    // defined in remove_all_spells.h, excluding when they are 
    // promoting up to the WoHS after completing the Test.

   if (!SOHM_MANAGER->query_passed_wohs_test(shadow_who))
      remove_all_spells(shadow_who);

    // Reset the start location of the person leaving the guild
    if (shadow_who->query_default_start_location() == (SOHM_STARTROOM))
    {
        shadow_who->set_default_start_location(shadow_who->query_def_start());
    }

    // Remove the command soul
    shadow_who->remove_cmdsoul(SOHM_SOUL);
    shadow_who->remove_cmdsoul(SOHM_SOULS   + "common_spell_soul");
    shadow_who->update_hooks();
    
    // Remove the guild object
    object guild_object = present("sohm_guild_object", shadow_who);
    if (objectp(guild_object))
    {
        guild_object->remove_object();
    }
    
    // Update the Guild Manager
    SOHM_MANAGER->remove_member(shadow_who);

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
        + break_string("You can cast " + COMPOSITE_WORDS(sort_array(possible_spells)) + ".", 71) +
"\n";
}

public void
do_die(object killer)
{
    object ob;
    
    seteuid(getuid());

    if (query_shadow_who()->query_hp() > 0)
        return query_shadow_who()->do_die(killer);

    if(SOHM_MANAGER->query_player_started_wohs_test(query_shadow_who()))
    {
        failed_wohs_test();
    }    

    return query_shadow_who()->do_die(killer);
} 
