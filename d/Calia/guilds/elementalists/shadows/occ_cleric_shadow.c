/* 
 * Elemental Clerics of Calia Occupational Guild Shadow
 *
 * This is the occupational guild shadow for the 
 * Elemental Clerics of Calia. This is a clerical 
 * occupational + layman guild. Members of this guild 
 * will select one branch to focus on, which equates 
 * to serving one of the Five Elementals of Calia.
 *
 * Created by Jaacar, January 2017
 * Modified to properly execute dicharge/expel - Mirandus - 2020
 */

#pragma save_binary

#include <ss_types.h>
#include <macros.h>
#include <files.h>
#include "../defs.h"

inherit "/std/guild/guild_occ_sh";

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Defines
#define CHILD_TITLES  \
          ({ "Novitiate of the Elementals", \
             "Student of Vision", \
             "Neophyte of Insight", \
             "Aspirant of Enlightenment", \
             "Eidolon of Transcendence" })

#define MASTER_FIRE_MALE_TITLE_DEFAULTS \
          ({ "Initiate of Fire", \
          	 "Servant of Fire", \
          	 "Agent of Fire", \
          	 "Bearer of Fire", \
          	 "Master of Fire" })

#define MASTER_FIRE_FEMALE_TITLE_DEFAULTS \
          ({ "Initiate of Fire", \
          	 "Servant of Fire", \
          	 "Agent of Fire", \
          	 "Bearer of Fire", \
          	 "Mistress of Fire" })
          	 
#define MASTER_AIR_MALE_TITLE_DEFAULTS \
          ({ "Initiate of Air", \
          	 "Servant of Air", \
          	 "Agent of Air", \
          	 "Bearer of Air", \
          	 "Master of Air" })

#define MASTER_AIR_FEMALE_TITLE_DEFAULTS \
          ({ "Initiate of Air", \
          	 "Servant of Air", \
          	 "Agent of Air", \
          	 "Bearer of Air", \
          	 "Mistress of Air" })

#define MASTER_WATER_MALE_TITLE_DEFAULTS \
          ({ "Initiate of Water", \
          	 "Servant of Water", \
          	 "Agent of Water", \
          	 "Bearer of Water", \
          	 "Master of Water" })

#define MASTER_WATER_FEMALE_TITLE_DEFAULTS \
          ({ "Initiate of Water", \
          	 "Servant of Water", \
          	 "Agent of Water", \
          	 "Bearer of Water", \
          	 "Mistress of Water" })

#define MASTER_EARTH_MALE_TITLE_DEFAULTS \
          ({ "Initiate of Earth", \
          	 "Servant of Earth", \
          	 "Agent of Earth", \
          	 "Bearer of Earth", \
          	 "Master of Earth" })

#define MASTER_EARTH_FEMALE_TITLE_DEFAULTS \
          ({ "Initiate of Earth", \
          	 "Servant of Earth", \
          	 "Agent of Earth", \
          	 "Bearer of Earth", \
          	 "Mistress of Earth" })

#define MASTER_SPIRIT_MALE_TITLE_DEFAULTS \
          ({ "Initiate of Spirit", \
          	 "Servant of Spirit", \
          	 "Agent of Spirit", \
          	 "Bearer of Spirit", \
          	 "Master of Spirit" })

#define MASTER_SPIRIT_FEMALE_TITLE_DEFAULTS \
          ({ "Initiate of Spirit", \
          	 "Servant of Spirit", \
          	 "Agent of Spirit", \
          	 "Bearer of Spirit", \
          	 "Mistress of Spirit" })

#define DEFAULT_ELDER_FIRE_TITLE   ({ "Erudite of Flame" })
#define DEFAULT_ELDER_AIR_TITLE    ({ "Essence of Storms" })
#define DEFAULT_ELDER_WATER_TITLE  ({ "Apotheosis of the Deep" })
#define DEFAULT_ELDER_EARTH_TITLE  ({ "Sage of Tremors" })
#define DEFAULT_ELDER_SPIRIT_TITLE ({ "Synthesis of Eternity" })

#define EVENT_LOG (ELEMENTALIST_LOGS + "events")
#define GUILD_MANAGER_TEST (ELEMENTALIST_LIBS + "guild_manager_test")

// Prototypes
public void     initialize_occ_cleric();
public object   query_top_shadow();
public void     notify_arrival(object player);
public void     notify_departure(object player);

// Global Variables
static string * CHILD_ADJS = 
    ({ "Unproven","Fledgling","Promising",
       "Gifted","Accomplished","Learned" }); 
          	                                
static string * MASTER_FIRE_ADJS = 
    ({ "Flickering","Burning","Blazing",
       "Radiant","Luminous","Vibrant", 
       "Raging","Intense","Glorious" });
          	                           
static string * MASTER_AIR_ADJS = 
    ({ "Unpredictable","Fanning","Whirling",
       "Strong","Forcible","Howling", 
       "Thundering","Intense","Quintessant" });          	                                        

static string * MASTER_WATER_ADJS = 
    ({ "Gentle","Nurturing","Thoughtful",
       "Flowing","Restless","Churning", 
       "Raging","Crashing","Fathomless" });

static string * MASTER_EARTH_ADJS = 
    ({ "Solid","Intense","Shining",
       "Strong","Powerful","Volcanic", 
       "Unmoving","Eternal","Sacred" });

static string * MASTER_SPIRIT_ADJS = 
    ({ "Opaque","Translucent","Crystalline",
       "Vibrant","Reverent","Divine", 
       "Intrinsic","Ethereal","Immortal" });

static string * MASTER_NOUN_1S = 
    ({ "Servant","Agent","Bearer",
	   "Master","Mistress","Minister",
	   "Missioner","Principal","Envoy",
	   "Abbetor","Bringer","Preceptor",
	   "Ambassador" });

static string * MASTER_FIRE_NOUN_2S = 
    ({ "Fire","Fires",
	   "t-Fire","t-Fires",
	   "Flame","Flames",
	   "t-Flame","t-Flames",
	   "Blaze","t-Blaze",
	   "Pyre","Pyres",
	   "t-Pyre","t-Pyres", 
       "Pyros","L-Pyros" });

static string * MASTER_AIR_NOUN_2S = 
    ({ "Air","t-Air",
	   "Wind","Winds",
	   "t-Wind","t-Winds",
	   "Sky","Skies",
	   "t-Sky","t-Skies",
	   "Storm","Storms",
	   "t-Storm","t-Storms",
	   "Breeze","t-Breeze", 
       "Aeria","L-Aeria" });

static string * MASTER_WATER_NOUN_2S = 
    ({ "Water","Waters",
	   "t-Water","t-Waters",
	   "Rain","Rains",
	   "t-Rain","t-Rains",
	   "Waves","t-Waves",
	   "Sea","Seas",
	   "t-Sea","t-Seas",
	   "Depths","t-Depths", 
       "Diabrecho","L-Diabrecho" });

static string * MASTER_EARTH_NOUN_2S = 
    ({ "Earth","t-Earth",
	   "Sand","Sands",
	   "t-Sand","t-Sands",
	   "Rock","Rocks",
	   "t-Rock","t-Rocks",
	   "Mountain","Mountains",
	   "t-Mountain","t-Mountains",
	   "Foundation","Foundations",
	   "t-Foundation","t-Foundations", 
       "Gu","L-Gu" });

static string * MASTER_SPIRIT_NOUN_2S = 
    ({ "Spirit","Spirits",
	   "t-Spirit","t-Spirits",
	   "Soul","Souls",
	   "t-Soul","t-Souls",
	   "Shadow","Shadows",
	   "t-Shadow","t-Shadows",
	   "Anima","t-Anima",
	   "Umbra","t-Umbra", 
       "Psuchae" });
          	                               
