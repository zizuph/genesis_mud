/*
 * Layman Command Soul for the Elemental Clerics of Calia
 *
 * This is the command soul that every Elemental Cleric will
 * have. It includes emotes as well as the abilities/spells that they
 * possess.
 *
 * Created by Jaacar, January 2017
 *
 * 2021-06-29 - Cotillion
 * - Disabled non loading anavo and ilithios
 */

#pragma strict_types

#include <cmdparse.h>
#include <macros.h>
#include <files.h>
#include <ss_types.h>
#include <composite.h>
#include <filter_funs.h>
#include "../defs.h"

inherit "/cmd/std/command_driver";
inherit "/d/Genesis/specials/abilities";
inherit "/d/Genesis/specials/guilds/lib/utility_functions";
inherit "/d/Genesis/specials/components";

#define LIVE_I_EDENO "_live_i_edeno"

/* 
 * Function name: get_soul_id
 * Description:   Give a name for this soul
 * Returns:       string - the soul's id
 */
public string
get_soul_id() 
{ 
    return GUILD_EC_NAME + " Layman Soul"; 
}

/*
 * Function name: query_cmd_soul
 * Description:   identify this as a valid cmdsoul
 * Returns:       1
 */
public int 
query_cmd_soul() 
{ 
    return 1; 
}
  
public mapping
query_cmdlist()
{
    return ([
        /* Command name : Function name */
        // Child Spells
        "eanemos"       : "do_ability", // Tell Spell
        "eapodosi"      : "do_ability", // Teleport Temple
        "eelefrinisi"   : "do_ability", // Relieve Encumbrance
        "epyrofosti"    : "do_ability", // See Darkness            
        "echoma"        : "do_ability", // Summon Familiar
        "eschirmo"      : "do_ability", // Shield Spell      
        "eunteristi"    : "do_ability", // Spell Resistance
        "ealeipso"      : "do_ability", // Heal
        "edynami"       : "do_ability", // Stat Boost
        "eenischyo"     : "do_ability", // Enhance club
        "eevimero"      : "do_ability", // Haste
        "ethafloga"     : "do_ability", // Fire Tendrils At-Will
        "emagikos"      : "do_ability", // Identify Magic

        // Master Spells
        "eenkav"        : "do_ability", // Burn At-Will
        "eastrapi"      : "do_ability", // Lightning At-Will
        "ekryo"         : "do_ability", // Frostbite At-Will
        "eoxy"          : "do_ability", // Acid Spray At-Will 
        "eousia"        : "do_ability", // Essence Shatter At-Will       
        "eanagnorizo"   : "do_ability", // True Identity
        "eskiamorfi"    : "do_ability", // Elemental Form
        "eviloda"       : "do_ability", // Fireball
        "eripi"         : "do_ability", // Air Gust
        "ekrystallos"   : "do_ability", // Frost Bolt
        "eonkolithos"   : "do_ability", // Boulder Throw
        "ediochetevo"   : "do_ability", // Soul Drain
        // "eanavo"        : "do_ability", // Ignite
        "eafoplizo"     : "do_ability", // Disarm
//        "etyflos"       : "do_ability", // Blind
        "ezalisma"      : "do_ability", // Stun
        "elivra"        : "do_ability", // Pound Armour
        "etihosskias"   : "do_ability", // Shadow Wall
        "etromazo"      : "do_ability", // Alarm
        "eparadido"     : "do_ability", // Teleport to Player
        "ekinisi"       : "do_ability", // Deliver Item
        "ediakopi"      : "do_ability", // Shatter Gem
        "ethesi"        : "do_ability", // Scry
        "eteichos"      : "do_ability", // Fire Wall
        "eperika"       : "do_ability", // Blind
        "eapofevgo"     : "do_ability", // Evade Damage Shield
        "easpida"       : "do_ability", // Reflect Damage Shield
        "ekato"         : "do_ability", // Lower Elemental Resistance
        "ethalamos"     : "do_ability", // Undead Ward
        // "eilithios"     : "do_ability", // Damage Mentals
        "esafi"         : "do_ability", // Cleanse Blindness

        // Guru Spells
        "egiatreou"     : "do_ability", // Neutralize Poison
        "efragmos"      : "do_ability", // Slow Player
        "eseira"        : "do_ability", // Detect Alignment/Killer
        "emetafora"     : "do_ability", // Enhanced Teleport
        "etreximo"      : "do_ability", // Blink Behind
        "ediasosi"      : "do_ability", // Rescue
        "eaorato"       : "do_ability", // Invisibility
        "epanikos"      : "do_ability", // Reduce Panic
        "etrefo"        : "do_ability", // Summon Food/Water
        "eantistasi"    : "do_ability", // Detect Resistances
        "ekourasi"      : "do_ability", // Reduce Fatigue
        "evekpos"       : "do_ability", // Turn Undead        	

        // Full Master Guru Spells
        "efotiafotias"  : "do_ability", // Combination Spell Fire/Fire
        "eaerafotias"   : "do_ability", // Combination Spell Fire/Air
        "enerofotias"   : "do_ability", // Combination Spell Fire/Water
        "efotiagi"      : "do_ability", // Combination Spell Fire/Earth
        "epyrosousia"   : "do_ability", // Combination Spell Fire/Spirit
        "epyrkagia"     : "do_ability", // Combination Spell Air/Fire
        "eaeraaeras"    : "do_ability", // Combination Spell Air/Air
        "eaeranerous"   : "do_ability", // Combination Spell Air/Water
        "eaeragis"      : "do_ability", // Combination Spell Air/Earth
        "eousiaaeras"   : "do_ability", // Combination Spell Air/Spirit
        "epyrkanerou"   : "do_ability", // Combination Spell Water/Fire
        "eneroaeras"    : "do_ability", // Combination Spell Water/Air
        "eneronerous"   : "do_ability", // Combination Spell Water/Water
        "enerogis"      : "do_ability", // Combination Spell Water/Earth
        "eneroousia"    : "do_ability", // Combination Spell Water/Spirit
        "efotiagis"     : "do_ability", // Combination Spell Earth/Fire
        "eatmoskoaera"  : "do_ability", // Combination Spell Earth/Air
        "egiinonero"    : "do_ability", // Combination Spell Earth/Water
        "egigis"        : "do_ability", // Combination Spell Earth/Earth
        "eousiagis"     : "do_ability", // Combination Spell Earth/Spirit
        "epyrkaousias"  : "do_ability", // Combination Spell Spirit/Fire
        "epnevmaaera"   : "do_ability", // Combination Spell Spirit/Air
        "eousiaydato"   : "do_ability", // Combination Spell Spirit/Water
        "epnevmatikgi"  : "do_ability", // Combination Spell Spirit/Earth
        "epnevmatos"    : "do_ability", // Combination Spell Spirit/Spirit
        	
        // Guild Abilities            
        "ehistory"      : "ehistory",   // Lists the recent anemos history
        "edate"         : "edate",      // Shows the Elemental date
        "emeditate"     : "emeditate",   // Shows the player's current personal 
        	                             // conduit
        "esummon"       : "do_ability", // Retrieve/Recall Elemental Ability        	 
        "edismiss"      : "do_ability", // Dismiss Elemental Ability 
        	        	
        // Emotes

        // Help and Options
        "help"          : "help", 
            
        // Casting and Spell Commands
        "pray"          : "pray",
        "prayers"       : "prayers",
        "ecteleport"    : "ecteleport",
        "eglobe"        : "eglobe",
        "edeno"         : "edeno",
        "syndselect"    : "syndselect",
        "syndyasmos"    : "esyndyasmos",

    ]);
}

