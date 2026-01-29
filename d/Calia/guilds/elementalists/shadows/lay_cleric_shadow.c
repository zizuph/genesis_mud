/* 
 * Elemental Clerics of Calia Layman Guild Shadow
 *
 * This is the layman guild shadow for the Elemental Clerics of Calia. This is
 * a clerical occupational + layman guild. Members of this guild will
 * select one branch to focus on, which equates to serving one of
 * the Five Elementals of Calia.
 *
 * Created by Petros, April 2010
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
 
#define COUNCIL_FIRE_TITLES         ({ "Harbinger of Flames" })
#define COUNCIL_AIR_TITLES 		   ({ "Harbinger of Storms" })
#define COUNCIL_WATER_TITLES 	   ({ "Harbinger of Waves" })
#define COUNCIL_EARTH_TITLES 	   ({ "Harbinger of Tremors" }) 
#define COUNCIL_SPIRIT_TITLES 	   ({ "Harbinger of Shadows" }) 

#define LEADER_TITLE               ({ "Focus of the Elementals" })
#define LUMINARY_TITLE             ({ "Luminary of the Elementals" })
#define ILLUMINATI_TITLE           ({ "Illuminati of the Elementals" })
#define EMISSARY_TITLE             ({ "Emissary of the Elementals" })
#define CULITVATOR_TITLE           ({ "Cultivator of the Elementals" })
#define LIBERATOR_TITLE            ({ "Liberator of the Elementals" })
#define CONSERVATOR_TITLE          ({ "Conservator of the Elementals" })
#define ARCHON_REVELATION_TITLE    ({ "Archon of Revelation" })
#define ARCHON_DELIVERANCE_TITLE   ({ "Archon of Deliverance" })
#define ARCHON_APOTHEOSIS_TITLE    ({ "Archon of Apotheosis" })

// Prototypes
public void     initialize_lay_cleric();
public object   query_top_shadow();

public string 
query_guild_style_lay() 
{ 
    return GUILD_STYLE; 
}

public string 
query_guild_name_lay() 
{ 
    return GUILD_EC_NAME; 
}

public int
query_guild_leader_occ()
{
    string pn;

    pn = shadow_who->query_real_name(); 
    setuid();
    seteuid(getuid()); 

    return (GUILD_MANAGER->query_is_ec_council(pn)); 
}

int 
query_guild_tax_lay() 
{
	if(GUILD_MANAGER->query_is_child_cleric(shadow_who)) 
    	return GUILD_EC_LAY_TAX;
    else
    	string element = (GUILD_MANAGER->query_primary_element(shadow_who));
    	
    	switch(element)
    	{
    		case "fire":
    			return GUILD_EC_FIRE_LAY_TAX;
    			break;
    		
    		case "air":
    			return GUILD_EC_AIR_LAY_TAX;
    			break;
    			
    		case "water":
    			return GUILD_EC_WATER_LAY_TAX;
    			break;
    			
    		case "earth":
    			return GUILD_EC_EARTH_LAY_TAX;
    			break;
    			
    		case "life":
    			return GUILD_EC_SPIRIT_LAY_TAX;
    			break;
    			
    		default:
    			return GUILD_EC_LAY_TAX;
    			break;
    	} 
}

void
init_lay_shadow(string str)
{
    ::init_lay_shadow(); 

    set_alarm(1.0, 0.0, initialize_lay_cleric);
}

public void
initialize_lay_cleric()
{
    setuid();
    seteuid(getuid());
    
    // Make sure the command soul gets added
    shadow_who->add_cmdsoul(EC_LAY_SOUL);
    shadow_who->add_cmdsoul(SPELL_MANAGER_SOUL);

    shadow_who->update_hooks();
    
    // Every caster guild using the new Genesis magic system will
    // use the mana shadow to get the new regeneration rates for mana.
    if (!query_top_shadow()->has_mana_shadow())
    {
        clone_object(MANA_SHADOW)->shadow_me(shadow_who);
    }    
    
}

public void
remove_shadow()
{
    // We use the removal of the shadow as a way to ensure that the
    // spells for the command soul are removed.
    EC_LAY_SOUL->remove_spells(shadow_who);
    
    // We also need to remove the mana shadow. This removal assumes
    // that the person can only have one caster guild shadow.
    query_top_shadow()->remove_mana_shadow();
   
    ::remove_shadow();    
}

public string 
query_guild_title_lay() 
{
    string primary_element;
    string council_title;
    string full_title;
	
	primary_element = GUILD_MANAGER->query_primary_element(shadow_who);
	
	// If they are temple banned, replace their special title with  
	// nothing
	
	if (GUILD_MANAGER->query_is_punish_temple_banned(shadow_who))
	{
		return "";
	}
	
	// Do they hold a "special" title?
	
	// Are they the Luminary?
	if (GUILD_MANAGER->query_ec_luminary() == shadow_who->query_real_name())
		full_title = LUMINARY_TITLE[0];	
		
	// Are they the Illuminati?
	if (GUILD_MANAGER->query_ec_illuminati() == shadow_who->query_real_name())
		full_title = ILLUMINATI_TITLE[0];
		
	// Are they the Emissary?
	if (GUILD_MANAGER->query_ec_emissary() == shadow_who->query_real_name())
		full_title = EMISSARY_TITLE[0];
		
	// Are they the Cultivator?
	if (GUILD_MANAGER->query_ec_cultivator() == shadow_who->query_real_name())
		full_title = CULITVATOR_TITLE[0];
		
	// Are they the Liberator?
	if (GUILD_MANAGER->query_ec_liberator() == shadow_who->query_real_name())
		full_title = LIBERATOR_TITLE[0];
		
	// Are they the Conservator?
	if (GUILD_MANAGER->query_ec_conservator() == shadow_who->query_real_name())
		full_title = CONSERVATOR_TITLE[0];

	// Are they the Archon of Revelation?
	if (GUILD_MANAGER->query_ec_archon_revelation() == shadow_who->
		query_real_name())
			full_title = ARCHON_REVELATION_TITLE[0];
		
	// Are they the Archon of Deliverance?
	if (GUILD_MANAGER->query_ec_archon_deliverance() == 
		lower_case(shadow_who->query_real_name()))
			full_title = ARCHON_DELIVERANCE_TITLE[0];
		
	// Are they the Archone of Apotheosis?
	if (GUILD_MANAGER->query_ec_archon_apotheosis() == 
		lower_case(shadow_who->query_real_name()))
			full_title = ARCHON_APOTHEOSIS_TITLE[0];
		    
	// Are they council? If so append Harbinger title
	if (GUILD_MANAGER->query_is_ec_council(shadow_who, 0))
	{
		switch(primary_element)
		{
			case "fire":
				council_title = COUNCIL_FIRE_TITLES[0];
				break;
			case "water":
				council_title = COUNCIL_WATER_TITLES[0];
				break;
			case "air":
				council_title = COUNCIL_AIR_TITLES[0];
				break;
			case "earth":
				council_title = COUNCIL_EARTH_TITLES[0];
				break;
			case "life":
				council_title = COUNCIL_SPIRIT_TITLES[0];
				break;
			default:
				council_title = "Harbinger of the Elementals";
				break;
		}
		
		// Are they the EC Leader? If so, append Focus title
		if (GUILD_MANAGER->query_is_ec_leader(shadow_who))
			council_title += ", and " + LEADER_TITLE[0];
	}
	
	if (council_title)
		if (full_title)
			full_title += ", " + council_title;
		else
			full_title = council_title;
				   
    return full_title;
} 

public string
query_guild_trainer_lay()
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