static string * ELDER_NOUN_1S = 
    ({ "Auspex","Avatar","Curate",
	   "Sibyl","Augur","Avatar",
	   "Effigy","Diviner","Epitome",
	   "Paragon","Paradigm" });

static string * ELDER_NOUN_2S = 
    ({ "Apocalypse","t-Apocalypse","Transcendence" });
    
private int gTeamAlarm = 0;	                                           	                               

public string
my_time()
{
    return (ctime(time())[4..9] + ": ");
}
          	                          
public string 
query_guild_style_occ() 
{ 
    return GUILD_STYLE; 
}

public string 
query_guild_name_occ() 
{ 
    return GUILD_EC_NAME; 
}

int 
query_guild_tax_occ() 
{ 
    return GUILD_EC_OCC_TAX; 
}

public string *
query_child_adjs()
{
	return CHILD_ADJS;
}

public string *
query_master_fire_adjs()
{
		return MASTER_FIRE_ADJS;
}

public string *
query_master_air_adjs()
{
		return MASTER_AIR_ADJS;
}

public string *
query_master_water_adjs()
{
		return MASTER_WATER_ADJS;
}

public string *
query_master_earth_adjs()
{
		return MASTER_EARTH_ADJS;
}

public string *
query_master_spirit_adjs()
{
		return MASTER_SPIRIT_ADJS;
}

public string *
query_master_noun_1s()
{
		return MASTER_NOUN_1S;
}

public string *
query_master_fire_noun_2s()
{
		return MASTER_FIRE_NOUN_2S;
}

public string *
query_master_air_noun_2s()
{
		return MASTER_AIR_NOUN_2S;
}

public string *
query_master_water_noun_2s()
{
		return MASTER_WATER_NOUN_2S;
}

public string *
query_master_earth_noun_2s()
{
		return MASTER_EARTH_NOUN_2S;
}

public string *
query_master_spirit_noun_2s()
{
		return MASTER_SPIRIT_NOUN_2S;
}

public string *
query_elder_noun_1s()
{
		return ELDER_NOUN_1S;
}

public string *
query_elder_noun_2s()
{
		return ELDER_NOUN_2S;
}

void
init_occ_shadow(string str)
{
    ::init_occ_shadow(); 

    set_alarm(1.0, 0.0, initialize_occ_cleric);
}

public void
initialize_occ_cleric()
{
    setuid();
    seteuid(getuid());
    
    // Make sure the command soul gets added
    shadow_who->add_cmdsoul(EC_SOUL);
    shadow_who->add_cmdsoul(SPELL_MANAGER_SOUL);

    shadow_who->update_hooks();
    
    // Every caster guild using the new Genesis magic system will
    // use the mana shadow to get the new regeneration rates for mana.
    if (!query_top_shadow()->has_mana_shadow())
    {
        clone_object(MANA_SHADOW)->shadow_me(shadow_who);
    }
    
    shadow_who->catch_tell("\nWelcome, "+query_guild_title_occ()+"!\n\n");
    notify_arrival(shadow_who);
    if (shadow_who->query_stat(SS_OCCUP) > 139)
    {
    	 if (!shadow_who->test_bit("Calia",EC_GURU_GROUP,EC_GURU_BIT))
    	 {
    	 	shadow_who->catch_tell("\n\n\nA vision suddenly enters your "+
    	 	    "mind of a person standing in the Obelisk Garden in "+
    	 	    "elemental form. They reach their hand out and touch "+
    	 	    "an obelisk briefly and then boldly step forward and "+
    	 	    "enter it!\n\nThe vision fades away as quickly as it "+
    	 	    "came.\n\n\n");
    	 }
    }
}