public mapping
query_ability_map()
{
    return ([
        "eanemos"       : ELEMENTALIST_SPELLS + "ec_anemos",
        "eapodosi"      : ELEMENTALIST_SPELLS + "ec_apodosi",
        "eelefrinisi"   : ELEMENTALIST_SPELLS + "ec_elefrinisi",
        "epyrofosti"    : ELEMENTALIST_SPELLS + "ec_pyrofosti",
        "echoma"        : ELEMENTALIST_SPELLS + "ec_choma",
        "eschirmo"      : ELEMENTALIST_SPELLS + "ec_schirmo",
        "eunteristi"    : ELEMENTALIST_SPELLS + "ec_unteristi",
        "ealeipso"      : ELEMENTALIST_SPELLS + "ec_aleipso",
        "edynami"       : ELEMENTALIST_SPELLS + "ec_dynami",
        "eenischyo"     : ELEMENTALIST_SPELLS + "ec_enischyo",
        "eevimero"      : ELEMENTALIST_SPELLS + "ec_evimero",
        "ethafloga"     : ELEMENTALIST_SPELLS + "ec_thafloga",
        "emagikos"      : ELEMENTALIST_SPELLS + "ec_magikos",
        "eenkav"        : ELEMENTALIST_SPELLS + "ec_enkav",
        "eastrapi"      : ELEMENTALIST_SPELLS + "ec_astrapi",
        "ekryo"         : ELEMENTALIST_SPELLS + "ec_kryo",
        "eoxy"          : ELEMENTALIST_SPELLS + "ec_oxy",
        "eousia"        : ELEMENTALIST_SPELLS + "ec_ousia",
        "eanagnorizo"   : ELEMENTALIST_SPELLS + "ec_anagnorizo",
        "eskiamorfi"    : ELEMENTALIST_SPELLS + "ec_skiamorfi",
        "eviloda"       : ELEMENTALIST_SPELLS + "ec_viloda",
        "eripi"         : ELEMENTALIST_SPELLS + "ec_ripi",
        "ekrystallos"   : ELEMENTALIST_SPELLS + "ec_krystallos",
        "eonkolithos"   : ELEMENTALIST_SPELLS + "ec_onkolithos",
        "ediochetevo"   : ELEMENTALIST_SPELLS + "ec_diochetevo",
        // "eanavo"        : ELEMENTALIST_SPELLS + "ec_anavo",
        "eafoplizo"     : ELEMENTALIST_SPELLS + "ec_afoplizo",
//        "etyflos"       : ELEMENTALIST_SPELLS + "ec_tyflos",
        "ezalisma"      : ELEMENTALIST_SPELLS + "ec_zalisma",
        "elivra"        : ELEMENTALIST_SPELLS + "ec_livra",
        "etihosskias"   : ELEMENTALIST_SPELLS + "ec_tihosskias",
        "etromazo"      : ELEMENTALIST_SPELLS + "ec_tromazo",
        "eparadido"     : ELEMENTALIST_SPELLS + "ec_paradido",
        "ekinisi"       : ELEMENTALIST_SPELLS + "ec_kinisi",                    
        "ediakopi"      : ELEMENTALIST_SPELLS + "ec_diakopi",
        "ethesi"        : ELEMENTALIST_SPELLS + "ec_thesi",
        "eteichos"      : ELEMENTALIST_SPELLS + "ec_teichos",
        "eperika"       : ELEMENTALIST_SPELLS + "ec_perika",
        "eapofevgo"     : ELEMENTALIST_SPELLS + "ec_apofevgo",
        "easpida"       : ELEMENTALIST_SPELLS + "ec_aspida",
        "ekato"         : ELEMENTALIST_SPELLS + "ec_kato",
        "ethalamos"     : ELEMENTALIST_SPELLS + "ec_thalamos",
        // "eilithios"     : ELEMENTALIST_SPELLS + "ec_ilithios",
        "esafi"         : ELEMENTALIST_SPELLS + "ec_safi",
        "egiatreou"     : ELEMENTALIST_SPELLS + "ec_giatreou",
        "efragmos"      : ELEMENTALIST_SPELLS + "ec_fragmos",
        "eseira"        : ELEMENTALIST_SPELLS + "ec_seira",
        "emetafora"     : ELEMENTALIST_SPELLS + "ec_metafora",
        "etreximo"      : ELEMENTALIST_SPELLS + "ec_treximo",
        "ediasosi"      : ELEMENTALIST_SPELLS + "ec_diasosi", 
        "eaorato"       : ELEMENTALIST_SPELLS + "ec_aorato",
        "epanikos"      : ELEMENTALIST_SPELLS + "ec_panikos",
        "etrefo"        : ELEMENTALIST_SPELLS + "ec_trefo",
        "eantistasi"    : ELEMENTALIST_SPELLS + "ec_antistasi",
        "ekourasi"      : ELEMENTALIST_SPELLS + "ec_kourasi",
        "evekpos "      : ELEMENTALIST_SPELLS + "ec_vekpos",        	
        "efotiafotias"  : ELEMENTALIST_SPELLS + "ec_syndyff",
        "eaerafotias"   : ELEMENTALIST_SPELLS + "ec_syndyfa",
        "enerofotias"   : ELEMENTALIST_SPELLS + "ec_syndyfw",
        "efotiagi"      : ELEMENTALIST_SPELLS + "ec_syndyfe",
        "epyrosousia"   : ELEMENTALIST_SPELLS + "ec_syndyfs",
        "epyrkagia"     : ELEMENTALIST_SPELLS + "ec_syndyaf",
        "eaeraaeras"    : ELEMENTALIST_SPELLS + "ec_syndyaa",
        "eaeranerous"   : ELEMENTALIST_SPELLS + "ec_syndyaw",
        "eaeragis"      : ELEMENTALIST_SPELLS + "ec_syndyae",
        "eousiaaeras"   : ELEMENTALIST_SPELLS + "ec_syndyas",
        "epyrkanerou"   : ELEMENTALIST_SPELLS + "ec_syndywf",
        "eneroaeras"    : ELEMENTALIST_SPELLS + "ec_syndywa",
        "eneronerous"   : ELEMENTALIST_SPELLS + "ec_syndyww",
        "enerogis"      : ELEMENTALIST_SPELLS + "ec_syndywe",
        "eneroousia"    : ELEMENTALIST_SPELLS + "ec_syndyws",
        "efotiagis"     : ELEMENTALIST_SPELLS + "ec_syndyef",
        "eatmoskoaera"  : ELEMENTALIST_SPELLS + "ec_syndyea",
        "egiinonero"    : ELEMENTALIST_SPELLS + "ec_syndyew",
        "egigis"        : ELEMENTALIST_SPELLS + "ec_syndyee",
        "eousiagis"     : ELEMENTALIST_SPELLS + "ec_syndyes",
        "epyrkaousias"  : ELEMENTALIST_SPELLS + "ec_syndysf",
        "epnevmaaera"   : ELEMENTALIST_SPELLS + "ec_syndysa",
        "eousiaydato"   : ELEMENTALIST_SPELLS + "ec_syndysw",
        "epnevmatikgi"  : ELEMENTALIST_SPELLS + "ec_syndyse",
        "epnevmatos"    : ELEMENTALIST_SPELLS + "ec_syndyss",
        "edismiss"      : ELEMENTALIST_SPECIALS + "edismiss",
        "esummon"       : ELEMENTALIST_SPECIALS + "esummon",        	
    ]);
}