string
query_elemental_cleric_title()
{
    string title = "";
    string adj = "";
    string rank_title = "";
    string council_title = "";
    string special_title = "";
    string player_element = "";
    int gstat, practice_level, personal_conduit, gender;
    
    practice_level = GUILD_MANAGER->query_practice_level(shadow_who);
    player_element = GUILD_MANAGER->query_primary_element(shadow_who);
    personal_conduit = GUILD_MANAGER->query_player_conduit_earned(shadow_who);
    gstat = shadow_who->query_stat(SS_OCCUP);
    
    switch(practice_level)  // Check players practice_level 
                            // and base adj off of that
    {
    	case 0..500:
    		adj = CHILD_ADJS[0];
    		break;
    	case 501..1000:
    		adj = CHILD_ADJS[1];
    		break;
    	case 1001..1500:
    		adj = CHILD_ADJS[2];
    		break;
    	case 1501..2000:
    		adj = CHILD_ADJS[3];
    		break;
    	case 2001..2500:
    		adj = CHILD_ADJS[4];
    		break;
    	case 2501..3000:
    		adj = CHILD_ADJS[5];
    		break;
    	case 3001..8000:
    		switch(player_element)
		    {
		        case "fire":
		            adj = MASTER_FIRE_ADJS[0];
		            break;
		        case "water":
		            adj = MASTER_WATER_ADJS[0];
		            break;
		        case "air":
		            adj = MASTER_AIR_ADJS[0];
		            break;
		        case "earth":
		            adj = MASTER_EARTH_ADJS[0];
		            break;
		        case "life":
		            adj = MASTER_SPIRIT_ADJS[0];
		            break;
		        default:
		        	adj = CHILD_ADJS[5];
		        	break;
		    }
		    break;
		case 8001..13000:
    		switch(player_element)
		    {
		        case "fire":
		            adj = MASTER_FIRE_ADJS[1];
		            break;
		        case "water":
		            adj = MASTER_WATER_ADJS[1];
		            break;
		        case "air":
		            adj = MASTER_AIR_ADJS[1];
		            break;
		        case "earth":
		            adj = MASTER_EARTH_ADJS[1];
		            break;
		        case "life":
		            adj = MASTER_SPIRIT_ADJS[1];
		            break;
		        default:
		        	adj = CHILD_ADJS[5];
		        	break;
		    }
		    break;
		case 13001..18000:
    		switch(player_element)
		    {
		        case "fire":
		            adj = MASTER_FIRE_ADJS[2];
		            break;
		        case "water":
		            adj = MASTER_WATER_ADJS[2];
		            break;
		        case "air":
		            adj = MASTER_AIR_ADJS[2];
		            break;
		        case "earth":
		            adj = MASTER_EARTH_ADJS[2];
		            break;
		        case "life":
		            adj = MASTER_SPIRIT_ADJS[2];
		            break;
		        default:
		        	adj = CHILD_ADJS[5];
		        	break;
		    }
		    break;
		case 18001..23000:
    		switch(player_element)
		    {
		        case "fire":
		            adj = MASTER_FIRE_ADJS[3];
		            break;
		        case "water":
		            adj = MASTER_WATER_ADJS[3];
		            break;
		        case "air":
		            adj = MASTER_AIR_ADJS[3];
		            break;
		        case "earth":
		            adj = MASTER_EARTH_ADJS[3];
		            break;
		        case "life":
		            adj = MASTER_SPIRIT_ADJS[3];
		            break;
		        default:
		        	adj = CHILD_ADJS[5];
		        	break;
		    }
		    break;
		case 23001..28000:
    		switch(player_element)
		    {
		        case "fire":
		            adj = MASTER_FIRE_ADJS[4];
		            break;
		        case "water":
		            adj = MASTER_WATER_ADJS[4];
		            break;
		        case "air":
		            adj = MASTER_AIR_ADJS[4];
		            break;
		        case "earth":
		            adj = MASTER_EARTH_ADJS[4];
		            break;
		        case "life":
		            adj = MASTER_SPIRIT_ADJS[4];
		            break;
		        default:
		        	adj = CHILD_ADJS[5];
		        	break;
		    }
		    break;
		case 28001..43000:
    		switch(player_element)
		    {
		        case "fire":
		            adj = MASTER_FIRE_ADJS[5];
		            break;
		        case "water":
		            adj = MASTER_WATER_ADJS[5];
		            break;
		        case "air":
		            adj = MASTER_AIR_ADJS[5];
		            break;
		        case "earth":
		            adj = MASTER_EARTH_ADJS[5];
		            break;
		        case "life":
		            adj = MASTER_SPIRIT_ADJS[5];
		            break;
		        default:
		        	adj = CHILD_ADJS[5];
		        	break;
		    }
		    break;
		case 43001..58000:
    		switch(player_element)
		    {
		        case "fire":
		            adj = MASTER_FIRE_ADJS[6];
		            break;
		        case "water":
		            adj = MASTER_WATER_ADJS[6];
		            break;
		        case "air":
		            adj = MASTER_AIR_ADJS[6];
		            break;
		        case "earth":
		            adj = MASTER_EARTH_ADJS[6];
		            break;
		        case "life":
		            adj = MASTER_SPIRIT_ADJS[6];
		            break;
		        default:
		        	adj = CHILD_ADJS[5];
		        	break;
		    }
		    break;
		case 58001..73000:
    		switch(player_element)
		    {
		        case "fire":
		            adj = MASTER_FIRE_ADJS[7];
		            break;
		        case "water":
		            adj = MASTER_WATER_ADJS[7];
		            break;
		        case "air":
		            adj = MASTER_AIR_ADJS[7];
		            break;
		        case "earth":
		            adj = MASTER_EARTH_ADJS[7];
		            break;
		        case "life":
		            adj = MASTER_SPIRIT_ADJS[7];
		            break;
		        default:
		        	adj = CHILD_ADJS[5];
		        	break;
		    }
		    break;
		case 73001..MAX_PRACTICE_LEVEL:
    		switch(player_element)
		    {
		        case "fire":
		            adj = MASTER_FIRE_ADJS[8];
		            break;
		        case "water":
		            adj = MASTER_WATER_ADJS[8];
		            break;
		        case "air":
		            adj = MASTER_AIR_ADJS[8];
		            break;
		        case "earth":
		            adj = MASTER_EARTH_ADJS[8];
		            break;
		        case "life":
		            adj = MASTER_SPIRIT_ADJS[8];
		            break;
		        default:
		        	adj = CHILD_ADJS[5];
		        	break;
		    }
		    break;		    
    }

    if (GUILD_MANAGER->query_is_elder_cleric(shadow_who))
    {   	
    	switch(player_element)  
	    { 
	    	case "fire":
	    		rank_title = DEFAULT_ELDER_FIRE_TITLE[0];
	    		break;
	    	case "water":
	    		rank_title = DEFAULT_ELDER_WATER_TITLE[0];
	    		break;
	    	case "air":
	    		rank_title = DEFAULT_ELDER_AIR_TITLE[0];
	    		break;
	    	case "earth":
	    		rank_title = DEFAULT_ELDER_EARTH_TITLE[0];
	    		break;
	    	default:
	    		rank_title = DEFAULT_ELDER_SPIRIT_TITLE[0];
	    		break;
	    }
        title = adj + " " + rank_title;
        return title;
    }
    
    if (GUILD_MANAGER->query_is_full_master(shadow_who))
    {   	
    	switch(player_element)  
	    { 
	    	case "fire":
	    		switch(gender)
    			{
    				case 1:
    					rank_title = MASTER_FIRE_FEMALE_TITLE_DEFAULTS[4];
    					break;
    				default:
    					rank_title = MASTER_FIRE_MALE_TITLE_DEFAULTS[4];
    					break;
    			}
	    		break;
	    	case "water":
	    		switch(gender)
    			{
    				case 1:
    					rank_title = MASTER_WATER_FEMALE_TITLE_DEFAULTS[4];
    					break;
    				default:
    					rank_title = MASTER_WATER_MALE_TITLE_DEFAULTS[4];
    					break;
    			}
	    		break;
	    	case "air":
	    		switch(gender)
    			{
    				case 1:
    					rank_title = MASTER_AIR_FEMALE_TITLE_DEFAULTS[4];
    					break;
    				default:
    					rank_title = MASTER_AIR_MALE_TITLE_DEFAULTS[4];
    					break;
    			}
	    		break;
	    	case "earth":
	    		switch(gender)
    			{
    				case 1:
    					rank_title = MASTER_EARTH_FEMALE_TITLE_DEFAULTS[4];
    					break;
    				default:
    					rank_title = MASTER_EARTH_MALE_TITLE_DEFAULTS[4];
    					break;
    			}
	    		break;
	    	default:
	    		switch(gender)
    			{
    				case 1:
    					rank_title = MASTER_SPIRIT_FEMALE_TITLE_DEFAULTS[4];
    					break;
    				default:
    					rank_title = MASTER_SPIRIT_MALE_TITLE_DEFAULTS[4];
    					break;
    			}
	    		break;
	    }
        title = adj + " " + rank_title;
        return title;
    }
    
    if (GUILD_MANAGER->query_is_child_cleric(shadow_who))
    {
    	// First factor in rank_title is occupational guild stat
    	// Second factor in rank_title is personal conduit score
    	
    	switch(gstat)  
    	{              
    		case 0..18:  // First rank as a Child
    			rank_title = CHILD_TITLES[0];
    			break;
    		case 19..35:  // Second rank as a Child
    			switch(personal_conduit)
    			{
    				case 0..500:  // Personal Conduit is only at first 
    					          // rank level
    					rank_title = CHILD_TITLES[0];
    					break;
    				default:  // Personal Conduit is at least where 
    					      // it should be
    					rank_title = CHILD_TITLES[1];
    					break;
    			}
    			break;
    		case 36..50:  // Third rank as a Child
    			switch(personal_conduit)
    			{
    				case 0..500:  // Personal Conduit is only at first 
    					          // rank level
    					rank_title = CHILD_TITLES[0];
    					break;
    				case 501..1000:  // Personal Conduit is only at 
    					             // second rank level
    					rank_title = CHILD_TITLES[1];
    					break;
    				default:  // Personal Conduit is at least where 
    					      // it should be
    					rank_title = CHILD_TITLES[2];
    					break;
    			}
    			break;
    		case 51..75:  // Fourth rank as a Child
    			switch(personal_conduit)
    			{
    				case 0..500:  // Personal Conduit is only at first 
    					          // rank level
    					rank_title = CHILD_TITLES[0];
    					break;
    				case 501..1000:  // Personal Conduit is only at 
    					             // second rank level
    					rank_title = CHILD_TITLES[1];
    					break;
    				case 1001..1500:  // Personal Conduit is only at 
    					              // third rank level
    					rank_title = CHILD_TITLES[2];
    					break;
    				default:  // Personal Conduit is at least where 
    					      // it should be
    					rank_title = CHILD_TITLES[3];
    					break;
    			}
    			break;
    		default:  // Last rank as a Child
    			switch(personal_conduit)
    			{
    				case 0..500:  // Personal Conduit is only at first 
    					          // rank level
    					rank_title = CHILD_TITLES[0];
    					break;
    				case 501..1000:  // Personal Conduit is only at 
    					             // second rank level
    					rank_title = CHILD_TITLES[1];
    					break;
    				case 1001..1500:  // Personal Conduit is only at 
    					              // third rank level
    					rank_title = CHILD_TITLES[2];
    					break;
    				case 1501..2000:  // Personal Conduit is only at 
    					              // fourth rank level
    					rank_title = CHILD_TITLES[3];
    					break;
    				default:  // Personal Conduit is at least where it 
    					      // should be
    					rank_title = CHILD_TITLES[4];
    					break;
    			}
    		break;
    	}
        title = adj + " " + rank_title;
        return title;
    }
        
    if (GUILD_MANAGER->query_is_master_cleric(shadow_who))
    {
    	// First factor in rank_title is occupational guild stat
    	// Second factor in rank_title is personal conduit score
    	// Third factor in rank_title is gender
    	
    	switch(player_element)  
	    {
	        case "fire":  // Fire Clerics
	        	switch(gstat)
		    	{
		    		case 0..100:  // First rank as a Master
		    			switch(personal_conduit)  //
		    			{  					
		    				default:  // We don't check personal conduit 
		    					      // at this rank because this is 
		    					      // the lowest rank
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_FIRE_FEMALE_TITLE_DEFAULTS[0];
				    					break;
				    				default:
				    					rank_title = MASTER_FIRE_MALE_TITLE_DEFAULTS[0];
				    					break;
				    			}
				    			break;
		    			}
		    			break;		    			
		    		case 101..120:  // Second rank as a Master
		    			switch(personal_conduit)
		    			{
		    				case 0..7500:  // Personal Conduit is lower 
		    					           // than it should be
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_FIRE_FEMALE_TITLE_DEFAULTS[0];
				    					break;
				    				default:
				    					rank_title = MASTER_FIRE_MALE_TITLE_DEFAULTS[0];
				    					break;
				    			}
				    			break;
		    				default:  // Personal Conduit is at least where it should be
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_FIRE_FEMALE_TITLE_DEFAULTS[1];
				    					break;
				    				default:
				    					rank_title = MASTER_FIRE_MALE_TITLE_DEFAULTS[1];
				    					break;
				    			}
				    			break;
		    			}
		    			break;
		    		case 121..140:  // Third rank as a Master
		    			switch(personal_conduit)
		    			{
		    				case 0..7500:  // Personal Conduit is way 
		    					           // lower than it should be
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_FIRE_FEMALE_TITLE_DEFAULTS[0];
				    					break;
				    				default:
				    					rank_title = MASTER_FIRE_MALE_TITLE_DEFAULTS[0];
				    					break;
				    			}
				    			break;
				    		case 7501..12500:  // Personal Conduit is 
				    			               // second Master rank level
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_FIRE_FEMALE_TITLE_DEFAULTS[1];
				    					break;
				    				default:
				    					rank_title = MASTER_FIRE_MALE_TITLE_DEFAULTS[1];
				    					break;
				    			}
				    			break;
		    				default:  // Personal Conduit is at least 
		    					      // where it should be
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_FIRE_FEMALE_TITLE_DEFAULTS[2];
				    					break;
				    				default:
				    					rank_title = MASTER_FIRE_MALE_TITLE_DEFAULTS[2];
				    					break;
				    			}
				    			break;
		    			}
		    			break;
		    		case 141..160:  // Fourth rank as a Master
		    			switch(personal_conduit)
		    			{
		    				case 0..7500:  // Personal Conduit is way 
		    					           // lower than it should be
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_FIRE_FEMALE_TITLE_DEFAULTS[0];
				    					break;
				    				default:
				    					rank_title = MASTER_FIRE_MALE_TITLE_DEFAULTS[0];
				    					break;
				    			}
				    			break;
				    		case 7501..12500:  // Personal Conduit is 
				    			               // second Master rank level
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_FIRE_FEMALE_TITLE_DEFAULTS[1];
				    					break;
				    				default:
				    					rank_title = MASTER_FIRE_MALE_TITLE_DEFAULTS[1];
				    					break;
				    			}
				    			break;
				    		case 12501..17500:  // Personal Conduit is 
				    			                // third Master rank level
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_FIRE_FEMALE_TITLE_DEFAULTS[2];
				    					break;
				    				default:
				    					rank_title = MASTER_FIRE_MALE_TITLE_DEFAULTS[2];
				    					break;
				    			}
				    			break;
		    				default:  // Personal Conduit is at least 
		    					      // where it should be
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_FIRE_FEMALE_TITLE_DEFAULTS[3];
				    					break;
				    				default:
				    					rank_title = MASTER_FIRE_MALE_TITLE_DEFAULTS[3];
				    					break;
				    			}
				    			break;
		    			}
		    			break;
		    		default:  // Fifth rank as a Master
		    			switch(personal_conduit)
		    			{
		    				case 0..7500:  // Personal Conduit is way 
		    					           // lower than it should be
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_FIRE_FEMALE_TITLE_DEFAULTS[0];
				    					break;
				    				default:
				    					rank_title = MASTER_FIRE_MALE_TITLE_DEFAULTS[0];
				    					break;
				    			}
				    			break;
				    		case 7501..12500:  // Personal Conduit is 
				    			               // second Master rank level
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_FIRE_FEMALE_TITLE_DEFAULTS[1];
				    					break;
				    				default:
				    					rank_title = MASTER_FIRE_MALE_TITLE_DEFAULTS[1];
				    					break;
				    			}
				    			break;
				    		case 12501..17500:  // Personal Conduit is 
				    			                // third Master rank level
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_FIRE_FEMALE_TITLE_DEFAULTS[2];
				    					break;
				    				default:
				    					rank_title = MASTER_FIRE_MALE_TITLE_DEFAULTS[2];
				    					break;
				    			}
				    			break;
				    		case 17501..22500:  // Personal Conduit is 
				    			                // fourth Master rank level
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_FIRE_FEMALE_TITLE_DEFAULTS[3];
				    					break;
				    				default:
				    					rank_title = MASTER_FIRE_MALE_TITLE_DEFAULTS[3];
				    					break;
				    			}
				    			break;
		    				default:  // Personal Conduit is at least where 
		    					      // it should be
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_FIRE_FEMALE_TITLE_DEFAULTS[4];
				    					break;
				    				default:
				    					rank_title = MASTER_FIRE_MALE_TITLE_DEFAULTS[4];
				    					break;
				    			}
				    			break;
		    			}
		    			break;    		
		    	}
	            break;
	        case "water":  // Water Clerics
	        	switch(gstat)
		    	{
		    		case 0..100:  // First rank as a Master
		    			switch(personal_conduit)  //
		    			{  					
		    				default:  // We don't check personal conduit 
		    					      // at this rank because this is 
		    					      // the lowest rank
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_WATER_FEMALE_TITLE_DEFAULTS[0];
				    					break;
				    				default:
				    					rank_title = MASTER_WATER_MALE_TITLE_DEFAULTS[0];
				    					break;
				    			}
				    			break;
		    			}
		    			break;		    			
		    		case 101..120:  // Second rank as a Master
		    			switch(personal_conduit)
		    			{
		    				case 0..7500:  // Personal Conduit is lower 
		    					           // than it should be
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_WATER_FEMALE_TITLE_DEFAULTS[0];
				    					break;
				    				default:
				    					rank_title = MASTER_WATER_MALE_TITLE_DEFAULTS[0];
				    					break;
				    			}
				    			break;
		    				default:  // Personal Conduit is at least 
		    					      // where it should be
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_WATER_FEMALE_TITLE_DEFAULTS[1];
				    					break;
				    				default:
				    					rank_title = MASTER_WATER_MALE_TITLE_DEFAULTS[1];
				    					break;
				    			}
				    			break;
		    			}
		    			break;
		    		case 121..140:  // Third rank as a Master
		    			switch(personal_conduit)
		    			{
		    				case 0..7500:  // Personal Conduit is way lower 
		    					           // than it should be
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_WATER_FEMALE_TITLE_DEFAULTS[0];
				    					break;
				    				default:
				    					rank_title = MASTER_WATER_MALE_TITLE_DEFAULTS[0];
				    					break;
				    			}
				    			break;
				    		case 7501..12500:  // Personal Conduit is second 
				    			               // Master rank level
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_WATER_FEMALE_TITLE_DEFAULTS[1];
				    					break;
				    				default:
				    					rank_title = MASTER_WATER_MALE_TITLE_DEFAULTS[1];
				    					break;
				    			}
				    			break;
		    				default:  // Personal Conduit is at least where 
		    					      // it should be
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_WATER_FEMALE_TITLE_DEFAULTS[2];
				    					break;
				    				default:
				    					rank_title = MASTER_WATER_MALE_TITLE_DEFAULTS[2];
				    					break;
				    			}
				    			break;
		    			}
		    			break;
		    		case 141..160:  // Fourth rank as a Master
		    			switch(personal_conduit)
		    			{
		    				case 0..7500:  // Personal Conduit is way lower 
		    					           // than it should be
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_WATER_FEMALE_TITLE_DEFAULTS[0];
				    					break;
				    				default:
				    					rank_title = MASTER_WATER_MALE_TITLE_DEFAULTS[0];
				    					break;
				    			}
				    			break;
				    		case 7501..12500:  // Personal Conduit is second
				    			               // Master rank level
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_WATER_FEMALE_TITLE_DEFAULTS[1];
				    					break;
				    				default:
				    					rank_title = MASTER_WATER_MALE_TITLE_DEFAULTS[1];
				    					break;
				    			}
				    			break;
				    		case 12501..17500:  // Personal Conduit is third
				    			                //  Master rank level
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_WATER_FEMALE_TITLE_DEFAULTS[2];
				    					break;
				    				default:
				    					rank_title = MASTER_WATER_MALE_TITLE_DEFAULTS[2];
				    					break;
				    			}
				    			break;
		    				default:  // Personal Conduit is at least where
		    					      // it should be
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_WATER_FEMALE_TITLE_DEFAULTS[3];
				    					break;
				    				default:
				    					rank_title = MASTER_WATER_MALE_TITLE_DEFAULTS[3];
				    					break;
				    			}
				    			break;
		    			}
		    			break;
		    		default:  // Fifth rank as a Master
		    			switch(personal_conduit)
		    			{
		    				case 0..7500:  // Personal Conduit is way lower
		    							   // than it should be
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_WATER_FEMALE_TITLE_DEFAULTS[0];
				    					break;
				    				default:
				    					rank_title = MASTER_WATER_MALE_TITLE_DEFAULTS[0];
				    					break;
				    			}
				    			break;
				    		case 7501..12500:  // Personal Conduit is second
				    			               //  Master rank level
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_WATER_FEMALE_TITLE_DEFAULTS[1];
				    					break;
				    				default:
				    					rank_title = MASTER_WATER_MALE_TITLE_DEFAULTS[1];
				    					break;
				    			}
				    			break;
				    		case 12501..17500:  // Personal Conduit is third
				    			                // Master rank level
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_WATER_FEMALE_TITLE_DEFAULTS[2];
				    					break;
				    				default:
				    					rank_title = MASTER_WATER_MALE_TITLE_DEFAULTS[2];
				    					break;
				    			}
				    			break;
				    		case 17501..22500:  // Personal Conduit is fourth
				    			                // Master rank level
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_WATER_FEMALE_TITLE_DEFAULTS[3];
				    					break;
				    				default:
				    					rank_title = MASTER_WATER_MALE_TITLE_DEFAULTS[3];
				    					break;
				    			}
				    			break;
		    				default:  // Personal Conduit is at least where
		    					      // it should be
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_WATER_FEMALE_TITLE_DEFAULTS[4];
				    					break;
				    				default:
				    					rank_title = MASTER_WATER_MALE_TITLE_DEFAULTS[4];
				    					break;
				    			}
				    			break;
		    			}
		    			break;    		
		    	}
	            break;
	        case "air":  // Air Clerics
	        	switch(gstat)
		    	{
		    		case 0..100:  // First rank as a Master
		    			switch(personal_conduit)  //
		    			{  					
		    				default:  // We don't check personal conduit
		    					      // at this rank because this is the
		    					      // lowest rank
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_AIR_FEMALE_TITLE_DEFAULTS[0];
				    					break;
				    				default:
				    					rank_title = MASTER_AIR_MALE_TITLE_DEFAULTS[0];
				    					break;
				    			}
				    			break;
		    			}
		    			break;		    			
		    		case 101..120:  // Second rank as a Master
		    			switch(personal_conduit)
		    			{
		    				case 0..7500:  // Personal Conduit is lower than
		    					           // it should be
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_AIR_FEMALE_TITLE_DEFAULTS[0];
				    					break;
				    				default:
				    					rank_title = MASTER_AIR_MALE_TITLE_DEFAULTS[0];
				    					break;
				    			}
				    			break;
		    				default:  // Personal Conduit is at least where
		    					      // it should be
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_AIR_FEMALE_TITLE_DEFAULTS[1];
				    					break;
				    				default:
				    					rank_title = MASTER_AIR_MALE_TITLE_DEFAULTS[1];
				    					break;
				    			}
				    			break;
		    			}
		    			break;
		    		case 121..140:  // Third rank as a Master
		    			switch(personal_conduit)
		    			{
		    				case 0..7500:  // Personal Conduit is way lower
		    					           // than it should be
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_AIR_FEMALE_TITLE_DEFAULTS[0];
				    					break;
				    				default:
				    					rank_title = MASTER_AIR_MALE_TITLE_DEFAULTS[0];
				    					break;
				    			}
				    			break;
				    		case 7501..12500:  // Personal Conduit is second
				    			               // Master rank level
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_AIR_FEMALE_TITLE_DEFAULTS[1];
				    					break;
				    				default:
				    					rank_title = MASTER_AIR_MALE_TITLE_DEFAULTS[1];
				    					break;
				    			}
				    			break;
		    				default:  // Personal Conduit is at least where
		    					      // it should be
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_AIR_FEMALE_TITLE_DEFAULTS[2];
				    					break;
				    				default:
				    					rank_title = MASTER_AIR_MALE_TITLE_DEFAULTS[2];
				    					break;
				    			}
				    			break;
		    			}
		    			break;
		    		case 141..160:  // Fourth rank as a Master
		    			switch(personal_conduit)
		    			{
		    				case 0..7500:  // Personal Conduit is way lower
		    					           // than it should be
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_AIR_FEMALE_TITLE_DEFAULTS[0];
				    					break;
				    				default:
				    					rank_title = MASTER_AIR_MALE_TITLE_DEFAULTS[0];
				    					break;
				    			}
				    			break;
				    		case 7501..12500:  // Personal Conduit is second
				    			               // Master rank level
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_AIR_FEMALE_TITLE_DEFAULTS[1];
				    					break;
				    				default:
				    					rank_title = MASTER_AIR_MALE_TITLE_DEFAULTS[1];
				    					break;
				    			}
				    			break;
				    		case 12501..17500:  // Personal Conduit is third
				    			                // Master rank level
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_AIR_FEMALE_TITLE_DEFAULTS[2];
				    					break;
				    				default:
				    					rank_title = MASTER_AIR_MALE_TITLE_DEFAULTS[2];
				    					break;
				    			}
				    			break;
		    				default:  // Personal Conduit is at least where
		    					      // it should be
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_AIR_FEMALE_TITLE_DEFAULTS[3];
				    					break;
				    				default:
				    					rank_title = MASTER_AIR_MALE_TITLE_DEFAULTS[3];
				    					break;
				    			}
				    			break;
		    			}
		    			break;
		    		default:  // Fifth rank as a Master
		    			switch(personal_conduit)
		    			{
		    				case 0..7500:  // Personal Conduit is way lower
		    					           // than it should be
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_AIR_FEMALE_TITLE_DEFAULTS[0];
				    					break;
				    				default:
				    					rank_title = MASTER_AIR_MALE_TITLE_DEFAULTS[0];
				    					break;
				    			}
				    			break;
				    		case 7501..12500:  // Personal Conduit is second
				    			               // Master rank level
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_AIR_FEMALE_TITLE_DEFAULTS[1];
				    					break;
				    				default:
				    					rank_title = MASTER_AIR_MALE_TITLE_DEFAULTS[1];
				    					break;
				    			}
				    			break;
				    		case 12501..17500:  // Personal Conduit is third
				    			                // Master rank level
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_AIR_FEMALE_TITLE_DEFAULTS[2];
				    					break;
				    				default:
				    					rank_title = MASTER_AIR_MALE_TITLE_DEFAULTS[2];
				    					break;
				    			}
				    			break;
				    		case 17501..22500:  // Personal Conduit is fourth
				    			                // Master rank level
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_AIR_FEMALE_TITLE_DEFAULTS[3];
				    					break;
				    				default:
				    					rank_title = MASTER_AIR_MALE_TITLE_DEFAULTS[3];
				    					break;
				    			}
				    			break;
		    				default:  // Personal Conduit is at least where
		    					      // it should be
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_AIR_FEMALE_TITLE_DEFAULTS[4];
				    					break;
				    				default:
				    					rank_title = MASTER_AIR_MALE_TITLE_DEFAULTS[4];
				    					break;
				    			}
				    			break;
		    			}
		    			break;    		
		    	}
	            break;
	        case "earth":  // Earth Clerics
	        	switch(gstat)
		    	{
		    		case 0..100:  // First rank as a Master
		    			switch(personal_conduit)  //
		    			{  					
		    				default:  // We don't check personal conduit at
		    					      // this rank because this is the
		    					      // lowest rank
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_EARTH_FEMALE_TITLE_DEFAULTS[0];
				    					break;
				    				default:
				    					rank_title = MASTER_EARTH_MALE_TITLE_DEFAULTS[0];
				    					break;
				    			}
				    			break;
		    			}
		    			break;		    			
		    		case 101..120:  // Second rank as a Master
		    			switch(personal_conduit)
		    			{
		    				case 0..7500:  // Personal Conduit is lower than
		    					           // it should be
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_EARTH_FEMALE_TITLE_DEFAULTS[0];
				    					break;
				    				default:
				    					rank_title = MASTER_EARTH_MALE_TITLE_DEFAULTS[0];
				    					break;
				    			}
				    			break;
		    				default:  // Personal Conduit is at least where
		    					      // it should be
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_EARTH_FEMALE_TITLE_DEFAULTS[1];
				    					break;
				    				default:
				    					rank_title = MASTER_EARTH_MALE_TITLE_DEFAULTS[1];
				    					break;
				    			}
				    			break;
		    			}
		    			break;
		    		case 121..140:  // Third rank as a Master
		    			switch(personal_conduit)
		    			{
		    				case 0..7500:  // Personal Conduit is way lower
		    					           // than it should be
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_EARTH_FEMALE_TITLE_DEFAULTS[0];
				    					break;
				    				default:
				    					rank_title = MASTER_EARTH_MALE_TITLE_DEFAULTS[0];
				    					break;
				    			}
				    			break;
				    		case 7501..12500:  // Personal Conduit is second
				    			               // Master rank level
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_EARTH_FEMALE_TITLE_DEFAULTS[1];
				    					break;
				    				default:
				    					rank_title = MASTER_EARTH_MALE_TITLE_DEFAULTS[1];
				    					break;
				    			}
				    			break;
		    				default:  // Personal Conduit is at least where
		    					      // it should be
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_EARTH_FEMALE_TITLE_DEFAULTS[2];
				    					break;
				    				default:
				    					rank_title = MASTER_EARTH_MALE_TITLE_DEFAULTS[2];
				    					break;
				    			}
				    			break;
		    			}
		    			break;
		    		case 141..160:  // Fourth rank as a Master
		    			switch(personal_conduit)
		    			{
		    				case 0..7500:  // Personal Conduit is way lower
		    					           // than it should be
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_EARTH_FEMALE_TITLE_DEFAULTS[0];
				    					break;
				    				default:
				    					rank_title = MASTER_EARTH_MALE_TITLE_DEFAULTS[0];
				    					break;
				    			}
				    			break;
				    		case 7501..12500:  // Personal Conduit is second
				    			               // Master rank level
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_EARTH_FEMALE_TITLE_DEFAULTS[1];
				    					break;
				    				default:
				    					rank_title = MASTER_EARTH_MALE_TITLE_DEFAULTS[1];
				    					break;
				    			}
				    			break;
				    		case 12501..17500:  // Personal Conduit is third
				    			                // Master rank level
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_EARTH_FEMALE_TITLE_DEFAULTS[2];
				    					break;
				    				default:
				    					rank_title = MASTER_EARTH_MALE_TITLE_DEFAULTS[2];
				    					break;
				    			}
				    			break;
		    				default:  // Personal Conduit is at least where
		    					      // it should be
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_EARTH_FEMALE_TITLE_DEFAULTS[3];
				    					break;
				    				default:
				    					rank_title = MASTER_EARTH_MALE_TITLE_DEFAULTS[3];
				    					break;
				    			}
				    			break;
		    			}
		    			break;
		    		default:  // Fifth rank as a Master
		    			switch(personal_conduit)
		    			{
		    				case 0..7500:  // Personal Conduit is way lower
		    					           // than it should be
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_EARTH_FEMALE_TITLE_DEFAULTS[0];
				    					break;
				    				default:
				    					rank_title = MASTER_EARTH_MALE_TITLE_DEFAULTS[0];
				    					break;
				    			}
				    			break;
				    		case 7501..12500:  // Personal Conduit is second
				    			               // Master rank level
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_EARTH_FEMALE_TITLE_DEFAULTS[1];
				    					break;
				    				default:
				    					rank_title = MASTER_EARTH_MALE_TITLE_DEFAULTS[1];
				    					break;
				    			}
				    			break;
				    		case 12501..17500:  // Personal Conduit is third
				    			                // Master rank level
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_EARTH_FEMALE_TITLE_DEFAULTS[2];
				    					break;
				    				default:
				    					rank_title = MASTER_EARTH_MALE_TITLE_DEFAULTS[2];
				    					break;
				    			}
				    			break;
				    		case 17501..22500:  // Personal Conduit is fourth
				    			                // Master rank level
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_EARTH_FEMALE_TITLE_DEFAULTS[3];
				    					break;
				    				default:
				    					rank_title = MASTER_EARTH_MALE_TITLE_DEFAULTS[3];
				    					break;
				    			}
				    			break;
		    				default:  // Personal Conduit is at least where
		    					      // it should be
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_EARTH_FEMALE_TITLE_DEFAULTS[4];
				    					break;
				    				default:
				    					rank_title = MASTER_EARTH_MALE_TITLE_DEFAULTS[4];
				    					break;
				    			}
				    			break;
		    			}
		    			break;    		
		    	}
	            break;
	        case "life":  // Spirit Clerics
	        	switch(gstat)
		    	{
		    		case 0..100:  // First rank as a Master
		    			switch(personal_conduit)  //
		    			{  					
		    				default:  // We don't check personal conduit at
		    					      // this rank because this is the
		    					      // lowest rank
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_SPIRIT_FEMALE_TITLE_DEFAULTS[0];
				    					break;
				    				default:
				    					rank_title = MASTER_SPIRIT_MALE_TITLE_DEFAULTS[0];
				    					break;
				    			}
				    			break;
		    			}
		    			break;		    			
		    		case 101..120:  // Second rank as a Master
		    			switch(personal_conduit)
		    			{
		    				case 0..7500:  // Personal Conduit is lower than
		    					           // it should be
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_SPIRIT_FEMALE_TITLE_DEFAULTS[0];
				    					break;
				    				default:
				    					rank_title = MASTER_SPIRIT_MALE_TITLE_DEFAULTS[0];
				    					break;
				    			}
				    			break;
		    				default:  // Personal Conduit is at least where
		    					      // it should be
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_SPIRIT_FEMALE_TITLE_DEFAULTS[1];
				    					break;
				    				default:
				    					rank_title = MASTER_SPIRIT_MALE_TITLE_DEFAULTS[1];
				    					break;
				    			}
				    			break;
		    			}
		    			break;
		    		case 121..140:  // Third rank as a Master
		    			switch(personal_conduit)
		    			{
		    				case 0..7500:  // Personal Conduit is way lower
		    					           // than it should be
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_SPIRIT_FEMALE_TITLE_DEFAULTS[0];
				    					break;
				    				default:
				    					rank_title = MASTER_SPIRIT_MALE_TITLE_DEFAULTS[0];
				    					break;
				    			}
				    			break;
				    		case 7501..12500:  // Personal Conduit is second
				    			               // Master rank level
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_SPIRIT_FEMALE_TITLE_DEFAULTS[1];
				    					break;
				    				default:
				    					rank_title = MASTER_SPIRIT_MALE_TITLE_DEFAULTS[1];
				    					break;
				    			}
				    			break;
		    				default:  // Personal Conduit is at least where
		    					      // it should be
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_SPIRIT_FEMALE_TITLE_DEFAULTS[2];
				    					break;
				    				default:
				    					rank_title = MASTER_SPIRIT_MALE_TITLE_DEFAULTS[2];
				    					break;
				    			}
				    			break;
		    			}
		    			break;
		    		case 141..160:  // Fourth rank as a Master
		    			switch(personal_conduit)
		    			{
		    				case 0..7500:  // Personal Conduit is way lower
		    					           // than it should be
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_SPIRIT_FEMALE_TITLE_DEFAULTS[0];
				    					break;
				    				default:
				    					rank_title = MASTER_SPIRIT_MALE_TITLE_DEFAULTS[0];
				    					break;
				    			}
				    			break;
				    		case 7501..12500:  // Personal Conduit is second
				    			               // Master rank level
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_SPIRIT_FEMALE_TITLE_DEFAULTS[1];
				    					break;
				    				default:
				    					rank_title = MASTER_SPIRIT_MALE_TITLE_DEFAULTS[1];
				    					break;
				    			}
				    			break;
				    		case 12501..17500:  // Personal Conduit is third
				    			                // Master rank level
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_SPIRIT_FEMALE_TITLE_DEFAULTS[2];
				    					break;
				    				default:
				    					rank_title = MASTER_SPIRIT_MALE_TITLE_DEFAULTS[2];
				    					break;
				    			}
				    			break;
		    				default:  // Personal Conduit is at least where
		    					      // it should be
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_SPIRIT_FEMALE_TITLE_DEFAULTS[3];
				    					break;
				    				default:
				    					rank_title = MASTER_SPIRIT_MALE_TITLE_DEFAULTS[3];
				    					break;
				    			}
				    			break;
		    			}
		    			break;
		    		default:  // Fifth rank as a Master
		    			switch(personal_conduit)
		    			{
		    				case 0..7500:  // Personal Conduit is way lower
		    					           // than it should be
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_SPIRIT_FEMALE_TITLE_DEFAULTS[0];
				    					break;
				    				default:
				    					rank_title = MASTER_SPIRIT_MALE_TITLE_DEFAULTS[0];
				    					break;
				    			}
				    			break;
				    		case 7501..12500:  // Personal Conduit is second
				    			               // Master rank level
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_SPIRIT_FEMALE_TITLE_DEFAULTS[1];
				    					break;
				    				default:
				    					rank_title = MASTER_SPIRIT_MALE_TITLE_DEFAULTS[1];
				    					break;
				    			}
				    			break;
				    		case 12501..17500:  // Personal Conduit is third
				    			                // Master rank level
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_SPIRIT_FEMALE_TITLE_DEFAULTS[2];
				    					break;
				    				default:
				    					rank_title = MASTER_SPIRIT_MALE_TITLE_DEFAULTS[2];
				    					break;
				    			}
				    			break;
				    		case 17501..22500:  // Personal Conduit is fourth
				    			                // Master rank level
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_SPIRIT_FEMALE_TITLE_DEFAULTS[3];
				    					break;
				    				default:
				    					rank_title = MASTER_SPIRIT_MALE_TITLE_DEFAULTS[3];
				    					break;
				    			}
				    			break;
		    				default:  // Personal Conduit is at least where
		    					      // it should be
		    					switch(gender)
				    			{
				    				case 1:
				    					rank_title = MASTER_SPIRIT_FEMALE_TITLE_DEFAULTS[4];
				    					break;
				    				default:
				    					rank_title = MASTER_SPIRIT_MALE_TITLE_DEFAULTS[4];
				    					break;
				    			}
				    			break;
		    			}
		    			break;    		
		    	}
	            break;
	        default:  // Unchosen branch (new Master Cleric)
	        	rank_title = "Initiate of the Elementals";
	        	break;
	    }
    	
        title = adj + " " + rank_title;
    }       
                
    return title;
}

string
query_guild_title_occ()
{
	// If they are temple banned, replace their title showing 
	// they are banned
	
	if (GUILD_MANAGER->query_is_punish_temple_banned(shadow_who))
	{
		return "Ostracized";
	}
	
	// Have they created their own title? If not, give the default one
    // for their current rank
    if (!GUILD_MANAGER->query_created_own_title(shadow_who))
    {
    	return query_elemental_cleric_title();
    }
    
    if (GUILD_MANAGER->query_is_child_cleric(shadow_who))
    {
    	return query_elemental_cleric_title();
    }
    
    // Return their created title
	if (GUILD_MANAGER->query_created_own_title(shadow_who))
	{
		return (GUILD_MANAGER->query_title_created(shadow_who));
	}   
}

public void
remove_shadow()
{
    // We use the removal of the shadow as a way to ensure that the
    // spells for the command soul are removed.
    EC_SOUL->remove_spells(shadow_who);
    
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

public string
query_guild_trainer_occ()
{
    return ELEMENTALIST_TEMPLE + "ec_practice";
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
          player->catch_tell(sprintf("\n\n%'='|75s\n", "EXPELLED"));
           player->catch_tell(sprintf("\n%=-75s\n\n", "You have been expelled from "
                  + "the Elemental Worshippers guild by the Clerical Council."));
           player->catch_tell(sprintf("%'='|75s\n\n", "")); 
           GUILD_MANAGER->leave_occ_guild(player);
           return 0;
         }
  
    if (GUILD_MANAGER->query_is_guild_discharged(player))
         {
           player->catch_tell(sprintf("\n\n%'='|75s\n", "DISCHARGED"));
           player->catch_tell(sprintf("\n%=-75s\n\n", "You have been discharged from "
                              + "the Elemental Clerics guild by the Clerical Council."));
           player->catch_tell(sprintf("%'='|75s\n\n", "")); 
           GUILD_MANAGER->leave_occ_guild_discharge(player);
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
is_elemental_cleric()
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

    object * members, * clerics, * wizards, * seekers, *scops, * audience;
    
    string name = player->query_real_name();

    members = filter(users(), &->is_elemental_worshipper());
    clerics = filter(users(), &->is_elemental_cleric());
    seekers = filter(users(), &->is_elemental_seeker());
    scops = filter(users(), &->is_spirit_member());
    members -= clerics; // subtract and add to get rid of duplicates
    members += clerics;
    members -= seekers;
    members += seekers;
    members -= scops;
    members += scops;
    members -= ({ player }); // don't notify self.
    
    for (int i=0; i < sizeof(members); i++)
    {
    	if (GUILD_MANAGER->query_stop_all_notifications(members[i]))
    		members -= ({ members[i] });
    	else  if (GUILD_MANAGER->query_stop_cleric_notifications(members[i]))
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
//    return audience;
    return members;
}

public void
notify_arrival(object player)
{
    if (!objectp(player) || !IS_PLAYER_OBJECT(player))
    {
        return;
    }

    string p_element = GUILD_MANAGER->query_primary_element(shadow_who);
    string diety_message;
    
    switch(p_element)
    {
        case "fire":
            diety_message = "The voice of Lord Pyros echoes through your " +
                "mind announcing that ";
            break;
        case "water":
            diety_message = "The voice of Lord Diabrecho echoes through your " +
                "mind announcing that ";
            break;
        case "air":
            diety_message = "The voice of Lady Aeria echoes through your " +
                "mind announcing that ";
            break;
        case "earth":
            diety_message = "The voice of Lady Gu echoes through your " +
                "mind announcing that ";
            break;
        case "life":
            diety_message = "The voice of Psuchae echoes through your " +
                "mind announcing that ";
            break;
        default:
            diety_message = "You sense the stirring of the elements as ";
            break;
    }
     
    object * audience = get_audience_for_notification(player);
    map(audience, &->catch_msg(diety_message + 
    	capitalize(player->query_real_name()) +
        ", "+query_guild_title_occ()+ " has entered the realms.\n"));    
}

public void
notify_departure(object player)
{
    if (!objectp(player) || !IS_PLAYER_OBJECT(player))
    {
        return;
    }
        
    string p_element = GUILD_MANAGER->query_primary_element(shadow_who);
    string diety_message, element;
    
    switch(p_element)
    {
        case "fire":
            diety_message = "The voice of Lord Pyros echoes through your " +
                "mind announcing that ";
            element = "fire";
            break;
        case "water":
            diety_message = "The voice of Lord Diabrecho echoes through "+
                "your mind announcing that ";
            element = "water";
            break;
        case "air":
            diety_message = "The voice of Lady Aeria echoes through your " +
                "mind announcing that ";
            element = "air";
            break;
        case "earth":
            diety_message = "The voice of Lady Gu echoes through your " +
                "mind announcing that ";
            element = "earth";
            break;
        case "life":
            diety_message = "The voice of Psuchae echoes through your " +
                "mind announcing that ";
            element = "shadows";
            break;
        default:
            diety_message = "You sense a calming of the elements as ";
            element = "elements";
            break;
    }
    
    object * audience = get_audience_for_notification(player);
    map(audience, &->catch_msg(diety_message + 
    	capitalize(player->query_real_name()) +
        ", "+query_guild_title_occ()+
        " has retired to " + player->query_possessive() + 
        " bunk, returning to "+
        "the realm of "+element+" and dreams.\n"));   
}

public void
do_die(object killer)
{
    object *members;

    if ((shadow_who->query_hp() > 0) || shadow_who->query_wiz_level() ||
        shadow_who->query_ghost())
    {
        return;
    }

    members = get_audience_for_notification(shadow_who);
    if (!sizeof(members))
    {
        shadow_who->do_die(killer);
        return;
    }
    
    string p_element = GUILD_MANAGER->query_primary_element(shadow_who);
    string diety_message;
    
    switch(p_element)
    {
        case "fire":
            diety_message = "The voice of Lord Pyros echoes through your " +
                "mind announcing that ";
            break;
        case "water":
            diety_message = "The voice of Lord Diabrecho echoes through "+
            	"your mind announcing that ";
            break;
        case "air":
            diety_message = "The voice of Lady Aeria echoes through your " +
                "mind announcing that ";
            break;
        case "earth":
            diety_message = "The voice of Lady Gu echoes through your " +
                "mind announcing that ";
            break;
        case "life":
            diety_message = "The voice of Psuchae echoes through your " +
                "mind announcing that ";
            break;
        default:
            diety_message = "You sense a calming of the elements as ";
            break;
    }
    
    shadow_who->add_prop(LIVE_I_NO_CORPSE,1);
    shadow_who->do_die(killer);
    map(members, &->catch_msg(diety_message + 
    	capitalize(shadow_who->query_real_name())+
        " has just perished.\n"));
    tell_room(environment(shadow_who),QCTNAME(shadow_who)+"'s body "+
        "suddenly blackens and fades into it's own shadow then "+
        "disappears!\n",shadow_who);
}

/* Function name: query_def_post
 * Description:   We change the default post office for our members.
 * Returns:       string - the path to the new postoffice
 */
string
query_def_post() 
{
    return CLERIC_GUILD_POST;
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
	        	string pri_elem, elem_name;
	        	pri_elem = (GUILD_MANAGER->query_primary_element(shadow_who->
	        		query_real_name()));
	        	switch(pri_elem)
	        	{
	        		case "fire":
	        			elem_name = "Lord Pyros";
	        			break;
	        		case "water":
	        			elem_name = "Lord Diabrecho";
	        			break;
	        		case "air":
	        			elem_name = "Lady Aeria";
	        			break;
	        		case "earth":
	        			elem_name = "Lady Gu";
	        			break;
	        		default:
	        			elem_name = "Psuchae";
	        			break;
	        	}
	        	
	            shadow_who->catch_tell("\n"+elem_name+" is angered and " +
	                "will now aid you less with their gifts.\n\n");
	            align = who->query_alignment();
	            align = min(-210, align);
	
	            ran_align = shadow_who->query_alignment();
	            align /= 3;
	            ran_align += align;
	            shadow_who->set_alignment(ran_align);
	            COUNCIL_LOG_BOOK->update_log_book(my_time() + 
	            capitalize(shadow_who->query_real_name()) +
	            " was penalized for teaming with " +
	            capitalize(who->query_real_name()) + ".\n");
	            send_debug_message("cleric", capitalize(shadow_who->
	            	query_real_name()) + " had alignment adjusted by " + 
	            	align + " to " + ran_align + " for teaming with " + 
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
        /* Make them join first so we can get team info. */
        success = shadow_who->set_leader(leader);
        
        /* They couldn't join. Don't do anything else. */
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