/*
 * Function name: edeno
 * Description:   The "edeno" command - this will allow the player
 *                to add/remove the target to their possible 
 *                syndyasmos partners list for use with the
 *                syndyasmos command (prayer)
 * Arguments:     string str - arguments to "edeno" command
 * Returns:       1/0 - edeno command executed/not executed
 */
public int
edeno(string str)
{
	// Are they Full Master rank in the guild? If not, let them know they can't 
	// use this.
	if (!GUILD_MANAGER->query_is_full_master(TP))
	{
		notify_fail("You cannot use this command unless you are a Full "+
		    "Master Cleric.\n");
		return 0;
	}

	mapping partners = GUILD_MANAGER->query_syndyasmos_partners(TP);
	int size = 0;
	string part = "";
	string arg;
	object target;
	str = lower_case(str);
	
	// No argument or gave 'list' or 'partners' as an argument.
    if(!str || str == "list" || str == "partners")
    {
        // They don't have anyone on the list?
       if(!m_sizeof(GUILD_MANAGER->query_syndyasmos_partners(TP)))
       {
          write("You have not set any possible Syndyasmos partners.\n");
          return 1;
       }

       foreach(string element: m_indexes(partners))
       {
           size++;
           part += capitalize(element);
           if (m_sizeof(partners) - size == 1)
               part += " and ";
           else if (m_sizeof(partners) - size > 1)
               part += ", ";
       }
       
       // Show them their list of potential partners already added.   
       write("You remember having previously set the following Syndyasmos "+
           "partners:\n" + "   "+ part + ".\n\n");
       return 1;
    }

    // They only put 'add'.
    if (str == "add")
    {
       write("Edeno add whom?\n");
       return 1;          
     }
    
    // They put 'add' and something else.
    if (parse_command(str, environment(TP), "'add' %s", arg))
    {
        if (!arg)
        {
            write("Edeno add whom?\n");
            return 1;          
        }
        
        // Did they select themselves as a partner to add? (Trixy humans!)
        if (lower_case(arg) == TP->query_real_name())
        {
        	notify_fail("You cannot add yourself!\n");
        	return 0;
        }
        
        target = present(arg,environment(TP));
	    
	    // Are they in the same room as the target?
		if (!target)
		{
			notify_fail("You need to be in the same location as "+
			    capitalize(arg)+".\n");
			return 0;
		}
		
		// Are they an actual player?
		if (!interactive(target))
		{
			notify_fail("I'm sorry, "+capitalize(arg)+" is not an "+
			    "actual player.\n");
			return 0;
		}
		
		// Are they Full Master rank in the guild?	
		if (!GUILD_MANAGER->query_is_full_master(arg))
		{
			notify_fail("I'm sorry, "+capitalize(arg)+" must also "+
			    "be a Full Master Cleric.\n");
			return 0;
		}    
    
        // Did they already add them on the list?
        if (member_array(arg, m_indexes(partners)) > -1)
        {
            write("You already have "+capitalize(arg)+" added as a possible "+
                "Syndyasmos partner.\n");
            return 1;
        }
    
        // All is good, attempt to add them to the list if confirmed
        arg = lower_case(arg);        
        string prop = TP->query_prop(LIVE_I_EDENO);
        if (prop)
        {
        	// Confirmed by partner, add to both lists.
            if (prop == target->query_real_name())
            {
                write("You have added " + capitalize(arg) +
                    " to your possible Syndyasmos partners.\n");
                target->catch_msg(QCTNAME(TP)+ " has authorized your request. "+
                    "You have added "+capitalize(TP->query_real_name())+
                    " to your possible Syndyasmos partners.\n");
        
                GUILD_MANAGER->add_syndyasmos_partner(TP, arg);
                TP->remove_prop(LIVE_I_EDENO);
                GUILD_MANAGER->add_syndyasmos_partner(arg, 
                    TP->query_real_name());
                return 1;
            }
        }
        
        // Notify partner for verification to add to the list.
        string myname = TP->query_real_name();
        target->add_prop(LIVE_I_EDENO, myname);
        write("You have requested to add "+capitalize(arg)+ " to your possible "+
            "Syndyasmos partners. They must now authorize your request.\n");
        target->catch_msg(QCTNAME(TP)+" has requested to add you as a possible "+
            "Syndyasmos partner. If you wish to authorized this, please "+
            "<edeno add "+capitalize(TP->query_real_name())+">.\n");
        return 1;        
    }
    
    // Did they put remove as an argument?
    else if (parse_command(str, environment(TP), "'remove' %s", arg))
    {  
    	// They are on the list, remove them from it (and remove them from their
    	// partners list.
        if(member_array(lower_case(arg), m_indexes(partners)) > -1)
        {
            write("You remove " + capitalize(arg) + " as a possible "+
                "Syndyasmos partner.\n");
            GUILD_MANAGER->remove_syndyasmos_partner(TP, lower_case(arg));
            GUILD_MANAGER->remove_syndyasmos_partner(lower_case(arg),
                TP->query_real_name());
            
            // If they are their current set partner, remove that as well.
            if (GUILD_MANAGER->query_current_syndyasmos_partner(TP) == 
            	    lower_case(arg))
            	GUILD_MANAGER->set_current_syndyasmos_partner(TP,0);
            
            if (GUILD_MANAGER->query_current_syndyasmos_partner(lower_case(arg))
            	     == TP->query_real_name())
            	GUILD_MANAGER->set_current_syndyasmos_partner(lower_case(arg),0);
    
            return 1;
        }
        
        else
        {
        	// They weren't on the list.
            write("You cannot recall having had "+capitalize(arg)+" as a "+
                "possible Syndyasmos partner.\n");
            return 1;
        }
    }
    
    // Give them the proper syntaxes for the command.
    notify_fail("What are you trying to do? edeno <add>, <remove>, <list> "+
        "or <partners>?\n");
    return 0;	
}

/*
 * Function name: syndselect
 * Description:   The "syndselect" command - this will allow
 *                the player to select their partner for a
 *                syndyasmos command from their "edeno" list.
 * Arguments:     string str - arguments to "syndselect" command
 * Returns:       1/0 - syndselect command executed/not executed
 */
public int
syndselect(string str)
{
	// Are they Full Master rank in the guild? If not, don't let them use this 
	// command.
	if (!GUILD_MANAGER->query_is_full_master(TP))
	{
		notify_fail("You cannot use this command unless you are a Full "+
		    "Master Cleric.\n");
		return 0;
	}
	
	// No argument given, display their current chosen partner.
	if (!str)
	{
		if (!GUILD_MANAGER->query_current_syndyasmos_partner(TP))
		{
			write("You do not have a Syndyasmos partner currently set.\n");
			return 1;
		}
		write("Your current Syndyasmos partner is set as: "+capitalize(
			GUILD_MANAGER->query_current_syndyasmos_partner(TP))+"\n");
		return 1;
	}
	
	str = lower_case(str);
		
	// If 'none' is the argument, unselect their current partner.
	if (str == "none")
	{
		string old_partner = GUILD_MANAGER->query_current_syndyasmos_partner(TP);
		
		// Do they have a partner? If so, unselect them and notify both partners.
		if (old_partner)
		{
			object old_partner_ob = find_player(old_partner);
			GUILD_MANAGER->set_current_syndyasmos_partner(TP,0);
		    write("You now have nobody selected as your Syndyasmos partner.\n");
		    old_partner_ob->catch_msg(capitalize(TP->query_real_name())+ 
		        " has "+ "unselected you as "+TP->query_possessive()+
		        " Syndyasmos partner.\n");
			return 1;
		}
		
		// No current partner selected.
		write("You do not have a Syndyasmos partner currently set.\n");
		return 1;		
	}
	
	object target = present(str,environment(TP));
	
	// Are they in the same room as their partner? If not, let them know.
	if (!target)
	{
		notify_fail("You need to be in the same locations as "+
		    "your target, "+capitalize(str)+".\n");
		return 0;
	}
	
	// Did they try to set a non-player as a partner? If so, let them know.
	if (!interactive(target))
	{
		notify_fail("I'm sorry, "+capitalize(str)+" is not an "+
		    "actual player.\n");
		return 0;
	}
	
	// Are they Full Master rank in the guild? If not, let them know they can't
	// use this.
	if (!GUILD_MANAGER->query_is_full_master(str))
	{
		notify_fail("I'm sorry, "+capitalize(str)+" must also "+
		    "be a Full Master Cleric.\n");
		return 0;
	}
	
	mapping partners = GUILD_MANAGER->query_syndyasmos_partners(TP);
	object env = environment(TP);
	string arg;
	
	if(parse_command(str, env, " %s", arg))
    {
    	// Are they on the members list? If not, let them know how to add them. 
        if (member_array(lower_case(arg), m_indexes(partners)) < 0)
        {
            notify_fail("You don't have "+capitalize(str)+" set as a "+
                "Syndyasmos partner. You may use <edeno add "+capitalize(str)+
                "> to set them as one.\n");
            return 0;
        }
    }
    
    // All good, select them as a partner and notify both players.
    object partner_obj = find_player(str);
    GUILD_MANAGER->set_current_syndyasmos_partner(TP,str);
    write("You have selected "+capitalize(str)+" as your Syndyasmos partner.\n");
    partner_obj->catch_tell(capitalize(TP->query_real_name())+ " has set you "+
        "as "+TP->query_possessive()+ " Syndyasmos partner.\n");
    
	return 1;
}

public void
remove_syndyasmos_alarm()
{
	TP->remove_prop(LIVE_I_SYNDYASMOS_CAST);
	TP->catch_msg("\n\n******************************************************"+
	    "***"+
	    "\n* You feel ready to use the powers of Syndyasmos again. *\n"+
	    "*********************************************************\n\n");
	say(QCTNAME(TP)+" seems to have recovered fully from "+
	    TP->query_possessive() + " intense prayer.\n");
}

public int
esyndyasmos(string str)
{
    int nc = 0;
    
	// Are they a Full Master? If not, don't let them use this command.
	if (!GUILD_MANAGER->query_is_full_master(TP))
	{
		notify_fail("You cannot use this prayer unless you are a Full "+
		    "Master Cleric.\n");
		return 0;
	}
	
	// Is their partner set? If not, don't continue.
	string partner = GUILD_MANAGER->query_current_syndyasmos_partner(TP);
	if (!partner)
	{
		notify_fail("You do not have a Syndyasmos partner currently set.\n");
		return 0;
	}
	    
	object partner_ob = find_player(partner);
	string partner_name = capitalize(partner_ob->query_real_name());
	if (!partner_name)
		partner_name = capitalize(partner);				
	
	// Does their partner have them set as their current partner? If not, don't 
	// continue.
	string partner_partner = GUILD_MANAGER->query_current_syndyasmos_partner(partner);
	if (!partner_partner)
	{
		notify_fail(partner_name+" does not have you set as their current "+
		"partner.\n");
		return 0;
	}
	
	if (partner_partner != TP->query_real_name())
	{
		notify_fail(partner_name+" does not have you set as their current "+
		"partner.\n");
		return 0;
	}
	
	// Are they teamed? If not, don't continue.
	mixed * team = TP->query_team_others();
	if (!team)
	{
		notify_fail("You are not teamed with "+partner_name+".\n");
		return 0;
	}
	
	// Are they teamed with their partner? If not, don't continue.
	int partnered;
	for (int i=0; i < sizeof(team); i ++)
	{
		if (partner_ob == team[i])
			partnered = 1;
	}
	if (!partnered)
	{
		notify_fail("You are not teamed with "+partner_name+".\n");
		return 0;
	}

    // Are they present in the same location? If not, don't continue.
    if (!present(partner_ob, environment(TP)))
    {
    	notify_fail("You are not in the same location as "+
    	    partner_name+".\n");
    	return 0;
    }
	
	// Does the caster have enough mana? If not, don't continue.
	if (TP->query_mana() < SYNDYASMOS_MANA)
	{
		notify_fail("You do not have enough mana.\n");
		return 0;
	} 
	
	// Does the partner have enough mana? If not, don't continue.
	if (partner_ob->query_mana() < SYNDYASMOS_MANA)
	{
		notify_fail(partner_name+" does not have enough mana.\n");
		return 0;
	}
		
	// Does the caster have enough conduit points? If not, don't continue.
	if (GUILD_MANAGER->query_player_conduit_earned(TP) < SYNDYASMOS_CONDUIT_COST)
	{
		notify_fail("You do not have enough Conduit Energy stored.\n");
		return 0;
	}

    // Does the partner have enough conduit points? If not, don't continue.
    if (GUILD_MANAGER->query_player_conduit_earned(partner_ob) < 
    	SYNDYASMOS_CONDUIT_COST)
	{
		notify_fail(capitalize(partner_name)+" does not have enough Conduit "+
		    "Energy stored.\n");
		return 0;
	}
	
    // Is the caster already casting? If not, don't continue.
    if (TP->query_prop(LIVE_I_CONCENTRATE))
    {
    	notify_fail("You are already busy concentrating on something else.\n");
    	return 0;
    }
    
    // Is the partner already casting? If not, don't continue.
    if (partner_ob->query_prop(LIVE_I_CONCENTRATE))
    {
    	notify_fail(partner_name+" is already busy concentrating on something "+
    	    "else.\n");
    	return 0;
    }
    
    // Look up the combination based on caster/partner
    string caster_element = GUILD_MANAGER->query_primary_element(TP);
    string partner_element = GUILD_MANAGER->query_primary_element(partner_ob);
    
    if (!caster_element || !partner_element)
    {
    	notify_fail("Something has gone wrong with one of the partners. Please "+
    	    "notify the guildmaster that something is wrong with Syndyasmos "+
    	    "and that caster = "+caster_element+" and partner = "+
    	    partner_element+".\n");
    	return 0;
    }        
    
    string spell;
    switch(caster_element)
    {
    	case "fire":
    		switch(partner_element)
    		{
    			case "fire":
    				spell = "fotiafotias";
    				break;
    			case "air":
    				spell = "aerafotias";
    				break;
    			case "water":
    				spell = "nerofotias";
		        	break;
		        case "earth":
		        	spell = "fotiagi";
		        	break;
		        case "life":
		        	spell = "pyrosousia";
		        	break;
		    }
    		break;
    	case "air":
    		switch(partner_element)
    		{
    			case "fire":
    				spell = "epyrkagia";
    				break;
    			case "air":
    				spell = "eaeraaeras";
    				break;
    			case "water":
    				spell = "eaeranerous";
		        	break;
		        case "earth":
		        	spell = "eaeragis";
		        	break;
		        case "life":
		        	spell = "eousiaaeras";
		        	break;
		    }
    		break;
        case "water":
        	switch(partner_element)
    		{
    			case "fire":
    				spell = "epyrkanerou";
    				break;
    			case "air":
    				spell = "eneroaeras";
    				break;
    			case "water":
    				spell = "eneronerous";
    				nc = 1;
		        	break;
		        case "earth":
		        	spell = "enerogis";
		        	break;
		        case "life":
		        	spell = "eneroousia";
		        	nc = 1;
		        	break;
		    }
        	break;
        case "earth":
        	switch(partner_element)
    		{
    			case "fire":
    				spell = "efotiagis";
    				break;
    			case "air":
    				spell = "eatmoskoaera";
    				break;
    			case "water":
    				spell = "egiinonero";
		        	break;
		        case "earth":
		        	spell = "egigis";
		        	break;
		        case "life":
		        	spell = "eousiagis";
		        	break;
		    }
        	break;
        case "life":
        	switch(partner_element)
    		{
    			case "fire":
    				spell = "epyrkaousias";
    				break;
    			case "air":
    				spell = "epnevmaaera";
    				break;
    			case "water":
    				spell = "eousiaydato";
		        	break;
		        case "earth":
		        	spell = "epnevmatikgi";
		        	break;
		        case "life":
		        	spell = "epnevmatos";
		        	break;
		    }
        	break;
    }
    
    if (TP->query_prop(LIVE_I_SYNDYASMOS_CAST))
    {
    	notify_fail("You are not ready to use Syndyasmos again.\n");
    	return 0;
    }
    
    if (!TP->query_attack())
    {
        if (!nc)
        {
        	notify_fail("You are not engaged in combat and therefore "+
        	    "cannot use Syndyasmos.\n");
        	return 0;
        }
    }
    
    object ob;

    if (ob = TP->find_spell(spell))
    {
    	// Is the caster already casting? If not, don't continue.
	    if (TP->query_prop(LIVE_I_CONCENTRATE))
	    {
	    	notify_fail("You are already busy concentrating on something "+
	    	    "else.\n");
	    	return 0;
	    }
	    
	    // Is the partner already casting? If not, don't continue.
	    if (partner_ob->query_prop(LIVE_I_CONCENTRATE))
	    {
	    	notify_fail(partner_name+" is already busy concentrating on "+
	    	    "something else.\n");
	    	return 0;
	    }
	    
    	// Take conduit points from caster
        GUILD_MANAGER->subtract_player_conduit_earned(TP, 
            SYNDYASMOS_CONDUIT_COST);
    
        // Take mana and conduit points from partner
        GUILD_MANAGER->subtract_player_conduit_earned(partner_ob, 
            SYNDYASMOS_CONDUIT_COST);
        partner_ob->add_mana(-SYNDYASMOS_MANA);
    
    	// Cast the actual spell
    	set_alarm(45.0, 0.0, &remove_syndyasmos_alarm());
    	TP->add_prop(LIVE_I_SYNDYASMOS_CAST,1);
    	TP->start_spell(spell, str, ob);
    	nc = 0;
    	return 1;
    }
    write("Something has gone wrong and you don't have any combination "+
        "prayers available.\nPlease let the guildmaster know and tell "+
        "them the combination was "+caster_element+
        " + "+partner_element+".\n");
	return 1;
}

/*
 * Function name: pray
 * Description:   The "pray" command.
 * Arguments:     string str - arguments to "pray" command
 * Returns:       1/0 - pray command executed/not executed
 */
public int
pray(string str)
{
    object ob;
    string spell, arg;

    if (!strlen(str))
    {
        notify_fail("Pray what?\n", 0);
        return 0;
    }

    if (!sscanf(str, "%s %s", spell, arg))
    {
        spell = str;
    }

    if (ob = this_player()->find_spell(spell))
    {    
        this_player()->start_spell(spell, arg, ob);
        return 1;
    }

    notify_fail("Pray what?\n", 0);
    return 0;
}

/*
 * Function:    print_spell_list
 * Description: Used in the prayers command, this will print out
 *              each classification of spells with a header.
 */
public string
print_spell_list(string header, object * spellobjs)
{
    string message_text = "";
    int spells_known = 0;
    if (sizeof(spellobjs))
    {
        message_text += sprintf("%'='" + sprintf("%d", strlen(header) + 4) +
            "s\n", "");
        message_text += sprintf("= %s =\n", header);
        message_text += sprintf("%'='" + sprintf("%d", strlen(header) + 4) +
            "s\n", "");
        foreach (object spellobj : spellobjs)
        {
            if (!spellobj->query_spell_can_be_learned(this_player()))
            {
                // Only show spells that we actually know
                continue;
            }
            spells_known++;
            message_text += sprintf("%-=12.12s %-=57.57s\n", 
                spellobj->query_spell_name(),
                spellobj->query_spell_desc() + " ("
                + spellobj->query_spell_ingredients_description() + ")");
        }
        message_text += "\n";
    }
    if (spells_known == 0) 
    {
        return "";
    }
    return message_text;
}
/*
 * prayers - Show what prayers we know
 */
/*
 * Function name: prayers
 * Description:   List the active prayers.
 */
public int
prayers(string str)
{
    object *spellobjs = this_player()->query_spellobjs();
    spellobjs = filter(spellobjs, &wildmatch(ELEMENTALIST_SPELLS + "*") 
        @ file_name);
    
    if (!sizeof(spellobjs))
    {
        write("You have no prayers.\n");
        return 1;
    }

    object * f_m_spells = filter(spellobjs, &->is_full_master_cleric_spell());
    object * m_g_c_spells = filter(spellobjs, &->is_master_guru_cleric_spell());
    object * m_c_c_spells = filter(spellobjs, &->is_master_cleric_spell());
    object * c_c_spells = spellobjs - m_g_c_spells - m_c_c_spells - f_m_spells;
    
    string message_text = "Prayers for the Elemental Clerics of Calia\n\n";
    message_text += print_spell_list("Child Cleric Gifts", c_c_spells);
    message_text += print_spell_list("Master Cleric Gifts", m_c_c_spells);
    message_text += print_spell_list("Master Cleric Gifts (Guru Quest "+
        "completed)", m_g_c_spells);
//	message_text += print_spell_list("Final Master Cleric Gifts", f_m_spells);
    message_text += "To invoke your gift, simply <pray> with the name of "+ 
        "the gift.\n";
    this_player()->more(generate_scroll_text(message_text, "Property of the "+
        "Elemental Guilds of Calia"));
    return 1;
}

/*
 * Function:    help
 * Description: Handler for the help system for Elemental Guilds
 */
public int
help(string str)
{
    // Access help files
    string content, *files; 
    setuid(); 
    seteuid(getuid()); 

    if (!stringp(str) || !strlen(str))
    { 
        return 0; 
    }
    
    if (str == "clerics" || str == "cleric") 
    {         
        if (!pointerp(files = get_dir(ELEMENTALIST_CLERIC_HELP)) || 
        	!sizeof(files))
        {
            return 0; 
        }
        
        if (!stringp(content = read_file(ELEMENTALIST_CLERIC_HELP + "general")))
        {
            notify_fail("Something is terribly wrong! Please contact "
                + "the guildmaster and let them know that the help files "
                + "for the Clerics are not working property.\n");
            return 0;
        }
        
        write("You fuss around with your notes and read the scroll "
            + "introducing the Elemental Clerics of Calia.\n");
        this_player()->more(generate_scroll_text(content, "Property of the "+
            "Elemental Guilds of Calia"));
        return 1;
    } 

    if (sscanf(str, "clerics %s", str) != 1)
    {
        if (sscanf(str, "cleric %s", str) !=1)
            return 0;
    }
    
    str = lower_case(str); // set everything to lowercase
    // Players can get information about spells that they know
    
    if (str == "syndyasmos")
    {
        if (!GUILD_MANAGER->query_is_full_master(TP))
    	{
    		notify_fail("You cannot use this prayer unless you are a Full "+
    		    "Master Cleric.\n");
    		return 0;
    	}
    	
        if (GUILD_MANAGER->query_is_full_master(TP))
        {
            string element = GUILD_MANAGER->query_primary_element(TP);
            switch (element)
            {
                case "fire":
                    stringp(content = read_file(ELEMENTALIST_HELP_CLERIC_SPELLS +
                        "syndyasmos_fire"));
                    break;
                case "air":
                    stringp(content = read_file(ELEMENTALIST_HELP_CLERIC_SPELLS +
                        "syndyasmos_air"));
                    break;
                case "water":
                    stringp(content = read_file(ELEMENTALIST_HELP_CLERIC_SPELLS +
                        "syndyasmos_water"));
                    break;
                case "earth":
                    stringp(content = read_file(ELEMENTALIST_HELP_CLERIC_SPELLS +
                        "syndyasmos_earth"));
                    break;
                case "life":
                    stringp(content = read_file(ELEMENTALIST_HELP_CLERIC_SPELLS +
                        "syndyasmos_spirit"));
                    break;
                default:
                    notify_fail("Something has gone terribly wrong - please "+
                        "notify the guildmaster that you cannot read the help "+
                        "scroll on Syndyasmos.\n");
                    return 0;
                    break;
            }
            
            write("You flip through your guild scrolls and read the scroll "
                + "pertaining to " + capitalize(str) + ".\n");
            TP->more(generate_scroll_text(content, "Property of the Elemental "+
                "Guilds of Calia"));
            return 1;
        }
    }
    
    if ((objectp(this_player()->find_spell(str))
         && stringp(content = read_file(ELEMENTALIST_HELP_CLERIC_SPELLS + str)))
        || stringp(content = read_file(ELEMENTALIST_CLERIC_HELP + str)))
    {        
        write("You flip through your guild scrolls and read the scroll "
            + "pertaining to " + capitalize(str) + ".\n");
        this_player()->more(generate_scroll_text(content, "Property of the "+
            "Elemental Guilds of Calia")); 
        return 1;         
    }

    notify_fail("You can't seem to find any scrolls on that topic "
        + "among the notes that you received upon joining the "
        + "guild.\n"); 
    return 0;     
}

public int
ehistory(string str)
{
    object player = this_player();
    // This will retrieve the last 10 messages in the tell history
    mixed history = GUILD_MANAGER->query_tell_history(player);
    if (!sizeof(history))
    {
        write("You have no message history.\n");
        return 1;
    }
    
    string history_text = "";
    history_text += sprintf("%15-s %-s\n", "Sender", "Message");
    history_text += sprintf("%'-'15-s %'-'60s\n", "", "");
    for (int index = sizeof(history) - 1; index >= 0; --index)
    {
        mixed message_item = history[index];
        if (sizeof(message_item) < 2)
        {
            continue;
        }
        string sender = message_item[0];
        string message = message_item[1];
        history_text += sprintf("%15-s %-s\n", capitalize(sender), message);
    }
    
    write(history_text + "\n");
    return 1;
}

public int
edate()
{
	string elemental_date;
	
	elemental_date = GUILD_MANAGER->query_calendar();
	write(elemental_date);
	return 1;
}

public int
emeditate()
{
	int personal_conduit, practice_level, guild_conduit;
	
	string conduit_desc, practice_desc, guild_desc;
	
	personal_conduit = GUILD_MANAGER->query_player_conduit_earned(this_player());
	practice_level = GUILD_MANAGER->query_practice_level(this_player());
	guild_conduit = GUILD_MANAGER->query_guild_conduit();

    switch(personal_conduit)
    {
    	case 0:
    		conduit_desc = "you have none stored.\n";
    		break;
    	case 1..999:
    		conduit_desc = "you barely have any stored.\n";
    		break;
    	case 1000..2500:
    		conduit_desc = "you have a tiny amount stored.\n";
    		break;
    	case 2501..5000:
    		conduit_desc = "you have a small amount stored.\n";
    		break;
    	case 5001..7500:
    		conduit_desc = "you have a little stored.\n";
    		break;
    	case 7501..10000:
    		conduit_desc = "you have some stored.\n";
    		break;
    	case 10001..15000:
    		conduit_desc = "you have a decent amount stored.\n";
    		break;
    	case 15001..20000:
    		conduit_desc = "you have a good amount stored.\n";
    		break;
    	case 20001..25000:
    		conduit_desc = "you have a very good amount stored.\n";
    		break;
    	case 25001..27500:
    		conduit_desc = "you have an immense amount stored.\n";
    		break;
    	default:
    		conduit_desc = "you have a fantastic amount stored.\n";
    		break;
    }
    
    switch(practice_level)
    {
    	case 0:
    		practice_desc = "you have no practice at prayers.\n";
    		break;
    	case 1..4999:
    		practice_desc = "you have insignificant practice at prayers.\n";
    		break;
    	case 5000..9999:
    		practice_desc = "you have a tiny amount of practice at prayers.\n";
    		break;
    	case 10000..14999:
    		practice_desc = "you have a minimal amount of practice at "+
    		    "prayers.\n";
    		break;
    	case 15000..19999:
    		practice_desc = "you have slight practice at prayers.\n";
    		break;
    	case 20000..24999:
    		practice_desc = "you have a low amount of practice at prayers.\n";
    		break;
    	case 25000..29999:
    		practice_desc = "you have some amount of practice at prayers.\n";
    		break;
    	case 30000..34999:
    		practice_desc = "you have a modest amount of practice at prayers.\n";
    		break;
    	case 35000..39999:
    		practice_desc = "you have a decent amount of practice at prayers.\n";
    		break;
    	case 40000..44999:
    		practice_desc = "you have a nice amount of practice at prayers.\n";
    		break;
    	case 45000..54999:
    		practice_desc = "you have a good amount of practice at prayers.\n";
    		break;
    	case 55000..59999:
    		practice_desc = "you have a very good amount of practice at "+
    		    "prayers.\n";
    		break;
    	case 60000..67499:
    		practice_desc = "you have a major amount of practice at prayers.\n";
    		break;
    	case 67500..72499:
    		practice_desc = "you have a great amount of practice at prayers.\n";
    		break;
    	case 72500..77499:
    		practice_desc = "you have an extremely good amount of practice "+
    		    "at prayers.\n";
    		break;
    	case 77500..82499:
    		practice_desc = "you have an awesome amount of practice at "+
    		    "prayers.\n";
    		break;
    	case 82500..87499:
    		practice_desc = "you have an immense amount of practice at "+
    		    "prayers.\n";
    		break;
    	case 87500..92499:
    		practice_desc = "you have a tremendous amount of practice at "+
    		    "prayers.\n";
    		break;
    	default:
    		practice_desc = "you have a fantastic amount of practice at "+
    		    "prayers.\n";
    		break;
    }
    
    switch(guild_conduit)
    {
    	case 0:
    		guild_desc = "the Temple Conduit is empty!\n";
    		break;
    	case 1..33750:
    		guild_desc = "the Temple Conduit has a low level of energy.\n";
    		break;    	
    	case 33751..67500:
    		guild_desc = "the Temple Conduit has a medium level of energy.\n";
    		break;    	
    	default:
    		guild_desc = "the Temple Conduit has a high level of energy.\n";
    		break;
    }
    
    write("You focus your energies outwards and meditate on your Chymos. "+
        "You determine " + conduit_desc);
    write("\nYou focus your energies inwards and meditate on yourself. "+
        "You determine " + practice_desc);
    write("\nYou focus your energies and meditate on the Temple Conduit. "+
        "You determine " + guild_desc);	
    
	return 1;
}

int
ecteleport(string str)
{
    int     size = 0;
    int     max_locs;
    object  caster = TP,
            env = environment(caster);
    string  fail, comm_str, arg, room, loc = "", locnum;
    mapping locations = GUILD_MANAGER->query_teleport_locations(caster);

    if(GUILD_MANAGER->query_is_child_cleric(caster))
    {
        notify_fail("This command is not available to you as a Child "+
            "Cleric.\n");
        return 0;
    }    

    max_locs = ECTELEPORT_OTHERS;
    locnum = "location";
    
    if(GUILD_MANAGER->query_primary_element(caster) == "air")
    	max_locs = ECTELEPORT_AIR;
    
    comm_str = "ecteleport";
    
    if (!str)
    {
          write("The teleport commands available to you:\n\n"+
                "    " +comm_str+ " <list> for a list of memorised "+
                "locations.\n"+
                "    " +comm_str+ " <set [location]> to set where you "+
                "stand as " +
                "a teleport location.\n"+
                "    " +comm_str+ " <remove [location]> to forget one of "+
                "your " +
                "teleport locations.\n    " +
                "<pray apodosi [location]> to teleport to a remembered "+
                "location.\n\n");
          return 1;
    }

    if(str == "list" || str == "locations")
    {
       if(!m_sizeof(GUILD_MANAGER->query_teleport_locations(caster)))
       {
          write("You cannot recall having previously set any locations.\n");
          return 1;
       }

       foreach(string element: m_indexes(locations))
       {
           size++;
           loc += capitalize(element);
           if (m_sizeof(locations) - size == 1)
               loc += " and ";
           else if (m_sizeof(locations) - size > 1)
               loc += ", ";
       }
       
       if (max_locs > 1)
           locnum = "locations";
           
       write("You remember having previously set the following teleportation "+
           "locations:\n" + "   "+ loc + ".\n\n" +
           "You can set a total of " +LANG_WNUM(max_locs)+ " teleportation "+
               locnum+".\n");
       return 1;
    }

    if (str == "set")
    {
       write("By what name do you want to set this location that you want to "+ 
             "teleport to?\n");
       return 1;          
     }

    if (parse_command(str, environment(caster), "'set' [to] %s", arg))
    {
        if (env->query_prop(ROOM_M_NO_TELEPORT) ||
            env->query_prop(ROOM_M_NO_TELEPORT_TO))
            fail = "Something prevents you from setting this place as a " +
                   "teleportation location.\n";

        if(fail)
        {
           write(fail);
           return 1;          
         }

        if (m_sizeof(locations) >= max_locs)
        {
            write("You cannot remember any more locations.\n");
            return 1;
        }

        if (!arg)
        {
            write("By what name do you want to set this location you want to "+ 
            "teleport to?\n");
            return 1;          
        }    
    
        if (member_array(arg, m_indexes(locations)) > -1)
        {
            write("You already have a location memorized by that name.\n");
            return 1;
        }
    
        if (!file_size(file_name(env) + ".c"))
        {
            write("The fabric of space seems different here, you " +
                "don't think you are able to teleport from here.\n");
            return 1;
          
        }
    
        if (member_array(file_name(env), m_values(locations)) > -1)
        {
            write("You already have that location memorized.\n");
            return 1;
        }

         if (strlen(arg) > 15 || sizeof(explode(arg, " ")) > 1)
         {
            write("Please refrain from any longer names and use single "+
                "words.\n");
            return 1;
         }

        arg = lower_case(arg);

        write("You mentally commit this place to memory " +
            "as " + capitalize(arg) + ".\n");

        set_this_player(caster);

        string set_room = file_name(env);

        set_this_player(caster);
        GUILD_MANAGER->add_teleport_locations(caster, arg, set_room);
        return 1;

    }
    
    else if (parse_command(str, environment(caster), "[to] 'remove' %s", arg))
    {  
        if(member_array(lower_case(arg), m_indexes(locations)) > -1)
        {
            write("You uncommit " +
            "the place you knew as " + capitalize(arg) + " from memory.\n");
            GUILD_MANAGER->remove_teleport_locations(caster, lower_case(arg));
    
            return 1;
        }
        
        else
        {
            write("You cannot recall having previously named such a "+
                "location.\n");
            return 1;
        }
    }

    notify_fail("What are you trying to do? " +comm_str+ " <set>, <remove> "+
        "or <list>?\n");
    return 0;
}

int
eglobe()
{
    object caster = TP;
    object globe;

    if(GUILD_MANAGER->query_primary_element(caster) != "water")
    	return 0;
    	    	
    if(GUILD_MANAGER->query_is_child_cleric(caster))
        return 0;

    if (present("_cleric_water_globe",caster))
    {
    	notify_fail("You already have a water globe. You can only have "+
    	    "one.\n");
    	return 0;
    }
    
    setuid(); 
    seteuid(getuid());
    globe = clone_object(ELEMENTALIST_OBJS + "water_globe");
    globe->move(caster,1);
    write("Concentrating on the powers granted to you by Lord Diabrecho, "+
        "you summon a water globe.\n");
    say(QCTNAME(caster)+" appears to concentrate for a brief moment. Suddenly "+
        "a water globe appears in "+caster->query_possessive()+" hands.\n");
    return 1;
}
